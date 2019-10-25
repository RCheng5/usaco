#include <iostream>
#include <fstream>
#include <string>

// 0: 1 A -> C
// 1: 2 A -> B
// ....
void move(int n, char a1, char a2, char a3);
int num = 1;

int main(){
    int x;
    printf("Enter the number of rings:\n");
    scanf("%d", &x);
    char A = 'A';
    char B = 'B';
    char C = 'C';
    move(x, A, B, C);
}

void move(int n, char a1, char a2, char a3){
    if(n == 1){
        printf("%d: 1 %c -> %c\n", num, a1, a2);
        num++;
        return;
    }
    move(n-1, a1, a3, a2);
    printf("%d: %d %c -> %c\n", num, n, a1, a3);
    num++;
    move(n-1, a2, a3, a1);
}