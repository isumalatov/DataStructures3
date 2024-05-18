#include "tavlcalendario.h"

TNodoAVL::TNodoAVL()
{
    item = TCalendario();
    iz = TAVLCalendario();
    de = TAVLCalendario();
    fe = 0;
}

TNodoAVL::TNodoAVL(const TNodoAVL &n)
{
    item = n.item;
    iz = n.iz;
    de = n.de;
    fe = n.fe;
}

TNodoAVL::~TNodoAVL()
{
    item = TCalendario();
    iz.~TAVLCalendario();
    de.~TAVLCalendario();
    fe = 0;
}

TNodoAVL &TNodoAVL::operator=(const TNodoAVL &n)
{
    if (this != &n)
    {
        (*this).~TNodoAVL();
        item = n.item;
        iz = n.iz;
        de = n.de;
        fe = n.fe;
    }
    return *this;
}

// =================================================================
// =================================================================

TAVLCalendario::TAVLCalendario()
{
    raiz = NULL;
}

TAVLCalendario::TAVLCalendario(const TAVLCalendario &arbol)
{
    if (arbol.raiz != NULL)
    {
        TNodoAVL *aux = new TNodoAVL();
        aux->item = arbol.raiz->item;
        this->raiz = aux;
        this->raiz->iz = TAVLCalendario(arbol.raiz->iz);
        this->raiz->de = TAVLCalendario(arbol.raiz->de);
    }
    else
        raiz = NULL;
}

TAVLCalendario::~TAVLCalendario()
{
    if (raiz != NULL)
    {
        delete raiz;
        raiz = NULL;
    }
}

TAVLCalendario &TAVLCalendario::operator=(const TAVLCalendario &arbol)
{
    if (this != &arbol)
    {
        this->~TAVLCalendario();
        if (arbol.raiz != NULL)
        {
            TNodoAVL *aux = new TNodoAVL();
            aux->item = arbol.raiz->item;
            this->raiz = aux;
            this->raiz->iz = TAVLCalendario(arbol.raiz->iz);
            this->raiz->de = TAVLCalendario(arbol.raiz->de);
        }
        else
            raiz = NULL;
    }
    return *this;
}

bool TAVLCalendario::operator==(const TAVLCalendario &arbol) const
{
    if (raiz == NULL && arbol.raiz == NULL)
        return true;
    if (raiz != NULL && arbol.raiz != NULL)
    {
        if (raiz->item == arbol.raiz->item)
        {
            return raiz->iz == arbol.raiz->iz && raiz->de == arbol.raiz->de;
        }
    }
    return false;
}

bool TAVLCalendario::operator!=(const TAVLCalendario &arbol) const
{
    return !(*this == arbol);
}

bool TAVLCalendario::EsVacio() const
{
    return raiz == NULL;
}

bool TAVLCalendario::Buscar(const TCalendario &cal) const
{
    if (raiz != NULL)
    {
        if (raiz->item == cal)
            return true;
        if (raiz->item > cal)
            return raiz->iz.Buscar(cal);
        if (raiz->item < cal)
            return raiz->de.Buscar(cal);
    }
    return false;
}

int TAVLCalendario::Altura() const
{
    if (raiz != NULL)
    {
        int iz = raiz->iz.Altura();
        int de = raiz->de.Altura();
        return (1 + (iz > de ? iz : de));
    }
    return 0;
}

int TAVLCalendario::Nodos() const
{
    if (raiz != NULL)
    {
        return 1 + raiz->iz.Nodos() + raiz->de.Nodos();
    }
    return 0;
}

int TAVLCalendario::NodosHoja() const
{
    if (raiz != NULL)
    {
        if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL)
            return 1;
        return raiz->iz.NodosHoja() + raiz->de.NodosHoja();
    }
    return 0;
}

TCalendario TAVLCalendario::Raiz() const
{
    if (raiz != NULL)
        return raiz->item;
    return TCalendario();
}

void TAVLCalendario::InordenAux(TVectorCalendario &vector, int &pos) const
{
    if (raiz != NULL)
    {
        raiz->iz.InordenAux(vector, pos);
        vector[pos] = raiz->item;
        pos++;
        raiz->de.InordenAux(vector, pos);
    }
}

TVectorCalendario TAVLCalendario::Inorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    InordenAux(vector, pos);
    return vector;
}

void TAVLCalendario::PreordenAux(TVectorCalendario &vector, int &pos) const
{
    if (raiz != NULL)
    {
        vector[pos] = raiz->item;
        pos++;
        raiz->iz.PreordenAux(vector, pos);
        raiz->de.PreordenAux(vector, pos);
    }
}

TVectorCalendario TAVLCalendario::Preorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    PreordenAux(vector, pos);
    return vector;
}

void TAVLCalendario::PostordenAux(TVectorCalendario &vector, int &pos) const
{
    if (raiz != NULL)
    {
        raiz->iz.PostordenAux(vector, pos);
        raiz->de.PostordenAux(vector, pos);
        vector[pos] = raiz->item;
        pos++;
    }
}

TVectorCalendario TAVLCalendario::Postorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    PostordenAux(vector, pos);
    return vector;
}














