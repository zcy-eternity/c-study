#include <iostream>
#include <cstring>
using namespace std;

int main(){
    char str[] = "str";
    int i=0,len=0;
    while (str[i]!='\0'){
        len++;
        i++;
    }
    cout<<len;
}

