#include <iostream>
using namespace std;
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
void BubbleSort(int a[], int n){
    int flag;
    for(int i=0;i<n-1;i++){
        flag = 0;
        for(int j=0;j<n-1-i;j++)
            if(a[j]>a[j+1]){
                swap(a[j],a[j+1]);
                flag = 1;
            }
        if(flag == 0)
            break;
    }
}
int main(){
    int a[] = {1,3,5,2,4,6,9,7,8};
//    SelectSort(a,9);
    BubbleSort(a,9);
    for(int i : a)
        cout<<i<<" ";
}
