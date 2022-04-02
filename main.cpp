#include <iostream>

using namespace std;

//判断二维数组中是否含有重复元素
bool judge(int **a, int m, int n){
    int b[m*n],k=0;
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++){
            b[k++] = a[i][j];
        }
    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
            if(i!=j && b[i]==b[j])
                return true;
    return false;
}
int main() {
    int m,n;
    int **a;
    cin>>m>>n;
    a = new int* [m];
    for(int i=0;i<m;i++)
        a[i] = new int[n];
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];
    if(judge(a, m, n))
        cout<<"YES";
    else
        cout<<"NO";
    return 0;
}
