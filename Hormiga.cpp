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

//int Hormiga::obtIdVrtActual() {
//    return idVrtActual;
//}

//vector< int > Hormiga::obtMemoria() {
//    return memoria;
//}

bool Hormiga::salio() {
    return haSalido;
}

bool Hormiga::regreso() {
    return haRegresado;
}

char Hormiga::obtDestino() {
    return destino;
}

//int Hormiga::obtLongitudSolucion() {
//    return longitudSolucion;
//}
//
//double Hormiga::obtDeltaFerormona() {
//    return deltaFerormona;
//}

/* MODIFICADORES */

//void Hormiga::asgIdVrtActual(int idVrtActualN) {
//    idVrtActual = idVrtActualN;
//}
//
//void Hormiga::agrIdVrtMemoria(int idVrtN) {
//    memoria.push_back(idVrtN);
//}

void Hormiga::salir(int idVrtInicial) {
    haSalido = true;
    idVrtActual = idVrtInicial;
}

//void Hormiga::asgDestino(char nd) {
//    destino = nd;
//}
//
//void Hormiga::asgRetroceso(int nr) {
//    enRetroceso = nr;
//}
//
//void Hormiga::asgDeltaFerormona(double ndf) {
//    deltaFerormona = ndf;
//}

void Hormiga::mover(const Laberinto& lbrt) {
    if (enRetroceso > 0) // verifica si la hormiga está en retroceso
        idVrtActual = retroceder();
    else if (destino == 'F') // verifica si la hormiga va hacia el objetivo
        if (idVrtActual == lbrt.obtIdVrtFinal()) { // verifica si la hormiga llegó al destino
            destino = 'I'; // comienza su viaje determinístico de regreso marcando con ferormona
            longitudSolucion = memoria.size(); // guarda al longitud de la solución encontrada para modular ferormona
            deltaFerormona = 1.0 / longitudSolucion; // cantidad de ferormona con que va a marcar su ruta de regreso
            memoria.pop_back(); // se alista para retornar quitando de la memoria el idVrt destino
        } else { // no ha llegado todavía debe avanzar hacia 'F'.
            int idVrtNuevo = seleccionaAdyMasCargada(lbrt);
            if (idVrtNuevo != -1) { // la hormiga puede seguir adelante
                idVrtActual = idVrtNuevo;
                memoria.push_back(idVrtActual);
            } else { // la hormiga topa con camino sin salida, debe retroceder
                enRetroceso = 1 + rand() % (memoria.size() - 1);
                idVrtActual = retroceder();
            }
        } else { // la hormiga va hacia el nido determinísticamente marcando con ferormona
        if (idVrtActual == lbrt.obtIdVrtInicial())
            haRegresado = true; // la hormiga llegó al nido después de pasar por el vértice objetivo
        else { // se supone que la memoria no se ha terminado
            int idVrtNuevoDeRegreso = memoria.back();
            memoria.pop_back();
            Adyacencia ady = lbrt.obtDatoAdy(idVrtActual, idVrtNuevoDeRegreso); // accede la adyacencia
            ady.asgCntFerormona(ady.obtCntFerormona() + deltaFerormona); // incrementa la ferormona
            idVrtActual = idVrtNuevoDeRegreso; // se traslada a nuevo vértice en ruta de regreso al nido
        }
    }
}

void Hormiga::filtraVrtsPosibles(vector< int >& vrtsPosibles) {
    // USO DE UNA LAMBDA!! [contexto](parámetros){predicado}: acá el contexto es un objeto Hormiga, el parámetro es un entero en la memoria.
    vector< int >::iterator itr = remove_if(vrtsPosibles.begin(), vrtsPosibles.end(), [this](int i) {
        return estaEnMemoria(i);
    });
}

/* MÉTODOS PRIVADOS */

bool Hormiga::estaEnMemoria(int idVrt) {
    return this->memoria.end() != find(this->memoria.begin(), this->memoria.end(), idVrt);
};

int Hormiga::retroceder() {
    int idVrtNuevoEnRetroceso = memoria.back();
    memoria.pop_back();
    if (idVrtActual == idVrtNuevoEnRetroceso){ // está empezando a retroceder
        if (memoria.size() > 0) {
            idVrtNuevoEnRetroceso = memoria.back();
            enRetroceso--;
        }               
    } else // ya ha retrocedido al menos una posición antes
        enRetroceso--;
    return idVrtNuevoEnRetroceso;
}

int Hormiga::seleccionaAdyMasCargada(const Laberinto& lbrt) {
    vector< int > adys;
    lbrt.obtIdVrtAdys(idVrtActual, adys);
    // falta filtrar las adyacencias que llevan a vértices ya recorridos
    // falta seleccionar la adyacencia más cargada de entre las filtradas,
    // recordar que en esta selección se usa azar también --> to-report l-selecciona-por-valoracion [ posibles ]
}