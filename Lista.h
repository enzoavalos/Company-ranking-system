#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include<iostream>
using namespace std;

template <typename T>
class Lista{
    private:
        struct Nodo{
            Lista *sig = NULL;
            T dato;
        };
        Nodo *nodo = NULL;
        Nodo *primero = NULL;
        Nodo *cursor = NULL;
    public:
        Lista();
        Lista(T nuevo_dato);
        virtual ~Lista();
        void agregarElemento(T nuevo_dato);
        bool listaVacia() const;
        void inicializarCursor();
        void avanzarCursor();
        bool cursorFinal() const;
        T obtenerElementoCursor() const;
};

#endif // LISTA_H_INCLUDED
