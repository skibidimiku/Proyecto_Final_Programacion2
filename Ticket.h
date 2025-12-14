#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include "Usuario.h"
#include "fecha.h"

using namespace std;

#ifndef Ticket_DEFINED
#define Ticket_DEFINED


class Ticket {
private:

int diat;
int mest;
int aniot;
int codigo;
bool estado; // 1: activo 0: devuelto
int id;
int idusu;
char nombre[30];


public:

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
    void setDiat(int d){ diat=d; }
    void setMest(int m){ mest=m; }
    void setAniot(int a){ aniot=a; }
    int getDiat(){ return diat; }
    int getmest(){ return mest; }
    int getAniot(){ return aniot; }


    /* friend istream& operator>>(istream& is, Ticket& t) {
        string line;
        if (!std::getline(is, line)) return is;
        if(!line.empty() && line.back() == '\r') line.pop_back();

        // Expect CSV: codigo|nombre|fechaPrestamo|id|fechaDevolucion|idusu|estado
        size_t p1 = line.find('|');
        size_t p2 = (p1==string::npos) ? string::npos : line.find('|', p1+1);
        size_t p3 = (p2==string::npos) ? string::npos : line.find('|', p2+1);
        size_t p4 = (p3==string::npos) ? string::npos : line.find('|', p3+1);
        size_t p5 = (p4==string::npos) ? string::npos : line.find('|', p4+1);
        size_t p6 = (p5==string::npos) ? string::npos : line.find('|', p5+1);

        if (p1==string::npos || p2==string::npos || p3==string::npos || p4==string::npos || p5==string::npos || p6==string::npos) {
            is.setstate(std::ios::failbit);
            return is;
        }

        try {
            t.codigo = stoi(line.substr(0, p1));
            string name = line.substr(p1+1, p2-p1-1);
            strncpy(t.nombre, name.c_str(), 29);
            t.nombre[29] = '\0';
            t.tiempodeprestamo = (time_t)stoll(line.substr(p2+1, p3-p2-1));
            t.id = stoi(line.substr(p3+1, p4-p3-1));
            t.tiempodeDevolucion = (time_t)stoll(line.substr(p4+1, p5-p4-1));
            t.idusu = stoi(line.substr(p5+1, p6-p5-1));
            t.estado = (line.substr(p6+1) == "1");
        } catch(...) {
            is.setstate(std::ios::failbit);
        }
        return is;
     } */

    void imprimirTicket(int id) {
        Ticket ticket;
        Usuario usu;
        int c=0;
        int codigo, idtic, idusu, dia, mes, anio;
        char nombreimp[30];
        bool estado; // 1: activo 0: devuelto
        
        
        fstream ticketFile("ticket.txt", ios::in | ios::app | ios::out);
        if (!ticketFile) {
            cout << "\n\t No se pudo crear/abrir ticket.dat";
            ticketFile.close();
            return;
        }

        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        if(!UsuArchivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            ticketFile.close();
            UsuArchivo.close();
            return;
        }

        UsuArchivo.seekg((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario));

        if (usu.getcantPrestamos() == 0){
            cout << "\n\t El usuario no tiene prestamos activos.";
            ticketFile.close();
            UsuArchivo.close();
            return;
        }
        

        ticketFile.seekg(0, ios::beg);
        while (ticketFile>> codigo >> nombreimp >> dia >> mes >> anio >> idtic >> idusu >> estado  && usu.getcantPrestamos() > c){
            if (ticket.getIdusu() == id && ticket.getEstado() == 1){
                c++;
                cout << "\t ====== Ticket ======\n";
                cout << "\t Id del ticket: " << idtic << "\n";
                cout << "\t Nombre del usuario: " << nombreimp << "\n";
                cout << "\t Id del contenido: " << codigo << "\n";
                cout << "\t Id del usuario: " << id << "\n";
                Fecha fechpres(dia, mes, anio);
                cout << "\t Fecha Prestamo:";
                fechpres.mostrar();
                cout << "\t Estado del ticket: " << (ticket.getEstado() ? "Activo" : "Devuelto") << "\n";
                cout << "\t ==========================\n";
            }
        }

        
    }

};

#endif   


