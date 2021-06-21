#include "headers/Lista.h"
#include "headers/Empresa.h"
#include<assert.h>

template <typename T> Lista<T>::Lista(){
}

template <typename T> Lista<T>::Lista(T nuevo_dato){
    nodo = new Nodo;
    nodo->dato = nuevo_dato;
    primero = this->nodo;
}

template <typename T> void Lista<T>::agregarElemento(T nuevo_dato){
    if (nodo == NULL){
        nodo = new Nodo;
        nodo->dato = nuevo_dato;
        if (primero == NULL){ primero = this->nodo;}
    }else{
        if (nodo->sig == NULL){
            nodo->sig = new Lista;
            nodo->sig->primero = primero;
        }
        nodo->sig->agregarElemento(nuevo_dato);
    }
}

template <typename T> bool Lista<T>::listaVacia() const{
    if (nodo != NULL){
        return false;
    }
    return true;
}

template <typename T> void Lista<T>::inicializarCursor(){
    cursor = primero;
}

template <typename T> void Lista<T>::avanzarCursor(){
    assert(cursor != NULL);
    if (cursor->sig != NULL){
        cursor = cursor->sig->nodo;
    }else{
        cursor = NULL;
    }
}

template <typename T> bool Lista<T>::cursorFinal() const{
    return (cursor == NULL);
}

template <typename T> T Lista<T>::obtenerElementoCursor() const{
    assert(cursor != NULL);
    return cursor->dato;
}

template <typename T> Lista<T>::~Lista(){
    delete nodo;
    nodo = NULL;
}

template class Lista<int>;
template class Lista<Empresa*>;
