#include "iostream"

using namespace std;
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;
int init(LinkList &L){
    L = new LNode;
    if(!L)
        return -1;
    L->next = nullptr;
    return 0;
}
//头插
void createLinkList1(LinkList &L){
    int n;
    cin>>n;
    LNode *p;
    while (n!=-1){
        p = new LNode;
        p->data = n;
        p->next = L->next;
        L->next = p;
        cin>>n;
    }
}
//尾插
void createLinkList2(LinkList &L){
    int n;
    cin>>n;
    LNode *p,*r = L;//r为尾指针
    while (n!=-1){
        p = new LNode;
        p->data = n;
        p->next = nullptr;
        r->next = p;
        r = p;
        cin>>n;
    }
}
int insert(LinkList &L, int i, int e){
    LNode *p = L;
    int j = 0;
    while (p&&j<i){
        p = p->next;
        j++;
    }//跳出循环时p指向待插入位置的前驱
    if(i<1||!p)
        return -1;
    LNode *s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return 0;
}

int deleteLNode(LinkList &L, int i){
    LNode *p = L,*q;
    int j = 0;
    while (p->next&&j<i){ //p前驱 p->next待删除元素
        p = p->next;
        j++;
    }
    if(i<1&&!(p->next))
        return -1;
    q = p->next;
    p->next = q->next;
    delete q;
    return 0;
}
void mergeList(LinkList L1, LinkList L2, LinkList &L){
    LNode *p1,*p2,*r;
    p1 = L1->next;
    p2 = L2->next;
    L = L1; //利用L1的头结点
    r = L;
    while (p1&&p2){
        if(p1->data <= p2->data){
            r->next = p1;
            p1 = p1->next;
            r = r->next; // r = p1
        }else{
            r->next = p2;
            p2 = p2->next;
            r = r->next;
        }
    }
    if (p1)
        r->next = p1;
    else
        r->next = p2; //r->next=p1?p1:p2;
    delete L2;
}
void print(LinkList L){
    LNode *p = L->next;
    while (p){
        cout<<p->data<<" ";
        p = p->next;
    }
}
void InterSect(LinkList &L1, LinkList L2){
    LNode *p1 = L1->next;
    LNode *p2 = L2->next;
    LNode *r;
    r = L1;
    while (p1 && p2){
        if(p1->data < p2->data)
            p1 = p1->next;
        else if(p1->data > p2->data)
            p2 = p2->next;
        else{
            r->next = p1;
            r = p1;
            p1 = p1->next;
            p2 = p2->next;
        }
    }
}

void Except(LinkList &L1, LinkList L2){
    LNode *p1,*p2,*r;
    p1 = L1->next;
    p2 = L2->next;
    r = L1;
    while (p1&&p2){
        if(p1->data<p2->data){
            r->next = p1;
            r = p1;
            p1 = p1->next;
        } else if(p1->data == p2->data){
            p1 = p1->next;
            p2 = p2->next;
        } else{
            p2 = p2->next;
        }
    }
    while (p1){
        r->next = p1;
        r = p1;
        p1 = p1->next;
    }
}
int main(){
//    LinkList L;
//    init(L);
//    createLinkList2(L);
//    insert(L,3,11111);
//    deleteLNode(L,3);
    LinkList L1,L2,L;
    init(L1);
    init(L2);
    createLinkList2(L1);
    createLinkList2(L2);
    mergeList(L1,L2,L);
    print(L);
}