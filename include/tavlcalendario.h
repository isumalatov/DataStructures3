#ifndef TAVLCALENDARIO_H
#define TAVLCALENDARIO_H

#include <iostream>
#include "tcalendario.h"
#include "tvectorcalendario.h"

using namespace std;

class TNodoAVL;

class TAVLCalendario
{
    friend class TNodoAVL;
    friend ostream &operator<<(ostream &, const TAVLCalendario &);

private:
    TNodoAVL *raiz;
    void InordenAux(TVectorCalendario &, int &) const;
    void PreordenAux(TVectorCalendario &, int &) const;
    void PostordenAux(TVectorCalendario &, int &) const;
    int nodoFE() const;
    void actualizarArbolFE();
    void arreglarArbol();
    void rotacionII();
    void rotacionDD();
    void rotacionID();
    void rotacionDI();
    void handleNodeDeletion();
    void replaceWithInorderPredecessor();

public:
    TAVLCalendario();
    TAVLCalendario(const TAVLCalendario &);
    ~TAVLCalendario();
    TAVLCalendario &operator=(const TAVLCalendario &);
    bool operator==(const TAVLCalendario &) const;
    bool operator!=(const TAVLCalendario &) const;
    bool EsVacio() const;
    bool Insertar(const TCalendario &);
    bool Borrar(const TCalendario &);
    bool Buscar(const TCalendario &) const;
    int Altura() const;
    int Nodos() const;
    int NodosHoja() const;
    TVectorCalendario Inorden() const;
    TVectorCalendario Preorden() const;
    TVectorCalendario Postorden() const;
    TCalendario Raiz() const;
};

class TNodoAVL
{
    friend class TAVLCalendario;

private:
    TCalendario item;
    TAVLCalendario iz, de;
    int fe;

public:
    TNodoAVL();
    TNodoAVL(const TNodoAVL &);
    ~TNodoAVL();
    TNodoAVL &operator=(const TNodoAVL &);
};

#endif
