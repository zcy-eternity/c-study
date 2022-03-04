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
void createLinkList2(LinkList &L){
    int n;
    cin>>n;
    LNode *p,*r = L;
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
    }
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
    while (p->next&&j<i){
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
    L = L1;
    r = L;
    while (p1&&p2){
        if(p1->data <= p2->data){
            r->next = p1;
            p1 = p1->next;
            r = r->next;
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