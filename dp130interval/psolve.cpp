/*
ID: billyz43
PROG: psolve
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <iomanip>
#include <cmath>
#include <climits>
#define INF 0x07070707
std::ifstream in("psolve.in");
std::ofstream out("psolve.out");
using namespace std;

struct prob{
    int bp, ap;
};

int M, P,ans = INT_MAX;
prob q[301];
int dp[302][1005];

int dfs(int AP,int cp){
//    cout << AP << ' ' << cp << ' ' << endl;
    if(AP > M){
        return INF;
    }
    if(cp >= P){
        return 1;
    }
    if(dp[cp][AP] < INF) return dp[cp][AP];

    int ret = INF;
    if(AP > 0){
        ret = dfs(0,cp)+1);
    }
    
    int l = M-AP;
    int lp = 0;
    int cpt = cp;

    while(l >= q[cpt].bp && cpt < P){ 
        l -= q[cpt].bp;
        lp += q[cpt].ap;
        cpt++;
        ret = min(ret,dfs(lp,cpt)+1);
    }
    dp[cp][AP] = ret;
    return ret;
}

int main(){
    in >> M >> P;
//    cout << "M " <<M << "\tP " << P << endl;
    for(int i = 0; i < P; i++){
        in >> q[i].bp >> q[i].ap;
    }
    memset(dp,0x07,sizeof(dp));
    int ans = dfs(0,0)+1;
    out << ans << endl;
}
