#include<bits/stdc++.h>
using namespace std;

#define N 8
#define POP_SIZE 6
#define GENERATIONS 200

vector<vector<int>> graph = {
    {0, 10, 15, 20, 25, 30, 35, 40},
    {12, 0, 35, 15, 20, 25, 30, 45},
    {25, 30, 0, 10, 40, 20, 15, 35},
    {18, 25, 12, 0, 15, 30, 20, 10},
    {22, 18, 28, 20, 0, 15, 25, 30},
    {35, 22, 18, 28, 12, 0, 40, 20},
    {30, 35, 22, 18, 28, 32, 0, 15},
    {40, 28, 35, 22, 18, 25, 12, 0}
};

struct Chromosome{
    vector<int> path;
    int cost;
};

int calcCost(vector<int> &path){
    int cost = 0;
    for(int i=0;i<N-1;i++){
        cost += graph[path[i]][path[i+1]];
    }
    cost += graph[path[N-1]][path[0]];
    return cost;
}

vector<int> randomPath(){
    vector<int> p;
    for(int i=0;i<N;i++) p.push_back(i);
    random_shuffle(p.begin()+1,p.end());
    return p;
}

bool cmp(Chromosome &a, Chromosome &b){
    return a.cost < b.cost;
}

// Tournament selection
vector<int> selectParent(vector<Chromosome> &pop){
    int a = rand()%POP_SIZE;
    int b = rand()%POP_SIZE;
    return (pop[a].cost < pop[b].cost) ? pop[a].path : pop[b].path;
}

// One-point crossover
vector<int> onePoint(vector<int> &p1, vector<int> &p2){
    int cut = rand()%N;
    vector<int> child(p1.begin(),p1.begin()+cut);

    for(int x : p2){
        if(find(child.begin(),child.end(),x)==child.end()){
            child.push_back(x);
        }
    }
    return child;
}

// Two-point crossover
vector<int> twoPoint(vector<int> &p1, vector<int> &p2){
    int l = rand()%N;
    int r = rand()%N;
    if(l>r) swap(l,r);

    vector<int> child(N,-1);

    for(int i=l;i<=r;i++) child[i] = p1[i];

    int idx = 0;
    for(int i=0;i<N;i++){
        if(find(child.begin(),child.end(),p2[i])==child.end()){
            while(child[idx]!=-1) idx++;
            child[idx] = p2[i];
        }
    }
    return child;
}

void mutate(vector<int> &p){
    int i = rand()%N;
    int j = rand()%N;
    swap(p[i],p[j]);
}

// mode = 1 → one-point
// mode = 2 → two-point
void runGA(int mode){
    vector<Chromosome> population;

    for(int i=0;i<POP_SIZE;i++){
        vector<int> p = randomPath();
        population.push_back({p,calcCost(p)});
    }

    for(int gen=0;gen<GENERATIONS;gen++){

        sort(population.begin(),population.end(),cmp);

        if(gen % 20 == 0){
            cout<<"Generation "<<gen<<" Best Cost: "<<population[0].cost<<endl;
        }

        vector<Chromosome> newPop;

        // Elitism
        newPop.push_back(population[0]);
        newPop.push_back(population[1]);
  
        while(newPop.size() < POP_SIZE){

            vector<int> p1 = selectParent(population);
            vector<int> p2 = selectParent(population);

            vector<int> child;

            if(mode == 1)
                child = onePoint(p1,p2);
            else
                child = twoPoint(p1,p2);

            if(rand()%100 < 20)
                mutate(child);

            newPop.push_back({child,calcCost(child)});
        }

        population = newPop;
    }
    sort(population.begin(),population.end(),cmp);

    cout<<"\n-----------------------------\n";
    cout<<"FINAL RESULT\n";
    cout<<"-----------------------------\n";

    cout<<"Best Path: ";
    for(int x : population[0].path){
        cout<<char('A'+x)<<" ";
    }
    cout<<char('A'+population[0].path[0]);

    cout<<"\nCost: "<<population[0].cost<<endl;
}

int main(){
    srand(time(0));

    cout<<"===== One-Point Crossover ====="<<endl;
    runGA(1);

    cout<<"\n\n===== Two-Point Crossover ====="<<endl;
    runGA(2);

    return 0;
}