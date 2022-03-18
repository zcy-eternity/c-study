// Created by zhangchaoyan1 on 2022/3/17.
#include <iostream>

using namespace std;
//判断输入的字符串是否符合a*n b*n c*n 的格式，符合的话输出YES 否则的话输出 NO
bool check1(const char str[]){
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
bool check2(const char str[]){
    int count = 1,cur_count;
    int i = 0;
    //记录第一个重复出现的元素有多少个
    while (str[i]==str[i+1]){
        count++;
        i++;  //i指针只有前后元素相等时才移动
    }
    i++;
    while (str[i]!='#'){
        cur_count = 1;
        while (str[i]==str[i+1]){
            i++;
            cur_count++;
        }
        i++;
        if(cur_count != count)
            return false;
    }
    return true;
}
int main(){
    char str[100];
//    aaabbbccc#  aabbacc# aabbbccc#
    cin>>str;
    if (check2(str))
        cout<<"YES";
    else
        cout<<"NO";
}
