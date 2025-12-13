#include <fstream>
#include <iostream>
#include <ctime>
#include <cctype>
#include <vector>
#include <algorithm>
#include "Usuario.h"
#include "CrearCascaron.h"
#include "SetUsuario.h"
#include "ticketDevolucion.h"
#include "SetLibro.h"
#include "DemostrarLibro.h"
#include "Libro.h"
#include "multa.h"
#include "ModificarLibro.h"
#include "EliminarLibro.h"
#include "generarTicket.h"
#include "menus_Ayuda.h"


using namespace std;


 void usuariosMorosos(){
        Usuario usu;
        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        if (!UsuArchivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            return;
        }

        cout << "\n\t ---> Usuarios con multas pendientes <---\n";
        while (UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario))){
            if (usu.getMulta() > 0.0 && strcmp(usu.getNombre(), "") != 0){
                cout << "\n\t Nombre: " << usu.getNombre();
                cout << "\n\t Matricula: " << usu.getMatricula();
                cout << "\n\t Dias Atrasados: " << usu.getMulta() / 5.0 << " dias\n";
                cout << "\n\t Multa pendiente: $" << usu.getMulta() << "\n";
            }else{
                cout << "\n\t No hay usuarios morosos.\n";
                return;
            }
        }

        UsuArchivo.close();
    }

void prestamosActivos(){
    Usuario usu;
    int pos;
    fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
    if (!UsuArchivo){
        cout << "\n\t El archivo no se abrio correctamente.";
        return;
    }

    Libro lib;
    fstream libarchivo("datos.dat", ios::binary | ios::in | ios::out);
    if (!libarchivo){
        cout << "\n\t El archivo no se abrio correctamente.";
        return;
    }

    cout << "\n\t --->Prestamos activos <---\n";
    cout << "\n\t [1] Por usuarios ";
    cout << "\n\t [2] Por MAterial prestado ";
    cout << "\n\t Elige una opcion: ";
    cin >> pos;

    switch (pos){
        case 1:
         while (UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario))){
            if (usu.getcantPrestamos() > 0 && strcmp(usu.getNombre(), "") != 0){
                cout << "\n\t Nombre: " << usu.getNombre();
                cout << "\n\t Matricula: " << usu.getMatricula();
                cout << "\n\t Cantidad de prestamos activos: " << usu.getcantPrestamos() << " libros\n";
            }else{
                cout << "\n\t No hay usuarios con prestamos activos.\n";
                return;
            }
        }
            break;
        case 2:
            while(libarchivo.read(reinterpret_cast<char*>(&lib), sizeof(Libro))){
                if (lib.getEjemplaresDisponibles() < lib.getEjemplaresTotales() && lib.getID() != 0){
                    cout << "\n\t Titulo: " << lib.getTitulo();
                    cout << "\n\t ID: " << lib.getID();
                    cout << "\n\t Autor: " << lib.getAutor();
                    cout << "\n\t Ejemplares prestados: " << (lib.getEjemplaresTotales() - lib.getEjemplaresDisponibles()) << " libros\n";
                }else{
                    cout << "\n\t No hay materiales prestados.\n";
                    return;
                }
            }
            return;
        default:
            cout << "\n\t Opcion invalida.\n";
            return;
            
    }
    UsuArchivo.close();
    libarchivo.close();
}

void topMatPrestamos(){
    Libro lib;
    struct TopMaterial {
        int matricula;
        char nombre[30];
        int prestamos;
    };
    vector<TopMaterial> topMaterial;
    fstream MatArchivo("Datos.dat", ios::binary | ios::in | ios::out);
    if (!MatArchivo){
        cout << "\n\t El archivo no se abrio correctamente.";
        return;
    }
    while (MatArchivo.read(reinterpret_cast<char*>(&lib), sizeof(Libro))){
        if (strcmp(lib.getTitulo(), "") != 0){
            TopMaterial tm;
            tm.matricula = lib.getID();
            strncpy(tm.nombre, lib.getTitulo(), 30);
            tm.prestamos = lib.getEjemplaresTotales() - lib.getEjemplaresDisponibles();
            topMaterial.push_back(tm);
        }

        sort(topMaterial.begin(), topMaterial.end(), [](const TopMaterial& a, const TopMaterial& b) {
            return a.prestamos > b.prestamos;
        });

        cout << "\n\t ---> Top Materiales mas prestados <---\n";
        for (size_t i = 0; i < topMaterial.size() && i < 5; ++i){
            cout << "\n\t Titulo: " << topMaterial[i].nombre;
            cout << "\n\t ID: " << topMaterial[i].matricula;
            cout << "\n\t Cantidad de prestamos: " << topMaterial[i].prestamos << " libros\n";
        }
    }
}