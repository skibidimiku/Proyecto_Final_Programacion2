#include <iostream>
#include <fstream>
using namespace std;
#include "Libro.h"
#include "Ticket.h"

int creaCascaron(){
    fstream archivo;
    archivo.open("datos.dat", ios::binary|ios::out);
    if(!archivo){
        cout << "\n\t No se pudo abrir el archivo.";
        return -1;
    }
    //blanco contiene todas las variables en blanco.
    Libro blanco;
    blanco.setID(0);
    blanco.setTitulo("");
    blanco.setPrecio(0);
    blanco.setCategoria("");
    blanco.setAutor("");
    blanco.setEjemeplaresTotales(0);
    for(int i=0; i<10; i++){
        //ahora le estoy diciendo: "Del documento, pon 10 ESPACIOS en blanco (usando la variable)"
        //esto deja la hoja en 0´s total para luego ser modificados
        archivo.write(reinterpret_cast<char*>(&blanco), sizeof(Libro));
    }
    archivo.close();

    //literalmente lo mismo 
    fstream ticketFile;
    ticketFile.open("ticket.dat",ios::binary|ios::out);
    Ticket ticketBlank;
    ticketBlank.setCodigo(0);
    ticketBlank.setNombre("");
    ticketBlank.setCantidad(0);
    ticketBlank.setSubtotal(0.0);
    ticketBlank.setTotal(0.0);
    for(int i=0; i<10; i++){
        ticketFile.write(reinterpret_cast<char*>(&ticketBlank), sizeof(Ticket));
    }
    ticketFile.close();

    return 1;
}
