#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#ifndef USUARIO_DEFINED
#define USUARIO_DEFINED

class Usuario {
private:


char nombre[30];
int matricula;
char carrera[30];
char correo[50];
char contrasena[30]; // solo aplica a administradores
char telefono[30];
int Estatus; // 1=Activo  0=Bloqueado 
int permisos; // 1=Administrador  0=Usuario

public:

    //setters y getters
    void setNombre(const char* nom) { strncpy(nombre, nom, 30); nombre[29] = '\0'; }
    const char* getNombre() const { return nombre; }

    void setMatricula(int c) { matricula = c; }
    int getMatricula() const { return matricula; }

    void setCarrera(const char* car) { strncpy(carrera, car, 30); carrera[29] = '\0'; }
    const char* getNCarrera() const { return carrera; }

    void setCorreo(const char* corr) { strncpy(correo, corr, 50); correo[49] = '\0'; }
    const char* getCorreo() const { return correo; }

    void setTelefono(const char* tel) { strncpy(telefono, tel, 30); carrera[29] = '\0'; }
    const char* getTelefono() const { return telefono; }

    void setEstatus(int est) { Estatus = est; }
    int getEstatus() const { return Estatus; }

    void setPermisos(int per){ permisos=per; }
    int getPermisos() const{ return permisos; }

    void setContrasena(const char* con){ strncpy(contrasena, con, 30); contrasena[29] = '\0'; }
    const char* getContrasena() const{ return contrasena; }

    int iniciarSecion(int id){
        fstream Archivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        Usuario usu;
        int intentos=0;
        char contra[30];
        if (!Archivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            return -1;
        }

        while(Archivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario))){
            if (usu.matricula == id){
                if (usu.permisos == 1){
                    cout << "\n\tDame la contraseña: ";
                    cin.ignore();
                    cin.getline(contra, 30);
                    while ((usu==contra) == 0 && intentos < 3){
                        cout << "\n\tLa contraseña es in correcta te quedan [" << 3 - intentos << "] intentos.";
                        cout << "\n\tDame la contraseña: ";
                        cin.ignore();
                        cin.getline(contra, 30);
                    }

                    if (usu==contra){
                        return 1;
                    }
                }else{
                    return 0;
                }
            }
        }

        cout << "\n\t El usuario no existe." << endl;
        return -1;
    }

    

    bool operator==(const string cont) const {
        return this->contrasena == cont;
    }
};

#endif // USUARIO_DEFINED


