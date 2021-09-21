#include <iostream>
#include <vector>
#include <cstring>
#include "Router.h"

/*El siguiente programa tiene incorporadas la clase Router, la cual ofrece la funcion de cam
 * biar el costo de un enlace en especifico, eliminar y agregar enlaces*/

//OBSERVACIÓ: A PESAR DE QUE SE LE DA AL USUARIO LA OPCION DE ELEGIR EL ROUTER, NO SE CAMBIA Y
//EL PROGRAMA TOMA EL PREDETERMINADO VALOR DEL ROUTER

using namespace std;

int main()
{
    Router n1;
    n1.lecturaConex();

    string camino="";
    char Router,destino;
    cout<<"Elija un router : ";cin>>Router;
    cout<<"Elija un destino : ";cin>>destino;

    char OrigenTemp=Router;
    vector<string>caminosTot;
    char LetraPas='A';
    int op = 7;

    cout<<"-- TOPOLOGIA ENRUTADORES --"<<endl;
    cout<<" Presione: "<<endl;

    while (op!=0) {

        cout<<" 1. Conocer tabla enrutamiento de un enrutador "<<Router<<endl;
        cout<<" 2. Ruta más corta de origen - Destino : "<<endl;
        cout<<" 3. Cambiar costo enlace "<<endl;
        cout<<" 4. Agregar enlace "<<endl;
        cout<<" 0. Salir"<<endl;

        cout<<"Su opcion : ";
        cin>>op;

        if(op==1){

            //cout<<"Ingrese el enrutador : "<<Router<<endl;
            caminosTot=n1.BusquedaCaminos(Router, camino, destino, OrigenTemp,LetraPas, caminosTot);

            n1.ConocerEnrutadores();
            n1.lecturaCostos();
            n1.ShowTablaRout(Router,camino,OrigenTemp,caminosTot);
        }


        else if(op==2){

            vector<string> Path=n1.BusquedaCaminos(Router, camino, destino, OrigenTemp,LetraPas, caminosTot);
            n1.ConocerEnrutadores();
            n1.lecturaCostos();
            n1.Camino(Path);
        }


        else if(op==3){

            n1.CambCostoEnla();
        }


        else if(op==4){

            n1.lecturaCostos();
            n1.AnadirEnlace();
        }


    }
    return 0;
}
