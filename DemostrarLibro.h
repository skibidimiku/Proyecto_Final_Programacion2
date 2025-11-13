#ifndef MOSTRARPRODUCTOS_H
#define MOSTRARPRODUCTOS_H

#include <iostream>
#include <fstream>
#include "Libro.h"

using namespace std;


inline int DemonstrarLibro(){
    fstream archivo;
    //habre el archivo en modo "solo leer."
    archivo.open("datos.dat", ios::binary|ios::in);
    if(!archivo){
        cout << "\n\t No se pudo abrir el archivo.";
        cin.get();
        return 1; 
    }
    Libro registro;
    int cont=0;
    archivo.seekg(0);
    //saca los datos del archivo, la formula simplemente dice "pasa de BINARIO a LO QUE ERA ORIGINALMENTE."
    while(archivo.read(reinterpret_cast<char*>(&registro), sizeof(Libro))){
        cout << "\n------------------------------------------";
        cout << "\n\t -> Datos del producto <-";
        cout << "\n\t ID: " << registro.getID();
        cout << "\n\t Titulo: " << registro.getTitulo();
        cout << "\n\t Precio: " << registro.getPrecio(); 
        cout << "\n\t Categoria: " << registro.getCategoria();  
        cout << "\n\t Autor: " << registro.getAutor();
        cout << "\n\t Ejmp totales: " << registro.getEjemplaresTotales() << endl;
        cont++;
    }

    if(cont == 0){
        cout << "\n\t Archivo vacio o no se encontraron registros.";
    }

    archivo.close();
    return 0;
}

#endif // MOSTRARPRODUCTOS_H