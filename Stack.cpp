#include <iostream>
#define MaxSize 10
using namespace std;

typedef struct {
    int data[MaxSize];
    int top;
}SqStack;
typedef struct StackNode{
    int data;
    struct StackNode *next;
}StackNode,*LinkStack;


void initStack(SqStack &s){
    s.top = -1;
}
int push(SqStack &s, int x){
    if(s.top == MaxSize-1)
        return -1;
    s.data[++s.top] = x;
    return 0;
}
int pop(SqStack &s, int &x){
    if(s.top == -1)
        return -1;
    x = s.data[s.top--];
    return 0;
}
int getTop(SqStack s, int &x){
    if(s.top == -1)
        return -1;
    x = s.data[s.top];
    return 0;
}
bool stackEmpty(SqStack s){
    if(s.top == -1)
        return true;
    else
        return false;
}

//-------------------------------
void initStack(LinkStack &s){
    s = nullptr;
}
int push(LinkStack &s, int x){
    StackNode *p = new StackNode;
    p->data = x;
    p->next = s;
    s = p;
    return 0;
}
int pop(LinkStack &s, int &x){
    if(!s)
        return -1;
    x = s->data;
    StackNode *p = s;
    s = s->next;
    delete p;
    return 0;
}
bool stackEmpty(LinkStack s){
    if(s== nullptr)
        return true;
    else
        return false;
}
int getTop(LinkStack s, int &x){
    if(!s)
        return -1;
    else
        x = s->data;
    return 0;
}
void print(LinkStack s){
    StackNode *p = s;
    while (p){
        cout<<p->data<<" ";
        p = p->next;
    }
}
void print(SqStack s){
    for(int i =0;i<=s.top;i++)
        cout<<s.data[i]<<" ";
}
//---------------------------------
//数制转换
void conversion(int n, int r){
    SqStack s;
    initStack(s);
    while (n){
        push(s,n%r);
        n /= r;
    }
    int x;
    while (!stackEmpty(s)){
        pop(s,x);
        cout<<x<<" ";
    }
    cout<<endl;
}
//括号匹配 ( ( ( ) )[ ( ) ] ) #
//[ ( ) ] ( #

bool bracketMatching(){
    LinkStack s;
    initStack(s);
    int x,flag = 1;
    char ch;
    cin>>ch;
    while (ch!='#'){
        switch (ch) {
            case '(': push(s,ch); break;
            case '[': push(s,ch); break;
            case ')':
                if(!stackEmpty(s)){
                    getTop(s,x);
                    if(x == '(')
                        pop(s,x);
                    else
                        flag = 0;
                } else
                    flag = 0;
                break;
            case ']':
                if(!stackEmpty(s)){
                    getTop(s,x);
                    if(x == '[')
                        pop(s,x);
                    else
                        flag = 0;
                } else
                    flag = 0;
                break;
        }
        cin>>ch;
    }
    if(!stackEmpty(s)||!flag)
        return false;
    else
        return true;

}
bool In(char ch){
    if(ch!='(' && ch!=')' && ch!='+' && ch!='-' && ch!='*' && ch!='/')
        return true;
    else
        return false;
}
int calculate(char op, char x ,char y){
    if(op == '+')
        return x+y;
    if(op == '-')
        return x-y;
    if(op == '*')
        return x*y;
    if(op == '/')
        return x/y;
}
int Precede(char ch1, char ch2){
    if(ch1 == '+' && ch2 == '+')
        return 0;
    if(ch1 == '-' && ch2 == '-')
        return 0;
    if(ch1 == '*' && ch2 == '*')
        return 0;
    if(ch1 == '/' && ch2 == '/')
        return 0;

    if(ch1 == '+' && ch2 == '-')
        return 0;
    if(ch1 == '*' && ch2 == '/')
        return 0;
    if(ch1 == '-' && ch2 == '+')
        return 0;
    if(ch1 == '/' && ch2 == '*')
        return 0;

    if(ch1 == '+' && ch2 == '*')
        return -1;
    if(ch1 == '-' && ch2 == '*')
        return -1;
    if(ch1 == '+' && ch2 == '/')
        return -1;
    if(ch1 == '-' && ch2 == '/')
        return -1;

    if(ch1 == '*' && ch2 == '+')
        return 1;
    if(ch1 == '*' && ch2 == '-')
        return 1;
    if(ch1 == '/' && ch2 == '+')
        return 1;
    if(ch1 == '/' && ch2 == '-')
        return 1;
}
//中缀表达式求值
//2+3*5+(7*8-6) #
//(2+3)*5 #
int EvaluateExpression(){
    SqStack s1,s2;
    initStack(s1);//操作数栈
    initStack(s2);//运算符栈
    int x,m,n;
    char ch;
    cin>>ch;
    while (ch!='#'){
        if(In(ch))
            push(s1,ch-'0');
        else if(ch == '(')
            push(s2,ch);
        else if(ch == ')'){
            getTop(s2,x);
            while (x!='('){
                pop(s2,x);
                pop(s1,m);
                pop(s1,n);
                push(s1, calculate(x,n,m));
                getTop(s2,x);
            }
            pop(s2,x);
        } else{
            if(!stackEmpty(s2)){
                getTop(s2,x);
                if(Precede(ch,x)==1)
                    push(s2,ch);
                else if(Precede(ch,x)<=0) {
                    getTop(s2,x);
                    while (Precede(ch,x)<=0 && !stackEmpty(s2)){
                        pop(s2, x);
                        pop(s1, m);
                        pop(s1, n);
                        push(s1, calculate(x, n, m));
                        getTop(s2,x);
                    }
                    push(s2, ch);
                } else{
                    push(s2,ch); // ( +
                }
            } else
                push(s2,ch);
        }
        cin>>ch;
    }
    if(!stackEmpty(s2)){
        pop(s2, x);
        pop(s1, m);
        pop(s1, n);
        push(s1, calculate(x, n, m));
    }
    getTop(s1,x);
    return x;
}
int main(){
    //3 2 0
//    LinkStack s;
//    initStack(s);
//    push(s,1);
//    push(s,2);
//    push(s,3);
//    int x;
//    pop(s,x);
//    cout<<x<<endl;
//    getTop(s,x);
//    cout<<x<<endl;
//    pop(s,x);
//    cout<<stackEmpty(s)<<endl;
//    conversion(7,2);
//    cout<<bracketMatching();
     cout<<EvaluateExpression();

}
