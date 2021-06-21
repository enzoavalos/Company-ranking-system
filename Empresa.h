#ifndef EMPRESA_H_INCLUDED
#define EMPRESA_H_INCLUDED

#include<iostream>
using namespace std;

class Empresa{
    private:
        string razon_social;
        string pais_origen;
        unsigned int empleados;
        string rubro;
    public:
        Empresa();
        Empresa(string,string,unsigned int,string);
        virtual ~Empresa();
        Empresa& operator=(const Empresa&);

        string obtenerRazonSocial() const;
        string obtenerPaisOrigen() const;
        string obtenerRubro() const;
        int obtenerEmpleados() const;
};

#endif // EMPRESA_H_INCLUDED
