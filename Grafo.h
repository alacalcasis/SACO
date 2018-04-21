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

#ifndef GRAFO_H
#define GRAFO_H

#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

template < typename V, typename A >
class Grafo {
    // Representa una red compleja con vértices de tipo V y adyacencias de tipo A.
    /* SUPUESTOS:
     * 1. Los vértices son identificados con números de 0 a N-1, dada N la cantidad
     * total de vértices.
     * 2. El tipo V tiene definido su constructor estándar V().
     * 3. El tipo V tiene definido su constructor de copias V(const V& orig);
     * 4. El tipo A tiene definido su constructor estándar A().
     * 5. El tipo A tiene definido su constructor de copias A(const A& orig);     * 
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
    Grafo(const Grafo< V, A >& orig);

    // Destructor
    ~Grafo();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el grafo.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por valor para que NO pueda ser modificado.
    V operator[](int idVrt) const;

    // REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
    // EFE: retorna los datos de la adyacencia entre <idVrtO, idVrtD>.
    // NOTA: retorna por valor para que NO pueda ser modificado.    
    A obtDatoAdy(int idVrtO, int idVrtD) const;

    // EFE: retorna el total de arcos o adyacencias en el grafo.
    int obtTotArc() const;

    // EFE: retorna el total de vértices en el grafo.
    int obtTotVrt() const;

    /* MÉTODOS OBSERVADORES NO BÁSICOS*/

    // REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
    // EFE: retorna en "camino" los índices de los vértices que conforman el
    //      camino más corto entre idVrtO y idVrtD.
    void caminoMasCorto(int idVrtO, int idVrtD, vector< int >& camino) const;

    /* MÉTODOS MODIFICADORES BÁSICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    V& operator[](int idVrt);

    // REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
    // EFE: asigna el valor "a" a la adyacencia <idVrtO, idVrtD>.
    void asgDatoAdy(int idVrtO, int idVrtD, const A& a);

private:

    template < typename W >
    struct Vrt {
        W w;
        list< int > lstAdy;

        Vrt< W >() : w(W()), lstAdy() {
        }; // constructor estándar de Vrt

        Vrt< W >(const W& ww) : w(ww), lstAdy() {
        }; // constructor con dato de vértice

        Vrt< W >(const Vrt< W >& vrt) : w(vrt.w), lstAdy(vrt.lstAdy) {
        }; // constructor de copias de Vrt
    };

    // REQ: (f >= 0) && (c >= 0) && (N > 0)
    // RET: valor único asociado a f, c y N.

    static long fIdUnico(int f, int c, int N) {
        return ((f == c) ? 0 : (f + c + N * (3 + abs(f - c))));
    };

    // RET: true si falta algún nodo por visitar y false en caso contrario.
    bool faltanPorVisitar(vector< bool >& v) const;

    vector< Vrt< V > > vectorVrts; // vector de vértices
    map< long, A > mapAdys; // map de adyacencias
};

template < typename V, typename A >
Grafo< V, A >::Grafo(int cantidadVrt, double probabilidadAdy) {
    vectorVrts.resize(cantidadVrt, V());

    srand(time(NULL)); /* initialize random seed: */
    for (int i = 0; i < cantidadVrt; i++)
        for (int j = i + 1; j < cantidadVrt; j++)
            if ((rand() % 1000) / 1000.0 < probabilidadAdy) {
                vectorVrts[i].lstAdy.push_front(j);
                vectorVrts[j].lstAdy.push_front(i);
                long idUnico = fIdUnico(i, j, cantidadVrt);
                //mapAdys[idUnico] = A();
                mapAdys.insert(typename map< long, A >::value_type(idUnico, A()));
            }
}

template < typename V, typename A >
Grafo< V, A >::Grafo(ifstream& archivo) {
    int x; // entero que se lee del archivo
    int f = 0; // número de fila
    char finLinea = ' ';

    archivo >> x; // se lee la cantidad de nodos
    vectorVrts.resize(x, Vrt< V >());

    archivo >> x;
    while (!archivo.eof()) {
        while (!archivo.eof()&&(finLinea != 10)) { // 10 ascii de fin de línea
            vectorVrts[f].lstAdy.push_back(x);
            archivo >> x;
            archivo.get(); // consume un blanco
            finLinea = archivo.peek(); // intenta leer fin de línea
        }
        if (!archivo.eof()) {
            vectorVrts[f].lstAdy.push_back(x);
        }
        f++; // se incrementa el índice de fila
        archivo >> x;
        archivo.get(); // consume un blanco final en la fila actual
        finLinea = archivo.peek(); // consume el cambio de línea
    }
}

template < typename V, typename A >
Grafo< V, A >::Grafo(const Grafo< V, A >& orig) : vectorVrts(orig.vectorVrts), mapAdys(orig.mapAdys) {

}

template < typename V, typename A >
Grafo< V, A >::~Grafo() {
}

template < typename V, typename A >
bool Grafo< V, A >::xstVrt(int idVrt) const {
    return idVrt < vectorVrts.size();
}

template < typename V, typename A >
bool Grafo< V, A >::xstAdy(int idVrtO, int idVrtD) const {
    return xstVrt(idVrtO)
            && xstVrt(idVrtD)
            && (find(vectorVrts.at(idVrtO).lstAdy.begin(), vectorVrts.at(idVrtO).lstAdy.end(), idVrtD) != vectorVrts.at(idVrtO).lstAdy.end())
            && (find(vectorVrts.at(idVrtD).lstAdy.begin(), vectorVrts.at(idVrtD).lstAdy.end(), idVrtO) != vectorVrts.at(idVrtD).lstAdy.end());
}

template < typename V, typename A >
void Grafo< V, A >::obtIdVrtAdys(int idVrt, vector< int >& rspRetornar) const {
    vector< int > rsp;
    for (typename list< V >::const_iterator itr = vectorVrts.at(idVrt).lstAdy.begin(); itr != vectorVrts.at(idVrt).lstAdy.end(); itr++)
        rsp.push_back(*itr);
    rspRetornar = rsp;
}

template < typename V, typename A >
V Grafo< V, A >::operator[](int idVrt) const {
    return vectorVrts[idVrt].w;
}

template < typename V, typename A >
A Grafo< V, A >::obtDatoAdy(int idVrtO, int idVrtD) const {
    int N = vectorVrts.size();
    long valorUnico = fIdUnico(idVrtO, idVrtD, N);
    return mapAdys.at(valorUnico);
}

template < typename V, typename A >
int Grafo< V, A >::obtTotArc() const {
    int rsl = 0;
    for (typename vector< Vrt< V > >::const_iterator itr = vectorVrts.begin(); itr != vectorVrts.end(); itr++)
        rsl = rsl + itr->lstAdy.size();
    return rsl / 2;
}

template < typename V, typename A >
int Grafo< V, A >::obtTotVrt() const {
    return vectorVrts.size();
}

template < typename V, typename A >
V& Grafo< V, A >::operator[](int idVrt) {
    return vectorVrts[idVrt].w;
}

template < typename V, typename A >
bool Grafo< V, A >::faltanPorVisitar(vector<bool>& v) const {
    bool rsl = true;
    int i = 0;
    while (i < vectorVrts.size() && ( rsl = v[i] )) 
        i++;
    return !rsl;
}

template < typename V, typename A >
void Grafo< V, A >::caminoMasCorto(int idVrtO, int idVrtD, vector< int >& camino) const {
    // Basado en algoritmo de Dijkstra: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
    vector< bool > visitado(vectorVrts.size(), false); // visitados[idVrt] == true indica que idVrt ha sido visitado
    vector< int > distancia(vectorVrts.size(), INT_MAX); // distancia[idVrt] representa la menor distancia encontrada de idVrtO a idVrt
    vector< int > antecesor(vectorVrts.size(), -1); // antecesor[idVrt] representa el antecesor a idVrt en el camino más corto de idVrtO a idVrt
    int idVrtActual = idVrtO;
    distancia[idVrtActual] = 0;
    while (faltanPorVisitar(visitado) && !visitado[idVrtD] && idVrtActual >= 0) {
        for (list< int >::const_iterator itr = vectorVrts[idVrtActual].lstAdy.begin(); itr != vectorVrts[idVrtActual].lstAdy.end(); itr++)
            if (!visitado[*itr] && (distancia[*itr] > distancia[idVrtActual] + 1)) {
                // se modifica la distancia de idVrtAdyacente al idVrtActual porque es menor la distancia a través de idVrtActual
                distancia[*itr] = distancia[idVrtActual] + 1;
                antecesor[*itr] = idVrtActual; // consecuentemente se cambia el antecesor;
            }
        visitado[idVrtActual] = true;
        
        if (idVrtActual != idVrtD) { // Encuentra el más cercano no visitado todavía:
            int idVrtNuevo = -1; // para indicar que no se pudo encontrar un vértice no visitado más cercano ==> no existe camino entre idVrtO e idVrtD
            int menorDistancia = INT_MAX;
            for (int i = 0; i < vectorVrts.size(); i++)
                if (!visitado[i] && (distancia[i] < menorDistancia)){
                    idVrtNuevo = i;
                    menorDistancia = distancia[i];
                }
            idVrtActual = idVrtNuevo;
        }
    }
    if (visitado[idVrtD]){ // se asignan los idVrt a camino
        int idVrtVisitado = idVrtD;
        camino.push_back(idVrtD);
        for(int i = 0; i < distancia[idVrtD] - 1; i++){
            camino.push_back(antecesor[idVrtVisitado]);
            idVrtVisitado = antecesor[idVrtVisitado];
        }
        camino.push_back(idVrtO); // para completar el camino
        reverse(camino.begin(),camino.end());
    } 
}

template < typename V, typename A >
void Grafo< V, A >::asgDatoAdy(int idVrtO, int idVrtD, const A& a) {
    int idUnico = fIdUnico(idVrtO, idVrtD, vectorVrts.size());
    mapAdys[idUnico] = a;
}
#endif /* GRAFO_H */

