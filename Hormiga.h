/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hormiga.h
 * Author: Alan
 *
 * Created on 7 de febrero de 2018, 05:53 PM
 */

#ifndef HORMIGA_H
#define HORMIGA_H

#include <vector>
#include <algorithm>    // std::remove_if
using namespace std;

class Hormiga {
public:
    Hormiga();
    Hormiga(const Hormiga& orig);
    virtual ~Hormiga();

    /* OBSERVADORES */
    int obtIdVrtActual();
    vector< int > obtMemoria();
    bool salio();
    char obtDestino();
    int obtDireccion();
    int obtLongitudSolucion();
    double obtDeltaFerormona();

    /* MODIFICADORES */

    // REQ: idVrtN sea válido en el laberinto que está recorriendo la hormiga.
    void asgIdVrtActual(int idVrtActualN);

    // REQ: idVrtN sea válido en el laberinto que está recorriendo la hormiga.
    // EFE: asigna idVrtN como parte de la memoria de recorrido de la hormiga.
    void agrIdVrtMemoria(int idVrtN);

    // EFE: salio = false.
    void sale();

    // REQ: nd == 'F' || nd == 'I'
    void asgDestino(char nd);
    void asgRetroceso(int nr);
    void asgDeltaFerormona(double ndf);

    /* MÉTODOS AUXILIARES */
    // REQ: que los idVrt en vrtsPosibles sean índices válidos de vértices en el laberinto que está recorriendo la hormiga.
    // EFE: elimina de vrtsPosibles los idVrt que ya aparecen en la memoria.
    void filtraVrtsPosibles(vector< int >& vrtsPosibles);

private:

    int idVrtActual; // idVrt del vértice donde se encuentra la hormiga actualmente
    vector< int > memoria; // vector de idVrt que representa el recorrido de la hormiga
    bool haSalido; // false mientras no haya salido, true si ya salió
    char destino; // "F"o "I", hacia adónde se dirige la hormiga
    int enRetroceso; // si es mayor a cero indica que la hormiga está en retroceso porque topó con un camino sin salida
    int longitudSolucion; // registra la longitud de la solución encontrada para moderar su aporte de ferormona en su retorno
    double deltaFerormona; // representa cuánta ferormona aporta la hormiga a cada link y se modula con base en length_solución x encuentros

    // RET: true si idVrt está en memoria y false en caso contrario.
    bool estaEnMemoria(int idVrt);
};
#endif /* HORMIGA_H */

