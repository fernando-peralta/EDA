#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <cmath>

using namespace std;


//Un punto se define con k dimensiones cuando k es el numero de coordenadas que tiene, por lo tanto, un punto en k dimensiones pasa a ser una matriz de n puntos multiplicada por k dimensiones


double calcularDistancia(const vector<double>& punto1, const vector<double>& punto2, int dimension) { // Calculamos la distancia entre dos puntos
    double aux = 0; // Valor auxiliar para almacenar la distancia euclidiana 
    for (int i = 0; i < dimension; ++i)
    {
        aux += (punto2[i] - punto1[i]) * (punto2[i] - punto1[i]); //hallamos la diferencia elevada al cuadrado
    }
    double distancia = sqrt(aux); // sacamos la raiz de todas las distancias encontradas
    return distancia; // devolvemos el valor de distancia
}


int main()
{
    int dimension = 10; //cantidad de dimensiones de los puntos
    int npuntos = 100; //cantidad de puntos

    vector<vector<double>> points(npuntos, vector<double>(dimension)); // vector de puntos de la dimension indicada
    random_device rd;  // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(0, 1.0); //Limites entre los cuales se hallan los valores random

    for (int n = 0; n < npuntos; ++n)
    {
        for (int i = 0; i < dimension; i++)
        {
            points[n][i] = dis(gen);// llenamos el vector de puntos random entre 0 y 1
        }
    }

    vector<double>* vectorp = &points[0]; //puntero hacia el primer punto
    vector<double> respuestas; // vector de respuestas
    ofstream archivo("datos_10.txt"); // archivo.txt en el que ponemos los datos 

    //Calculamos la distancia entre todos los puntos 
    for (int j = 0; j < npuntos; j++) {
        vector<double>* vectorrecor = vectorp + 1;// recorremos los puntos que faltan a excepcion del punto inicial

        for (int a = j + 1; a < npuntos; a++)
        {
            respuestas.push_back(calcularDistancia(*vectorp, *vectorrecor, dimension));// Agregamos la distancia de la respuesta a nuestro vector
            vectorrecor += 1;
        }
        vectorp += 1; //avanzamos el punto
    }

    // En caso el archivo de respuestas este abierto
    if (archivo.is_open()) {
        for (const double& item : respuestas) { // por cada uno de los items agregamos con un salto de linea
            archivo << item << endl;
        }
        archivo.close(); // cerramos el archivo
        cout << "Datos exportados correctamente";
    }
    else
    {
        cout << "No se pudo abrir el archivo correctamente";
    }
}