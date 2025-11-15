#ifndef MODIFICARLIBRO_H
#define MODIFICARLIBRO_H
#include "Libro.h"
using namespace std;


//se hace uso el INLINE para evitar errores de "redificion."
inline int ModificarLibro(){
    fstream archivo;
    //abre el archivo en modo Modificar
    archivo.open("datos.dat", ios::binary|ios::in|ios::out);
    if(!archivo){
        cout << "\n\t El archivo no se abrio correctamente.";
        cin.get();
        return 1;
    }
    int id;
    bool nom, prec,cat,aut; 
    char resp;
    Libro registro;
    do{ 
        cout << "\n\t Ingresa el ID del libro a buscar: ";  
        cin >> id;
        if(id < 1 || id > 10){
            cout << "\n\t El ID del libro debe estar entre 1 y 10.";
            cout << "\n\t Quieres intentar buscar otro ID? s/n: ";
            cin >> resp;
            if(resp == 'n' || resp == 'N'){
                archivo.close();
                return 1;
            }
        }
    }while(id < 1 || id > 10);

    while(id > 0 && id <= 10){
        nom=prec=false;
        //pone el cursor en donde se localiza 
        //la "id" en el archivo
        archivo.seekg((id-1) * sizeof(Libro));
        //Despues, ya que tiene la posicion
        //correcta, simplemente lo traduce a lo que era
        //para que no te salgan datos en binario
        archivo.read((char*)&registro, sizeof(Libro));
        if(registro.getID() == 0){
            cout << "\n\t Aun no hay datos registrados para el Libro " << id <<".";
            break;
        }
        if(registro.getID() != 0){
            cout << "\n\t-----------------------------------------------------";
        cout << "\n\t -> Datos del producto <-";
        cout << "\n\t ID: " << registro.getID();
        cout << "\n\t Titulo: " << registro.getTitulo();
        cout << "\n\t Precio: " << registro.getPrecio(); 
        cout << "\n\t Categoria: " << registro.getCategoria();  
        cout << "\n\t Autor: " << registro.getAutor();
        cout << "\n\t Ejmp totales: " << registro.getEjemplaresTotales() << endl;
        }


        //se utilizan variables en "bool" como un interruptor para que
        //se modifiquen, o NO se modifiquen.
        cout << "\n\n\t Quieres modificar el nombre del libro? s/n: ";
        cin.ignore();
        cin >> resp;
        if(resp == 's' || resp == 'S') nom = true;
        cout << "\n\n\t Quieres modificar el autor del libro? s/n: ";
        cin.ignore();
        cin >> resp;
        if(resp == 's' || resp == 'S') aut = true;
        cout << "\n\t Quieres modificar el precio del libro? s/n: ";
        cin.ignore();
        cin >> resp;
        if(resp == 's' || resp == 'S') prec = true;
        cout << "\n\n\t Quieres modificar la categoria del libro? s/n: ";
        cin.ignore();
        cin >> resp;
        if(resp == 's' || resp == 'S') cat = true;


        //aqui despues de todo eso, simplemente decide si correr los if´s o no para modificar
        if(nom == true){
            cout << "\n------------------------------------------------";
            cout << "\n\t Dame el nuevo nombre para el libro: ";
            cin.ignore();

            char NuevoNombre[30];
            cin.getline(NuevoNombre, 30);
            registro.setTitulo(NuevoNombre);

            archivo.seekp((registro.getID()-1)*sizeof(Libro));
            archivo.write(reinterpret_cast<char*>(&registro), sizeof(Libro));
        }

        if(prec == true){
            cout << "\n\t Dame el nuevo precio para el producto: ";

            float NuevoPrecio;
            cin >> NuevoPrecio;
            registro.setPrecio(NuevoPrecio);

            archivo.seekp((registro.getID()-1)*sizeof(Libro));
            archivo.write(reinterpret_cast<char*>(&registro), sizeof(Libro));
        }

        if(cat == true){
        cout << "\n------------------------------------------------";
        cout << "\n\t Dame la nueva categoria para el libro: ";
        cin.ignore();

        char NuevaCategoria[30];
        cin.getline(NuevaCategoria, 30);
        registro.setCategoria(NuevaCategoria);

        archivo.seekp((registro.getID()-1)*sizeof(Libro));
        archivo.write(reinterpret_cast<char*>(&registro), sizeof(Libro));
        }

        if(aut == true){
        cout << "\n------------------------------------------------";
        cout << "\n\t Dame el nuevo autor para el libro: ";
        cin.ignore();

        char NuevoAutor[30];
        cin.getline(NuevoAutor, 30);
        registro.setAutor(NuevoAutor);

        archivo.seekp((registro.getID()-1)*sizeof(Libro));
        archivo.write(reinterpret_cast<char*>(&registro), sizeof(Libro));
        }
        
        cout << "\n\t Quieres buscar otro producto por su ID? s/n: ";
        cin >> resp;
        if(resp == 'n' || resp == 'N') break;

        do{
            cout << "\n\t Ingresa el ID a buscar: ";
            cin >> id;
            if(id < 1 || id > 10){
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

#endif // MODIFICARPRODUCTO_H