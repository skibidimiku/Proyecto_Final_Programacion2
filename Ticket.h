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
int id;
char nombre[30];
float subtotal;
float total;

public:
    Ticket() : codigo(0), subtotal(0.0), total(0.0) {}
    Ticket(int c, float sub, float tot) : codigo(c), subtotal(sub), total(tot) {}
    Ticket(const Ticket& otro) : codigo(otro.codigo), subtotal(otro.subtotal), total(otro.total) {}

    //setters y getters
    void setCodigo(int c) { codigo = c; }
    int getCodigo() const { return codigo; }
    void setId(int i) { id=i; }
    int getId(){ return id; }
    void setNombre(const char* nom) { strncpy(nombre, nom, 30); nombre[29] = '\0'; }
    const char* getNombre() const { return nombre; }
    void setSubtotal(float sub) { subtotal = sub; }
    float getSubtotal() const { return subtotal; }
    void setTotal(float total) { this->total = total; }
    float getTotal() const { return total; }
    void setfechaPrestamo(time_t fechaAct){ tiempodeprestamo=fechaAct; }
    time_t getfechaPrestamo(){ return tiempodeprestamo; }
    void setfechaDevolucion(time_t fechaAct){ tiempodeDevolucion=fechaAct; }
    time_t getfechaDevolucion(){ return tiempodeDevolucion; }

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


