#include <iostream>
#include <fstream>
#include "Libro.h"
using namespace std;


int SetLibro() {
    //abre el archivo en modo modificar
    fstream archivo("datos.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "\n\t El archivo no se abrio correctamente.";
        return 1;
    }

    Libro registro;
    int selec;

    do {   //aqui va a tomar todos los datos del usuario, los guarda con los SET
        int id;
        cout << "\n\n\t Ingresa el ID del libro [1-10]: ";
        cin >> id;
        registro.setID(id);

        char titulo[30];
        cout << "\n\t Ingresa el TITULO del LIBRO: ";
        cin.ignore();
        cin.getline(titulo, 30);
        registro.setTitulo(titulo );

        float precio;
        cout << "\n\t Ingresa el PRECIO: ";
        cin >> precio;
        registro.setPrecio(precio);

        char cat[30];
        cout << "\n\t Ingresa la CATEGORIA del LIBRO: ";
        cin.ignore();
        cin.getline(cat, 30);
        registro.setCategoria(cat);


        char aut[30];
        cout << "\n\t Ingresa el AUTOR del LIBRO: ";
        cin.ignore();
        cin.getline(aut, 30);
        registro.setAutor(aut);


        int existencia; 
        cout << "\n\t Ingresa los EJEMPLARES TOTALES: ";
        cin >> existencia;
        registro.setEjemeplaresTotales(existencia);
        
        //mueve el cursor de "POINTER" para saber en donde va a hacer cambios en el archivo 
        //esto lo hace usando le posicion de nuestra "ID"
        //EJ: ID: 6 -> "voy a buscar en la posicion 6 del archivo".
        archivo.seekp((registro.getID() - 1) * sizeof(Libro), ios::beg);
        //ya tiene la posicion correcta, entonces traduce los datos a su estado original de esa posicion
        //EJ: "voy a escribir en la posicion del archivo que estoy posicionado."
        archivo.write(reinterpret_cast<char*>(&registro), sizeof(Libro));
        cout << "\n\t -> Datos grabados <-\n";
        do {
            cout << "\n--------------------------------------";
            cout << "\n\t [1] ingresar otro libro";
            cout << "\n\t [2] volver al menu principal";
            cout << "\n\t opcion: ";
            cin >> selec;
        } while (selec != 1 && selec != 2);

        if (selec == 2)
            break;

    } while (true);

    archivo.close();
    return 0;
}
