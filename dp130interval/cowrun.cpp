/*
ID: billyz43
PROG: cowrun
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
#define INF 0x4f4f
std::ifstream in("cowrun.in");
std::ofstream out("cowrun.out");
using namespace std;
int N;
int ar[1001];
struct node{
    int t, d;
};
node dp[2][1000][1000];

int dfs(){
    for(int i = 0; i < N; i++){
        dp[0][i][i].t = dp[0][i][i].d = abs(ar[i]);
        dp[1][i][i].t = dp[1][i][i].d = abs(ar[i]);
    }    

    for(int l = 1; l < N; l++){
        for(int s = 0, e = l; e < N; e++,s++){
            int t1 = dp[0][s+1][e].t + abs(ar[s]-ar[s+1]);
            int t2 = dp[1][s+1][e].t + abs(ar[s]-ar[e]);
            int d1 = dp[0][s+1][e].d + t1 * (N-l);
            int d2 = dp[1][s+1][e].d + t2 * (N-l);

//            cout << s << " " << e << " 0 t\t" << t1 << " d\t" << d1 << endl;;
//            cout << s << " " << e << " 0 t\t" << t2 << " d\t" << d2 << endl;;

            if(d1 < d2){
                dp[0][s][e].t = t1;
                dp[0][s][e].d = dp[0][s+1][e].d + t1;
            } else{
                dp[0][s][e].t = t2;
                dp[0][s][e].d = dp[1][s+1][e].d + t2;
            }

            t1 = dp[0][s][e-1].t + abs(ar[e]-ar[s]);
            t2 = dp[1][s][e-1].t + abs(ar[e]-ar[e-1]);
            d1 = dp[0][s][e-1].d + t1 * (N-l);
            d2 = dp[1][s][e-1].d + t2 * (N-l);

//            cout << s << " " << e << " 0 t\t" << t1 << " d\t" << d1 << endl;;
//            cout << s << " " << e << " 0 t\t" << t2 << " d\t" << d2 << endl;;

            if(d1 < d2){
                dp[1][s][e].t = t1;
                dp[1][s][e].d = dp[0][s][e-1].d + t1;
            } else{
                dp[1][s][e].t = t2;
                dp[1][s][e].d = dp[1][s][e-1].d + t2;
            }

            
        }
    }
    return min(dp[0][0][N-1].d,dp[1][0][N-1].d);   
}

int main(){
    in >> N;
    for(int i = 0; i < N; i++){
        in >> ar[i];
    }
    sort(ar,ar+N);
    int ans = dfs();
    out << ans << endl;
}
