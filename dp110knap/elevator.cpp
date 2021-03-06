/*
ID: billyz43
PROG: elevator
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <unordered_map>
#include <iomanip>
#include <cmath>
#define INF 9999
std::ifstream in("elevator.in");
std::ofstream out("elevator.out");
using namespace std;
int K,mx,N;
struct node{
    int h,a,c;
    
    bool operator < (const node& o) const{
        return a < o.a;
    }
};
node e[4010];
int dp[2][40002];

int dfs(){
    int a = 0,b = 1;
    for(int i = 1; i <= N; i++){
        //dp[i][0] = 0;
        for(int j = 1; j <= mx; j++){
            if(j > e[i].a){
                dp[b][j] = max(dp[a][j],dp[b][e[i].a]);
            } else{
                dp[b][j] = dp[a][j];
                if(j-e[i].h >= 0){
                    int tmp = dp[a][j-e[i].h]+e[i].h;
                    dp[b][j] = max(dp[b][j],tmp);
                }
            }
        }
        swap(a,b);
    }
    return dp[a][mx];    
}

int main(){
    in >> K;
    for(int i = 1; i <= K; i++){
        N++;
        in >> e[N].h >> e[N].a >> e[N].c;
        mx = max(mx,e[N].a);
        int j = e[N].c;
        while(j > 1){
            N++;
            j--;
            e[N].h = e[N-1].h;
            e[N].a = e[N-1].a;
        }       
    }
    cout << N << endl;
    sort(e+1,e+N+1);
    int res = dfs();
    out << res << endl;
}
