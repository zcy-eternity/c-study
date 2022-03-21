// Created by zhangchaoyan on 2022/3/18.

#include <iostream>
using namespace std;

bool judge(const char str[]){
    int index1=-1,index2=-1;
    int i=0,n1=0,n2=0;
    while (str[i]!='\0'){
        if(str[i]==':'){
            index1 = i;
            n1++;
        }
        else if(str[i] == '.'){
            index2 = i;
            n2++;
        }
        i++;
    }
    if(n1>1||n2>1)
        return false;
    if(n1==1 && n2==1){
        if(index1+1 == index2) //booker:.txt
            return false;
        else if(index1==0||index2==i) //:name.txt booker:name.
            return false;
        else
            return true;
    }
    if(n1==0 && n2==1){
        if(index2==0 || index2==i) //.txt name. 既不在头也不在尾
            return false;
        else
            return true;
    }
    if(n1==1 && n2==0){
        if(index1==0 || index1==i) //:name booker:
            return false;
        else
            return true;
    }
    if(n1==0 && n2==0){
        if(i>0)   //排除空串
            return true;
        else
            return false;
    }
}
int main(){
    char str[100];
//    booker:myname.txt booker:.txt myname.txt .txt
    cin>>str;
    if(judge(str))
        cout<<"是"<<endl;
    else
        cout<<"否"<<endl;
}
