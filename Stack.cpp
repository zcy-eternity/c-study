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

void initStack(LinkStack &s){
    s = NULL;
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
    if(s==NULL)
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
int main(){
    //3 2 0
    LinkStack s;
    initStack(s);
    push(s,1);
    push(s,2);
    push(s,3);
    int x;
    pop(s,x);
    cout<<x<<endl;
    getTop(s,x);
    cout<<x<<endl;
    pop(s,x);
    cout<<stackEmpty(s);
}
