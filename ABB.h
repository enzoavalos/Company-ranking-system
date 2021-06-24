#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

#include "Empresa.h"
#include "Arreglo.h"

template <typename T>
class ABB{
    private:
        struct Nodo{
            Nodo *izq = NULL;
            Nodo *der = NULL;
            Empresa *empresa = NULL;
            unsigned int pos_ranking = 0;
        };
        Nodo *nodo = NULL;
        void agregar(Nodo *&arbol,Empresa *,int);
        void eliminar(Nodo *&);
        Empresa* buscar(Nodo *arbol,int) const;
        int buscar(Nodo *,string) const;

    public:
        ABB();
        ABB(Empresa *nueva_empresa,unsigned int pos_ranking);
        virtual ~ABB();
        void agregarElemento(Empresa *empresas,unsigned int pos_ranking);
        Empresa* buscarEmpresa(unsigned int posicion);
        int buscarEmpresa(string razon_social);
};

#endif // ABB_H_INCLUDED
