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

int TAVLCalendario::nodoFE() const
{
    return raiz->de.Altura() - raiz->iz.Altura();
}

void TAVLCalendario::actualizarArbolFE()
{
    if (raiz != NULL)
    {
        raiz->iz.actualizarArbolFE();
        raiz->de.actualizarArbolFE();
        raiz->fe = nodoFE();
    }
}

void TAVLCalendario::arreglarArbol()
{

    raiz->fe = nodoFE();

    if (raiz->fe < -1)
    {
        raiz->fe <= 0 ? rotacionII() : rotacionID();
    }
    else if (raiz->fe > 1)
    {
        raiz->fe >= 0 ? rotacionDD() : rotacionDI();
    }
}

void TAVLCalendario::rotacionII()
{

    TNodoAVL *j = raiz->iz.raiz;
    raiz->iz.raiz = raiz->iz.raiz->de.raiz;
    j->de.raiz = raiz;
    raiz = j;
    actualizarArbolFE();
}

void TAVLCalendario::rotacionID()
{

    TNodoAVL *j = raiz->iz.raiz;
    raiz->iz.raiz = j->de.raiz->de.raiz;
    j->de.raiz->de.raiz = raiz;
    raiz = j->de.raiz;
    j->de.raiz = raiz->iz.raiz;
    raiz->iz.raiz = j;
    actualizarArbolFE();
}

void TAVLCalendario::rotacionDD()
{

    TNodoAVL *j = raiz->de.raiz;
    raiz->de.raiz = raiz->de.raiz->iz.raiz;
    j->iz.raiz = raiz;
    raiz = j;
    actualizarArbolFE();
}

void TAVLCalendario::rotacionDI()
{

    TNodoAVL *j = raiz->de.raiz;
    raiz->de.raiz = j->iz.raiz->iz.raiz;
    j->iz.raiz->iz.raiz = raiz;
    raiz = j->iz.raiz;
    j->iz.raiz = raiz->de.raiz;
    raiz->de.raiz = j;
    actualizarArbolFE();
}

bool TAVLCalendario::Insertar(const TCalendario &cal)
{

    if (this->Buscar(cal))
        return false;

    if (this->EsVacio())
    {
        TNodoAVL *nodoInsertar = new TNodoAVL();
        nodoInsertar->item = cal;
        raiz = nodoInsertar;
    }
    else
    {
        raiz->item > cal ? raiz->iz.Insertar(cal) : raiz->de.Insertar(cal);
    }

    arreglarArbol();
    return true;
}

void TAVLCalendario::handleNodeDeletion()
{
    if (raiz->iz.EsVacio() && raiz->de.EsVacio())
    {
        raiz = NULL;
    }
    else if (raiz->iz.EsVacio())
    {
        raiz = raiz->de.raiz;
    }
    else if (raiz->de.EsVacio())
    {
        raiz = raiz->iz.raiz;
    }
    else
    {
        replaceWithInorderPredecessor();
    }
}

void TAVLCalendario::replaceWithInorderPredecessor()
{
    TNodoAVL *aux = raiz->iz.raiz;
    TCalendario sustituto = raiz->iz.raiz->item;

    while (!aux->de.EsVacio())
    {
        sustituto = aux->de.raiz->item;
        aux = aux->de.raiz;
    }

    raiz->item = sustituto;
    raiz->iz.Borrar(sustituto);
}

bool TAVLCalendario::Borrar(const TCalendario &cal)
{
    if (!Buscar(cal))
        return false;

    if (Raiz() > cal)
    {
        raiz->iz.Borrar(cal);
    }
    else if (Raiz() < cal)
    {
        raiz->de.Borrar(cal);
    }
    else
    {
        handleNodeDeletion();
    }

    if (raiz != NULL)
        arreglarArbol();
    return true;
}

ostream &operator<<(ostream &s, const TAVLCalendario &arbol)
{

    s << arbol.Inorden();

    return s;
}
