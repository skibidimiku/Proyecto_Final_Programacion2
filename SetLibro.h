#include <iostream>
#include <fstream>
#include "Libro.h"
using namespace std;

int esnumli();

int SetLibro() {
    //abre el archivo en modo modificar
    fstream archivo("datos.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "\n\t El archivo no se abrio correctamente.";
        return 1;
    }

    contenido* registro=new Libro();
    int selec;

    do {   //aqui va a tomar todos los datos del usuario, los guarda con los SET
        int id;
        cout << "\n\n\t Ingresa el ID del libro [1-10]: ";
        id = esnumli();

        while (id < 1 && id > 10){
            cout << "\n\t La anterior es invalida. Ingresa la id del libro [1-10]: ";
            id = esnumli();
        }

        registro->setID(id);

        char titulo[30];
        cout << "\n\t Ingresa el TITULO del LIBRO: ";
        cin.ignore();
        cin.getline(titulo, 30);

        while (titulo[0]=='\0' || titulo[0]==' '){
            cout << "\n\t El nombre no puede estar vacio. Ingresa el nombre del usuario: ";
            cin.getline(titulo, 30);
        }

        registro->setTitulo(titulo );

        int cat;
        cout << "\n\t Ingresa la CATEGORIA del LIBRO[1-3]: ";
        cat = esnumli();

        while (cat < 1 && cat > 3){
            cout << "\n\t La anterior es invalida. Ingresa la categoria del libro [1-3]: ";
            cat = esnumli();
        }

        registro->setCategoria(cat);


        char aut[30];
        cout << "\n\t Ingresa el AUTOR del LIBRO: ";
        cin.ignore();
        cin.getline(aut, 30);

        while (aut[0]=='\0' || aut[0]==' '){
            cout << "\n\t El nombre no puede estar vacio. Ingresa el nombre del usuario: ";
            cin.getline(aut, 30);
        }

        registro->setAutor(aut);


        int existencia; 
        cout << "\n\t Ingresa los EJEMPLARES TOTALES: ";
        existencia = esnumli();

        while (existencia <= 0){
            cout << "\n\t No puede ser meno a 1. Ingresa la nueva cantidad [1-3]: ";
            existencia = esnumli();
        }
        
        registro->setEjemeplaresTotales(existencia);
        registro->setEjemplaresDisponibles(existencia);
        
        //mueve el cursor de "POINTER" para saber en donde va a hacer cambios en el archivo 
        //esto lo hace usando le posicion de nuestra "ID"
        //EJ: ID: 6 -> "voy a buscar en la posicion 6 del archivo".
        archivo.seekp((registro->getID() - 1) * sizeof(Libro), ios::beg);
        //ya tiene la posicion correcta, entonces traduce los datos a su estado original de esa posicion
        //EJ: "voy a escribir en la posicion del archivo que estoy posicionado."
        archivo.write(reinterpret_cast<char*>(registro), sizeof(Libro));
        cout << "\n\t -> Datos grabados <-\n";
        do {
            cout << "\n--------------------------------------";
            cout << "\n\t [1] ingresar otro libro";
            cout << "\n\t [2] volver al menu principal";
            cout << "\n\t opcion: ";
            selec = esnumli();
        } while (selec != 1 && selec != 2);

        if (selec == 2)
            break;

    } while (true);

    delete registro;
    archivo.close();
    return 0;
}

int esnumli(){
    string num;
    while (true){
        getline(cin, num);

        // Si la cadena está vacía → seguir pidiendo
        if (num.empty()) {
            cout << "\n\t No ingreso nada. Intente de nuevo.\n";
            continue;
        }

        bool valida = true;
        for (char c : num) {
            if (!isdigit(c)) {
                valida = false;
                break;
            }
        }

        if (!valida){
            cout << "\n\t No es un numero valido. Intente de nuevo.\n";
            continue;
        }

        // Ahora SI es seguro llamar a stoi
        return stoi(num);
    }
}