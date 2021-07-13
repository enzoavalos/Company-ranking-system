#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include "Empresa.h"
#include "Arreglo.h"
#include "ABB.h"
#include "Lista.h"

void procesar_archivo_entrada(string,Empresa *&,ABB<string> *&,ABB<int> *&,unsigned int&);
void crearArbolPosiciones(Empresa*,ABB<int> *&,int,int);
void destruirPunteros(Empresa *&,ABB<string> *&,ABB<int> *&);
void menuPrincipal(Empresa *&,unsigned int,ABB<string> *&,ABB<int> *&);
void busquedaPorRango(Empresa *,unsigned int,unsigned int,Lista<int> &);
void mostrarEmpresa(Empresa);

/**
 * Abre el archivo según el origen, procesa las líneas del mismo y
 * almacena la información resultante en el contenedor pasado por referencia.
 * Comentarios: atoi y atof requieren un char * para converter a número, usamos c_str de la clase string.
 */
void procesar_archivo_entrada(string origen,Empresa *&empresas,ABB<string> *&arbol_razonsocial,
                              ABB<int> *&arbol_posiciones,unsigned int &size_arreglo)
{
    ifstream archivo(origen);
    if (!archivo.is_open())
        cout << "No se pudo abrir el archivo: " << origen << endl;
    else {
        string linea;
        getline(archivo, linea);
        int cantidad_empresas = atoi(linea.c_str());

        size_arreglo = cantidad_empresas;
        empresas = new Empresa[cantidad_empresas];
        arbol_razonsocial = new ABB<string>;
        arbol_posiciones = new ABB<int>;

        //Leemos de una linea completa por vez (getline).
        int posicion_ranking = 0;
        while (getline(archivo, linea)) {

            //Primer posición del separador ;
            int pos_inicial = 0;
            int pos_final = linea.find(';');

            //Informacion entre pos_inicial y pos_final
            string razon_social = linea.substr(pos_inicial, pos_final);

            //Segunda posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            string pais_origen = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Tercera posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            unsigned int empleados = atoi(linea.substr(pos_inicial, pos_final - pos_inicial).c_str());

            //Cuarta posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            string rubro = linea.substr(pos_inicial, pos_final - pos_inicial);

            Empresa empresa_leida(razon_social,pais_origen,empleados,rubro);
            //arr_empresas->agregarElemento(empresa_leida);
            empresas[posicion_ranking] = empresa_leida;
            posicion_ranking+=1;

            arbol_razonsocial->agregarElemento(empresas,posicion_ranking);
        }
        crearArbolPosiciones(empresas,arbol_posiciones,1,size_arreglo);
    }
}

void crearArbolPosiciones(Empresa *empresas,ABB<int> *&arbol_posiciones,int inferior,int superior){
    /* Crea un arbol balanceado aprovechando que se tiene el arreglo ordenado por posiciones*/
    if (inferior <= superior){
        int mitad = (superior+inferior)/2;
        arbol_posiciones->agregarElemento(empresas,mitad);
        crearArbolPosiciones(empresas,arbol_posiciones,inferior,mitad-1);
        crearArbolPosiciones(empresas,arbol_posiciones,mitad+1,superior);
    }else{ return ;}
}

void destruirPunteros(Empresa *&arreglo_empresas,ABB<string> *&arbol_razonsocial,ABB<int> *&arbol_posiciones){
    delete[] arreglo_empresas;
    delete arbol_razonsocial;
    delete arbol_posiciones;
    arreglo_empresas = NULL;
    arbol_razonsocial = NULL;
    arbol_posiciones = NULL;
}

void busquedaPorRango(Empresa *arreglo_empresas,unsigned int size_arreglo,unsigned int inferior,unsigned int superior,
                      Lista<int> &lista){
    for (int i=0;i<size_arreglo;i++){
        unsigned int empleados = arreglo_empresas[i].obtenerEmpleados();
        if ((empleados >= inferior)&&(empleados <= superior)){
            lista.agregarElemento(i+1);
        }
    }
}

void mostrarEmpresa(Empresa emp_mostrar){
    cout<<"\n ~ "<<emp_mostrar.obtenerRazonSocial();
    cout<<"\n Rubro: "<<emp_mostrar.obtenerRubro();
    cout<<"\n Origen: "<<emp_mostrar.obtenerPaisOrigen();
    cout<<"\n Cantidad de empleados: "<<emp_mostrar.obtenerEmpleados()<<endl;
}

void menuPrincipal(Empresa *&empresas,unsigned int size_arreglo,ABB<string> *&arbol_razonsocial,ABB<int> *&arbol_posiciones){
    char input_usuario='a';
    do{
        fflush(stdin);
        system("cls");
        cout<<"\n\t\t ~~ Bienvenido ~~";
        cout<<"\n Elija una de las opciones siguientes: ";
        cout<<"\n 1- Consultar posicion de una empresa";
        cout<<"\n 2- Obtener informacion de una empresa en cierta posicion";
        cout<<"\n 3- Buscar empresas con cantidad de empleados dentro de un rango";
        cout<<"\n 4- Salir"<<endl;
        cin>>input_usuario;

        switch(input_usuario){
            case '1':{ //Obtener la posición en el ranking para una empresa en particular.
                fflush(stdin);
                system("cls");
                string empresa_ingresada = "";
                cout<<"\n Ingrese el nombre de la empresa buscada: ";
                getline(cin,empresa_ingresada);

                int pos_empresa_buscada = arbol_razonsocial->buscarEmpresa(empresa_ingresada);
                if (pos_empresa_buscada > 0){
                    cout<<"\n La empresa buscada se encuentra en la posicion: "<<pos_empresa_buscada<<endl;
                }else{
                    cout<<"\n La empresa buscada no fue encontrada. Intentelo nuevamente\n";
                }
                break;
                }
            case '2':{ //Obtener la información de la empresa que se encuentra en una posición determinada.
                fflush(stdin);
                system("cls");
                string pos_ingresada;
                cout<<"\n Ingrese la posicion que desea consultar: ";
                getline(cin,pos_ingresada);

                unsigned int posicion_buscada;
                try{
                    posicion_buscada = stoi(pos_ingresada);
                }catch(...){
                    cout<<"\n Entrada invalida, intentelo nuevamente";
                    break;
                }

                Empresa *empresa_buscada = arbol_posiciones->buscarEmpresa(posicion_buscada);
                if (empresa_buscada != NULL){
                    mostrarEmpresa(*empresa_buscada);
                }else{
                    cout<<"\n La empresa buscada no fue encontrada. Intentelo nuevamente\n";
                }
                break;
                }
            case '3':{ //Listar las empresas, y su posición, con un número de empleados dentro de un rango especificado.
                fflush(stdin);
                system("cls");
                string minimo,maximo;
                cout<<"\n Ingrese los limites para la busqueda \n";
                cout<<" Minimo de empleados: ";
                getline(cin,minimo);
                cout<<" Maximo de empleados: ";
                getline(cin,maximo);

                unsigned int limite_inf,limite_sup;
                try{
                    limite_inf = stoi(minimo);
                    limite_sup = stoi(maximo);
                    if (limite_inf > limite_sup){ throw(NULL); }
                }catch(...){
                    cout<<"\n Entrada invalida, intentelo nuevamente";
                    break;
                }

                Lista<int> lista_rango;
                busquedaPorRango(empresas,size_arreglo,limite_inf,limite_sup,lista_rango);
                if (!lista_rango.listaVacia()){
                    lista_rango.inicializarCursor();
                    unsigned int pos_a_buscar;
                    while (!lista_rango.cursorFinal()){
                        pos_a_buscar = lista_rango.obtenerElementoCursor();
                        cout<<"\n Posicion: "<<pos_a_buscar;
                        mostrarEmpresa(empresas[pos_a_buscar-1]);
                        lista_rango.avanzarCursor();
                    }
                }else{
                    cout<<"\n No se han encontrado empresas con las caracteristicas buscadas";
                }
                break;}
            case '4':{
                cout<<"\n\t Hasta Luego!!\n";
                break;
            }
            default:{
                cout<<"\n Opcion invalida, intentelo nuevamente.";
                break;
            }
        }
        getch();
    }while(input_usuario != '4');

    destruirPunteros(empresas,arbol_razonsocial,arbol_posiciones);
}

#endif // FUNCIONES_H_INCLUDED
