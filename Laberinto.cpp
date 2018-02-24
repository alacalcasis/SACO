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
bool Laberinto::xstVrt(int idVrt) const {
    return laberinto.xstVrt(idVrt);
}

bool Laberinto::xstAdy(int idVrtO, int idVrtD) const {
    return laberinto.xstAdy(idVrtO, idVrtD);
}

int Laberinto::obtIdVrtInicial() const {
    return idVrtInicial;
}

int Laberinto::obtIdVrtFinal() const {
    return idVrtFinal;
}

void Laberinto::obtIdVrtAdys(int idVrt, vector< int >& rsp) const {
    laberinto.obtIdVrtAdys(idVrt, rsp);
}

Adyacencia Laberinto::obtDatoAdy(int idVrtO, int idVrtD) const {
    return laberinto.obtDatoAdy(idVrtO, idVrtD);
}

int Laberinto::obtTotArc() const {
    laberinto.obtTotArc();
}

int Laberinto::obtTotVrt() const {
    laberinto.obtTotVrt();
}

void Laberinto::caminoMasCorto(int idVrtO, int idVrtD, vector< int >& camino) const {
    laberinto.caminoMasCorto(idVrtO, idVrtD, camino);
}

double Laberinto::sumaTotalFerormona() const {
    double suma = 0.0;
    for (int i = 0; i < cntVrts; i++) {
        vector<int> adyacenciasI;
        laberinto.obtIdVrtAdys(i, adyacenciasI);
        for (int j = 0; j < adyacenciasI.size(); j++)
            suma += laberinto.obtDatoAdy(i, adyacenciasI[j]).obtCntFerormona();
    }
    return suma;
}

void Laberinto::asgVrtInicial(int idVrtInicialN) {
    idVrtInicial = idVrtInicialN;
}

void Laberinto::asgVrtFinal(int idVrtFinalN) {
    idVrtFinal = idVrtFinalN;
}

void Laberinto::asgDatoAdy(int idVrtO, int idVrtD, const Adyacencia& ady) {
    laberinto.asgDatoAdy(idVrtO, idVrtD, ady);
}

void Laberinto::decrementarFerormonaAdys(double decrFerormona) {
    for (int i = 0; i < cntVrts; i++) {
        vector<int> adyacenciasI;
        laberinto.obtIdVrtAdys(i, adyacenciasI);
        for (int j = 0; j < adyacenciasI.size(); j++) {
            Adyacencia adyI = laberinto.obtDatoAdy(i, adyacenciasI[j]);
            adyI.asgCntFerormona(adyI.obtCntFerormona() * decrFerormona);
            laberinto.asgDatoAdy(i, adyacenciasI[j], adyI);
        }
    }
}

void Laberinto::actualizarValoracionAdys() {
    double sumatoriaFerormona = sumaTotalFerormona();
    if (sumatoriaFerormona > 0)
        for (int i = 0; i < cntVrts; i++) {
            vector<int> adyacenciasI;
            laberinto.obtIdVrtAdys(i, adyacenciasI);
            for (int j = 0; j < adyacenciasI.size(); j++) {
                Adyacencia adyI = laberinto.obtDatoAdy(i, adyacenciasI[j]);
                adyI.asgValoracion(adyI.obtCntFerormona() / sumatoriaFerormona);
                laberinto.asgDatoAdy(i, adyacenciasI[j], adyI);
            }
        }
}