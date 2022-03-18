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
//删除链表中大于等于mink小于等于maxk的结点，输出被删除元素后的链表
void deleteLinkList1(LinkList &L, int mink, int maxk){
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
void deleteLinkList2(LinkList &L, int mink, int maxk){ //删除一个元素，仅需找到前驱即可
    LNode *pre,*p;
    pre = L;
    p = L->next;
    while (p){
        if(p->data>=mink&&p->data<=maxk){
            pre->next = p->next;
            delete p;
            p = pre->next; //删除一个元素时 pre指针不动 仅p指针移动到pre的下一个元素
        } else{
            pre = p;
            p = p->next;
        }
    }
}
int main(){
    LinkList L;
//    1 2 3 4 5 6 -1
    create(L);
    deleteLinkList2(L,1,2);
    print(L);
}