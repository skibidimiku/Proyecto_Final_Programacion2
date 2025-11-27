#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

#ifndef Ticket_DEFINED
#define Ticket_DEFINED

class Ticket {
private:

time_t tiempodeprestamo;
time_t tiempodeDevolucion;
int codigo;
bool estado; // 1: activo 0: devuelto
int id;
int idusu;
char nombre[30];
float total;

public:
    Ticket() : codigo(0), total(0.0) {}
    Ticket(int c, float tot) : codigo(c), total(tot) {}
    Ticket(const Ticket& otro) : codigo(otro.codigo), total(otro.total) {}

    //setters y getters
    void setCodigo(int c) { codigo = c; }
    int getCodigo() const { return codigo; }
    void setEstado(bool est) { estado = est; }
    bool getEstado() const { return estado; }
    void setId(int i) { id=i; }
    int getId(){ return id; }
    void setIdusu(int i) { idusu=i; }
    int getIdusu(){ return idusu; }
    void setNombre(const char* nom) { strncpy(nombre, nom, 30); nombre[29] = '\0'; }
    const char* getNombre() const { return nombre; }
    void setTotal(float total) { this->total = total; }
    float getTotal() const { return total; }
    void setfechaPrestamo(time_t fechaAct){ tiempodeprestamo=fechaAct; }
    time_t getfechaPrestamo(){ return tiempodeprestamo; }
    void setfechaDevolucion(time_t fechaAct){ tiempodeDevolucion=fechaAct; }
    time_t getfechaDevolucion(){ return tiempodeDevolucion; }

    friend istream& operator>>(istream& is, Ticket& t) {
        is >> t.codigo >> t.nombre >> t.tiempodeprestamo >> t.id >> t.total >> t.tiempodeDevolucion >> t.idusu >> t.estado;
        return is;
    }

    bool operator==(const Ticket& other) const {
        return codigo == other.codigo &&
               id == other.id &&
               strcmp(nombre, other.nombre) == 0 &&
               tiempodeprestamo == other.tiempodeprestamo &&
               tiempodeDevolucion == other.tiempodeDevolucion &&
               total == other.total;
    }
 /*   void mostrarTicket() {
        cout << "Codigo de producto: " << codigo << endl;
        cout << "Cantidad: " << cantidad << endl;
        cout << "Subtotal: " << subtotal << endl;
    }

    friend Ticket operator+(const Ticket& t1, const Ticket& t2) {
        return Ticket(0, t1.cantidad + t2.cantidad, t1.subtotal + t2.subtotal, t1.total + t2.total);
    }

    friend ostream& operator<<(ostream& os, const Ticket& t) {
        os << "Resumen de venta:" << endl;
        os << "Cantidad total: " << t.cantidad << endl;
        os << "Total: $" << t.subtotal << endl;
        return os;
    }*/
};

#endif   


