#include "headers/ABB.h"
#include<assert.h>

template <typename T> ABB<T>::ABB(){
}

template <typename T> ABB<T>::ABB(Empresa *nueva_empresa,unsigned int pos_ranking){
    nodo = new Nodo;
    nodo->empresa = nueva_empresa;
    nodo->pos_ranking = pos_ranking;
}

template <> void ABB<int>::agregarElemento(Arreglo<Empresa> *empresas,unsigned int pos_ranking){
    if (nodo == NULL){
        nodo = new Nodo;
        nodo->pos_ranking = pos_ranking;
        empresas->referenciarElemento(nodo->empresa,pos_ranking);
    }else{
        if (pos_ranking < nodo->pos_ranking){
            if (nodo->izq == NULL){
                nodo->izq = new ABB;
            }
            nodo->izq->agregarElemento(empresas,pos_ranking);
        }else{
            if (nodo->der == NULL){
                nodo->der = new ABB;
            }
            nodo->der->agregarElemento(empresas,pos_ranking);
        }
    }
}

template <> void ABB<string>::agregarElemento(Arreglo<Empresa> *empresas,unsigned int pos_ranking){
    if (nodo == NULL){
        nodo = new Nodo;
        nodo->pos_ranking = pos_ranking;
        empresas->referenciarElemento(nodo->empresa,pos_ranking);
    }else{
        Empresa empresa_actual = empresas->obtenerDatos(pos_ranking);
        if (empresa_actual.obtenerRazonSocial() < nodo->empresa->obtenerRazonSocial()){
            if (nodo->izq == NULL){
                nodo->izq = new ABB;
            }
            nodo->izq->agregarElemento(empresas,pos_ranking);
        }else{
            if (nodo->der == NULL){
                nodo->der = new ABB;
            }
            nodo->der->agregarElemento(empresas,pos_ranking);
        }
    }
}

template <typename T> ABB<T>::~ABB(){
    if (nodo->der != NULL){
        delete nodo->der;
        nodo->der = NULL;
    }
    if (nodo->izq != NULL){
        delete nodo->izq;
        nodo->izq = NULL;
    }
    delete nodo;
    nodo = NULL;
}

template <> int ABB<string>::buscarEmpresa(string razon_social) const{
    if (nodo == NULL){
        return -1;
    }else{
        if (razon_social == nodo->empresa->obtenerRazonSocial()){
            return nodo->pos_ranking;
        }else if (razon_social < nodo->empresa->obtenerRazonSocial()){
            if (nodo->izq != NULL){
                return nodo->izq->buscarEmpresa(razon_social);
            }
        }else{
            if (nodo->der != NULL){
                return nodo->der->buscarEmpresa(razon_social);
            }
        }
        return -1;
    }
}

template <> Empresa* ABB<int>::buscarEmpresa(unsigned int posicion) const{
    if (nodo == NULL){
        return NULL;
    }else{
        if (posicion == nodo->pos_ranking){
            return nodo->empresa;
        }else if (posicion < nodo->pos_ranking){
            if (nodo->izq != NULL){
                return nodo->izq->buscarEmpresa(posicion);
            }
        }else{
            if (nodo->der != NULL){
                return nodo->der->buscarEmpresa(posicion);
            }
        }
        return NULL;
    }
}

template class ABB<int>;
template class ABB<string>;
