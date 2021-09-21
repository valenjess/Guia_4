#ifndef ROUTER_H
#define ROUTER_H
#include <vector>
#include <string>
#define FILENAME  "../Lab4_Routers/BD/conexiones.txt"

using namespace std;

class Router
{
private:
    vector<char> _Enrutadores;
    vector<string>_Conexiones;
    vector<int>_Costos;
    string _Archivo = FILENAME;
    char LetraPas ='A';
public:
    Router();
    vector<string> BusquedaCaminos(char origen, string camino, char destino,char LetraPas, char OrigenTemp,vector<string> &caminosTot);
    // Este metodo permite buscar los posibles caminos para llegar de un enrutador
    // origen a uno destino

    void  lecturaConex(); // Lee el txt que contiene la topologia y almacena las conexiones
                          // en un vector llamado _Conexiones

    void  lecturaCostos();//Almacena en un vector los costos de cada enlace,
                                    //en orden correspondiente

    int RutaCorta(vector<string>caminosTot); // Compara los costos de todos los caminos posibles del
                                             // origen al destino y retorna la posicion del camino
                                             // mas economico en el contenedor

    void ConocerEnrutadores();// Llena un vector _Enrutadores con los enrutadores de la topologia

    void ShowTablaRout(char Router ,string camino, char OrigenTemp,vector<string>&caminosTot);
    // Muestra la Tabla de enrutamiento de un determinado enrutador

    void CambCostoEnla();//Permite el cambio del costo de un enlace especifico

    void Camino(vector<string>caminosTot);// Recibe todos los caminos de un origen al
                                          //destino, busca e Imprime el más económico

    void AnadirEnlace(); //Permite al usuario añadir un nuevo enlace, con su costo asociado

    void RemoverEnrutador(char EnrutadorBorra);//Permite al usuario borrar un enrutador
                                              // y porsupuesto, todos los enlaces que lo involucran
};

#endif // ROUTER_H
