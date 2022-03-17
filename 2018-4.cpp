// Created by zhangchaoyan1 on 2022/3/16.

#include <iostream>
using namespace std;

void R(int a[], int n){
    cout<<'['<<']'<<",";
    for(int i=0;i<n;i++)
        cout<<'['<<a[i]<<']'<<",";
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            cout<<'['<<a[i]<<','<<a[j]<<']'<<",";
    cout<<endl;
    for(int i=0;i<n-2;i++)
        for(int j=i+1;j<n-1;j++)
            for(int k=j+1;k<n;k++)
                cout<<'['<<a[i]<<','<<a[j]<<','<<a[k]<<']'<<",";
    cout<<'[';
    for(int i=0;i<n;i++){
        if(i!=n-1)
            cout<<a[i]<<',';
        else
            cout<<a[i];
    }
    cout<<']';
}
//求集合子集
void R2(int a[], int n){
    int end = (1<<n)-1;//n位全1
    int b[100],count; //用b数组存符合条件的值，消除最后一个输出的逗号，方便找边界条件(最后一个元素)
    for(int i=0;i<=end;i++){
        cout<<'[';
        count = 0;
        for(int j=0;j<n;j++){
            if((i&(1<<j))!=0) //10010 和 1左移j位相与 若不为0,则输出
               b[count++]=a[j];
        }
        for(int j=0;j<count;j++)
            if(j==count-1) //最后一个元素
                cout<<b[j];
            else
                cout<<b[j]<<',';
        if(i<=end-1)
            cout<<']'<<',';
        else
            cout<<']';
    }
}
int main(){
    int a[] = {1,2,5,8};
    R2(a,4);
}