/*
ID: billyz43
PROG: path
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <unordered_map>
#include <list>
#include <cmath>
#define INF 0x3F3F3F3F
std::ifstream in("path.in");
std::ofstream out("path.out");
using namespace std;

struct node{
    unsigned short b,t;
    node(int b, int t): b(b),t(t) {}
};

int N, M,K;
list<node> g[5001];
unsigned int dp[5001][601];

int dfs(){
    for(auto i: g[N]){
        dp[i.b][1] = i.t;
    }

    for(int k = 2; k <= K; k++){
        for(int i = 1; i <= N; i++){
            for(auto j: g[i]){
                dp[i][k] = min(dp[i][k],dp[j.b][k-1] + j.t);
            }   
        }
    }
    return dp[1][K];
}

int main(){
    in >> N >> M >> K;
    for(int i = 0; i < M; i++){
        int a,b,t;
        in >> a >> b >> t;
        g[a].push_back(node(b,t));
        g[b].push_back(node(a,t));
    }
    memset(dp,0x3F,sizeof(dp));

    int ans = dfs();
//cout << ans << ' ' << dp[1][0] << endl;
    out << ans << endl;
}
