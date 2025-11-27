#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstring>
using namespace std;

#ifndef USUARIO_DEFINED
#define USUARIO_DEFINED


class Persona{
protected:
    char nombre[30];
    char carrera[30];
    char correo[50];
    char telefono[30];
public:

    void setNombre(const char* nom) { strncpy(nombre, nom, 30); nombre[29] = '\0'; }
    const char* getNombre() const { return nombre; }

    void setCarrera(const char* car) { strncpy(carrera, car, 30); carrera[29] = '\0'; }
    const char* getNCarrera() const { return carrera; }

    void setCorreo(const char* corr) { strncpy(correo, corr, 50); correo[49] = '\0'; }
    const char* getCorreo() const { return correo; }

    void setTelefono(const char* tel) { strncpy(telefono, tel, 30); carrera[29] = '\0'; }
    const char* getTelefono() const { return telefono; }
};


class Usuario : public Persona {
private:

int matricula;
char contrasena[30]; // solo aplica a administradores
int cantPres=0;
bool multa;
int Estatus; // 1=Activo  0=Bloqueado 
int permisos; // 1=Administrador  0=Usuario

public:

    //setters y getters

    void setMatricula(int c) { matricula = c; }
    int getMatricula() const { return matricula; }

    void setEstatus(int est) { Estatus = est; }
    int getEstatus() const { return Estatus; }

    void setPermisos(int per){ permisos=per; }
    int getPermisos() const{ return permisos; }

    void setcantPrestamos(int can){ cantPres=can; }
    int getcantPrestamos() const{ return cantPres; }

    void setContrasena(const char* con){ strncpy(contrasena, con, 30); contrasena[29] = '\0'; }
    const char* getContrasena() const{ return contrasena; }

    void setMulta(bool mul){ multa=mul; }
    bool getMulta(){ return multa; }

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
                    cout << "\n\tDame la contrasena: ";
                    cin.ignore();
                    cin.getline(contra, 30);
                    while (!(usu==contra) && intentos < 3){
                        cout << "\n\tLa contrasena es in correcta te quedan [" << 3 - intentos << "] intentos.";
                        cout << "\n\tDame la contrasena: ";
                        cin.getline(contra, 30);
                        intentos++;
                    }

                    if (usu==contra){
                        return 1;
                    }
                }else{
                    return 0;
                }
            }
        }

        if (intentos==3){
            cout<<"\n\t Muchos intentos fallidos." << endl;
        }else{
            cout << "\n\t El usuario no existe." << endl;
        }

        return -1;
    }

    void printUsuario(int id){
        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        UsuArchivo.seekp((id - 1) * sizeof(Usuario), ios::beg);
        Usuario usu;
        UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));
        cout << "\n\t El Nombre es: " << nombre;
        cout << "\n\t Su carrera es es: " << nombre;

    }

    bool operator==(const string cont) const {
        return this->contrasena == cont;
    }

    void operator +=(int cant){
        cantPres=cantPres+cant;
    }
};

#endif // USUARIO_DEFINED


