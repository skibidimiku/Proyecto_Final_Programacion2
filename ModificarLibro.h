#ifndef MODIFICARLIBRO_H
#define MODIFICARLIBRO_H
#include "Libro.h"
using namespace std;

int esnumliMo();

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
    bool nom, ejem,cat,aut; 
    char resp;
    Libro registro;
    do{ 
        cout << "\n\t Ingresa el ID del libro a buscar: ";  
        id = esnumliMo();
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
        nom=ejem=aut=cat=false;
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
            cout << "\n\t Categoria: " << registro.getCategoria();  
            cout << "\n\t Autor: " << registro.getAutor();
            cout << "\n\t Ejmp totales: " << registro.getEjemplaresTotales() << endl;
        }


        //se utilizan variables en "bool" como un interruptor para que
        //se modifiquen, o NO se modifiquen.
        cout << "\n\n\t Quieres modificar el nombre del libro? s/n: ";
        cin>>ws;
        cin >> resp;
        if(resp == 's' || resp == 'S') nom = true;
        cout << "\n\n\t Quieres modificar el autor del libro? s/n: ";
        cin>>ws;
        cin >> resp;
        if(resp == 's' || resp == 'S') aut = true;
        cout << "\n\n\t Quieres modificar la categoria del libro? s/n: ";
        cin>>ws;
        cin >> resp;
        if(resp == 's' || resp == 'S') cat = true;
        cout << "\n\n\t Quieres modificar la cantidad de ejemplares del libro? s/n: ";
        cin>>ws;
        cin >> resp;
        if(resp == 's' || resp == 'S') ejem = true;


        //aqui despues de todo eso, simplemente decide si correr los if´s o no para modificar
        if(nom == true){
            cout << "\n------------------------------------------------";
            cout << "\n\t Dame el nuevo nombre para el libro: ";
            cin>>ws;

            char NuevoNombre[30];
            cin.getline(NuevoNombre, 30);

            while (NuevoNombre[0]=='\0' || NuevoNombre[0]==' ' || (strcmp(registro.getTitulo(), NuevoNombre) == 0)){
                cout << "\n\t El nombre no puede estar vacio o ser igual al anterior. Ingresa el nombre del libro: ";
                cin.getline(NuevoNombre, 30);
            }

            registro.setTitulo(NuevoNombre);

            archivo.seekp((registro.getID()-1)*sizeof(Libro));
            archivo.write(reinterpret_cast<char*>(&registro), sizeof(Libro));
        }

        if(cat == true){
            cout << "\n------------------------------------------------";
            cout << "\n\t Dame la nueva categoria para el libro[1-3]: ";
        
            int NuevaCategoria;
            NuevaCategoria = esnumliMo();
            while (NuevaCategoria < 1 && NuevaCategoria > 3){
                cout << "\n\t La anterior es invalida. Ingresa la categoria del libro [1-3]: ";
                NuevaCategoria = esnumliMo();
            }
        
            registro.setCategoria(NuevaCategoria);

            archivo.seekp((registro.getID()-1)*sizeof(Libro));
            archivo.write(reinterpret_cast<char*>(&registro), sizeof(Libro));
        }

        if(aut == true){
            cout << "\n------------------------------------------------";
            cout << "\n\t Dame el nuevo autor para el libro: ";
            cin>>ws;

            char NuevoAutor[30];
            cin.getline(NuevoAutor, 30);
        
            while (NuevoAutor[0]=='\0' || NuevoAutor[0]==' ' || (strcmp(registro.getAutor(), NuevoAutor) == 0)){
                cout << "\n\t El autor no puede estar vacio o ser igual al anterior. Ingresa el autor del libro: ";
                cin.getline(NuevoAutor, 30);
            }

            registro.setAutor(NuevoAutor);

            archivo.seekp((registro.getID()-1)*sizeof(Libro));
            archivo.write(reinterpret_cast<char*>(&registro), sizeof(Libro));
        }

        if (ejem == true){
            cout << "\n------------------------------------------------";
            cout << "\n\t Existencia anterior: " << registro.getEjemplaresTotales();
            cout << "\n\t Dame la nueva cantidad de ejemplares para el libro: ";

            int nuevacant, nuevcant=0;
            nuevacant = esnumliMo();

            while (nuevacant <= 0 || nuevacant == registro.getEjemplaresTotales()){
                cout << "\n\t No puede ser menor a 1 o igual a la cantidad anterior. Ingresa la nueva cantidad: ";
                nuevacant = esnumliMo();
            }

            if (nuevacant < registro.getEjemplaresTotales()){ 
                if (registro.getEjemplaresDisponibles() == nuevacant || registro.getEjemplaresDisponibles() < nuevacant){
                    registro.setEjemeplaresTotales(nuevacant);
                }else if(registro.getEjemplaresDisponibles() > nuevacant){
                    nuevcant = registro.getEjemplaresTotales() - nuevacant;
                    registro.setEjemeplaresTotales(nuevacant);
                    registro.setEjemplaresDisponibles(registro.getEjemplaresDisponibles() - nuevcant);
                }
            }else if(nuevacant > registro.getEjemplaresTotales()){
                nuevcant = nuevacant - registro.getEjemplaresTotales();
                registro.setEjemeplaresTotales(nuevacant);
                registro.setEjemplaresDisponibles(registro.getEjemplaresDisponibles() + nuevcant);
            }

            archivo.seekp((registro.getID()-1)*sizeof(Libro));
            archivo.write(reinterpret_cast<char*>(&registro), sizeof(Libro));
        }

        
        cout << "\n\t Quieres buscar otro producto por su ID? s/n: ";
        cin >> resp;
        if(resp == 'n' || resp == 'N') break;

        do{
            cout << "\n\t Ingresa el ID a buscar: ";
            id = esnumliMo();
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

int esnumliMo(){
    string num;
    while (true){
        cin>>ws;
        getline(cin, num);

        // Si la cadena está vacía → seguir pidiendo
        if (num.empty()) {
            cout << "\n\t No ingreso nada. Intente de nuevo.\n";
            continue;
        }

        bool valida = true;
        for (char c : num) {
            if (!isdigit(c)) {
                valida = false;
                break;
            }
        }

        if (!valida){
            cout << "\n\t No es un numero valido. Intente de nuevo.\n";
            continue;
        }

        // Ahora SI es seguro llamar a stoi
        return stoi(num);
    }
}

#endif // MODIFICARPRODUCTO_H