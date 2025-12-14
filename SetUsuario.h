#ifndef SETUSU_DEFINED
#define SETUSU_DEFINED

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
        cout << "\n\n\t Ingresa la matricula del usuario [1-10]: ";
        id = usuar.esnumUsu();
        while (id < 1 && id > 10){
            cout << "\n\t La anterior es invalida. Ingresa la matricula del usuario [1-10]: ";
            id = usuar.esnumUsu();
        }
        
        usuar.setMatricula(id);

        char nombre[30];
        cout << "\n\t Ingresa el nombre del usuario: ";
        cin >> ws;
        cin.getline(nombre, 30);
        while (nombre[0]=='\0' || nombre[0]==' '){
            cout << "\n\t El nombre no puede estar vacio. Ingresa el nombre del usuario: ";
            cin.getline(nombre, 30);
        }
        usuar.setNombre(nombre);

        int permisos;
        char contrasena[30];
        cout << "\n\t Ingresa el nivel de usuario (1=administrador 0=Usuario): ";
        permisos = usuar.esnumUsu();
        while (permisos != 0 && permisos != 1){
            cout << "\n\t El valor de permisos no existe";
            cout << "\n\t Ingresa el nivel de usuario (1=administrador 0=Usuario): ";
            permisos = usuar.esnumUsu();
        }

        cout << "\n\t Ingresa la contrasena: ";
        cin >> ws;
        cin.getline(contrasena, 30);
        while (contrasena[0]=='\0' || contrasena[0]==' '){
            cout << "\n\t La contrasena no puede estar vacia. Ingresa la contrasena: ";
            cin.getline(contrasena, 30);
        }

        usuar.setContrasena(contrasena);
        usuar.setPermisos(permisos);

        char carrera[30];
        cout << "\n\t Ingresa la carrera: ";
        cin >> ws;
        cin.getline(carrera, 30);
        while (carrera[0]=='\0' || carrera[0]==' '){
            cout << "\n\t La carrera no puede estar vacia. Ingresa la carrera: ";
            cin.getline(carrera, 30);
        }
        
        usuar.setCarrera(carrera);

        char correo[30];
        cout << "\n\t Ingresa el correo: ";
        cin >> ws;
        cin.getline(correo, 30);
        while (correo[0]=='\0' || correo[0]==' '){
            cout << "\n\t El correo no puede estar vacio. Ingresa el correo: ";
            cin.getline(correo, 30);
        }
        
        usuar.setCorreo(correo);

        char tel[30];
        cout << "\n\t Ingresa tu telefono: ";
        cin >> ws;
        cin.getline(tel, 30);
        while (tel[0]=='\0' || tel[0]==' '){
            cout << "\n\t El telefono no puede estar vacio. Ingresa el telefono: ";
            cin.getline(tel, 30);
        }
        usuar.setTelefono(tel);

        int estatus=1; 
        usuar.setEstatus(estatus);

        UsuArchivo.seekp((usuar.getMatricula() - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.write(reinterpret_cast<char*>(&usuar), sizeof(Usuario));

        do {
            cout << "\n--------------------------------------";
            cout << "\n\t [1] ingresar otro usuario";
            cout << "\n\t [2] volver al menu principal";
            cout << "\n\t opcion: ";
            cin >> op;
        } while (op != 1 && op != 2);

        if (op == 2) break;


    }while(true);
    UsuArchivo.close();

    return 1;
}

#endif