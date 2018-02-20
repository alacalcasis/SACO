/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Simulador.cpp
 * Author: Alan
 * 
 * Created on 19 de febrero de 2018, 02:53 PM
 */

#include "Simulador.h"

Simulador::Simulador(Laberinto& lbr): laberinto(lbr), decrFerormona(0.0), probMovimientoAzar(0.0) {
}

Simulador::Simulador(const Simulador& orig): laberinto(*(new Laberinto(orig.laberinto))) {
}

Simulador::~Simulador() {
}

void Simulador::iniciar(int idVrtInicial, int idVrtFinal, int cntHrm, double decrFerormona, double probMovimientoAzar) {
    laberinto.asgVrtInicial(idVrtInicial);
    laberinto.asgVrtFinal(idVrtFinal);
    hormigas.resize(cntHrm, Hormiga());
    this->decrFerormona = decrFerormona;
    this->probMovimientoAzar = probMovimientoAzar;
}

void Simulador::ejecutar(int p) {
    int iteracion = 0;
    int cntdHormigasActivas = 0;
    int cntdHormigasSinRegresar = hormigas.size();
    while ((p > 0)&&(iteracion < p)||(cntdHormigasSinRegresar > 0)) {
        // Si hay hormigas que no han salido del hormiguero, sacarlas:
        if (cntdHormigasActivas < hormigas.size()){
            hormigas[cntdHormigasActivas].salir(laberinto.obtIdVrtInicial());
            cntdHormigasActivas++;
        }
        
        // Mover a todas las hormigas un paso:
        for(int i = 0; i < cntdHormigasActivas; i++)
            hormigas[i].mover(laberinto); // h-caminar-morir
       
        // Decrementar la cantidad de ferormona en todas las adyacencias del laberinto:
        laberinto.decrementarFerormonaAdys(decrFerormona); // ask links [ set cnt_ferormona cnt_ferormona * dec_ferormona ]
        
        // Actualizar valoración de las adyacencias:
        laberinto.actualizarValoracionAdys();
        
        // Contar cuántas hormigas aún no han regresado al idVrtInicial o nido:
        // USO DE LAMBDA!! [contexto](parámetros){predicado}: acá el contexto es hormigas y el parámetro es el índice
        cntdHormigasSinRegresar = count_if(hormigas.begin(), hormigas.end(), [](Hormiga h){return h.obtDestino() == 'F';});
    }
}