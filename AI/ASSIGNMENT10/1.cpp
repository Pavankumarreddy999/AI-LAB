#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x,y;
};

// ─── squared Euclidean distance ───────────────────────────────────────────────
double distSq(Point a,Point b){
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx*dx + dy*dy;
}

// ─── load cities from CSV (no header, format: x,y) ───────────────────────────
vector<Point> loadCSV(const string& filename){
    vector<Point> pts;
    ifstream f(filename);
    if (!f) { cerr << "Cannot open " << filename << "\n"; exit(1); }
    string line;
    while (getline(f,line)){
        if (line.empty()) continue;
        stringstream ss(line);
        string sx,sy;
        getline(ss,sx,',');
        getline(ss,sy,',');
        pts.push_back({stod(sx),stod(sy)});
    }
    return pts;
}

// ─── assign each city to its nearest airport ─────────────────────────────────
vector<int> assignClusters(const vector<Point>& cities,const vector<Point>& airports){
    int n = cities.size(),k = airports.size();
    vector<int> label(n);
    for (int i = 0;i < n;i++) {
        double best = 1e18;int nearest = 0;
        for (int j = 0;j < k;j++) {
            double d = distSq(cities[i],airports[j]);
            if (d < best) { best = d;nearest = j; }
        }
        label[i] = nearest;
    }
    return label;
}

// ─── total cost = sum of squared distances ───────────────────────────────────
double totalCost(const vector<Point>& cities,const vector<Point>& airports,const vector<int>&   label){
    double cost = 0;
    for (int i = 0;i<(int)cities.size();i++)
        cost += distSq(cities[i], airports[label[i]]);
    return cost;
}

vector<Point> gradientDescent(const vector<Point>& cities,int k,int iterations = 500){
    int n = cities.size();

    // Estimate data range to auto-scale the learning rate
    double xmin = 1e18, xmax = -1e18, ymin = 1e18, ymax = -1e18;
    for (auto& c : cities){
        xmin = min(xmin,c.x);
        xmax = max(xmax, c.x);
        ymin = min(ymin, c.y); 
        ymax = max(ymax, c.y);
    }
    double range = max(xmax - xmin, ymax - ymin);
    // lr chosen so a step moves ~1% of the data range per update for one city
    double lr = 0.005 / (range > 0 ? range : 1.0);

    // Initialise airports at random cities (fixed seed)
    mt19937 rng(42);
    vector<Point> airports(k);
    vector<int> idx(n); iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end(), rng);
    for (int i = 0;i < k;i++) airports[i] = cities[idx[i]];

    for (int iter = 0; iter < iterations; iter++) {
        vector<int> label = assignClusters(cities, airports);

        // Accumulate gradient: delta L contribution for each airport
        vector<Point> grad(k, {0.0, 0.0});
        vector<int> cnt(k, 0);
        for (int i = 0; i < n; i++) {
            int c = label[i];
            grad[c].x += cities[i].x - airports[c].x;   // = −∂L/∂μ / 2
            grad[c].y += cities[i].y - airports[c].y;
            cnt[c]++;
        }

        for (int j = 0; j < k; j++) {
            if (cnt[j] == 0) continue;
            airports[j].x += 2.0 * lr * grad[j].x;
            airports[j].y += 2.0 * lr * grad[j].y;
        }
    }
    return airports;
}

vector<Point> newtonRaphson(const vector<Point>& cities,int k,int iterations = 10){
    int n = cities.size();

    // Initialise airports at random cities (different fixed seed)
    mt19937 rng(123);
    vector<Point> airports(k);
    vector<int> idx(n); iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end(), rng);
    for (int i = 0; i < k; i++) airports[i] = cities[idx[i]];

    for (int iter = 0; iter < iterations; iter++) {
        vector<int> label = assignClusters(cities, airports);

        // Accumulate cluster sums and counts
        vector<Point> sum(k, {0.0, 0.0});
        vector<int>cnt(k, 0);
        for (int i = 0; i < n; i++) {
            int c = label[i];
            sum[c].x += cities[i].x;
            sum[c].y += cities[i].y;
            cnt[c]++;
        }
        for (int j = 0; j < k; j++) {
            if (cnt[j] == 0) continue;   // FIX: keep old position if empty
            airports[j].x = sum[j].x / cnt[j];
            airports[j].y = sum[j].y / cnt[j];
        }
    }
    return airports;
}

// ─── print results ─────────────────────────────────────────────────────
void printResults(const string& method,const vector<Point>& airports,const vector<Point>& cities,const vector<int>&   label) {
    int k = airports.size();
    cout << "\n══ " << method << " ══\n";
    cout << fixed << setprecision(6);
    for (int j = 0; j < k; j++) {
        int cnt = count(label.begin(), label.end(), j);
        cout << "  Airport " << j+1 << "  x=" << airports[j].x << "  y=" << airports[j].y << "  (cities assigned: " << cnt << ")\n";
    }
    double cost = totalCost(cities, airports, label);
    cout << "  Total cost (sum of sq. distances) = " << cost << "\n";
}

int main() {
    vector<Point> cities = loadCSV("cities.csv");
    cout << "Cities loaded: " << cities.size() << "\n";

    int k = 3;

    // ── Gradient Descent ──────────────────────────────────────────────────────
    vector<Point> gAirports = gradientDescent(cities, k, 500);
    vector<int>   gLabel    = assignClusters(cities, gAirports);
    printResults("Gradient Descent (500 iterations)", gAirports, cities, gLabel);

    // ── Newton-Raphson ────────────────────────────────────────────────────────
    vector<Point> nAirports = newtonRaphson(cities, k, 10);
    vector<int>   nLabel    = assignClusters(cities, nAirports);
    printResults("Newton-Raphson / K-Means (10 iterations)", nAirports, cities, nLabel);

    // ── Comparison ───────────────────────────────────────────────────────────
    double gCost = totalCost(cities, gAirports, gLabel);
    double nCost = totalCost(cities, nAirports, nLabel);
    cout << "\n── Comparison ──\n";
    cout << fixed << setprecision(2);
    cout << "  Gradient cost : " << gCost << "\n";
    cout << "  Newton cost   : " << nCost << "\n";
    cout << "  Winner        : "<< (nCost < gCost ? "Newton-Raphson" : "Gradient Descent") << " (lower cost = better placement)\n";
    return 0;
}