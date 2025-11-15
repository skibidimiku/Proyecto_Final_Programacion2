#include <iostream>
#include <fstream>
#include <cstring>
#include "Libro.h"
#include "Ticket.h"

using namespace std;

int GenerarTicketVenta(Libro& registro, int cantidad) {
    Ticket ticket;
    int id;
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
        cin >> id;
        if (id < 1 || id > 10) {
            cout << "\n\t El ID debe estar entre 1 y 10.";
            cout << "\n\t Quieres intentar buscar otro libro por su ID? s/n: ";
            cin >> resp;
            if (resp == 'n' || resp == 'N') {
                archivo.close();
                return 1;
            }
        }
    } while (id < 1 || id > 10);

    do {
        cout << "\n\t Ingresa la cantidad a vender: ";
        cin >> cantidad;
        if (cantidad < 1) {
            cout << "\n\t La cantidad debe ser al menos 1.";
        }
    } while (cantidad < 1);


    archivo.seekg((id - 1) * sizeof(Libro), ios::beg);
    archivo.read(reinterpret_cast<char*>(&registro), sizeof(Libro));
    if (registro.getID() == 0) {
        cout << "\n\t Aun no hay datos registrados para el ID " << id << ".";
        archivo.close();
        return 1;
    }

    // Verificar si hay suficiente existencia
    if (registro.getEjemplaresTotales() < cantidad) {
        cout << "\n\t No hay suficiente existencia. Disponible: " << registro.getEjemplaresTotales();
        archivo.close();
        return 1;
    }

    // Actualizar el ticket
    ticket.setNombre(registro.getTitulo());
    ticket.setCodigo(registro.getID());
    ticket.setCantidad(cantidad);
    ticket.setSubtotal(registro.getPrecio());
    ticket.setTotal(registro.getPrecio() * cantidad);

    // Restar la cantidad vendida de la existencia
    registro.setEjemeplaresTotales(registro.getEjemplaresTotales() - cantidad);
    
    // Guardar el producto actualizado
    archivo.seekp((id - 1) * sizeof(Libro), ios::beg);
    archivo.write(reinterpret_cast<const char*>(&registro), sizeof(Libro));
    
    if (!archivo) {
        cout << "\n\t Error al actualizar la existencia del libro";
        archivo.close();
        return 1;
    }

    archivo.close();


    fstream ticketFile("ticket.dat", ios::binary | ios::in | ios::out);
    if (!ticketFile) {
        ofstream createFile("ticket.dat", ios::binary | ios::out);
        createFile.close();
        ticketFile.open("ticket.dat", ios::binary | ios::in | ios::out);
        if (!ticketFile) {
            cout << "\n\t No se pudo crear/abrir ticket.dat";
            return 1;
        }
    }

    ticketFile.seekp((ticket.getCodigo() - 1) * sizeof(Ticket), ios::beg);
    ticketFile.write(reinterpret_cast<char*>(&ticket), sizeof(Ticket));

    ticketFile.clear();
    ticketFile.seekp(0, ios::end);
    ticketFile << "====== TICKET DE VENTA ======\n";
    ticketFile << "Producto: " << ticket.getNombre() << "\n";
    ticketFile << "Cantidad: " << ticket.getCantidad() << "\n";
    ticketFile << "Precio unitario: $" << ticket.getSubtotal() << "\n";
    ticketFile << "Total: $" << ticket.getTotal() << "\n";
    ticketFile << "==========================\n";

    ticketFile.close();

    cout << "\n\t====== TICKET DE VENTA ======" << endl;
    cout << "\tProducto: " << ticket.getNombre() << endl;
    cout << "\tCantidad: " << ticket.getCantidad() << endl;
    cout << "\tPrecio unitario: $" << ticket.getSubtotal() << endl;
    cout << "\tTotal: $" << ticket.getTotal() << endl;
    cout << "\t==========================" << endl;
    cout << "\n\tTicket generado exitosamente!" << endl;

    return 0;
}