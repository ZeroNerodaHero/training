/*
ID: billyz43
PROG: prime3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_set>
#include <iomanip>
#include <math.h>
using namespace std;
std::ifstream in("prime3.in");
std::ofstream out("prime3.out");
int s;

struct mat{
    int a[5][5];

    bool operator< (const mat& o)const{
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(a[i][j] < o.a[i][j]) return true;
                if(a[i][j] > o.a[i][j]) return false;
            }
        }
        return false;
    }
};

bool nprime[100005];
int primen[10][200][5];
mat ans[50];
int cind[10];
int tab[5][5];
int has = 0;

void print(){
    if(has) out << endl;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            out << tab[i][j];
        }
        out << endl;
    }
}
int tprime = 0;
void primes(){
    int N = sqrt(99999);
    for(int i = 2; i <= N; i++){
        if(nprime[i] == 0){
            for(int j = i+i; j < 99999; j+=i){
                nprime[j] = true;
            }
        }
    }
    for(int i = 10001; i < 99999; i++){
        if(nprime[i] == 0){
//            cout << i << endl;
            int x = i;
            int ind = i/10000;
            int &k = cind[ind];
            int cs = ind;
            primen[ind][k][0] = ind;
            for(int j = 4; j > 0; j--){
                primen[ind][k][j] = x%10;
                x/=10;
                cs += primen[ind][k][j];
            }
//if(cs == s)             cout <<i << ' ' <<  cs << endl;
            if(cs == s) k++;
            else nprime[i] = true;
        }
    }
#if 0
    for(int i = 0; i < 10; i++){
        cout << i << ' ' << cind[i] << endl;
        for(int j = 0; j < cind[i]; j++){
            cout << j << ": ";
            for(int k = 0; k < 5; k++){
                cout << primen[i][j][k];
            }
            cout << endl;
        }   
        cout << endl;
    }
#endif
}


bool check(){
    for(int i = 1; i < 5; i++){
        int ch = 0;
        for(int j = 0; j < 5; j++){
            ch = ch*10+tab[j][i];
        }
//        cout << ch << ' ' << nprime[ch] << endl;
        if(ch < 10000 || nprime[ch]) return false;
    } 
    return true;
}

void dfs(int d){
    int tc = tab[0][0];
#if 0
    if (d==7) {
        cout << "step " <<  d << ' ' <<  tc << ' ' << cind[tc] << endl;
        print();
    }
#endif
    switch(d){
        case 0: 
            for(int i = 0; i <cind[tc]; i++){
                for(int j = 1; j < 5; j++){
                    tab[0][j] = primen[tc][i][j];
                }
                dfs(d+1);
            }
            break;
        case 1: 
            for(int i = 0; i <cind[tc]; i++){
//                cout << "cur " << i << endl;
                for(int j = 1; j < 5; j++){
                    tab[j][0] = primen[tc][i][j];
                }
                dfs(d+1);
            }
            break;
        case 2:
            tc = tab[4][0];
            for(int i = 0; i <cind[tc]; i++){
                if(primen[tc][i][4] == tab[0][4]){
                    for(int j = 1; j <= 3; j++){
                        tab[4-j][j] = primen[tc][i][j];
                    }
                    dfs(d+1);
                }
            }
            break;
        case 3:
            for(int i = 0; i <cind[tc]; i++){
                if(primen[tc][i][2] == tab[2][2]){
                    for(int j = 1; j < 5; j++){
                        tab[j][j] = primen[tc][i][j];
                    }
                    dfs(d+1);
                }
            }
            break;
        case 4: 
        case 6:
            tc = tab[d-3][0];
            for(int i = 0; i < cind[tc]; i++){
                if(primen[tc][i][1] == tab[d-3][1] && primen[tc][i][3] == tab[d-3][3]){
                    for(int j = 2; j < 5; j++){
                        tab[d-3][j] = primen[tc][i][j];
                    }
                    dfs(d+1);
                }
            }
            break;
        case 5:
            tc = tab[2][0];
            for(int i = 0; i < cind[tc]; i++){
                if(primen[tc][i][2] == tab[2][2]){
                    for(int j = 1; j < 5; j++){
                        tab[2][j] = primen[tc][i][j];
                    }
                    dfs(d+1);
                }
            }
            break;
        case 7:
            tc = tab[4][0];
            for(int i = 0; i < cind[tc]; i++){
                if(primen[tc][i][4] == tab[4][4]){
                    int j = 1;
                    for(; j < 4; j++){
                        if(((primen[tc][i][j]&1) == 0) || (primen[tc][i][j] == 5)) break;
                        tab[4][j] = primen[tc][i][j];
                    }
                    if(j == 4) dfs(d+1);
                }
            }
            break;
        case 8:
            if(check()){
//                cout << "res********\n";
                for(int i = 0; i < 5; i++){
                    for(int j = 0; j < 5; j++){
                        ans[has].a[i][j] = tab[i][j];
                    }
                }
                has++;
            }
    }
}

int main(){
    in >> s >> tab[0][0];
//    cout << s << ' ' << tab[0][0] << endl;

    primes();
    dfs(0);
    if(!has){
        out << "NONE\n";
        return 0;
    }
    sort(ans,ans+has);
    for(int i = 0; i < has; i++){
        if(i != 0) out << endl;
        for(int j =0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                out << ans[i].a[j][k];
            }
            out << endl;
        }
    }
}
