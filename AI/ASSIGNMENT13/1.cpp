#include <bits/stdc++.h>
using namespace std;

class LogicSystem
{
private:

    int getPriority(string op){
        if(op=="~")return 4;
        if(op=="^")return 3;
        if(op=="v")return 2;
        if(op=="->")return 1;
        if(op=="<->")return 0;
        return -1;
    }

    bool isRightAssociative(string op){
        return(op=="~"||op=="->"||op=="<->");
    }

    bool applyLogic(string op,bool a,bool b=false){
        if(op=="~")return !a;
        if(op=="^")return a&&b;
        if(op=="v")return a||b;
        if(op=="->")return (!a)||b;
        if(op=="<->")return a==b;
        return false;
    }

    vector<string> parseExpression(string expr){
        vector<string> elements;

        for(int i=0;i<expr.size();i++){
            if(expr[i]==' ')continue;

            if(isalpha(expr[i]))
                elements.push_back(string(1,expr[i]));

            else if(expr[i]=='~')
                elements.push_back("~");

            else if(expr[i]=='^')
                elements.push_back("^");

            else if(expr[i]=='v'||expr[i]=='∨')
                elements.push_back("v");

            else if(expr[i]=='∧')
                elements.push_back("^");

            else if(i+2<expr.size()&&expr.substr(i,3)=="<->"){
                elements.push_back("<->");
                i+=2;
            }
            else if(i+1<expr.size()&&expr.substr(i,2)=="->"){
                elements.push_back("->");
                i++;
            }
            else if(expr[i]=='('||expr[i]==')')
                elements.push_back(string(1,expr[i]));
        }

        return elements;
    }

    vector<string> convertToPostfix(vector<string>&elements){
        vector<string> output;
        stack<string> st;

        for(int i=0;i<elements.size();i++){
            string item=elements[i];

            if(isalpha(item[0])){
                output.push_back(item);
            }
            else if(item=="("){
                st.push(item);
            }
            else if(item==")"){
                while(!st.empty()&&st.top()!="("){
                    output.push_back(st.top());
                    st.pop();
                }
                st.pop();
            }
            else{
                while(!st.empty()&&st.top()!="("){
                    string top=st.top();

                    int p1=getPriority(item);
                    int p2=getPriority(top);

                    if((!isRightAssociative(item)&&p1<=p2)||(isRightAssociative(item)&&p1<p2)){
                        output.push_back(top);
                        st.pop();
                    }
                    else break;
                }
                st.push(item);
            }
        }

        while(!st.empty()){
            output.push_back(st.top());
            st.pop();
        }

        return output;
    }

    bool evaluatePostfixExpression(vector<string>&postfix,bool values[]){
        stack<bool> st;

        for(int i=0;i<postfix.size();i++){
            string item=postfix[i];

            if(isalpha(item[0])){
                int idx=item[0]-'P';
                st.push(values[idx]);
            }
            else if(item=="~"){
                bool a=st.top();st.pop();
                st.push(applyLogic("~",a));
            }
            else{
                bool b=st.top();st.pop();
                bool a=st.top();st.pop();
                st.push(applyLogic(item,a,b));
            }
        }

        return st.top();
    }

    void extractVariables(string expr,bool used[]){
        for(int i=0;i<expr.size();i++){
            if(isalpha(expr[i])){
                int idx=expr[i]-'P';
                used[idx]=true;
            }
        }
    }

public:

    void generateTruthTable(string expr){
        bool used[3]={false};
        extractVariables(expr,used);

        vector<char> vars;
        for(int i=0;i<3;i++)
            if(used[i])vars.push_back('P'+i);

        vector<string> elements=parseExpression(expr);
        vector<string> postfix=convertToPostfix(elements);

        int n=vars.size();
        int rows=1<<n;

        cout<<"\n==============================\n";
        cout<<"Expression: "<<expr<<"\n";
        cout<<"==============================\n";

        for(int i=0;i<n;i++)cout<<vars[i]<<" ";
        cout<<"| Result\n";

        for(int i=0;i<rows;i++){
            bool values[3]={false};
            for(int j=0;j<n;j++){
                bool val=(i>>(n-j-1))&1;
                values[vars[j]-'P']=val;

                cout<<(val?"T ":"F ");
            }
            bool res=evaluatePostfixExpression(postfix,values);
            cout<<"| "<<(res?"T":"F")<<"\n";
        }
    }
};

int main(){
    LogicSystem obj;
    vector<string> exp={
        "~P->Q",
        "~P^~Q",
        "~Pv~Q",
        "~P->~Q",
        "~P<->~Q",
        "(PvQ)^(~P->Q)",
        "(PvQ)->~R",
        "((PvQ)->~R)<->((~P^~Q)->~R)",
        "((P->Q)^(Q->R))->(Q->R)",
        "((P->(QvR))->(~P^~Q^~R))"
    };
    for(int i=0;i<exp.size();i++){
        obj.generateTruthTable(exp[i]);
    }
    return 0;
}