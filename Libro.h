#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;

#ifndef LIBRO_DEFINED
#define LIBRO_DEFINED


class Libro{
    private:
    int ID;
    char titulo[30];
    char categoria[30];
    char autor[30];
    float precio;
    int EjemplaresTotales;


    public:
    void setID(int c) { ID = c; }
    int getID() { return ID; }

    void setTitulo(const char* t) { strncpy(titulo, t, 30); titulo[29] = '\0'; }
    const char* getTitulo() { return titulo; }

    void setCategoria(const char* c) { strncpy(categoria, c, 30); categoria[29] = '\0'; }
    const char* getCategoria() { return categoria; }

    void setAutor(const char* a) { strncpy(autor, a, 30); autor[29] = '\0'; }
    const char* getAutor() { return autor; }


    void setPrecio(float p) { precio = p; }
    float getPrecio() { return precio; }

    void setEjemeplaresTotales(int e) { EjemplaresTotales = e; }
    int getEjemplaresTotales() { return EjemplaresTotales; }


    //sobrecargas 

    //si es igual a otro libro 
    bool operator==(const Libro &otro) const {
        return this->ID == otro.ID;
    }
    //sumar existencia
        Libro& operator+=(int cant) {
        EjemplaresTotales += cant;
        return *this;
    }
    //restar existencia
    Libro& operator-=(int cant) {
        EjemplaresTotales -= cant;
        if (EjemplaresTotales < 0) EjemplaresTotales = 0;
        return *this;
    }
    

};
#endif // LIBRO_DEFINED