#include "headers/PST.h"
#include<assert.h>

PST::PST(){
}

PST::PST(Empresa *empresas,unsigned int tamanio_arreglo){
    assert(empresas != NULL);
    Nodo *arr_auxiliar[tamanio_arreglo];

    for (int i=0;i<tamanio_arreglo;i++){
        arr_auxiliar[i] = new Nodo;
        arr_auxiliar[i]->empresa = &empresas[i];
        arr_auxiliar[i]->posicion = i+1;
        arr_auxiliar[i]->empleados = empresas[i].obtenerEmpleados();
    }
    construirPST(nodo,arr_auxiliar,0,tamanio_arreglo-1);
}

void PST::construirPST(Nodo *&padre,Nodo *subarreglo[],int inicio,int fin){
    if (inicio > fin){
        return;
    }else if(inicio == fin){
        padre = subarreglo[inicio];
    }else{
        //cout<<"bien"<<endl;
        int pos_menor_prior = ubicarElementoMenorPrioridad(subarreglo,inicio,fin);
        if (pos_menor_prior != inicio){
            Nodo *aux = subarreglo[inicio];
            subarreglo[inicio] = subarreglo[pos_menor_prior];
            subarreglo[pos_menor_prior] = aux;
        }

        mergeSort(subarreglo,inicio+1,fin);
        int indice_mediana = -1;
        int mediana = calcularMediana(subarreglo,inicio+1,fin,indice_mediana);

        padre = subarreglo[inicio];
        padre->clave_distribucion = mediana;

        construirPST(padre->izq,subarreglo,inicio+1,indice_mediana);
        construirPST(padre->der,subarreglo,indice_mediana+1,fin);
    }
}

void PST::eliminar(Nodo *&nodo){
    if (nodo != NULL){
        eliminar(nodo->izq);
        eliminar(nodo->der);
    }
    delete nodo;
    nodo = NULL;
}

PST::~PST(){
    eliminar(nodo);
}

void PST::mergeSort(Nodo *subarreglo[],int l,int r){
    /*Complejidad O(n*log n)*/
	int m;
	if(l<r){
		int m = (l+r) / 2;
		//Ordenamos primer y segundo array
		mergeSort(subarreglo,l,m);
		mergeSort(subarreglo,m+1,r);
		merge(subarreglo,l,r,m);
	}else{
		return;
	}
}

void PST::merge(Nodo *subarreglo[],int left,int right,int middle){
	int n1 = middle - left +1;
	int n2 = right - middle;
	Nodo *l_array[n1],*r_array[n2];

	for (int x=0; x < n1; x++)
        l_array[x] = subarreglo[left + x];
    for (int z = 0; z < n2; z++)
        r_array[z] = subarreglo[middle + 1 + z];

	int i=0,j=0,k=left;
	while ((i < n1)&&(j < n2)){
		if (l_array[i]->empleados <= r_array[j]->empleados){
			subarreglo[k] = l_array[i];
			i++;
		}else{
			subarreglo[k] = r_array[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
        subarreglo[k] = l_array[i];
        i++;
        k++;
    }

    while (j < n2) {
        subarreglo[k] = r_array[j];
        j++;
        k++;
    }
}

int PST::calcularMediana(Nodo *arreglo_ordenado[],unsigned int left, unsigned int right,int &indice){
    indice = (right+left)/2;
    return arreglo_ordenado[indice]->empleados;
}

int PST::ubicarElementoMenorPrioridad(Nodo *subarreglo[],int inicio,int fin){
    if (inicio >= fin){ return inicio;}
    int menor_prioridad = subarreglo[inicio]->posicion;
    int pos_menor = inicio;
    for (int i=inicio+1;i<fin;i++){
        if (subarreglo[i]->posicion < menor_prioridad){
            menor_prioridad = subarreglo[i]->posicion;
            pos_menor = i;
        }
    }
    return pos_menor;
}

void PST::recorrer(Nodo *nodo){
    if (nodo != NULL){
        recorrer(nodo->izq);
        cout<<nodo->posicion<<endl;
        recorrer(nodo->der);
    }
}

void PST::mostrar(){
    recorrer(nodo);
}
