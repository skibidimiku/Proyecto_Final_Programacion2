#include "Libro.h"
#include <cstring>
using namespace std;

int EliminarLibro(){
    fstream archivo;
    archivo.open("datos.dat", ios::binary|ios::in|ios::out);
    if(!archivo){
        cout << "\n\t El archivo no se abrio correctamente.";
        cin.get();
        return 1;
    }
    int id;
    bool baja; 
    char resp;
    Libro registro;
    Libro blanco;
    
    //vuelvo a traer blanco aqui, la logica va a ser algo como:
    //ENCUENTRA EL LUGAR DE LA ID -> ENSEÑASELO AL USER -> REPLAZA TODO ESO POR "blanco"
    //esto basicamente borra todos los datos, y hace que esten en 0´s limpios

    blanco.setID(0);
    blanco.setTitulo("");
    blanco.setPrecio(0);
    blanco.setCategoria("");
    blanco.setAutor("");
    blanco.setEjemeplaresTotales(0);
    do{
        cout << "\n\t Ingresa el ID del libro a buscar: ";
        cin >> id;
        if(id < 1 || id > 10){
            cout << "\n\t El ID debe estar entre 1 y 10.";
            cout << "\n\t Quieres intentar buscar otro libro por su ID? s/n: ";
            cin >> resp;
            if(resp == 'n' || resp == 'N'){
                archivo.close();
                return 1;
            }
        }
    }while(id < 1 || id > 10);

    while(id > 0 || id <= 10){
        baja = false;
        archivo.seekg((id-1) * sizeof(Libro));
        archivo.read((char*)&registro, sizeof(Libro));
        if(registro.getID() == 0){
            cout << "\n\t Aun no hay datos registrados para el ID " << id <<".";
            break;
        }
        if(registro.getID()!= 0){
            cout << "\n-----------------------------------------------------";
        cout << "\n\t -> Datos del producto <-";
        cout << "\n\t ID: " << registro.getID();
        cout << "\n\t Titulo: " << registro.getTitulo();
        cout << "\n\t Precio: " << registro.getPrecio(); 
        cout << "\n\t Categoria: " << registro.getCategoria();  
        cout << "\n\t Autor: " << registro.getAutor();
        cout << "\n\t Ejmp totales: " << registro.getEjemplaresTotales() << endl;
        }
        cout << "\n\n\t Quieres borrar este producto? s/n: ";
        cin.ignore();
        cin >> resp;
        if(resp == 's' || resp == 'S') baja = true;

        if(baja == true){
            archivo.seekp((id-1)*sizeof(Libro));
            archivo.write(reinterpret_cast<char*>(&blanco), sizeof(Libro));
        }
        
        cout << "\n\t Deseas realizar la eliminacion de otro producto? s/n: ";
        cin >> resp;
        if(resp == 'n' || resp == 'N') break;

        do{
            cout << "\n\n\t Ingresa el ID a buscar: ";
            cin >> id;
            if(id < 0 || id > 10){
                cout << "\n\t El ID debe estar entre 1 y 10.";
                cout << "\n\t Quieres intentar buscar otro ID? s/n: ";
                cin >> resp;
                if(resp == 'n' || resp == 'N') break;
            }
        }while(id < 1 || id > 10);
    }
    archivo.close();
    return 0;
}