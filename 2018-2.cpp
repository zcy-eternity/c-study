// Created by zhangchaoyan on 2022/3/16.
#include <iostream>

using namespace std;
//找出字符在一串数字中的起始位置和最终出现的位置
void locate(char str[], char ch){
    int i=0,count=0;
    int loc[100];//用一个数组存放每一个符合条件的值 用一个变量count记录符合条件的总数
    for (int j=0;j<100;j++){
        loc[j] = -1;
    }
    while (str[i]!='\0'){
        if(str[i] == ch)
            loc[count++] = i;
        i++;
    }
    cout<<'['<<loc[0]<<','<<loc[count-1]<<']'<<endl;
}
int main(){
    char str[100];
    //1599985
    cin>>str;
    char ch;
    //9
    cin>>ch;
    locate(str,ch);
}


