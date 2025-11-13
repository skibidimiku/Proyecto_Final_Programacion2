#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#ifndef Ticket_DEFINED
#define Ticket_DEFINED

class Ticket {
private:

int codigo; 
int cantidad; 
string nombre;
float subtotal;
float total;

public:
    Ticket() : codigo(0), cantidad(0), subtotal(0.0), total(0.0) {}
    Ticket(int c, int cant, float sub, float tot) : codigo(c), cantidad(cant), subtotal(sub), total(tot) {}
    Ticket(const Ticket& otro) : codigo(otro.codigo), cantidad(otro.cantidad), subtotal(otro.subtotal), total(otro.total) {}

    //setters y getters
    void setCodigo(int c) { codigo = c; }
    int getCodigo() const { return codigo; }
    void setCantidad(int cant) { cantidad = cant; }
    int getCantidad() const { return cantidad; }
    void setNombre(const string& nom) { nombre = nom; }
    string getNombre() const { return nombre; }
    void setSubtotal(float sub) { subtotal = sub; }
    float getSubtotal() const { return subtotal; }
    void setTotal(float total) { this->total = total; }
    float getTotal() const { return total; }

    void mostrarTicket() {
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
    }
};

#endif   


