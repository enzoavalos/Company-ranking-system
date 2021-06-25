#ifndef PST_H_INCLUDED
#define PST_H_INCLUDED

#include "Empresa.h"

class PST{
    private:
        struct Nodo{
            Empresa *empresa;
            unsigned int posicion;
            unsigned int empleados;
            int clave_distribucion = -1;
            Nodo *izq = NULL;
            Nodo *der = NULL;
        };
        Nodo *nodo = NULL;

        int ubicarElementoMenorPrioridad(Nodo *[],int,int);
        void construirPST(Nodo *&,Nodo *[],int,int);
        void mergeSort(Nodo *[],int,int);
        void merge(Nodo *[],int,int,int);
        void eliminar(Nodo *&);
        int calcularMediana(Nodo *[],unsigned int,unsigned int,int&);
        void recorrer(Nodo *);

    public:
        PST();
        PST(Empresa *,unsigned int);
        ~PST();
        void mostrar();
};

#endif // PST_H_INCLUDED
