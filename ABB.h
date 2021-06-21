#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

#include "Empresa.h"
#include "Arreglo.h"

template <typename T>
class ABB{
    private:
        struct Nodo{
            ABB *izq = NULL;
            ABB *der = NULL;
            Empresa *empresa = NULL;
            unsigned int pos_ranking = 0;
        };
        Nodo *nodo = NULL;
    public:
        ABB();
        ABB(Empresa *nueva_empresa,unsigned int pos_ranking);
        virtual ~ABB();
        void agregarElemento(Arreglo<Empresa> *empresas,unsigned int pos_ranking);
        Empresa* buscarEmpresa(unsigned int posicion) const;
        int buscarEmpresa(string razon_social) const;
};

#endif // ABB_H_INCLUDED
