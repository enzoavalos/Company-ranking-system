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

int main()
{
    Arreglo<Empresa> *arreglo_empresas;
    ABB<string> *arbol_razonsocial;
    ABB<int> *arbol_posiciones;

    procesar_archivo_entrada("ranking_empresas.csv",arreglo_empresas,arbol_razonsocial,arbol_posiciones);
    menuPrincipal(arreglo_empresas,arbol_razonsocial,arbol_posiciones);

    return 0;
}
