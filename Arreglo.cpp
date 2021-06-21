#include "headers/Arreglo.h"
#include "headers/Empresa.h"
#include<assert.h>

template <typename T> Arreglo<T>::Arreglo(){
}

template <typename T> Arreglo<T>::Arreglo(unsigned int n){
    cant_elementos = n;
    arreglo = new T[cant_elementos];
}

template <typename T> void Arreglo<T>::agregarElemento(T nuevo_elemento){
    if (pos_actual < cant_elementos){
        arreglo[pos_actual] = nuevo_elemento;
        pos_actual+=1;
    }
}

template <typename T> T Arreglo<T>::obtenerDatos(unsigned int pos_buscada) const{
    assert((pos_buscada > 0)&&(pos_buscada <= cant_elementos+1)&&(cant_elementos != 0));
    return arreglo[pos_buscada-1];
}

template <typename T> Arreglo<T>::~Arreglo(){
    delete[] arreglo;
    arreglo = NULL;
}

template <typename T> int Arreglo<T>::obtenerCantidadElementos() const{
    return cant_elementos;
}

template <typename T> void Arreglo<T>::referenciarElemento(T *&puntero_referencia,unsigned int posicion) const{
    assert((posicion > 0)&&(posicion <= cant_elementos+1)&&(cant_elementos != 0));
    puntero_referencia = &arreglo[posicion-1];
}

template class Arreglo<Empresa>;
