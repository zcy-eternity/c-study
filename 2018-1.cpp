// Created by zhangchaoyan on 2022/3/16.
#include <iostream>

using namespace std;
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;

void create(LinkList &L){
    LNode *r=L;
    LNode *s;
    int n;
    cin>>n;
    while (n!=0){
        s = new LNode;
        s->data = n;
        s->next = nullptr;
        r->next = s;
        r = s;
        cin>>n;
    }
}
//链表逆序
void reverse(LinkList &L){
    LNode *p = L->next;
    LNode *q = p->next;//记录p指针下一个位置
    L->next = nullptr; //头插法头结点next域为空
    //头插法实现链表逆置
    while (q){
        p->next = L->next;
        L->next = p;
        p = q; //p指针向后移动
        q = q->next;
    }//退出循环时p指针指向最后一个结点，q指针为空
    p->next = L->next;
    L->next = p;
}
void print(LinkList L){
    LNode *p = L->next;
    while (p){
        cout<<p->data<<" ";
        p = p->next;
    }
}
int main(){
    LinkList L;
    L = new LNode;
    L->next = nullptr;
    //1 2 3 4 5 6 -1
    create(L);
    reverse(L);
    print(L);
}

