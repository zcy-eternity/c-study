#include <iostream>
using namespace std;

int strLen(const char str[]){
    int len=0;
    while(str[len]!='\0'){
        len++;
    }
    return len;
}

char* subStr(const char str[],int pos,int len){
    char *subStr = new char[len+1];
    int i;
    for(i=pos-1;i<=pos+len-2;i++){
        subStr[i-pos+1] = str[i];
    }
    subStr[i-pos+1] = '\0';
    return subStr; //不能返回作为局部变量的字符数组，但字符指针可以
}
int strCompare(const char str1[], const char str2[]){
    int len1 = strLen(str1);
    int len2 = strLen(str2);
    int i;
    for(i=0;i<len1 && i<len2;i++){
        if(str1[i] != str2[i])
            return str1[i] - str2[i];
    }
    //扫描过的所有字符都相同，则长度长的串更大
    return len1 - len2;
}
int index_BF(char str1[], char str2[]){
    int i=0,j=0;
    int len1 = strLen(str1);
    int len2 = strLen(str2);
    while (i<len1 && j<len2){
        if(str1[i]==str2[j]){
            i++;
            j++;
        } else{
            i=i-j+1;
            j=0;
        }
    }
    if(j==len2)
        return i-j+1;//子串位置，不是数组下标
    else
        return -1;
}
//-1 0 0 1 1 2
int* get_next(char str[]){
    int i=0,j=-1;
    int len = strLen(str);
    int *next = new int[len];
    next[0] = -1;
    while (i<len){
        if(str[i]==str[j]||j==-1){
            i++;
            j++;
            next[i]=j;
        } else
            j = next[j];
    }
    return next;
}
int index_KMP(char str1[], char str2[]){
    int i=0,j=0;
    int len1 = strLen(str1);
    int len2 = strLen(str2);
    while (i<len1 && j<len2){
        if(str1[i] == str2[j]||j == -1){
            i++;
            j++;
        } else
            j = get_next(str2)[j];
    }
    if(j==len2)
        return i-j+1;
    else
        return -1;
}
int main(){
    char str[] = "string";
    char str1[] = "in";
    cout<<"BF算法 字符串in在string的位置：";
    cout<<index_BF(str,str1)<<endl;
    cout<<"KMP算法 字符串in在string的位置：";
    cout<<index_KMP(str,str1)<<endl;
    cout<<"字符串string从第2个字符开始长度为3的子串为：";
    cout<<subStr(str,2,3)<<endl;
    cout<<"字符串abaabc的next数组为：";
    char str2[] = "abaabc";
    int *next = get_next(str2);
    for(int i=0;i<strLen(str2);i++)
        cout<<next[i]<<" ";
    cout<<endl<<strCompare(str1,str2);
    return 0;
}

