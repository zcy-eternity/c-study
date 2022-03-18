// Created by zhangchaoyan on 2022/3/17.
#include <iostream>

using namespace std;
//输入10个数，输出最大的那个数，然后把数组逆序存放并输出
int max_reverse(int a[], int n){
    int max=a[0];
    for(int i=0;i<n;i++){
        if(a[i]>max)
            max = a[i];
    }
    int mid = n/2-1;
    int temp;
    for(int i=0;i<=mid;i++){
        temp = a[i];
        a[i] = a[n-1-i];
        a[n-1-i] = temp;
    }
    return max;
}
int main(){
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    cout<<max_reverse(a,10)<<endl;
    for(int i=0;i<10;i++)
        cout<<a[i]<<" ";
}

