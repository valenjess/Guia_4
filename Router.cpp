#include "Router.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

Router::Router()
{

}

vector<string> Router::BusquedaCaminos(char origen, string camino, char destino, char OrigenTemp, char LetraPas, vector<string> &caminosTot)
{


        int longitud=_Conexiones.size();

        string caminoAcum;

        for(int i=0;i<longitud;i++){
            if ( _Conexiones[i][0] == OrigenTemp){

                if (_Conexiones[i][1]==origen or LetraPas==_Conexiones[i][1]){ //Se verifica que no se haya pasado por ese enrutador

                }
                else if(_Conexiones[i][1]==destino){
                    camino+=_Conexiones[i];

                if(camino[0]==origen && camino[camino.length()-1]==destino){
                        caminoAcum=camino;
                        caminosTot.push_back(camino);
                        //cout<<"El camino es: "<<camino<<endl;
                        camino = ""; //Se vacía el string para crear un nuevo camino

                    }
             //OrigenTemp = caminoAcum[1];
                }
                else{
                    camino+=_Conexiones[i];

                    OrigenTemp=_Conexiones[i][1];
                    LetraPas=_Conexiones[i][0];
                    BusquedaCaminos(origen,camino,destino,OrigenTemp,LetraPas,caminosTot);
                    OrigenTemp=_Conexiones[i][0];



                    camino.pop_back();
                     camino.pop_back();
                }


            }
    }
        return caminosTot;
}

void Router::lecturaConex()
{
    string data,texto,path;
    ifstream infile;
    //vector<string>_Conexiones;


     infile.open(_Archivo);

     if (!infile.is_open())
          {
            cout << "Error abriendo el archivo" << endl;
            exit(1);
          }



          while(!infile.eof()){

                getline(infile,texto);
                data+=texto;
                for(int index=0; index<2;index++){
                path +=data[index];
                }
                _Conexiones.push_back(path);
                data="";
                path="";
          }

          infile.close();

}

void Router::lecturaCostos()
{
    string data,texto,path;
    ifstream infile;
    int pathNum;


    infile.open(_Archivo);

     if (!infile.is_open())
          {
            cout << "Error abriendo el archivo" << endl;
            exit(1);
          }



          while(!infile.eof()){

                getline(infile,texto);
                data+=texto;

                path +=data[3];
                pathNum = stoi(path);

                _Costos.push_back(pathNum);
                data="";
                path="";
          }

          infile.close();



}

int Router::RutaCorta(vector<string> caminosTot)
{

        string conex="";
        int valor=0;
        int cont =0;
        vector<int>Valor_Camino;
        int lonCad = 0;
        int min = 0;
        int posicion;

        for(int ind=0; ind<caminosTot.size(); ind++){
            lonCad = caminosTot[ind].length();

            for(int ind2=0; ind2<lonCad/2 ; ind2++){

                for(int y=0; y<2;y++){
                    conex += caminosTot[ind][cont];
                    cont++;
                }


                for(int elem=0 ;elem<_Conexiones.size(); elem++){
                    if(conex==_Conexiones[elem]){
                        valor += _Costos[elem];
                        break;
                    }
                }

                conex="";
            }
            Valor_Camino.push_back(valor);
            valor=0;
            cont = 0;
        }

        min = Valor_Camino[0];
        for(int index=0; index<Valor_Camino.size(); index++){
            if(min > Valor_Camino[index]){
                min = Valor_Camino[index];
                posicion=index;
            }
        }
        //cout<<"El camino es "<<caminosTot[posicion];
        return Valor_Camino[posicion];
}

void Router::ConocerEnrutadores()
{

    char EnrutadorPas;
    EnrutadorPas = _Conexiones[0][0];

    for(int elem=0; elem<_Conexiones.size(); elem++){

        if(elem==0){
             _Enrutadores.push_back(EnrutadorPas);
        }
        else if(_Conexiones[elem][0]!=EnrutadorPas){
            _Enrutadores.push_back(_Conexiones[elem][0]);
            EnrutadorPas = _Conexiones[elem][0];
        }

    }



}

void Router::ShowTablaRout(char Router, string camino, char OrigenTemp, vector<string> &caminosTot)
{
    map<char,int> TablaRout;
    int CostoRts=0;//Costo minimo de router a router
    char destino ;
    vector<string>Rutas;

    std::map<char,int>::iterator it = TablaRout.begin();

    for(int indice=0; indice<_Enrutadores.size(); indice++){
        if(_Enrutadores[indice]==Router){
            TablaRout.insert (it, std::pair<char,int>(_Enrutadores[indice],0));
        }
        else{
            destino=_Enrutadores[indice];

            CostoRts=RutaCorta( BusquedaCaminos(Router, camino, destino, OrigenTemp,LetraPas, caminosTot));
             //Rutas= BusquedaCaminos(Router, camino, destino, OrigenTemp,LetraPas, caminosTot);
            //CostoRts=RutaCorta(Rutas);
            TablaRout.insert (it, std::pair<char,int>(_Enrutadores[indice],CostoRts));
            caminosTot.clear();
         }

    }

    cout<< " La tabla de enrutamiento para el enrutador "<<Router<<" es :"<<endl;
    map<char,int>::iterator i;
    for(i=TablaRout.begin(); i !=TablaRout.end(); i++ ){
        cout<<" Router "<<i->first<<"|"<<"Valor: "<<i->second<<endl;
    }
}

void Router::CambCostoEnla()
{
    string Enlace = "";
    int NewValor = 0;

    cout<<"Ingrese el enlace que desea cambiar valor -Ej: DE "<<endl;
    cout<<"--> ";cin>>Enlace;

    cout<<" Su valor es --> ";cin>>NewValor;

    for(int index=0; index<_Costos.size(); index++){
        if(_Conexiones[index]== Enlace){
            _Costos[index]=NewValor;
        }
    }
}

void Router::Camino(vector<string> caminosTot)
{

        string conex="";
        int valor=0;
        int cont =0;
        vector<int>Valor_Camino;
        int lonCad = 0;
        int min = 0;
        int posicion=0;

        for(int ind=0; ind<caminosTot.size(); ind++){
            lonCad = caminosTot[ind].length();

            for(int ind2=0; ind2<lonCad/2 ; ind2++){

                for(int y=0; y<2;y++){
                    conex += caminosTot[ind][cont];
                    cont++;
                }


                for(int elem=0 ;elem<_Conexiones.size(); elem++){
                    if(conex==_Conexiones[elem]){
                        valor += _Costos[elem];
                        break;
                    }
                }

                conex="";
            }
            Valor_Camino.push_back(valor);
            valor=0;
            cont = 0;
        }

        min = Valor_Camino[0];
        for(int index=0; index<Valor_Camino.size(); index++){
            if(min > Valor_Camino[index]){
                min = Valor_Camino[index];
                posicion=index;
            }
        }

        cout<<"**";
        cout<<"El camino mas corto es "<<caminosTot[posicion]<<endl;

}

void Router::AnadirEnlace()
{
    string newConex = "";
    int newValor=0;

    cout<<"Ingrese enlace nuevo --> ej: AB "<<endl;
    cin>>newConex;

    cout<<"Valor enlace --> "<<endl;
    cin>>newValor;

    _Conexiones.push_back(newConex);
    _Costos.push_back(newValor);

    /*
    for(int indi=0; indi<_Conexiones.size(); indi++){
        cout<<_Conexiones[indi];
    }
    for(int indi=0; indi<_Conexiones.size(); indi++){ //Mirar que se modifique en la clase
        cout<<_Costos[indi];
    }
    */


}

void Router::RemoverEnrutador(char EnrutadorBorra)
{
    for(int elem=0; elem<_Enrutadores.size(); elem++){
        if(_Enrutadores[elem]==EnrutadorBorra){
            _Enrutadores.erase(_Enrutadores.begin() + elem);
        }
    }


}


