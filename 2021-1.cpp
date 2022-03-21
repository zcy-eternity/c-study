// Created by zhangchaoyan on 2022/3/18.
#include <iostream>
using namespace std;
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;

//β�巨����������
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
//����������������͵�����k��ֵ
void loc(LinkList L, int k){
    if(k<0||!L->next)
        return;
    int i=1;
    LNode *p = L->next;
    while (p&&i<k){
        p = p->next;
        i++;
    }
//    while (--k){   k=0ʱ�˳� �ȼ����ҵ���k��Ԫ��
//        p = p->next;
//    }
    if(p)
        cout<<"������k��ֵΪ��"<<p->data<<endl;
    else
        return;
    LNode *q = L;
    while (p){
        q = q->next;
        p = p->next;
    }
    if(q)
        cout<<"������k��ֵΪ��"<<q->data<<endl;
}
//��������Ԫ�����ֵ�����
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
//���������С��������
void sort(LinkList &L){
    LNode *p = L->next;
    int n = 0;
    while (p){
        n++;
        p = p->next;
    }//���������Ԫ�ظ���
    int count;
    LNode *pre,*q;
    for(int i=0;i<n-1;i++){  //n-1Ϊð����������
        count = n-i-1;  //countΪÿ��ð��������Ҫ�ȽϵĴ�����n��Ԫ�رȽ�n-1��
        pre = L;
        p = L->next;
        q = p->next; //ÿ��ð������ȱȽ�p q ��ֵ
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
}//Ҳ�ɽ���������Ԫ��ȡ���浽�����У�����������������½������������Ƽ�
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
    cout<<"������k:"<<endl;
    cin>>k;
    loc(L,k);
    sort(L);
    print(L);
}
/*
ð�����򣬶������Լ����������У���������Ͷ������ʺϵ�������Ϊ��������Ҫ���ϵĴ�����ҷֱ��������������㣬��������ֻ�д�ͷ��β�����Ĺ��ܡ�
�������ڽ��ѵ��ʺϻ�����ݽ��������ȡ������������������ԡ���ð���������ʹ�õ�����
 */
