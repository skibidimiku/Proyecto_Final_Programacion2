#include <iostream>
#include <fstream>
using namespace std;
#include "Libro.h"
#include "Usuario.h"
#include "Ticket.h"

int creaCascaron(){
    fstream archivo, UsuArchivo;
    UsuArchivo.open("Usuarios.dat", ios::binary | ios::out);
    archivo.open("datos.dat", ios::binary|ios::out);
    if(!archivo || !UsuArchivo){
        cout << "\n\t No se pudo abrir el archivo.";
        return -1;
    }
    //blanco contiene todas las variables en blanco.
    contenido* blanco= new Libro();
    blanco->setID(0);
    blanco->setTitulo("");
    blanco->setCategoria(0);
    blanco->setAutor("");
    blanco->setEjemeplaresTotales(0);
    blanco->setEjemplaresDisponibles(0);

    Usuario Blancousu;
    int ids[3]={0,0,0};
    Blancousu.setEstatus(1);
    Blancousu.setContrasena("");
    Blancousu.setCarrera("");
    Blancousu.setCorreo("");
    Blancousu.setMatricula(0);
    Blancousu.setNombre("");
    Blancousu.setMulta(0.0);
    Blancousu.setDinero(0.0);
    Blancousu.setidTic(ids);
    Blancousu.setcantPrestamos(0);
    Blancousu.setPermisos(0);
    Blancousu.setTelefono("");
    for(int i=0; i<10; i++){
        //ahora le estoy diciendo: "Del documento, pon 10 ESPACIOS en blanco (usando la variable)"
        //esto deja la hoja en 0´s total para luego ser modificados
        UsuArchivo.write(reinterpret_cast<char*>(&Blancousu), sizeof(Usuario));
        archivo.write(reinterpret_cast<char*>(&blanco), sizeof(Libro));
    }

    ofstream ticketFile("ticket.txt");
    if(!ticketFile.is_open()){
        cout << "\n\t No se pudo crear/abrir ticket.txt";
        ticketFile.close();
        archivo.close();
        UsuArchivo.close();
        return -1;
    }
    
    ofstream TicketDev("TicketDev.txt");
    if(!TicketDev.is_open()){
        cout << "\n\t No se pudo crear/abrir TicketDev.txt";
        TicketDev.close();
        ticketFile.close();
        archivo.close();
        UsuArchivo.close();
        return -1;
    }

    delete blanco;
    ticketFile.close();                                          
    archivo.close();
    UsuArchivo.close();
    
    return 1;
}
