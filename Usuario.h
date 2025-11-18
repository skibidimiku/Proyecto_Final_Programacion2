#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#ifndef USUARIO_DEFINED
#define USUARIO_DEFINED

class Usuario {
private:


string nombre;
int matricula;
string carrera;
string correo;
string contrasena; // solo aplica a administradores
string telefono;
int Estatus; // 1=Activo  0=Bloqueado 
int permisos; // 1=Administrador  0=Usuario

public:

    //setters y getters
    void setNombre(const string& nom) { nombre = nom; }
    string getNombre() const { return nombre; }

    void setMatricula(int c) { matricula = c; }
    int getMatricula() const { return matricula; }

    void setCarrera(const string& car) { carrera = car; }
    string getNCarrera() const { return carrera; }

    void setCorreo(const string& corr) { correo = corr; }
    string getCorreo() const { return correo; }

    void setTelefono(string tel) { telefono = tel; }
    string getTelefono() const { return telefono; }

    void setEstatus(int est) { Estatus = est; }
    int getEstatus() const { return Estatus; }

    void setPermisos(int per){ permisos=per; }
    int getPermisos() const{ return permisos; }

    void setContrasena(string con){ contrasena=con; }
    string getContrasena() const{ return contrasena; }

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


