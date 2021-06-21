#include "headers/Empresa.h"
#include<assert.h>

Empresa::Empresa(){
}

Empresa::Empresa(string razon_social,string pais_origen,unsigned int empleados,string rubro){
    assert(empleados > 0);
    this->razon_social = razon_social;
    this->pais_origen = pais_origen;
    this->empleados = empleados;
    this->rubro = rubro;
}

Empresa::~Empresa(){
}

string Empresa::obtenerRazonSocial() const{
    return razon_social;
}

string Empresa::obtenerPaisOrigen() const{
    return pais_origen;
}

string Empresa::obtenerRubro() const{
    return rubro;
}

int Empresa::obtenerEmpleados() const{
    return empleados;
}

Empresa& Empresa::operator=(const Empresa& otra_empresa){
    this->razon_social = otra_empresa.razon_social;
    this->pais_origen = otra_empresa.pais_origen;
    this->empleados = otra_empresa.empleados;
    this->rubro = otra_empresa.rubro;
}
