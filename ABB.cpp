#include "headers/ABB.h"
#include<assert.h>

template <typename T> ABB<T>::ABB(){
}

template <typename T> ABB<T>::ABB(Empresa *nueva_empresa,unsigned int pos_ranking){
    nodo = new Nodo;
    nodo->empresa = nueva_empresa;
    nodo->pos_ranking = pos_ranking;
}

template <typename T> void ABB<T>::agregarElemento(Empresa *empresas,unsigned int pos_ranking){
    agregar(nodo,empresas,pos_ranking);
}

template <> void ABB<int>::agregar(Nodo *&arbol,Empresa *empresas,int pos_ranking){
    if (arbol == NULL){
        arbol = new Nodo;
        arbol->pos_ranking = pos_ranking;
        arbol->empresa = &empresas[pos_ranking-1];
    }else{
        if (pos_ranking < arbol->pos_ranking){
            agregar(arbol->izq,empresas,pos_ranking);
        }else{
            agregar(arbol->der,empresas,pos_ranking);
        }
    }
}

template <> void ABB<string>::agregar(Nodo *&arbol,Empresa *empresas,int pos_ranking){
    if (arbol == NULL){
        arbol = new Nodo;
        arbol->pos_ranking = pos_ranking;
        arbol->empresa = &empresas[pos_ranking-1];
    }else{
        Empresa empresa_actual = empresas[pos_ranking-1];
        if (empresa_actual.obtenerRazonSocial() < arbol->empresa->obtenerRazonSocial()){
            agregar(arbol->izq,empresas,pos_ranking);
        }else{
            agregar(arbol->der,empresas,pos_ranking);
        }
    }
}

template <typename T> void ABB<T>::eliminar(Nodo *&arbol){
   if (arbol != NULL){
        eliminar(arbol->izq);
        eliminar(arbol->der);
        delete arbol;
        arbol = NULL;
   }
}

template <typename T> ABB<T>::~ABB(){
    eliminar(nodo);
}

template <> Empresa* ABB<int>::buscar(Nodo *arbol,int posicion) const{
    if (arbol != NULL){
        if (posicion == arbol->pos_ranking){
            return arbol->empresa;
        }else if (posicion < arbol->pos_ranking){
            if (arbol->izq != NULL){
                return buscar(arbol->izq,posicion);
            }
        }else{
            if (arbol->der != NULL){
                return buscar(arbol->der,posicion);
            }
        }
    }
    return NULL;
}

template <> int ABB<string>::buscar(Nodo *arbol,string razon_social) const{
    if (arbol != NULL){
        if (razon_social == arbol->empresa->obtenerRazonSocial()){
            return arbol->pos_ranking;
        }else if (razon_social < arbol->empresa->obtenerRazonSocial()){
            if (arbol->izq != NULL){
                return buscar(arbol->izq,razon_social);
            }
        }else{
            if (arbol->der != NULL){
                return buscar(arbol->der,razon_social);
            }
        }
    }
    return -1;
}

template <> int ABB<string>::buscarEmpresa(string razon_social){
    return buscar(nodo,razon_social);
}

template <> Empresa* ABB<int>::buscarEmpresa(unsigned int posicion){
    return buscar(nodo,posicion);
}

template class ABB<int>;
template class ABB<string>;
