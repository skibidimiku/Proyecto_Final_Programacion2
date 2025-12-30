#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;

#ifndef LIBRO_DEFINED
#define LIBRO_DEFINED


class contenido{
    protected:
    int ID;
    char titulo[30];
    int categoria;
    char autor[30];
    int EjemplaresTotales;
    int EjemplaresDisponibles;

    public:
    virtual void setID(int c) = 0;
    virtual int getID() = 0;

    virtual void setTitulo(const char* t) = 0;
    virtual const char* getTitulo() = 0;
    
    void setCategoria(int c) { categoria = c; }
    int getCategoria() { return categoria; }

    virtual void setAutor(const char* a) = 0;
    virtual const char* getAutor() = 0;

    virtual void setEjemeplaresTotales(int e) = 0;
    virtual int getEjemplaresTotales() = 0;

    virtual void setEjemplaresDisponibles(int cant)=0;
    virtual int getEjemplaresDisponibles()=0;

    virtual void imprCond()=0;
    virtual float calcMulta(int dias)=0;
    virtual ~contenido() {}
};

class Libro : public contenido {
    public:

    void setID(int c) override { ID = c; }
    int getID() override { return ID; }

    void setTitulo(const char* t) override { strncpy(titulo, t, 30); titulo[29] = '\0'; }
    const char* getTitulo() override { return titulo; }

    void setAutor(const char* a) override { strncpy(autor, a, 30); autor[29] = '\0'; }
    const char* getAutor() override { return autor; }

    void setEjemeplaresTotales(int e) override { EjemplaresTotales = e; }
    int getEjemplaresTotales() override { return EjemplaresTotales; }

    void setEjemplaresDisponibles(int cant) override { EjemplaresDisponibles=cant; }
    int getEjemplaresDisponibles() override { return EjemplaresDisponibles; }

    void imprCond() override {
        cout << "\n\t El contenido prestado es un LIBRO, si pasan 14 dias despues \n\t del prestamo se te cobrara $20 por dia" << endl;
    }
    
    float calcMulta(int dias) override {
        if (dias > 14) {
            return (dias - 14) * 20.0; // Multa de $20 por día extra
        } else {
            return 0.0; // No hay multa si se devuelve a tiempo
        }
    }
};

class Revista : public contenido {
    public:

    void setID(int c) override { ID = c; }
    int getID() override { return ID; }

    void setTitulo(const char* t) override { strncpy(titulo, t, 30); titulo[29] = '\0'; }
    const char* getTitulo() override { return titulo; }

    void setAutor(const char* a) override { strncpy(autor, a, 30); autor[29] = '\0'; }
    const char* getAutor() override { return autor; }

    void setEjemeplaresTotales(int e) override { EjemplaresTotales = e; }
    int getEjemplaresTotales() override { return EjemplaresTotales; }

    void setEjemplaresDisponibles(int cant) override { EjemplaresDisponibles=cant; }
    int getEjemplaresDisponibles() override { return EjemplaresDisponibles; }

    void imprCond() override {
        cout << "\n\t El contenido prestado es una REVISTA, si pasan 7 dias despues \n\t del prestamo se te cobrara $10 por dia" << endl;
    }

    float calcMulta(int dias) override {
        if (dias > 7) {
            return (dias - 7) * 10.0; // Multa de $10 por día extra
        } else {
            return 0.0; // No hay multa si se devuelve a tiempo
        }
    }

};

class Tesis : public contenido {
    public:

    void setID(int c) override { ID = c; }
    int getID() override { return ID; }

    void setTitulo(const char* t) override { strncpy(titulo, t, 30); titulo[29] = '\0'; }
    const char* getTitulo() override { return titulo; }

    void setAutor(const char* a) override { strncpy(autor, a, 30); autor[29] = '\0'; }
    const char* getAutor() override { return autor; }

    void setEjemeplaresTotales(int e) override { EjemplaresTotales = e; }
    int getEjemplaresTotales() override { return EjemplaresTotales; }

    void setEjemplaresDisponibles(int cant) override { EjemplaresDisponibles=cant; }
    int getEjemplaresDisponibles() override { return EjemplaresDisponibles; }

    void imprCond() override {
        cout << "\n\t El contenido prestado es una TESIS, si pasan 30 dias despues \n\t del prestamo se te cobrara $50 por dia" << endl;
    }
    
    float calcMulta(int dias) override {
        if (dias > 30) {
            return (dias - 30) * 50.0; // Multa de $50 por día extra
        } else {
            return 0.0; // No hay multa si se devuelve a tiempo
        }
    }

};

#endif // LIBRO_DEFINED