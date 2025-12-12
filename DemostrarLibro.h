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
    
    int cont=0;
    archivo.seekg(0);
    //saca los datos del archivo, la formula simplemente dice "pasa de BINARIO a LO QUE ERA ORIGINALMENTE."
    Libro tmp;
    while(archivo.read(reinterpret_cast<char*>(&tmp), sizeof(Libro))){
        if(tmp.getID() != 0){  // Verifica si hay datos (ID != 0)
            contenido* registro = nullptr;
            int cat = tmp.getCategoria();
            if(cat == 1) registro = new Libro();
            else if(cat == 2) registro = new Revista();
            else if(cat == 3) registro = new Tesis();
            else {
                delete registro;
                continue;  // Salta registros inválidos
            }
            
            // Copiar datos del tmp al objeto polimorfico
            registro->setID(tmp.getID());
            registro->setTitulo(tmp.getTitulo());
            registro->setCategoria(tmp.getCategoria());
            registro->setAutor(tmp.getAutor());
            registro->setEjemeplaresTotales(tmp.getEjemplaresTotales());
            registro->setEjemplaresDisponibles(tmp.getEjemplaresDisponibles());
            
            cout << "\n------------------------------------------";
            cout << "\n\t -> Datos del producto <-";
            cout << "\n\t ID: " << registro->getID();
            cout << "\n\t Titulo: " << registro->getTitulo();
            cout << "\n\t Categoria: " << registro->getCategoria();  
            cout << "\n\t Autor: " << registro->getAutor();
            cout << "\n\t Ejmp totales: " << registro->getEjemplaresTotales();
            cout << "\n\t Ejemplares disponibles: " << registro->getEjemplaresDisponibles() << endl;
            
            delete registro;
            cont++;
        }
        
    }

    if(cont == 0){
        cout << "\n\t Archivo vacio o no se encontraron registros.";
    }

    archivo.close();
    return 0;
}

#endif // MOSTRARPRODUCTOS_H