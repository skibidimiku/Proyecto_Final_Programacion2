#ifndef GENTI_DEFINED
#define GENTI_DEFINED

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "Libro.h"
#include "Usuario.h"
#include "Ticket.h"
#include "fecha.h"
#include "multa.h"

using namespace std;

int GenerarTicketPrestamo(Usuario& usu, int id) {
    int codigo, idtic, idusu, dia, mes, anio, diasPermitidos;
    bool estado; // 1: activo 0: devuelto
    char nombre[30];
    float precioDia;

    Ticket ticket;
    contenido* registro = nullptr;
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
        idl = usu.esnumUsu();
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

    // Leer el registro físico desde el archivo en un objeto temporal (Libro tiene la estructura de almacenamiento)
    Libro tmp;
    archivo.seekg((idl - 1) * sizeof(Libro), ios::beg);
    archivo.read(reinterpret_cast<char*>(&tmp), sizeof(Libro));
    
    int cat = tmp.getCategoria();
    contenido* tmp2 = nullptr;
    if (cat==1) tmp2 = new Libro();
    else if (cat==2) tmp2 = new Revista();
    else tmp2 = new Tesis();
    
    // Copiar datos del tmp al objeto polimórfico
    tmp2->setID(tmp.getID());
    tmp2->setTitulo(tmp.getTitulo());
    tmp2->setCategoria(tmp.getCategoria());
    tmp2->setAutor(tmp.getAutor());
    tmp2->setEjemeplaresTotales(tmp.getEjemplaresTotales());
    tmp2->setEjemplaresDisponibles(tmp.getEjemplaresDisponibles());
    
    registro = tmp2;

    // Verificar si hay suficiente existencia
    if (registro->getEjemplaresDisponibles() < 1) {
        cout << "\n\t No hay libros disponibles.";
        delete registro;
        archivo.close();
        return 1;
    }

    // Actualizar el ticket (codigo de contenido)
    ticket.setCodigo(registro->getID());

    // Restar la cantidad prestada de la existencia y escribir de vuelta
    registro->setEjemplaresDisponibles(registro->getEjemplaresDisponibles() - 1);
    
    // Copiar el valor actualizado de vuelta a tmp
    tmp.setEjemplaresDisponibles(registro->getEjemplaresDisponibles());
    

    if (!archivo) {
        cout << "\n\t Error al actualizar la existencia del libro";
        delete registro;
        archivo.close();
        return 1;
    }

    fstream ticketFile("ticket.txt", ios::in | ios::app | ios::out);
    if (!ticketFile) {
        cout << "\n\t No se pudo crear/abrir ticket.txt";
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

    if (usu.getEstatus()==0){
        cout << "\n\t El usuario esta bloqueado por una multa. No puede realizar prestamos.";
        archivo.close();
        UsuArchivo.close();
        ticketFile.close();
        return 1;
    }
    

    if (usu.getcantPrestamos() < 3){

        archivo.seekp((idl - 1) * sizeof(Libro), ios::beg);
        archivo.write(reinterpret_cast<const char*>(&tmp), sizeof(Libro));
    
        if (!archivo) {
            cout << "\n\t Error al actualizar la existencia del libro";
            ticketFile.close();
            UsuArchivo.close();
            archivo.close();
            return 1;
        }
        
        usu.setcantPrestamos(usu.getcantPrestamos()+1);
        cout << "\n\t Este es tu prestamo numero: " << usu.getcantPrestamos() << endl;

        Multa config;
        config.cargar();
    
        if (registro->getCategoria() == 1) {           // Libro
            diasPermitidos = config.getdiaL();
            precioDia = config.getpreciL();
        }else if (registro->getCategoria() == 2) {      // Revista
            diasPermitidos = config.getdiaR();
            precioDia = config.getpreciR();
        }else {                    // Tesis
            diasPermitidos = config.getdiaT();
            precioDia = config.getpreciT();
        }

        Fecha fecha;
        // fechaDevolucion inicial 0 (no devuelto aún)
        while(ticketFile>> codigo >> nombre >> dia >> mes >> anio >> idtic >> idusu >> estado){
            //busca el ultimo ticket para asignar el siguiente codigo
            cont++;
        }
        ticket.setId(cont+1);
        ticket.setEstado(1);
        ticket.setIdusu(usu.getMatricula());
        ticket.setNombre(usu.getNombre());
        ticket.setDiat(fecha.getDia());
        ticket.setMest(fecha.getmes());
        ticket.setAniot(fecha.getAnio());
        // Guardar el codigo tal cual corresponde al ID del libro (1-based)
        ticket.setCodigo(registro->getID());
        usu.setidTic(ticket.getId(), usu.getcantPrestamos()-1);
        
        UsuArchivo.seekp((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));

        // Escribir en formato espacio-separado: codigo nombre fechaPrestamo id fechaDevolucion idusu estado
        ticketFile.clear();
        ticketFile.seekp(0, ios::end);
        ticketFile << ticket.getCodigo() << " " << ticket.getNombre() << " " << ticket.getDiat() << " " << ticket.getmest() 
        << " " << ticket.getAniot() << " " << ticket.getId() << " "  <<  ticket.getIdusu() << " " << ticket.getEstado() << endl;

        
        cout << "\t ====== Ticket De Prestamo ======\n";
        cout << "\t Id del ticket: " << ticket.getId() << "\n";
        cout << "\t Nombre del usuario: " << ticket.getNombre() << "\n";
        cout << "\t Id del contenido: " << ticket.getCodigo() << "\n";
        cout << "\t Id del usuario: " << ticket.getIdusu() << "\n";
        fecha.mostrar();
        registro->imprCond(diasPermitidos, precioDia);
        cout << "\t ==========================\n";

    }else{
        cout << "\n\t El usuario exede la cantidad de prestamos.";
        delete registro;
        archivo.close();
        UsuArchivo.close();
        ticketFile.close();
        return 1;
    }
    
    delete registro;
    archivo.close();
    UsuArchivo.close();
    ticketFile.close();

    return 0;
}

#endif