// Created by zhangchaoyan1 on 2022/3/17.
#include <iostream>
using namespace std;

typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;
void create(LinkList &L){
    L = new LNode;
    L->next = nullptr;
    int n;
    cin>>n;
    LNode *s;
    while (n!=-1){
        s = new LNode;
        s->data = n;
        s->next = L->next;
        L->next = s;
        cin>>n;
    }
}
void print(LinkList L){
    LNode *p = L->next;
    while (p){
        cout<<p->data<<" ";
        p = p->next;
    }
}
void deleteLinkList(LinkList &L, int mink, int maxk){
    LNode *pre,*p,*q;
    pre = L;
    p = L->next;
    q = p->next;
    while (q){
        if(p->data>=mink&&p->data<=maxk){
            pre->next = q;
            delete p;
            p = q;
            q = q->next; //最后一个结点会空指针
        } else{
            pre = p;
            p = q;
            q = q->next;
        }
    }
    if(p->data>=mink&&p->data<=maxk){
        pre->next = nullptr;
        delete p;
    }

}
int main(){
    LinkList L;
//    1 2 3 4 5 6 -1
    create(L);
    deleteLinkList(L,1,2);
    print(L);
}