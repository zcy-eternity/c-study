// Created by zhangchaoyan1 on 2022/3/17.
#include <iostream>

using namespace std;

bool check(const char str[]){
    int i=0;
    int flag =0; //引入标志位，消除aabbacc
    int a_count=0,b_count=0,c_count=0;
    while (str[i]!='#'){
        if(str[i]=='b')
            flag = 1;
        if(str[i]=='c')
            flag = 2;
        if(str[i]=='a'&& flag !=0)
            return false;
        if(str[i]=='b'&& flag !=1)
            return false;
        if(str[i]=='c'&& flag !=2)
            return false;
        if(str[i]=='a'&& flag ==0)
            a_count++;
        if(str[i]=='b'&&flag==1){
            b_count++;
        }
        if(str[i]=='c'&&flag==2)
            c_count++;
        i++;
    }
    if(a_count==b_count && b_count==c_count)
        return true;
    else
        return false;
}
int main(){
    char str[100];
//    aaabbbccc#  aabbacc# aabbbccc#
    cin>>str;
    if (check(str))
        cout<<"YES";
    else
        cout<<"NO";
}
