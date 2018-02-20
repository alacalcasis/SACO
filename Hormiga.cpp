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

Hormiga::Hormiga() : idVrtActual(0), haSalido(false), haRegresado(false), destino('F'), enRetroceso(0), longitudSolucion(0), deltaFerormona(0.0) {
}

Hormiga::Hormiga(const Hormiga& orig) : haSalido(orig.haSalido), haRegresado(orig.haRegresado), destino(orig.destino), enRetroceso(orig.enRetroceso), longitudSolucion(orig.longitudSolucion), deltaFerormona(orig.deltaFerormona) {
}

Hormiga::~Hormiga() {
}

/* OBSERVADORES */

int Hormiga::obtIdVrtActual() {
    return idVrtActual;
}

vector< int > Hormiga::obtMemoria() {
    return memoria;
}

bool Hormiga::salio() {
    return haSalido;
}

bool Hormiga::regreso(){
    return haRegresado;
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

void Hormiga::asgIdVrtActual(int idVrtActualN) {
    idVrtActual = idVrtActualN;
}

void Hormiga::agrIdVrtMemoria(int idVrtN) {
    memoria.push_back(idVrtN);
}

void Hormiga::salir(int idVrtInicial) {
    haSalido = true;
    idVrtActual = idVrtInicial;
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

void Hormiga::mover(const Laberinto& lbrt){
    
}

void Hormiga::filtraVrtsPosibles(vector< int >& vrtsPosibles) {
    // USO DE UNA LAMBDA!! [contexto](parámetros){predicado}: acá el contexto es un objeto Hormiga, el parámetro es un entero en la memoria.
    vector< int >::iterator itr = remove_if(vrtsPosibles.begin(), vrtsPosibles.end(), [this](int i){return estaEnMemoria(i);});
}

/* MÉTODOS PRIVADOS */

bool Hormiga::estaEnMemoria(int idVrt) {
    return this->memoria.end() != find(this->memoria.begin(), this->memoria.end(), idVrt);
};

