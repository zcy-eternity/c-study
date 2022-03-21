// Created by zhangchaoyan on 2022/3/18.
#include <iostream>
using namespace std;
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;

//尾插法建立单链表
void create(LinkList &L){
    int n;
    cin>>n;
    LNode *s,*r=L;
    while (n!=-1){
        s = new LNode;
        s->data = n;
        s->next = nullptr;
        r->next = s;
        r = s;
        cin>>n;
    }
}
//输出单链表中正数和倒数第k个值
void loc(LinkList L, int k){
    if(k<0||!L->next)
        return;
    int i=1;
    LNode *p = L->next;
    while (p&&i<k){
        p = p->next;
        i++;
    }
//    while (--k){   k=0时退出 等价于找到第k个元素
//        p = p->next;
//    }
    if(p)
        cout<<"正数第k个值为："<<p->data<<endl;
    else
        return;
    LNode *q = L;
    while (p){
        q = q->next;
        p = p->next;
    }
    if(q)
        cout<<"倒数第k个值为："<<q->data<<endl;
}
//求单链表中元素最大值并输出
int maxValue(LinkList L){
    LNode *p = L->next;
    if(!p)
        return -1;
    int max=p->data;
    p = p->next;
    while (p){
        if(p->data>max)
            max = p->data;
        p = p->next;
    }
    return max;
}
//将单链表从小到大排序
void sort(LinkList &L){
    LNode *p = L->next;
    int n = 0;
    while (p){
        n++;
        p = p->next;
    }//求出待排序元素个数
    int count;
    LNode *pre,*q;
    for(int i=0;i<n-1;i++){  //n-1为冒泡排序趟数
        count = n-i-1;  //count为每趟冒泡排序需要比较的次数，n个元素比较n-1次
        pre = L;
        p = L->next;
        q = p->next; //每趟冒泡排序比比较p q 的值
        while (count>0){
            if(p->data>q->data){
                p->next = q->next;
                q->next = p;
                pre->next = q;
            } else{
                pre = p;
                p = q;
                q = q->next;
            }
            count--;
        }
    }
}//也可将单链表中元素取出存到数组中，对数组进行排序，重新建立单链表，不推荐
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
//    1 2 3 4 5 6 -1
    create(L);
    cout<<maxValue(L)<<endl;
    int k;
//    2
    cout<<"请输入k:"<<endl;
    cin>>k;
    loc(L,k);
    sort(L);
    print(L);
}
/*
冒泡排序，堆排序以及快速排序中，快速排序和堆排序不适合单链表，因为快速排序要不断的从左和右分别向反向遍历交换结点，而单链表只有从头向尾遍历的功能。
堆排序在建堆的适合会对数据进行随机存取，单链表不符合这个特性。而冒泡排序可以使用单链表。
 */
