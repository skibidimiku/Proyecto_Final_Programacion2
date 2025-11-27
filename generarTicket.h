#include <iostream>
#include <fstream>
#include <cstring>
#include "Libro.h"
#include "Usuario.h"
#include "Ticket.h"

using namespace std;

int GenerarTicketVenta(Libro& registro, Usuario& usu, int id) {
    Ticket ticket, ticketCont;
    int idl, cont=0;
    char resp;

    fstream archivo;
    archivo.open("datos.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "\n\t El archivo Producto no se abrio correctamente.";
        cin.get();
        return 1;
    }

    

    do {
        cout << "\n\t Ingresa el ID del Libro: ";
        cin >> idl;
        if (idl < 1 || idl > 10) {
            cout << "\n\t El ID debe estar entre 1 y 10.";
            cout << "\n\t Quieres intentar buscar otro libro por su ID? s/n: ";
            cin >> resp;
            if (resp == 'n' || resp == 'N') {
                archivo.close();
                return 1;
            }
        }
    } while (idl < 1 || idl > 10);

    archivo.seekg((idl - 1) * sizeof(Libro), ios::beg);
    archivo.read(reinterpret_cast<char*>(&registro), sizeof(Libro));
    if (registro.getID() == 0) {
        cout << "\n\t Aun no hay datos registrados para el ID " << id << ".";
        archivo.close();
        return 1;
    }

    // Verificar si hay suficiente existencia
    if (registro.getEjemplaresDisponibles() < 1) {
        cout << "\n\t No hay libros disponibles.";
        archivo.close();
        return 1;
    }

    // Actualizar el ticket
    ticket.setCodigo(registro.getID());

    // Restar la cantidad vendida de la existencia
    registro.setEjemplaresDisponibles(registro.getEjemplaresDisponibles() - 1);

    fstream ticketFile("ticket.txt", ios::in | ios::app | ios::out);
    if (!ticketFile) {
        if (!ticketFile) {
            cout << "\n\t No se pudo crear/abrir ticket.dat";
            ticketFile.close();
            archivo.close();
            return 1;
        }
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

    if (usu.getcantPrestamos() < 3){

        archivo.seekp((idl - 1) * sizeof(Libro), ios::beg);
        archivo.write(reinterpret_cast<const char*>(&registro), sizeof(Libro));
    
        if (!archivo) {
            cout << "\n\t Error al actualizar la existencia del libro";
            ticketFile.close();
            UsuArchivo.close();
            archivo.close();
            return 1;
        }
        
        usu.setcantPrestamos(usu.getcantPrestamos()+1);
        cout << "\n\t Este es tu prestamo numero: " << usu.getcantPrestamos() << endl;
    
        UsuArchivo.seekp((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));

        time_t tiempoPres;
        time(&tiempoPres);
        time_t tiempoDev;
        time(&tiempoDev);
        ticket.setfechaPrestamo(tiempoPres);
        while(ticketFile>>ticketCont){
            //busca el ultimo ticket para asignar el siguiente codigo
            cont++;
        }
        ticket.setId(cont+1);
        ticket.setEstado(1);
        ticket.setIdusu(usu.getMatricula());
        ticket.setTotal(0);
        ticket.setNombre(usu.getNombre());
        ticket.setCodigo(registro.getID());
        ticket.setfechaDevolucion(tiempoDev);

        ticketFile << " " << ticket.getCodigo() << " " << ticket.getNombre() << " " << ticket.getfechaPrestamo() << " " << ticket.getId() << " " << ticket.getTotal() << " " << ticket.getfechaDevolucion() << ticket.getIdusu() << ticket.getEstado() <<endl;

        time_t fec= ticket.getfechaPrestamo();
        char* fecha= ctime(&fec);
        cout << "\t ====== Ticket De Prestamo ======\n";
        cout << "\t Id del ticket: " << ticket.getId() << "\n";
        cout << "\t Nombre del usuario: " << ticket.getNombre() << "\n";
        cout << "\t Id del contenido: " << ticket.getCodigo() << "\n";
        cout << "\t Id del usuario: " << ticket.getIdusu() << "\n";
        cout << "\t Fecha Prestamo:"<< fecha << "\n";
        cout << "\t ==========================\n";

    }else{
        cout << "\n\t El usuario exede la cantidad de prestamos.";
        archivo.close();
        UsuArchivo.close();
        ticketFile.close();
        return 1;
    }
    
    archivo.close();
    UsuArchivo.close();
    ticketFile.close();

    return 0;
}