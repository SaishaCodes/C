#include<stdio.h>
#include<string.h>

int main(){
    int l;
    char str[50] = "abbba";
    int h = strlen(str) - 1;
    while(h>l){
        if(str[l++] != str[h--]){
            printf("%s is not a palindrome", str);
        }
        else{
            printf("It is a palindrome");
        }
    }
    return 0;
}