/*
ID: rickycp1
LANG: C++
PROG: wormhole
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#define NUM 12

using namespace std;

struct coord{
    int x, y;

    bool operator == (const coord& a) const{
        return (a.x == x && a.y == y);
    }
};

// -- pr[0] = 3;  0--3
// -- ...
//std::vector<int> pr;

struct pairing{
    // coord a[2];
    int a[2];

    bool conflict(pairing x){
        /* if(x.a[0] == a[0] || x.a[1] == a[0] 
        || x.a[0] == a[1] || x.a[1] == a[1]){
            return true;
        } */
        return a[0] == x.a[0] || a[1] == x.a[1] || a[0] == x.a[1] || a[1] == x.a[0];
    }

    bool operator < (const pairing& x) const{
        // return (x.a[0].x < a[0].x);
        return a[0] < x.a[0];
    }

    pairing(int x, int y){
        setV(x, y);
    }

    void setV(int x, int y){
        a[0] = std::min(x, y);
        a[1] = std::max(x, y);
    }

    pairing(){
    }

    void print(){
        cout << a[0] << " --- " << a[1] << endl;
    }
};

int read();
int config(int n, int t);
void fill_moves(vector<coord> a_coord);
bool test(vector<int>& a, vector<coord>& a_coord);
void write(int x);
void print_pair(pairing x);

vector<int> moves;
vector<pairing> pairs;
vector<int> pr;

int cnt = 0;
vector<coord> wormholes;

int main(){
    int N = read();
    fill_moves(wormholes);

    // -- you MUST set the size of pairs!!!
    pairs.resize(wormholes.size() / 2);
    pr.resize(wormholes.size());

    config(0, -1);
    //cout << cnt << endl;
    write(cnt);
}

int read(){
    std::ifstream is("wormhole.in");
    if(!is.is_open()){
        return -1;
    }

    int N;
    is >> N;
                                                 
    for(int i = 0; i < N; i++){
        coord hole;
        is >> hole.x;
        is >> hole.y; // what is wrong here!!!!!!!!!!!!!
        wormholes.push_back(hole);

        //cout << "hole " << hole.x << ", " << hole.y << endl;
    }

    //cout << "wh size = " <<wormholes.size() << endl;
}

int config(int n, int t){
    for(int i = t+1; i < wormholes.size() - 1; i++){
        for(int j = i+1; j < wormholes.size(); j++){
            pairing nPair(i, j);
            bool r = false;
            for(int k = 0; k < n; k++){
                if(nPair.conflict(pairs[k])){
                    //cout << n << " conf " << k << endl;
                    r = true;
                    break;
                }
            }
            if(r){
                continue;
            }

            pairs[n] = nPair;

            if(n == wormholes.size()/2 - 1){
                for(int i2 = 0; i2 < wormholes.size()/2; i2++){
                    pr[pairs[i2].a[0]] = pairs[i2].a[1];
                    pr[pairs[i2].a[1]] = pairs[i2].a[0];
                }
                if(test(pr, wormholes)){
                    /*pairs[0].print();
                    cout << endl;
                    pairs[1].print();
                    cout << "end" << endl;*/
                    cnt++;
                }
            } else{
                config(n + 1, i);
            }
        }
    }
}

void fill_moves(vector<coord> a_coord){
    for(int i = 0; i < a_coord.size(); i++){
        moves.push_back(-1);
    }
    for(int i = 0; i < a_coord.size(); i++){
        vector<int> a;
        int j, j2 = -1;
        int min = 2147483647;
        for(j = 0; j < a_coord.size(); j++){
            if(i != j){
                if(a_coord[i].y == a_coord[j].y && a_coord[j].x > a_coord[i].x){
                    if(a_coord[j].x <= min){
                        min = a_coord[j].x;
                        j2 = j;
                    }
                }
            }
        }
        moves[i] = j2;
    }
}

bool test(vector<int>& a, vector<coord>& a_coord){
    /*for(int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < moves.size(); i++){
        cout << moves[i] << " ";
    }
    cout << endl;*/

    vector<int> sequence;
    bool x = false;
    for(int i = 0; i < a_coord.size(); i++){
        int j = i;
        int k = 0;
        sequence.clear();

        while(!x){
            if(k % 2 == 0){
                j = a[j];
                for(int l2 = 0; l2 < sequence.size(); l2 += 2){
                    if(j == sequence[l2]){
                        x = true;
                        break;
                    }
                }
                sequence.push_back(j);
                k++;
            }else{
                j = moves[j];
                if(j == -1){
                    x = false;
                    break;
                }else{
                    for(int l = 1; l < sequence.size(); l += 2){
                        if(j == sequence[l]){
                            x = true;
                            break;
                        }
                    }
                    sequence.push_back(j);
                }
                k++;
            }
        }

        if(x){
            break;
        }
    }

    return x;
}

void write(int x){
    FILE *fp = fopen("wormhole.out", "w");
    if(fp == NULL){
        return;
    }

    fprintf(fp, "%d\n", x);
    fclose(fp);
}

/* void print_pair(pairing x){
    // cout << x.a[0].x << " " << x.a[0].y << "------" << x.a[1].x << " " << x.a[1].y;
    cout << x.a[0] << " --- " << x.a[1] << endl;
} */