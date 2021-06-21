#ifndef ARREGLO_H_INCLUDED
#define ARREGLO_H_INCLUDED

#include<iostream>
using namespace std;

template <typename T>
class Arreglo{
	private:
		unsigned int pos_actual = 0;
		unsigned int cant_elementos = 0;
		T *arreglo = NULL;
	public:
	    Arreglo();
	    Arreglo(unsigned int n);
		virtual ~Arreglo();
		void agregarElemento(T nuevo_elemento);
		T obtenerDatos(unsigned int pos_buscada) const;
		int obtenerCantidadElementos() const;
		void referenciarElemento(T *&puntero_referencia,unsigned int posicion) const;
};

#endif // ARREGLO_H_INCLUDED
