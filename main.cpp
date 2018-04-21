/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Alan
 *
 * Created on 5 de febrero de 2018, 04:26 PM
 */

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
using namespace std;

#include "Grafo.h" 

/*
 * 
 */

// REQ: (f >= 0) && (c >= 0) && (N > 0)
// RET: valor único asociado a f, c y N.

static long fIdUnico(int f, int c, int N) {
    return ((f == c) ? 0 : (f + c + N * (3 + abs(f - c))));
};

int main(int argc, char** argv) {
    /*int N = 10;
    Grafo< int, int > grafoInts(N, 0.5);
    vector< int > adyacentes;

    cout << "adyacencias: " << endl;
    for (int i = 0; i < N; i++) {
        grafoInts.obtIdVrtAdys(i, adyacentes);
        cout << "i: " << i << "->";
        for (int j = 0; j < adyacentes.size(); j++)
            cout << adyacentes[j] << ",";
        cout << endl;
        adyacentes.erase(adyacentes.begin(), adyacentes.end());
    }

    cout << "idUnicos: " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if ((i != j) && grafoInts.xstAdy(i, j))
                cout << fIdUnico(i, j, N) << "\t";
            else cout << 0 << "\t";
        cout << endl;
    }

    // asigna datos a adyacencias:
    srand(time(NULL)); 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if ((i != j) && grafoInts.xstAdy(i, j))
                grafoInts.asgDatoAdy(i, j, rand() % 1000);
            else grafoInts.asgDatoAdy(i, j, 0);
    }
    
    cout << "datos de adyacencias: " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if ((i != j) && grafoInts.xstAdy(i, j))
                cout << grafoInts.obtDatoAdy(i, j) << "\t";
            else cout << 0 << "\t";
        cout << endl;
    }   
    
    Grafo< int, int> grafoInts2(grafoInts); */
    ifstream archGrafoMuyPeqNoCnx ("laberintop.txt", ios::in);
    Grafo< int, int > grafoMuyPeqNoCnx(archGrafoMuyPeqNoCnx);
    
    /*for(int i = 0; i < grafoMuyPeqNoCnx.obtTotVrt(); i++){
        vector< int > adys;
        grafoMuyPeqNoCnx.obtIdVrtAdys(i, adys);
        cout << "adys de: " << i << ": ";
        for(int j = 0; j < adys.size(); j++)
            cout << adys[j] << ',';
        cout << endl;
    }*/
        
    vector< int > caminoEncontrado;
    grafoMuyPeqNoCnx.caminoMasCorto(0, 9, caminoEncontrado);
    for(int i = 0; i < caminoEncontrado.size(); i++)
        cout << caminoEncontrado[i] << ',';
    cout << endl;
    return 0;
}

