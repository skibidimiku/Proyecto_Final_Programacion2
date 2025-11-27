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
    Blancousu.setEstatus(1);
    Blancousu.setContrasena("");
    Blancousu.setCarrera("");
    Blancousu.setCorreo("");
    Blancousu.setMatricula(0);
    Blancousu.setNombre("");
    Blancousu.setMulta(0);
    Blancousu.setcantPrestamos(0);
    Blancousu.setPermisos(0);
    Blancousu.setTelefono("");
    for(int i=0; i<10; i++){
        //ahora le estoy diciendo: "Del documento, pon 10 ESPACIOS en blanco (usando la variable)"
        //esto deja la hoja en 0´s total para luego ser modificados
        UsuArchivo.write(reinterpret_cast<char*>(&Blancousu), sizeof(Usuario));
        archivo.write(reinterpret_cast<char*>(&blanco), sizeof(Libro));
    }

    fstream ticketFile("ticket.txt", ios::in | ios::app | ios::out);
    if(!ticketFile){
        cout<<"\n\t No se pudo abrir el archivo de ticket.";
        return -1;
    }
    
    ticketFile.clear();

    ticketFile.close();                                          
    archivo.close();
    UsuArchivo.close();
    
    return 1;
}
