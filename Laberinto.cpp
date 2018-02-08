/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Laberinto.cpp
 * Author: Alan
 * 
 * Created on 7 de febrero de 2018, 04:46 PM
 */

#include "Laberinto.h"

Laberinto::Laberinto(int cantidadVrts, double probabilidadAdy) : laberintoPtr(shared_ptr< Grafo< int, Adyacencia > >(new Grafo< int, Adyacencia>(cantidadVrts, probabilidadAdy))), idVrtInicial(0), idVrtFinal(0), cntVrts(cantidadVrts), laberinto(*laberintoPtr) {
}

Laberinto::Laberinto(ifstream& archivo) : laberintoPtr(shared_ptr< Grafo< int, Adyacencia > >(new Grafo< int, Adyacencia>(archivo))), laberinto(*laberintoPtr), idVrtInicial(0), idVrtFinal(0) {
}

Laberinto::Laberinto(const Laberinto& orig) : laberintoPtr(shared_ptr< Grafo< int, Adyacencia > >(new Grafo< int, Adyacencia>(*orig.laberintoPtr))), cntVrts(orig.cntVrts), idVrtInicial(orig.idVrtInicial), idVrtFinal(orig.idVrtFinal), laberinto(*laberintoPtr) {
}

Laberinto::~Laberinto() {
}

/* MÉTODOS OBSERVADORES BÁSICOS */

// EFE: retorna true si 0 <= idVrt < N.
// NOTA: idNdo significa "identificador de vértice".
bool Laberinto::xstVrt(int idVrt) const {
    return laberinto.xstVrt(idVrt);
}

// REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
// EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
bool Laberinto::xstAdy(int idVrtO, int idVrtD) const {
    return laberinto.xstAdy(idVrtO, idVrtD);
}

int Laberinto::obtIdVrtInicial() {
    return idVrtInicial;
}

int Laberinto::obtIdVrtFinal() {
    return idVrtFinal;
}

// REQ: 0 <= idVrt < N.
// EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
// adyacentes a idVrt en el grafo.
void Laberinto::obtIdVrtAdy(int idVrt, vector< int >& rsp) const {
    laberinto.obtIdVrtAdy(idVrt, rsp);
}

// REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
// EFE: retorna los datos de la adyacencia entre <idVrtO, idVrtD>.
// NOTA: retorna por valor para que NO pueda ser modificado.    
Adyacencia Laberinto::obtDatoAdy(int idVrtO, int idVrtD) const {
    return laberinto.obtDatoAdy(idVrtO, idVrtD);
}

// EFE: retorna el total de arcos o adyacencias en el grafo.
int Laberinto::obtTotArc() const {
    laberinto.obtTotArc();
}

// EFE: retorna el total de vértices en el grafo.
int Laberinto::obtTotVrt() const {
    laberinto.obtTotVrt();
}

/* MÉTODOS OBSERVADORES NO BÁSICOS*/

// REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
// EFE: retorna en "camino" los índices de los vértices que conforman el
//      camino más corto entre idVrtO y idVrtD.
void Laberinto::caminoMasCorto(int idVrtO, int idVrtD, vector< int >& camino) const {
    laberinto.caminoMasCorto(idVrtO, idVrtD, camino);
}

/* MÉTODOS MODIFICADORES BÁSICOS */

// REQ: 0 <= idVrtInicialN < N
// EFE: asigna el identificador del vértice inicial del laberinto.
void Laberinto::asgVrtInicial(int idVrtInicialN) {
    idVrtInicial = idVrtInicialN;
}

// REQ: 0 <= idVrtFinalN < N
// EFE: asigna el identificador del vértice inicial del laberinto.    
void Laberinto::asgVrtFinal(int idVrtFinalN) {
    idVrtFinal = idVrtFinalN;
}

// REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
// EFE: asigna el valor "ady" a la adyacencia <idVrtO, idVrtD>.
void Laberinto::asgDatoAdy(int idVrtO, int idVrtD, const Adyacencia& ady) {
    laberinto.asgDatoAdy(idVrtO, idVrtD, ady);
}