#include <iostream>
#include <fstream>
#include <string>
#define NUM 1000
#define N8 8

using namespace std;

int abs(int x);
int solutions(int n);
bool test(int x, int n, int a[]);
int queens[N8];
int cnt = 0;

int main(){
    solutions(0);
    printf("The number of solutions = %d", cnt);
}

int abs(int x){
    if(x >= 0){
        return x;
    }else{
        return -x;
    }
}

int solutions(int n){
    for(int i = 0; i < N8; i++){    
        if(test(i, n, queens)){
            if(n == N8-1){
                queens[n] = i;
                for(int j = 0; j < N8; j++){
                    printf("%d", queens[j]);
                }
                printf("\n");
                cnt++;
                break;
            }else{
                queens[n] = i;
                solutions(n+1);
            }
        }
    }
}

bool test(int x, int n, int a[]){
    for(int i = 0; i < n; i++){
        if(abs(x - a[i]) == abs(n - i) || x == a[i]){
            return false;
        }
    }
    return true;
}