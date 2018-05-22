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
#include <stdlib.h>     /* srand, rand */
#include <iostream>
using namespace std;

#include "Laberinto.h"

class Hormiga {
public:
    
    // EFE: construye un hormiga en el nido y con destino == nodoFinal.
    Hormiga();
    
    // EFE: construye una copia idéntica e independiente de orig.
    Hormiga(const Hormiga& orig);
    
    virtual ~Hormiga();

    /* OBSERVADORES */
    //int obtIdVrtActual();
    //vector< int > obtMemoria();
    
    // EFE: retorna true si la hormiga ya salió del vértice inicial.
    bool salio();
    
    // EFE: retorna true si la hormiga ya regresó al vértice inicial después de encontrar el vértice final.
    bool regreso();
    
    // EFE: retorna 'F' o 'I' para indicar hacia adónde se dirige
    char obtDestino();
    
    // EFE: retorna la longitud de la solución encontrada por la hormiga.
    //int obtLongitudSolucion();
    
    //double obtDeltaFerormona();

    /* MODIFICADORES */

    // REQ: idVrtN sea válido en el laberinto que está recorriendo la hormiga.
    //void asgIdVrtActual(int idVrtActualN);

    // REQ: idVrtN sea válido en el laberinto que está recorriendo la hormiga.
    // EFE: asigna idVrtN como parte de la memoria de recorrido de la hormiga.
    //void agrIdVrtMemoria(int idVrtN);

    // EFE: activa la hormiga y la ubica en nodoInicial.
    void salir(int idVrtInicial);

    // REQ: nd == 'F' || nd == 'I'
    //void asgDestino(char nd);
    //void asgRetroceso(int nr);
    //void asgDeltaFerormona(double ndf);
    
    // REQ: que la hormiga (*this) esté activa.
    // EFE: la hormiga avanza a un vértice adyacente.
    void mover(const Laberinto& lbrt);

    // EFE: asigna la referencia al laberinto que accesarán todas las hormigas.
    static void asgLaberinto(Laberinto& lbrt);

private:
    /* VARIABLES STATIC PRIVADAS PARA ACCESO AL LABERINTO */
    static Laberinto* laberinto_p;
    
    /* MÉTODOS PRIVADOS */

    // REQ: memoria.size() > 0.
    // RET: la posición anterior en la memoria de la hormiga cuando retrocede.
    int retroceder();
    
    // EFE: retorna -1 en caso de que no la hormiga llegue a camino sin salida,
    // y un idVrt válido en caso de que la hormiga pueda continuar.
    int seleccionaAdyMasCargada(const Laberinto& lbrt);

    // REQ: que los idVrt en vrtsPosibles sean índices válidos de vértices en el laberinto que está recorriendo la hormiga.
    // EFE: elimina de vrtsPosibles los idVrt que ya aparecen en la memoria.
    void filtraVrtsPosibles(vector< int >& vrtsPosibles);

    // RET: true si idVrt está en memoria y false en caso contrario.
    bool estaEnMemoria(int idVrt);
    
    /* atributos privados: */
    int idVrtActual; // idVrt del vértice donde se encuentra la hormiga actualmente
    vector< int > memoria; // vector de idVrt que representa el recorrido de la hormiga
    bool haSalido; // false mientras no haya salido, true si ya salió
    bool haRegresado; // false mientras no haya regresado de idVrtFinal a idVrtInicial
    char destino; // "F"o "I", hacia adónde se dirige la hormiga
    int enRetroceso; // si es mayor a cero, la hormiga está retrocediendo esta cantidad de pasos porque topó con un camino sin salida
    int longitudSolucion; // registra la longitud de la solución encontrada para moderar su aporte de ferormona en su retorno
    double deltaFerormona; // representa cuánta ferormona aporta la hormiga a cada link y se modula con base en length_solución x encuentros
};
#endif /* HORMIGA_H */

