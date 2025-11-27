#include <iostream>
#include <fstream>
#include <cstring>
#include "Libro.h"
#include "Usuario.h"
#include "multa.h"
#include "Ticket.h"

using namespace std;

int GenerarTicketDevolucion(Libro& registro, Usuario& usu, int id) {
    time_t tiempodeprestamo;
    time_t tiempodeDevolucion;
    multa multaObj;
    Ticket ticket;
    Ticket ticket1;
    Ticket ticket2;
    Ticket ticket3;
    int cantTic=0;
    int op;

    fstream archivo;
    archivo.open("datos.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "\n\t El archivo Producto no se abrio correctamente.";
        cin.get();
        return 1;
    }

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

    if (usu.getcantPrestamos() == 0){
        cout << "\n\t El usuario no tiene prestamos activos.";
        archivo.close();
        UsuArchivo.close();
        ticketFile.close();
        return 1;
    }

    while(ticketFile >> ticket && usu.getcantPrestamos() > cantTic){
        if(id==ticket.getId() && ticket.getEstado()==1){
            if (cantTic==0){
                ticket1.setfechaPrestamo(ticket.getfechaPrestamo());
                ticket1.setId(ticket.getId());
                ticket1.setTotal(ticket.getTotal());
                ticket1.setNombre(ticket.getNombre());
                ticket1.setCodigo(ticket.getCodigo());
                ticket1.setfechaDevolucion(ticket.getfechaDevolucion());
                cantTic++;
            }if (cantTic==1){
                ticket2.setfechaPrestamo(ticket.getfechaPrestamo());
                ticket2.setId(ticket.getId());
                ticket2.setTotal(ticket.getTotal());
                ticket2.setNombre(ticket.getNombre());
                ticket2.setCodigo(ticket.getCodigo());
                ticket2.setfechaDevolucion(ticket.getfechaDevolucion());
                cantTic++;
            }if (cantTic==2){
                ticket3.setfechaPrestamo(ticket.getfechaPrestamo());
                ticket3.setId(ticket.getId());
                ticket3.setTotal(ticket.getTotal());
                ticket3.setNombre(ticket.getNombre());
                ticket3.setCodigo(ticket.getCodigo());
                ticket3.setfechaDevolucion(ticket.getfechaDevolucion());
                cantTic++;
                break;
            }
            
        }
    }

    if (cantTic==3){
        tiempodeprestamo = ticket1.getfechaPrestamo();
        cout << "\n\t Tienes 3 prestamos activos, Cual deseas devolver?";
        cout << "\n\t [1] Libro: " << ticket1.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);

        tiempodeprestamo = ticket2.getfechaPrestamo();
        cout << "\n\t [2] Libro: " << ticket2.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);

        tiempodeprestamo = ticket3.getfechaPrestamo();
        cout << "\n\t [3] Libro: " << ticket3.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);

        cout << "\n\t [0] Salir.";

        cout << "\n\t Opcion: ";
        cin >> op;

        do{
            cout << "\n\t Opcion invalida, intenta de nuevo: ";

            tiempodeprestamo = ticket1.getfechaPrestamo();
            cout << "\n\t Tienes 3 prestamos activos, Cual deseas devolver?";
            cout << "\n\t [1] Libro: " << ticket1.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);

            tiempodeprestamo = ticket2.getfechaPrestamo();
            cout << "\n\t [2] Libro: " << ticket2.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);

            tiempodeprestamo = ticket3.getfechaPrestamo();
            cout << "\n\t [3] Libro: " << ticket3.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);

            cout << "\n\t [0] Salir.";

            cout << "\n\t Opcion: ";
            cin >> op;
        } while (op < 0 && op > 3);
        

    }else if(cantTic==2){
        tiempodeprestamo = ticket1.getfechaPrestamo();
        cout << "\n\t Tienes 2 prestamos activos, Cual deseas devolver?";
        cout << "\n\t [1] Libro: " << ticket1.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);

        tiempodeprestamo = ticket2.getfechaPrestamo();
        cout << "\n\t [2] Libro: " << ticket2.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);

        cout << "\n\t [0] Salir.";

        cout << "\n\t Opcion: ";
        cin >> op;

        do{
            cout << "\n\t Opcion invalida, intenta de nuevo: ";

            tiempodeprestamo = ticket1.getfechaPrestamo();
            cout << "\n\t Tienes 2 prestamos activos, Cual deseas devolver?";
            cout << "\n\t [1] Libro: " << ticket1.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);

            tiempodeprestamo = ticket2.getfechaPrestamo();
            cout << "\n\t [2] Libro: " << ticket2.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);

            cout << "\n\t [0] Salir.";

            cout << "\n\t Opcion: ";
            cin >> op;
        } while (op < 0 && op > 2);
    }else{
        tiempodeprestamo = ticket1.getfechaPrestamo();
        cout << "\n\t Tienes 1 prestamo activo, Lo deseas devolver?";
        cout << "\n\t Libro: " << ticket1.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);
        cout << "\n\t [1] Devolver";
        cout << "\n\t [0] Salir.";

        cout << "\n\t Opcion: ";
        cin >> op;

        do{
            cout << "\n\t Opcion invalida, intenta de nuevo: ";

            tiempodeprestamo = ticket1.getfechaPrestamo();
            cout << "\n\t Tienes 1 prestamo activo.";
            cout << "\n\t [1] Libro: " << ticket1.getCodigo() << " Prestado el: " << ctime(&tiempodeprestamo);
            cout << "\n\t [0] Salir.";

            cout << "\n\t Opcion: ";
            cin >> op;
        } while (op < 0 && op > 1);
    }

    switch(op){
        case 1:
            cout << "\n\t Devolviste el libro con ID: " << ticket1.getCodigo();
            ticket1.setEstado(0);

            ticketFile.seekp((ticket1.getId()) * sizeof(Ticket), ios::beg);
            ticketFile.write(reinterpret_cast<const char*>(&ticket1), sizeof(Ticket));

            archivo.seekg((ticket1.getCodigo() - 1) * sizeof(Libro), ios::beg);
            archivo.read(reinterpret_cast<char*>(&registro), sizeof(Libro));

            registro.setEjemplaresDisponibles(registro.getEjemplaresDisponibles()+1);

            archivo.seekp((ticket1.getCodigo() - 1) * sizeof(Libro), ios::beg);
            archivo.write(reinterpret_cast<const char*>(&registro), sizeof(Libro));

            if (multaObj.getMulta(id) > 0){
                cout << "\n\t Tienes una multa de: $" << multaObj.getMulta(id);
            }
            

            usu.setcantPrestamos(usu.getcantPrestamos()-1);

            UsuArchivo.seekp((id - 1) * sizeof(Usuario), ios::beg);
            UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));

            break;
        case 2:
            cout << "\n\t Devolviste el libro con ID: " << ticket2.getCodigo();

            break;
        case 3:
            cout << "\n\t Devolviste el libro con ID: " << ticket3.getCodigo();
            break;
        case 0:
            cout << "\n\t Saliendo de la devolucion...";
            archivo.close();
            UsuArchivo.close();
            ticketFile.close();
            return 0;
            break;
    }
    
    archivo.close();
    UsuArchivo.close();
    ticketFile.close();

    return 0;
}