#include <iostream>
#include <queue>
#define MaxSize 10
using namespace std;

typedef struct {
    int data[MaxSize];
    int front,rear;
}SqQueue;

typedef struct QNode{
    int data;
    struct QNode *next;
}QNode,*QueuePtr;
typedef struct {
    QueuePtr front,rear;
}LinkQueue;

typedef struct {
    char name[20];
    char sex;
}Person;

void init(SqQueue &q){
    q.front = q.rear = 0;
}
int EnQueue(SqQueue &q, int x){
    if((q.rear+1)%MaxSize == q.front)
        return -1;
    q.data[q.rear] = x;
    q.rear = (q.rear+1) % MaxSize;
    return 0;
}
int DeQueue(SqQueue &q, int &x){
    if(q.front == q.rear)
        return -1;
    x = q.data[q.front];
    q.front = (q.front+1) % MaxSize;
    return 0;
}
int GetHead(SqQueue q, int &x){
    if(q.front == q.rear)
        return -1;
    x = q.data[q.front];
    return 0;
}
bool QueueEmpty(SqQueue q){
    if(q.front == q.rear)
        return true;
    else
        return false;
}
// -------------------------------
void init(LinkQueue &q){
    q.rear = q.front = new QNode;
    q.front->next = NULL;
}
void EnQueue(LinkQueue &q, int x){
    QNode *s = new QNode;
    s->data = x;
    s->next = NULL;
    q.rear->next = s;
    q.rear = s;
}
int DeQueue(LinkQueue &q, int &x){
    if(q.front == q.rear)
        return -1;
    QNode *p = q.front->next;
    x = p->data;
    q.front->next = p->next;
    if(p == q.rear)
        q.rear = q.front;
    delete p;
    return 0;
}
bool QueueEmpty(LinkQueue q){
    if(q.front == q.rear)
        return true;
    else
        return false;
}
int GetHead(LinkQueue q, int &x){
    if(q.front == q.rear)
        return -1;
    x = q.front->next->data;
    return 0;
}
//---------------------------------
//舞伴问题
void DancePartner(Person dancer[], int n){
    queue<Person> Fdancers, Mdancers;
    for(int i=0;i<n;i++){
        if(dancer[i].sex == 'F')
            Fdancers.push(dancer[i]);
        else
            Mdancers.push(dancer[i]);
    }
    cout<<"The dancing partners are: \n";
    while (!Fdancers.empty()&&!Mdancers.empty()){
        cout<<Fdancers.front().name<<" ";
        cout<<Mdancers.front().name<<endl;
        Fdancers.pop();
        Mdancers.pop();
    }
    if(!Fdancers.empty())
        cout<<"The first woman to get a partner is :"<<Fdancers.front().name;
    else if(!Mdancers.empty())
        cout<<"The first man to get a partner is :"<<Mdancers.front().name;
}
// 1 2 1
int main(){
    LinkQueue q;
    init(q);
    EnQueue(q,1);
    EnQueue(q,2);
    EnQueue(q,3);
    int x;
    GetHead(q,x);
    cout<<x<<endl;
    DeQueue(q,x);
    DeQueue(q,x);
    cout<<x<<endl;
    DeQueue(q,x);
    cout<<QueueEmpty(q)<<endl;

    Person dancer[6] = {
            {"LiMing",'M'},
            {"YangZi",'F'},
            {"YangMi",'F'},
            {"NaZha",'F'},
            {"ReBa",'F'},
            {"ZhangWei",'M'}
    };
    DancePartner(dancer,6);
    return 0;
}