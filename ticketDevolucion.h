#ifndef TICKETDEVOLUCION_DEFINED
#define TICKETDEVOLUCION_DEFINED

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "Libro.h"
#include "Usuario.h"
#include "multa.h"
#include "Ticket.h"

using namespace std;

int GenerarTicketDevolucion(Usuario& usu, int id) {
    int codigo, idtic, idusu, dia, mes, anio;
    bool estado; // 1: activo 0: devuelto
    char nombre[30];
    Multa multaObj;
    Fecha fecha;
    
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

    fstream ticketFile("ticket.txt",  ios::in | ios::out);
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

    if (usu.getcantPrestamos() == 0){
        cout << "\n\t El usuario no tiene prestamos activos.";
        archivo.close();
        UsuArchivo.close();
        ticketFile.close();
        return 1;
    }

    // Leer tickets en formato espacio-separado: codigo nombre fechaPrestamo id fechaDevolucion idusu estado
    ticketFile.seekg(0, ios::beg);
    while(ticketFile>> codigo >> nombre >> dia >> mes >> anio >> idtic >> idusu >> estado && usu.getcantPrestamos() > cantTic){
        if (idusu == id && usu.getidTic(cantTic) == idtic){
            cantTic++;
            if (cantTic == 1){
                ticket1.setCodigo(codigo);
                ticket1.setNombre(nombre);
                ticket1.setDiat(dia);
                ticket1.setMest(mes);
                ticket1.setAniot(anio);
                ticket1.setId(idtic);
                ticket1.setIdusu(idusu);
                ticket1.setEstado(estado);
            } else if (cantTic == 2){
                ticket2.setCodigo(codigo);
                ticket2.setNombre(nombre);
                ticket2.setDiat(dia);
                ticket2.setMest(mes);
                ticket2.setAniot(anio);
                ticket2.setId(idtic);
                ticket2.setIdusu(idusu);
                ticket2.setEstado(estado);
            } else if (cantTic == 3){
                ticket3.setCodigo(codigo);
                ticket3.setNombre(nombre);
                ticket3.setDiat(dia);
                ticket3.setMest(mes);
                ticket3.setAniot(anio);
                ticket3.setId(idtic);
                ticket3.setIdusu(idusu);
                ticket3.setEstado(estado);
            }
        }
    }

    if (cantTic==3){
        Fecha fecha(ticket1.getDiat(), ticket1.getmest(), ticket1.getAniot());
        cout << "\n\t Tienes 3 prestamos activos, Cual deseas devolver?";
        cout << "\n\t [1] Libro: " << ticket1.getCodigo() << " Prestado el:";
        fecha.mostrar();

        fecha.setfecha(ticket2.getDiat(), ticket2.getmest(), ticket2.getAniot());
        cout << "\n\t [2] Libro: " << ticket2.getCodigo() << " Prestado el:";
        fecha.mostrar();

        fecha.setfecha(ticket3.getDiat(), ticket3.getmest(), ticket3.getAniot());
        cout << "\n\t [3] Libro: " << ticket3.getCodigo() << " Prestado el:";
        fecha.mostrar();

        cout << "\n\t [0] Salir.";

        cout << "\n\t Opcion: ";
        op = usu.esnumUsu();

        while (op < 0 || op > 3){
            cout << "\n\t Opcion invalida, intenta de nuevo: ";

            fecha.setfecha(ticket1.getDiat(), ticket1.getmest(), ticket1.getAniot());
            cout << "\n\t Tienes 3 prestamos activos, Cual deseas devolver?";
            cout << "\n\t [1] Libro: " << ticket1.getCodigo() << " Prestado el:";
            fecha.mostrar();

            fecha.setfecha(ticket2.getDiat(), ticket2.getmest(), ticket2.getAniot());
            cout << "\n\t [2] Libro: " << ticket2.getCodigo() << " Prestado el:";
            fecha.mostrar();

            fecha.setfecha(ticket3.getDiat(), ticket3.getmest(), ticket3.getAniot());
            cout << "\n\t [3] Libro: " << ticket3.getCodigo() << " Prestado el:";
            fecha.mostrar();

            cout << "\n\t [0] Salir.";

            cout << "\n\t Opcion: ";
            op = usu.esnumUsu();
        } 
        

    }else if(cantTic==2){
        Fecha fecha(ticket1.getDiat(), ticket1.getmest(), ticket1.getAniot());
        cout << "\n\t Tienes 2 prestamos activos, Cual deseas devolver?";
        cout << "\n\t [1] Libro: " << ticket1.getCodigo() << " Prestado el:";
        fecha.mostrar();

        fecha.setfecha(ticket2.getDiat(), ticket2.getmest(), ticket2.getAniot());
        cout << "\n\t [2] Libro: " << ticket2.getCodigo() << " Prestado el:";
        fecha.mostrar();

        cout << "\n\t [0] Salir.";

        cout << "\n\t Opcion: ";
        op = usu.esnumUsu();

        while (op < 0 || op > 2){
            cout << "\n\t Opcion invalida, intenta de nuevo: ";

            fecha.setfecha(ticket1.getDiat(), ticket1.getmest(), ticket1.getAniot());
            cout << "\n\t Tienes 2 prestamos activos, Cual deseas devolver?";
            cout << "\n\t [1] Libro: " << ticket1.getCodigo() << " Prestado el:";
            fecha.mostrar();

            fecha.setfecha(ticket2.getDiat(), ticket2.getmest(), ticket2.getAniot());
            cout << "\n\t [2] Libro: " << ticket2.getCodigo() << " Prestado el:";
            fecha.mostrar();

            cout << "\n\t [0] Salir.";

            cout << "\n\t Opcion: ";
            op = usu.esnumUsu();
        }
    }else{
        Fecha fecha(ticket1.getDiat(), ticket1.getmest(), ticket1.getAniot());
        cout << "\n\t Tienes 1 prestamos activos, Cual deseas devolver?";
        cout << "\n\t [1] Libro: " << ticket1.getCodigo() << " Prestado el:";
        fecha.mostrar();

        cout << "\n\t [1] Devolver";
        cout << "\n\t [0] Salir.";

        cout << "\n\t Opcion: ";
        op = usu.esnumUsu();

        while (op < 0 || op > 1){
            cout << "\n\t Opcion invalida, intenta de nuevo: ";

            cout << "\n\t Tienes 1 prestamo activo.";
            cout << "\n\t [1] Libro: " << ticket1.getCodigo() << " Prestado el:";
            fecha.mostrar();
            cout << "\n\t [0] Salir.";

            cout << "\n\t Opcion: ";
            op = usu.esnumUsu();
        }
    }

    float multaTotal=0.0;
    Libro tmpLib;

    fstream TickeDev("TicketDev.txt", ios::out | ios::app);

    Fecha fechdev;

    switch(op){
        case 1:
            cout << "\n\t Devolviste el libro con ID: " << ticket1.getCodigo();
            ticket1.setEstado(0);
            ticket1.setDiat(fechdev.getDia());
            ticket1.setMest(fechdev.getmes());
            ticket1.setAniot(fechdev.getAnio());
            
            // Escribir cambio en ticket.txt (formato espacio-separado, sin seekp en texto)
            // Nota: Marcar como devuelto agregando nueva línea (mejor que tratar de actualizar línea existente)

            // Actualizar existencia en datos.dat
            if(ticket1.getCodigo() > 0){
                archivo.clear();
                archivo.seekg((ticket1.getCodigo() - 1) * sizeof(Libro), ios::beg);
                archivo.read(reinterpret_cast<char*>(&tmpLib), sizeof(Libro));
                if(!archivo) {
                    cout << "\n\t Error leyendo datos.dat para actualizar ejemplares.";
                } else {
                    tmpLib.setEjemplaresDisponibles(tmpLib.getEjemplaresDisponibles() + 1);
                    archivo.seekp((ticket1.getCodigo() - 1) * sizeof(Libro), ios::beg);
                    archivo.write(reinterpret_cast<const char*>(&tmpLib), sizeof(Libro));
                    if(!archivo) cout << "\n\t Error escribiendo datos.dat al devolver libro.";
                }
            }

            multaTotal= multaObj.getMulta(id, ticket1.getId());
            

            if (multaTotal > 0.0){
                cout << "\n\t Tienes una multa de: $" << multaTotal << " por la devolucion tardia.";
                usu.setMulta(multaTotal);
                usu.setEstatus(0); //bloquea al usuario
            }

           TickeDev << ticket1.getCodigo() << " " << ticket1.getNombre() << " " << ticket1.getDiat() << " " << ticket1.getmest() 
            << " " << ticket1.getAniot() << " " << ticket1.getId() << " "  <<  ticket1.getIdusu() << " " << ticket1.getEstado() << endl;
            usu.setcantPrestamos(usu.getcantPrestamos()-1);
            usu.setidTic(0, 0); // Limpiar el ID del ticket devuelto
            usu.aplastaridTic();

            UsuArchivo.seekp((id - 1) * sizeof(Usuario), ios::beg);
            UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));

            break;
        case 2:
            cout << "\n\t Devolviste el libro con ID: " << ticket2.getCodigo();
            ticket2.setEstado(0);
            ticket2.setDiat(fechdev.getDia());
            ticket2.setMest(fechdev.getmes());
            ticket2.setAniot(fechdev.getAnio());

            // Escribir cambio en ticket.txt (formato espacio-separado, sin seekp en texto)
            // Nota: Marcar como devuelto agregando nueva línea (mejor que tratar de actualizar línea existente)

            // Actualizar existencia en datos.dat
            if(ticket2.getCodigo() > 0){
                archivo.clear();
                archivo.seekg((ticket2.getCodigo() - 1) * sizeof(Libro), ios::beg);
                archivo.read(reinterpret_cast<char*>(&tmpLib), sizeof(Libro));
                if(!archivo) {
                    cout << "\n\t Error leyendo datos.dat para actualizar ejemplares.";
                } else {
                    tmpLib.setEjemplaresDisponibles(tmpLib.getEjemplaresDisponibles() + 1);
                    archivo.seekp((ticket2.getCodigo() - 1) * sizeof(Libro), ios::beg);
                    archivo.write(reinterpret_cast<const char*>(&tmpLib), sizeof(Libro));
                    if(!archivo) cout << "\n\t Error escribiendo datos.dat al devolver libro.";
                }
            }

            multaTotal= multaObj.getMulta(id, ticket2.getId());

            if (multaTotal > 0){
                cout << "\n\t Tienes una multa de: $" << multaTotal << " por la devolucion tardia.";
                usu.setMulta(multaTotal);
                usu.setEstatus(0); //bloquea al usuario
            }

             TickeDev << ticket2.getCodigo() << " " << ticket2.getNombre() << " " << ticket2.getDiat() << " " << ticket2.getmest() 
            << " " << ticket2.getAniot() << " " << ticket2.getId() << " "  <<  ticket2.getIdusu() << " " << ticket2.getEstado() << endl;

            usu.setidTic(0,1);
            usu.setcantPrestamos(usu.getcantPrestamos()-1);
            usu.aplastaridTic();

            UsuArchivo.seekp((id - 1) * sizeof(Usuario), ios::beg);
            UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));

            break;
        case 3:
            cout << "\n\t Devolviste el libro con ID: " << ticket3.getCodigo();
            ticket3.setEstado(0);
            ticket3.setDiat(fechdev.getDia());
            ticket3.setMest(fechdev.getmes());
            ticket3.setAniot(fechdev.getAnio());

            // Escribir cambio en ticket.txt (formato espacio-separado, sin seekp en texto)
            // Nota: Marcar como devuelto agregando nueva línea (mejor que tratar de actualizar línea existente)
            // Actualizar existencia en datos.dat
            if(ticket3.getCodigo() > 0){
                archivo.clear();
                archivo.seekg((ticket3.getCodigo() - 1) * sizeof(Libro), ios::beg);
                archivo.read(reinterpret_cast<char*>(&tmpLib), sizeof(Libro));
                if(!archivo) {
                    cout << "\n\t Error leyendo datos.dat para actualizar ejemplares.";
                } else {
                    tmpLib.setEjemplaresDisponibles(tmpLib.getEjemplaresDisponibles() + 1);
                    archivo.seekp((ticket3.getCodigo() - 1) * sizeof(Libro), ios::beg);
                    archivo.write(reinterpret_cast<const char*>(&tmpLib), sizeof(Libro));
                    if(!archivo) cout << "\n\t Error escribiendo datos.dat al devolver libro.";
                }
            }
            multaTotal= multaObj.getMulta(id, ticket3.getId());
            

            if (multaTotal > 0){
                cout << "\n\t Tienes una multa de: $" << multaTotal << " por la devolucion tardia.";
                usu.setMulta(multaTotal);
                usu.setEstatus(0); //bloquea al usuario
            }

             TickeDev << ticket2.getCodigo() << " " << ticket2.getNombre() << " " << ticket2.getDiat() << " " << ticket2.getmest() 
            << " " << ticket2.getAniot() << " " << ticket2.getId() << " "  <<  ticket2.getIdusu() << " " << ticket2.getEstado() << endl;

            usu.setidTic(0,2);
            usu.setcantPrestamos(usu.getcantPrestamos()-1);

            UsuArchivo.seekp((id - 1) * sizeof(Usuario), ios::beg);
            UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));

            break;
        case 0:
            cout << "\n\t Saliendo de la devolucion...";
            archivo.close();
            UsuArchivo.close();
            ticketFile.close();
            return 1;
            break;
        default: cout << "\n\t Opcion invalida.\n";
            break;
    }
    
    archivo.close();
    UsuArchivo.close();
    ticketFile.close();

    return 0;
}

#endif // TICKETDEVOLUCION_DEFINED