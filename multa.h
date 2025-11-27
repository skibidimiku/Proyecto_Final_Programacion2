#include <iostream>
#include <fstream>
#include <cstring>
#include "Libro.h"
#include "Usuario.h"
#include "Ticket.h"

using namespace std;

class multa{
public:
    float getMulta(int id){
        contenido* libro;
        Ticket ticket;
        Usuario usu;
        float multa=0.0;

        fstream archivo;
        archivo.open("datos.dat", ios::binary | ios::in | ios::out);
        if (!archivo) {
            cout << "\n\t El archivo Producto no se abrio correctamente.";
            cin.get();
            return 1;
        }

        fstream ticketFile("ticket.txt", ios::in | ios::app | ios::out);
        if (!ticketFile) {
            cout << "\n\t No se pudo crear/abrir ticket.dat";
            ticketFile.close();
            archivo.close();
            return 1;
        }

        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        if(!UsuArchivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            ticketFile.close();
            UsuArchivo.close();
            archivo.close();
            return 1;
        }

        UsuArchivo.seekg((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario));


        while(ticketFile >> ticket){
            
                if(ticket.getId()==id){
                    archivo.seekg((ticket.getCodigo() - 1) * sizeof(Libro), ios::beg);
                    archivo.read(reinterpret_cast<char*>(&libro), sizeof(Libro));
                    if(libro->getCategoria()==1){
                        libro=new Libro();
                    }else if(libro->getCategoria()==2){
                        libro=new Revista();
                    }else{
                        libro=new Tesis();
                    }
                    time_t fechaDevolucion= ticket.getfechaDevolucion();
                    time_t fechaPrestamo= ticket.getfechaPrestamo();
                    double segundos= difftime(fechaDevolucion, fechaPrestamo);
                    int dias= segundos/86400;
                    if (dias>7){
                        multa= libro->calcMulta(dias);
                    }else{
                        multa=0.0;
                    }
            }
        }

        return multa;
    }
};