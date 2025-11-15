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
int telefono;
int activo;

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

    void setTelefono(int tel) { telefono = tel; }
    int getTelefono() const { return telefono; }

    void setActivo(int act) { activo = act; }
    int getActivo() const { return activo; }
};

#endif // USUARIO_DEFINED


