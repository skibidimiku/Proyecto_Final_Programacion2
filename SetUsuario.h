#include <iostream>
#include <fstream>
#include "Usuario.h"

using namespace std;

int SetUsuario(){
    fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
    if(!UsuArchivo){
        cout << "\n\t El archivo no se abrio correctamente.";
        return 1;
    }

    Usuario usuar;
    int op;

    do{
        int id;
        cout << "\n\n\t Ingresa el ID del usuario [1-10]: ";
        cin >> id;
        usuar.setMatricula(id);

        char nombre[30];
        cout << "\n\t Ingresa el nombre del usuario: ";
        cin.ignore();
        cin.getline(nombre, 30);
        usuar.setNombre(nombre);

        int permisos, newpermisos;
        char contrasena[30];
        cout << "\n\t Ingresa el nivel de usuario (1=administrador 0=Usuario): ";
        cin >> permisos;
        newpermisos=permisos;
        do{
            if (newpermisos ==1){
                cout << "\n\t Dame la contrasena: ";
                cin.ignore();
                cin.getline(contrasena, 30);
                usuar.setContrasena(contrasena);
                break;
            }else if (newpermisos ==0){
                usuar.setContrasena("Contrasena");
                break;
            }else{
                cout << "\n\t El valor de permisos no existe";
                cout << "\n\t Ingresa el nivel de usuario (1=administrador 0=Usuario): ";
                cin >> newpermisos;
            } 
        } while (newpermisos != 0 || newpermisos != 1);
        
        usuar.setPermisos(newpermisos);

        char carrera[30];
        cout << "\n\t Ingresa la carrera: ";
        cin.ignore();
        cin.getline(carrera, 30);
        usuar.setCorreo(carrera);

        char correo[30];
        cout << "\n\t Ingresa el correo: ";
        cin.ignore();
        cin.getline(correo, 30);
        usuar.setCorreo(correo);

        char tel[30];
        cout << "\n\t Ingresa el telefono: ";
        cin.ignore();
        cin.getline(tel, 30);
        usuar.setTelefono(tel);


        int estatus=1; 
        usuar.setEstatus(estatus);

        do {
            cout << "\n--------------------------------------";
            cout << "\n\t [1] ingresar otro usuario";
            cout << "\n\t [2] volver al menu principal";
            cout << "\n\t opcion: ";
            cin >> op;
        } while (op != 1 && op != 2);

        if (op == 2) break;


    }while(true);

    return -1;
}