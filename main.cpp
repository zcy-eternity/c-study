#include <iostream>
#include <string>

using namespace std;
int main() {
    int a[] = {1,4,8,5,9,3};
    int len = sizeof(a)/sizeof(a[0]);
    //冒泡排序
    for(int i=0;i<len;i++)
        cout<<a[i]<<" ";
    string s;
    cin>>s;
    cout<<s;
    return 0;
}
