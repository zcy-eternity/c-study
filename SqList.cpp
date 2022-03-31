#include "iostream"
#define MaxSize 100

using namespace std;
typedef struct {
    int *data;
    int length;
}SqList;

int init(SqList &L){
    L.data = new int[MaxSize];
    if(!L.data)
        return -1;
    L.length = 0;
    return 0;
}

void createSqList(SqList &L){
    int n,i=0;
    cin>>n;
    while (n!=-1){
        L.data[i++] = n;
        L.length++;
        cin>>n;
    }
}

void print(SqList L){
    for(int i=0;i<L.length;i++)
        cout<<L.data[i]<<" ";
}
int insert(SqList &L, int i, int e){
    int j = 0;
    if(i<0||i>L.length-1)
        return -1;
    if(L.length==MaxSize)
        return -1;
    for(j=L.length-1;j>i-2;j--){
        L.data[j+1] = L.data[j];
    }
    L.data[j+1] = e;
    L.length++;
    return 0;
}
//有序表合并
void mergeList(SqList la, SqList lb, SqList &lc){
    lc.length = la.length + lb.length;
    lc.data = new int[lc.length];
    int *pa = la.data,
    *pb = lb.data,
    *pc = lc.data;
    int *la_end = pa + la.length -1,
    *lb_end = pb + lb.length - 1;
    while (pa <= la_end && pb <= lb_end){
        if(*pa <= *pb){
            *pc++ = *pa++; //*和++优先级相同 结合性自右向左
        } else{
          *pc++ = *pb++;
        }
    }
    while (pa<=la_end)
        *pc++ = *pa++;
    while (pb<=lb_end)
        *pc++ = *pb++;
}
int main(){
//    SqList L;
//    init(L);
//    createSqList(L);
//    insert(L,2,-1);
    SqList la,lb,lc;
    init(la);
    init(lb);
    createSqList(la);
    createSqList(lb);
    mergeList(la,lb,lc);
    print(lc);
    return 0;
}