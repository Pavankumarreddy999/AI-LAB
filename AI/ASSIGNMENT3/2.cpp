#include<bits/stdc++.h>
using namespace std;
struct Action{
    string gate;
    string siren;
    string signal;
};
Action simple_reflex_agent(int inbound,int outbound,int obstacle,int emergency){
    Action a;
    if(emergency == 1){
        a.gate = "Lower";
        a.siren = "ON";
        a.signal = "RED";
    }
    else if(obstacle == 1){
        a.gate = "Lower";
        a.siren = "ON";
        a.signal = "RED";
    }else if(inbound == 1 || outbound == 1){
        a.gate = "Lower";
        a.siren = "ON";
        a.signal = "GREEN";
    }else{
        a.gate = "RAISE";
        a.siren = "OFF";
        a.signal = "GREEN";
    }
    return a;
}

int main(){
    int inbound,outbound,obstacle,emergency;
    cout << "ENTER THE PERCEPTS :\n";
    cout << "ENTER THE INBOUND(1 = DETECTED,0 = NOT DETECTED) : \n";
    cin >> inbound;
    cout << "ENTER THE OUTBOUND(1 = DETECTED,0 = NOT DETECTED) : \n";
    cin >> outbound;
    cout << "ENTER THE OBSTACLE IN BETWEEN GATES(1 = DETECTED,0 = NOT DETECTED) : \n";
    cin >> obstacle;
    cout << "ENTER THE MANUAL EMERGENCY(1 = DETECTED,0=NOT DETECTED) : \n";
    cin >> emergency;

    Action a = simple_reflex_agent(inbound,outbound,obstacle,emergency);

    cout << "------AGENT DECISIONS---------\n";
    cout << "GATE TO (RAISE) OR (LOWER) :" << a.gate << "\n";
    cout << "SIREN TO (ON) OR (OFF) : " << a.siren << "\n";
    cout << "SIGNAL TO TRAIN (GREEN) OR (RED) : " << a.signal << "\n";

}