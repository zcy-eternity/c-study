#include <iostream>

using namespace std;
typedef struct PNode{
    float coef;
    int expn;
    struct PNode *next;
}PNode,*Polynomial;

//10 0 -4 2 5 1 2 4 3 3
void createPoly(Polynomial &p, int n){
    p = new PNode;
    p->next = nullptr;
    PNode *s,*pre,*q;
    for(int i=0;i<n;i++){
        s = new PNode;
        cin>>s->coef>>s->expn;
        pre = p;
        q = p->next;
        while (q&&q->expn<s->expn){
            pre = q;
            q = q->next;
        }
        s->next = q;
        pre->next =s;
    }
}
void print(Polynomial p){
    PNode *q = p->next;
    while (q->next){
        if(q->next->coef>0)
            cout<<q->coef<<"x"<<q->expn<<"+";
        else
            cout<<q->coef<<"x"<<q->expn;
        q = q->next;
    }
    cout<<q->coef<<"x"<<q->expn;
}
//7 0 3 1 9 8 5 17
//8 1 22 7 -9 8
void addPoly(Polynomial &p1 , Polynomial p2){
    PNode *L1,*L2,*r;
    PNode *s;
    L1 = p1->next;
    L2 = p2->next;
    r = p1;
    while (L1&&L2){
        if(L1->expn < L2->expn){
            r->next = L1;
            L1 = L1->next;
            r = r->next;
        } else if(L1->expn == L2->expn){
            if(L1->coef + L2->coef!=0){
                s = new PNode;
                s->coef = L1->coef + L2->coef;
                s->expn = L1->expn;
                r->next = s;
                L1 = L1->next;
                L2 = L2->next;
                r = r->next;
            } else{
                L1 = L1->next;
                L2 = L2->next;
            }
        } else{
            r->next = L2;
            L2 = L2->next;
            r = r->next;
        }
    }
    if(L1)
        r->next = L1;
    else
        r->next = L2;
    delete p2;
}

int main(){
    Polynomial p,q;
    createPoly(p,4);
    createPoly(q,3);
    addPoly(p,q);
    print(p);
    return 0;
}
