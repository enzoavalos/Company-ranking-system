#include <iostream>
using namespace std;

#include <fstream>
#include<assert.h>
#include<stdlib.h>
#include<conio.h>

#include "headers/Empresa.h"
#include "headers/Arreglo.h"
#include "headers/ABB.h"
#include "headers/Funciones.h"
#include "headers/PST.h"

int main()
{
    Empresa *empresas = NULL;
    unsigned int tamanio_arreglo;
    ABB<string> *arbol_razonsocial;
    ABB<int> *arbol_posiciones;

    procesar_archivo_entrada("ranking_empresas.csv",empresas,arbol_razonsocial,arbol_posiciones,tamanio_arreglo);
    menuPrincipal(empresas,tamanio_arreglo,arbol_razonsocial,arbol_posiciones);

    return 0;
}
