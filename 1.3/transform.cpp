/*
ID: NomNom
PROG: transform
LANG: C++
*/
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

int N;
char a[10][10], b[10][10], tmp[10][10];;

bool isequal(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

void rot(){
    for(int i = 0; i < N; i++){
        int col = N-i-1;
        for(int j = 0; j < N; j++){
            tmp[j][col] = a[i][j];            
        }
    }    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            a[i][j] = tmp[i][j];
        }
    }
}

void reflect(){
    for(int j = 0; j < N; j++){
        int col = N-j-1;
        for(int i = 0; i < N; i++){
            tmp[i][col] = a[i][j];
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            a[i][j] = tmp[i][j];
        }
    }
}

int main(){
    std::ifstream in("transform.in");
    std::ofstream out("transform.out");

    in >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            in >> a[i][j];
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            in >> b[i][j];
        }
    }
    for(int i = 1; i < 4; i++){
        rot();
        if(isequal()){
            out << i << '\n';
            return 0;
        }
    } 
    rot();
    if(isequal()){
        out << 6 << endl;
        return 0;
    }
    reflect();
    if(isequal()){
        out << 4 << endl;
        return 0;
    }
    for(int i = 0; i < 3; i++){
        rot();
        if(isequal()){
            out << 5 << endl;
            return 0;
        }
    }   
    out << 7  << '\n';
    return 0;
}
