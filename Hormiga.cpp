/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hormiga.cpp
 * Author: Alan
 * 
 * Created on 7 de febrero de 2018, 05:53 PM
 */

#include "Hormiga.h"

Hormiga::Hormiga() : haSalido(false), destino('F'), enRetroceso(0), longitudSolucion(0), deltaFerormona(0.0) {
}

Hormiga::Hormiga(const Hormiga& orig) : haSalido(orig.haSalido), destino(orig.destino), enRetroceso(orig.enRetroceso), longitudSolucion(orig.longitudSolucion), deltaFerormona(orig.deltaFerormona) {
}

Hormiga::~Hormiga() {
}

/* OBSERVADORES */
vector< int > Hormiga::obtMemoria() {
    return memoria;
}

bool Hormiga::salio() {
    return haSalido;
}

char Hormiga::obtDestino() {
    return destino;
}

int Hormiga::obtDireccion() {
    return enRetroceso;
}

int Hormiga::obtLongitudSolucion() {
    return longitudSolucion;
}

double Hormiga::obtDeltaFerormona() {
    return deltaFerormona;
}

/* MODIFICADORES */

// REQ: idVrtN sea válido en el laberinto que está recorriendo la hormiga.
// EFE: asigna idVrtN como parte de la memoria de recorrido de la hormiga.

void Hormiga::agrIdVrtMemoria(int idVrtN) {
    memoria.push_back(idVrtN);
}

// EFE: salio = false.

void Hormiga::sale() {
    haSalido = true;
}

void Hormiga::asgDestino(char nd) {
    destino = nd;
}

void Hormiga::asgRetroceso(int nr) {
    enRetroceso = nr;
}

void Hormiga::asgDeltaFerormona(double ndf) {
    deltaFerormona = ndf;
}