#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<map>
#include<algorithm>

using namespace std;

struct pipe{
    int b, c, f;

    pipe(int y, int z, int w){
        b = y;
        c = z;
        f = w;
    }

    pipe(){}

    bool operator == (const pipe& x) const{
        return b == x.b && c == x.c && f == x.f;
    }
};

struct Path{
    int end, cost, flow;

    Path(int x, int y, int z){
        end = x;
        cost = y;
        flow = z;
    }

    Path(){}
};

int N;
bool done = false;
map<int, vector<pipe> > pi;  
vector<Path> visited;
vector<Path> active;
int thres = 0;

int dominate(Path& x, Path& y){
    if(x.flow > y.flow && x.cost < y.cost){
        return 1;
    }

    if(y.flow > x.flow && y.cost < x.cost){
        return 2;
    }

    return 0;
}

Path add(Path& p, pipe& q){
    return Path(q.b, p.cost+q.c, std::min(p.flow, q.f));
}

void find_ac(){
    vector<Path> next;
    done = true;
    for(int i = 0; i < active.size(); i++){
        vector<pipe>& p = pi[i];
        for(int j = 0; j < p.size(); j++){
            Path x = add(active[i], p[j]);
            if(x.flow/x.cost < thres){
                continue;
            }
            if(x.end == N){
                thres = x.flow/x.cost;
            }
            for(int k = 0; k < visited.size(); k++){
                int y = dominate(x, visited[k]);
                if(visited[k].end == p[j].b){
                    if(y == 0){
                        visited.push_back(x);
                        next.push_back(x);
                        done = false;
                    }
                    if(y == 1){
                        visited.erase(visited.begin()+k);
                        visited.push_back(x);
                        next.push_back(x);
                        done = false;
                    }
                    if(y == 2){
                        continue;
                    }
                }
            }
        }
    }
    active.clear();
    active = next;
}

void visit(){
    while(!done){
        find_ac();
    }
}

int read(){
    std::ifstream is("pump.in");
    if(!is.is_open()){
        return -1;
    }

    int M;
    is >> N >> M;

    for(int i = 0; i < M; i++){
        int a, b, f, c;
        is >> a >> b >> c >> f;
        pi[a].push_back(pipe(b, c, f));
    }

    return M;
}

int main(){
    int M = read();

    visited.push_back(Path(1, 0, INT_MAX));
    active.push_back(Path(1, 0, INT_MAX));
    visit();

    int max = (int)(thres*10e-6);
    std::ofstream os("pump.out");
    if(!os.is_open()){
        return 0;
    }

    os << max << endl;
    os.close();
}