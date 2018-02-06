/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Grafo.h
 * Author: Alan
 *
 * Created on 5 de febrero de 2018, 05:49 PM
 */

#include <fstream>
#include <vector>
#include <list>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

#ifndef GRAFO_H
#define GRAFO_H

template < typename V >
class Grafo {
    // Representa una red compleja con vértices de tipo V.
    /* SUPUESTOS:
     * 1. Los vértices son identificados con números de 0 a N-1, dada N la cantidad
     * total de vértices.
     * 2. El tipo V tiene definido su constructor estándar V().
     * 3. El tipo v tiene definido su constructor de copias V(const V& orig);
     */

public:
    /* CONSTRUCTORES */

    // REQ: cantidadVrt > 0. En este caso, N es igual a cantidadVrt.
    // REQ: 0 < probabilidadAdy < 1.
    // Construye un grafo con cantidadVrt de vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando probabilidadAdy. Esto
    // implica que la probabilidad de que un arco exista entre cualesquiera dos
    // dos vértices es igual a probabilidadAdy
    Grafo(int cantidadVrt, double probabilidadAdy);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices tienen un índice que va de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
    // NOTA: todos los vértices son inicializados con V().
    Grafo(ifstream& archivo);

    // Construye una copia idéntica a orig.
    Grafo(const Grafo< V >& orig);

    ~Grafo();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= indVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el grafo.
    void obtIdVrtAdy(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por valor para que NO pueda ser modificado.
    V operator[](int idVrt) const;

    // EFE: retorna el total de arcos o adyacencias en el grafo.
    int obtTotArc() const;

    // EFE: retorna el total de vértices en el grafo.
    int obtTotVrt() const;

    /* MÉTODOS MODIFICADORES BÁSICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    V& operator[](int idVrt);

private:

    template < typename W >
    struct Vrt {
        W w;
        list< int > lstAdy;

        Vrt< W >() : w(W()), lstAdy() {
        };

        Vrt< W >(const W& ww) : w(ww), lstAdy() {
        };
    };

    vector< Vrt< V > > vectorVrts; // vector de vértices
};

template < typename V >
Grafo< V >::Grafo(int cantidadVrt, double probabilidadAdy) {
    vectorVrts.resize(cantidadVrt, V());
    
    srand(time(NULL)); /* initialize random seed: */
    for (int i = 0; i < cantidadVrt; i++)
        for (int j = i + 1; j < cantidadVrt; j++)
            if ((rand() % 1000) / 1000.0 < probabilidadAdy) {
                vectorVrts[i].lstAdy.push_front(j);
                vectorVrts[j].lstAdy.push_front(i);
            }
}

template < typename V >
Grafo< V >::Grafo(ifstream& archivo) {

}

template < typename V >
Grafo< V >::Grafo(const Grafo< V >& orig) {

}

template < typename V >
Grafo< V >::~Grafo() {

}

template < typename V >
bool Grafo< V >::xstVrt(int idVrt) const {
    return idVrt < vectorVrts.size();
}

template < typename V >
bool Grafo< V >::xstAdy(int idVrtO, int idVrtD) const {
    return xstVrt(idVrtO) && xstVrt(idVrtD) && (find(vectorVrts.at(idVrtO).lstAdy.begin(), vectorVrts.at(idVrtO).lstAdy.end(), idVrtD) != vectorVrts.at(idVrtO).lstAdy.end());
}

template < typename V >
void Grafo< V >::obtIdVrtAdy(int idVrt, vector< int >& rsp) const {
    for(typename list< V >::const_iterator itr = vectorVrts.at(idVrt).lstAdy.begin(); itr != vectorVrts.at(idVrt).lstAdy.end(); itr++)
        rsp.push_back(*itr);
}

template < typename V >
V Grafo< V >::operator[](int idVrt) const {
    return vectorVrts[idVrt];
}

template < typename V >
int Grafo< V >::obtTotArc() const {
    int rsl = 0;
    for (typename vector< V >::const_iterator itr = vectorVrts.begin(); itr != vectorVrts.end(); itr++)
        rsl = rsl + vectorVrts[itr].lstAdy.size();
    return rsl / 2;
}

template < typename V >
int Grafo< V >::obtTotVrt() const {
    return vectorVrts.size();
}

template < typename V >
V& Grafo< V >::operator[](int idVrt) {
    return vectorVrts[idVrt];
}
#endif /* GRAFO_H */

