#include <iostream>
#include <cmath>
using namespace std;


typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;
typedef struct {
   LNode *front,*rear;
}LinkQueue;
void init(LinkQueue &Q){
    Q.front = new LNode;
    Q.rear = Q.front;
    Q.front->next = nullptr;
}
void EnQueue(LinkQueue &Q, int x){
    auto *s = new LNode;
    s->data = x;
    s->next = nullptr;
    Q.rear->next = s;
    Q.rear = s;
}
int DeQueue(LinkQueue &Q, int &x){
    if(Q.rear == Q.front)
        return 0;
    LNode *p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if(p == Q.rear)
        Q.rear = Q.front;
    delete p;
    return 1;
}
bool QueueEmpty(LinkQueue Q){
    if(Q.front == Q.rear)
        return true;
    else
        return false;
}
void create(LinkList &L){
    L = new LNode; //初始化
    L->next = nullptr;
    LNode *s;
    int n;
    cin>>n;
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
//直接插入
void InsertSort1(int a[], int n){
    int temp,i,j;
    for(i=1;i<n;i++){ //第一个元素有序，从第二元素开始选择插入位置
        temp = a[i];  //存储待插入的元素，因为会往后移动元素，发生覆盖
        for(j=i-1;j>=0&&a[j]>temp;j--)
            a[j+1] = a[j];
        a[j+1] = temp; //跳出循环时 j指针指向小于待插入元素的位置
    }
}
//折半插入
void InsertSort2(int a[], int n){
    int temp,i,j,low,high,mid;
    for(i=1;i<n;i++){
        temp = a[i];
        low = 0,high = i-1;
        while(low<=high){
            mid = (low+high)/2;
            if(a[mid]>temp)
                high=mid-1;
            else           //当a[min]=temp时为了保证算法的稳定性 应继续在mid所指位置右边寻找插入位置
                low=mid+1;
        }
        for(j=i-1;j>=low;j--)
            a[j+1] = a[j];
        a[low] = temp;
    }
}
//希尔排序
void ShellSort(int a[], int n){
    int i,j,d,temp;
    for(d=n/2;d>=1;d--){ //选取增量d
        for(i=d;i<n;i++){ //从第一个待插入元素开始 注意i指针步长为1
            temp = a[i];
            for(j=i-d;j>=0&&a[j]>temp;j-=d)
                a[j+d] = a[j];
            a[j+d] = temp;
        }
    }
}
//简单选择排序
void SelectSort(int a[],int n){
    int min,i,j;
    for(i=0;i<n-1;i++){
        min = i;
        for(j=i+1;j<n;j++){
            if(a[j]<a[min])
                min = j;
        }
        if(i!=min) {
            swap(a[i], a[min]);
        }
    }
}
//冒泡排序1
void BubbleSort1(int a[], int n){
    int flag;
    for(int i=0;i<n-1;i++){
        flag = 0;
        for(int j=0;j<n-1-i;j++) //初始j指针到n-2 因为下面比较的是j和j+1
            if(a[j]>a[j+1]){
                swap(a[j],a[j+1]);
                flag = 1;
            }
        if(flag == 0)
            break;
    }
}
//冒泡排序2
void BubbleSort2(LinkList &L){
    int n=0,count,flag;
    LNode *p = L->next;
    LNode *pre,*q;
    while (p){
        n++;
        p = p->next;
    }
    for(int i=0;i<n-1;i++){
        flag = 0;
        count = n-i-1;
        pre = L;
        p = L->next;
        q = p->next;
        while (count>0){  //结束循环条件为>0 内部循环次数为count
            if(p->data>q->data){
                p->next = q->next;
                q->next = p;
                pre->next = q;
                flag = 1;
            }
            pre = pre->next;
            p = pre->next;
            q = p->next;
            count--;
        }
        if(flag == 0)
            break;
    }
}
int Partition(int a[], int low, int high){
    int pivot = a[low];
    while (low<high){ //退出循环时low=high 注意在折半查找里是low<=high
        while (a[high]>=pivot&&low<high)
            high--;
        a[low] = a[high];
        while (a[low]<=pivot&&low<high)
            low++;
        a[high] = a[low];
    }
    a[low] = pivot;//将枢轴元素放到low或high指向的位置
    return low;
}
//快速排序
void QuickSort(int a[], int low, int high){
    if(low<high){
        int pivotpos = Partition(a,low,high);
        QuickSort(a,low,pivotpos-1);
        QuickSort(a,pivotpos+1,high);
    }
}
void HeadAdjust(int a[], int k, int len){
    a[0] = a[k];
    for(int i=2*k;i<=len;i*=2){
        if(a[i]<a[i+1]&&(i+1)<=len)
            i++;  //i较大孩子的下标
        if(a[0]>=a[i]) //相等时跳出循环，保持算法稳定
            break;
        else{
            a[k] = a[i];  //将孩子结点调整到双亲结点
            k = i;   //从孩子结点的位置继续向下删选
        }
    }
    a[k] = a[0];
}
void BuildMaxHeap(int a[], int len){
    for(int i=len/2;i>0;i--)
        HeadAdjust(a,i,len);
}
//堆排序
void HeapSort(int a[],int len){
    for(int i=1;i<len;i++){  //堆排序len-1趟
        swap(a[1],a[len-i+1]);
        HeadAdjust(a,1,len-i);
    }
}
/*
 * 从10亿个数中找出最小的10个数
 * 首先构建长度为10的大顶堆,假设这10个数为最小的10个数
 * 不断地从10亿个数据中读取,若大于等于顶元素,则丢弃;
 * 若小于顶元素,则替换顶元素,并调整堆adjustHeap
 * 最大的10个数构建小根堆
 */
void merge(int a[], int low, int mid, int high){
    int b[100];
    for(int i=low;i<=high;i++)
        b[i] = a[i];
    int i=low,j=mid+1;
    while (i<=mid&&j<=high){
        while (i<=mid&&b[i]<=b[j]) //加上i<=mid 防止while循环时i指针越界
            a[low++] = b[i++];     // 两元素相等时优先使用靠前的那个保持稳定性
        while (j<=high&&b[i]>b[j])
            a[low++] = b[j++];
    }
    while (i<=mid)
        a[low++] = b[i++];
    while (j<=high)
        a[low++] = b[j++];
}
//归并排序
void MergeSort(int a[],int low,int high){
    if(low<high){
        int mid = (low+high)/2;
        MergeSort(a,low,mid);
        MergeSort(a,mid+1,high);
        merge(a,low,mid,high);
    }
}
//基数排序
void RadixSort(int a[], int d, int n){ //把关键字分为d个部分
    LinkQueue Q[10];
    for(auto & i : Q)
        init(i);
    int pre,r;
    for(int i=0;i<d;i++){
        for(int j=0;j<n;j++)
            for(int k=0;k<10;k++)
                if(a[j]/(int)pow(10,i)%10 == k){
                    EnQueue(Q[k],a[j]);
                    break;
                }
        pre = -1;
        for(int m=0;m<10;m++){
            if(!QueueEmpty(Q[m])&&pre==-1){ //设置pre初值
                pre = m;
                r = m; //r记录队列的起始位置
                continue;
            }
            if(!QueueEmpty(Q[m])){
                Q[pre].rear->next = Q[m].front->next;
                pre = m;
            }
        }
        LNode *p = Q[r].front->next;
        int q = 0;
        while (p!= nullptr){
            a[q++] = p->data;
            p = p->next;
        }
        for(r=0;r<10;r++)
            init(Q[r]);
    }

}
int main(){
//    int a[] = {1,8,5,2,23,6,12,7,8};
//    QuickSort(a,0,8);
//    LinkList L;
//    create(L);
//    BubbleSort2(L);
//    print(L);
//    ShellSort(a,9);
//    1 8 5 2 23 6 12 7 8
//    int a[10];
//    for(int i=1;i<=9;i++)
//        cin>>a[i];
//    BuildMaxHeap(a,9);
//    HeapSort(a,9);
//    MergeSort(a,1,9);
//    for(int i=1;i<=9;i++)
//        cout<<a[i]<<" ";
//    return 0;
int a[] = {123,324,343,445,908,356,456,424};
    RadixSort(a,3,8);
    for(int i=0;i<8;i++)
        cout<<a[i]<<" ";
}
