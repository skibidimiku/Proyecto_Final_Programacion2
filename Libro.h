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

    virtual void imprCond(int dias, float preci)=0;
    virtual float calcMulta(int dias, int diasPermitidos, float precioDia) = 0;
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

    void imprCond(int dias, float preci) override {
        cout << "\n\t El contenido prestado es un LIBRO, si pasan " << dias <<  " dias despues \n\t del prestamo se te cobrara $" << preci << " por dia" << endl;
    }
    
    float calcMulta(int dias, int diasPermitidos, float precioDia) override {
        if (dias > diasPermitidos) return (dias - diasPermitidos) * precioDia;
        return 0.0;
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

    void imprCond(int dias, float preci) override {
        cout << "\n\t El contenido prestado es una REVISTA, si pasan " << dias <<  " dias despues \n\t del prestamo se te cobrara $" << preci << " por dia" << endl;
    }

    float calcMulta(int dias, int diasPermitidos, float precioDia) override {
        if (dias > diasPermitidos) return (dias - diasPermitidos) * precioDia;
        return 0.0;
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

    void imprCond(int dias, float preci) override {
        cout << "\n\t El contenido prestado es una TESIS, si pasan " << dias <<  " dias despues \n\t del prestamo se te cobrara $" << preci << " por dia" << endl;
    }
    
    float calcMulta(int dias, int diasPermitidos, float precioDia) override {
        if (dias > diasPermitidos) return (dias - diasPermitidos) * precioDia;
        return 0.0;
    }

};

#endif // LIBRO_DEFINED