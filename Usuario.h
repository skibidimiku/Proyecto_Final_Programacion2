<<<<<<< Updated upstream
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstring>
#include "Libro.h"
using namespace std;

#ifndef USUARIO_DEFINED
#define USUARIO_DEFINED

class Persona{
protected:
    char nombre[30];
    char carrera[30];
    char correo[50];
    char telefono[30];
    float dinero=0.0;
public:

    void setNombre(const char* nom) { strncpy(nombre, nom, 30); nombre[29] = '\0'; }
    const char* getNombre() const { return nombre; }

    void setCarrera(const char* car) { strncpy(carrera, car, 30); carrera[29] = '\0'; }
    const char* getNCarrera() const { return carrera; }

    void setCorreo(const char* corr) { strncpy(correo, corr, 50); correo[49] = '\0'; }
    const char* getCorreo() const { return correo; }

    void setTelefono(const char* tel) { strncpy(telefono, tel, 30); telefono[29] = '\0'; }
    const char* getTelefono() const { return telefono; }

    void setDinero(float din){ dinero+=din; }
    float getDinero(){ return dinero; }
};


class Usuario : public Persona {
private:

int matricula;
char contrasena[30]; // solo aplica a administradores
int cantPres=0;
float multa=0.0;
int idtic[3];
int Estatus; // 1=Activo  0=Bloqueado 
int permisos; // 1=Administrador  0=Usuario

public:

    //setters y getters

    void setMatricula(int c) { matricula = c; }
    int getMatricula() const { return matricula; }

    void setEstatus(int est) { Estatus = est; }
    int getEstatus() const { return Estatus; }

    void setPermisos(int per){ permisos=per; }
    int getPermisos() const{ return permisos; }

    void setcantPrestamos(int can){ cantPres=can; }
    int getcantPrestamos() const{ return cantPres; }

    void setidTic( int id, int pos){ idtic[pos]=id; }
    int getidTic(int pos){ return idtic[pos]; }
    
    void setidTic(int ids[3]){
        for (int i = 0; i < 3; i++){
            idtic[i] = ids[i];
        }
    }

    void aplastaridTic(){ 
        for (int i = 0; i < 2; i++){
            if (idtic[i] == 0){
                idtic[i] = idtic[i+1];
                idtic[i+1] = 0;
            }
        }
    }

    void setContrasena(const char* con){ strncpy(contrasena, con, 30); contrasena[29] = '\0'; }
    const char* getContrasena() const{ return contrasena; }

    void setMulta(float mul){ multa=multa+mul; }
    float getMulta(){ return multa; }

    int iniciarSecion(int id){
        fstream Archivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        Usuario usu;
        int intentos=0;
        char contra[30];
        if (!Archivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            return -1;
        }

        while(Archivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario))){
            if (usu.matricula == id && usu.nombre[0] != '\0'){
                cout << "\n\tDame la contrasena: ";
                cin.ignore();
                cin.getline(contra, 30);
                while (!(usu==contra) && intentos < 3){
                    cout << "\n\tLa contrasena es in correcta te quedan [" << 3 - intentos << "] intentos.";
                    cout << "\n\tDame la contrasena: ";
                    cin.getline(contra, 30);
                    intentos++;
                }

                if (usu==contra && usu.permisos==1){
                    return 1;
                }
                else if (usu==contra && usu.permisos==0){
                    return 0;
                }
            }
        }

        if (intentos==3){
            cout<<"\n\t Muchos intentos fallidos." << endl;
        }else{
            cout << "\n\t El usuario no existe." << endl;
        }

        return -1;
    }

    void printUsuario(int id){
        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        Usuario usu;
        UsuArchivo.seekg((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario));
        cout << "\n------------------------------------------";
        cout << "\n\t El Nombre es: " << usu.getNombre();
        cout << "\n\t Su carrera es es: " << usu.getNCarrera();
        cout << "\n\t Su correo es: " << usu.getCorreo();
        cout << "\n\t Su telefono es: " << usu.getTelefono();
        if (usu.getEstatus() == 0) {
            cout << "\n\t El usuario esta bloqueado por una multa.";
            cout << "\n\t Debe una multa de: $" << usu.getMulta();
        } else {
            cout << "\n\t El usuario esta activo.";
        }
        cout << "\n\t Tiene: $" << usu.getDinero() << " disponible." << endl;
        cout << "\n\t Tiene: " << usu.getcantPrestamos() << " prestamos activos." << endl;

        UsuArchivo.close();
    }

    void BajaUsuario(int id, vector<int> idtics){
        Usuario usu;
        int cantTic;
        char resp;
        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        if (!UsuArchivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            return;
        }
        UsuArchivo.seekg((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario));

        if (strcmp(usu.getNombre(), "") == 0){
            cout << "\n\t El usuario no existe." << endl;
            UsuArchivo.close();
            return;
        }
        

        cout<<"Esta seguro de borrar a "<< usu.getNombre() <<"(s/n)";
        cin >> resp;
        while (resp != 'S' && resp != 's' && resp != 'N' && resp != 'n'){
            cout<<"La opcion no es valida quiere borrar a "<< usu.getNombre() <<"(s/n)";
            cin >> resp;
        }

        if (resp == 'N' || resp == 'n'){
            UsuArchivo.close();
            return;
        }
        
        cantTic = usu.getcantPrestamos();

        fstream archivo;
        archivo.open("datos.dat", ios::binary | ios::in | ios::out);
        if (!archivo) {
            cout << "\n\t El archivo Producto no se abrio correctamente.";
            UsuArchivo.close();
            archivo.close();
            cin.get();
            return;
        }

        for (size_t i = 0; i < (size_t)cantTic; i++){ // para regresar los prestamos del usuario
            if (i >= idtics.size()) break;
            int codigoLibro = idtics[i];

            if (codigoLibro <= 0) continue; // evitar lecturas inválidas

            Libro tmpLib;
            archivo.seekg((codigoLibro - 1) * sizeof(Libro), ios::beg);
            archivo.read(reinterpret_cast<char*>(&tmpLib), sizeof(Libro));

            // corregir el ejemplar disponible
            tmpLib.setEjemplaresDisponibles(tmpLib.getEjemplaresDisponibles() + 1);

            archivo.seekp((codigoLibro - 1) * sizeof(Libro), ios::beg);
            archivo.write(reinterpret_cast<const char*>(&tmpLib), sizeof(Libro));
        }

        int ids[3]={0,0,0};
        usu.setMatricula(0);
        usu.setNombre("");
        usu.setCarrera("");
        usu.setCorreo("");
        usu.setTelefono("");
        usu.setContrasena("");
        usu.setidTic(ids);
        usu.setEstatus(1);
        usu.setPermisos(0);
        usu.setDinero(0.0);
        usu.setMulta(0.0);
        usu.setcantPrestamos(0);

        UsuArchivo.seekp((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));

        UsuArchivo.close();
        archivo.close();
    }

    bool operator ==(const char* cont) const {
        return strcmp(this->contrasena, cont) == 0;
    }

    void operator +=(int cant){
        cantPres=cantPres+cant;
    }

    int esnumUsu(){
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
};

=======
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstring>
#include "Libro.h"
using namespace std;

#ifndef USUARIO_DEFINED
#define USUARIO_DEFINED

class Persona{
protected:
    char nombre[30];
    char carrera[30];
    char correo[50];
    char telefono[30];
    float dinero=0.0;
public:

    void setNombre(const char* nom) { strncpy(nombre, nom, 30); nombre[29] = '\0'; }
    const char* getNombre() const { return nombre; }

    void setCarrera(const char* car) { strncpy(carrera, car, 30); carrera[29] = '\0'; }
    const char* getNCarrera() const { return carrera; }

    void setCorreo(const char* corr) { strncpy(correo, corr, 50); correo[49] = '\0'; }
    const char* getCorreo() const { return correo; }

    void setTelefono(const char* tel) { strncpy(telefono, tel, 30); telefono[29] = '\0'; }
    const char* getTelefono() const { return telefono; }

    void setDinero(float din){ dinero+=din; }
    float getDinero(){ return dinero; }
};


class Usuario : public Persona {
private:

int matricula;
char contrasena[30]; // solo aplica a administradores
int cantPres=0;
float multa=0.0;
int idtic[3];
int Estatus; // 1=Activo  0=Bloqueado 
int permisos; // 1=Administrador  0=Usuario

public:

    //setters y getters

    void setMatricula(int c) { matricula = c; }
    int getMatricula() const { return matricula; }

    void setEstatus(int est) { Estatus = est; }
    int getEstatus() const { return Estatus; }

    void setPermisos(int per){ permisos=per; }
    int getPermisos() const{ return permisos; }

    void setcantPrestamos(int can){ cantPres=can; }
    int getcantPrestamos() const{ return cantPres; }

    void setidTic( int id, int pos){ idtic[pos]=id; }
    int getidTic(int pos){ return idtic[pos]; }
    
    void setidTic(int ids[3]){
        for (int i = 0; i < 3; i++){
            idtic[i] = ids[i];
        }
    }

    void aplastaridTic(){ 
        for (int i = 0; i < 2; i++){
            if (idtic[i] == 0){
                idtic[i] = idtic[i+1];
                idtic[i+1] = 0;
            }
        }
    }

    void setContrasena(const char* con){ strncpy(contrasena, con, 30); contrasena[29] = '\0'; }
    const char* getContrasena() const{ return contrasena; }

    void setMulta(float mul){ multa=multa+mul; }
    float getMulta(){ return multa; }

    int iniciarSecion(int id){
        fstream Archivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        Usuario usu;
        int intentos=0;
        char contra[30];
        if (!Archivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            return -1;
        }

        while(Archivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario))){
            if (usu.matricula == id && usu.nombre[0] != '\0'){
                cout << "\n\tDame la contrasena: ";
                cin.ignore();
                cin.getline(contra, 30);
                while (!(usu==contra) && intentos < 3){
                    cout << "\n\tLa contrasena es in correcta te quedan [" << 3 - intentos << "] intentos.";
                    cout << "\n\tDame la contrasena: ";
                    cin.getline(contra, 30);
                    intentos++;
                }

                if (usu==contra && usu.permisos==1){
                    return 1;
                }
                else if (usu==contra && usu.permisos==0){
                    return 0;
                }
            }
        }

        if (intentos==3){
            cout<<"\n\t Muchos intentos fallidos." << endl;
        }else{
            cout << "\n\t El usuario no existe." << endl;
        }

        return -1;
    }

    void printUsuario(int id){
        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        Usuario usu;
        UsuArchivo.seekg((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario));
        cout << "\n------------------------------------------";
        cout << "\n\t El Nombre es: " << usu.getNombre();
        cout << "\n\t Su carrera es es: " << usu.getNCarrera();
        cout << "\n\t Su correo es: " << usu.getCorreo();
        cout << "\n\t Su telefono es: " << usu.getTelefono();
        if (usu.getEstatus() == 0) {
            cout << "\n\t El usuario esta bloqueado por una multa.";
            cout << "\n\t Debe una multa de: $" << usu.getMulta();
        } else {
            cout << "\n\t El usuario esta activo.";
        }
        cout << "\n\t Tiene: $" << usu.getDinero() << " disponible." << endl;
        cout << "\n\t Tiene: " << usu.getcantPrestamos() << " prestamos activos." << endl;

        UsuArchivo.close();
    }

    void BajaUsuario(int id, vector<int> idtics){
        Usuario usu;
        int cantTic;
        char resp;
        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        if (!UsuArchivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            return;
        }
        UsuArchivo.seekg((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario));

        if (strcmp(usu.getNombre(), "") == 0){
            cout << "\n\t El usuario no existe." << endl;
            UsuArchivo.close();
            return;
        }
        

        cout<<"Esta seguro de borrar a "<< usu.getNombre() <<"(s/n)";
        cin >> resp;
        while (resp != 'S' && resp != 's' && resp != 'N' && resp != 'n'){
            cout<<"La opcion no es valida quiere borrar a "<< usu.getNombre() <<"(s/n)";
            cin >> resp;
        }

        if (resp == 'N' || resp == 'n'){
            UsuArchivo.close();
            return;
        }
        
        cantTic = usu.getcantPrestamos();

        fstream archivo;
        archivo.open("datos.dat", ios::binary | ios::in | ios::out);
        if (!archivo) {
            cout << "\n\t El archivo Producto no se abrio correctamente.";
            UsuArchivo.close();
            archivo.close();
            cin.get();
            return;
        }

        for (int i = 0; i < cantTic; i++){ // para regresar los prestamos del usuario
            if (i >= idtics.size()) break;
            int codigoLibro = idtics[i];

            if (codigoLibro <= 0) continue; // evitar lecturas inválidas

            Libro tmpLib;
            archivo.seekg((codigoLibro - 1) * sizeof(Libro), ios::beg);
            archivo.read(reinterpret_cast<char*>(&tmpLib), sizeof(Libro));

            // corregir el ejemplar disponible
            tmpLib.setEjemplaresDisponibles(tmpLib.getEjemplaresDisponibles() + 1);

            archivo.seekp((codigoLibro - 1) * sizeof(Libro), ios::beg);
            archivo.write(reinterpret_cast<const char*>(&tmpLib), sizeof(Libro));
        }

        int ids[3]={0,0,0};
        usu.setMatricula(0);
        usu.setNombre("");
        usu.setCarrera("");
        usu.setCorreo("");
        usu.setTelefono("");
        usu.setContrasena("");
        usu.setidTic(ids);
        usu.setEstatus(1);
        usu.setPermisos(0);
        usu.setDinero(0.0);
        usu.setMulta(0.0);
        usu.setcantPrestamos(0);

        UsuArchivo.seekp((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));

        UsuArchivo.close();
        archivo.close();
    }

    bool operator ==(const char* cont) const {
        return strcmp(this->contrasena, cont) == 0;
    }

    void operator +=(int cant){
        cantPres=cantPres+cant;
    }

    int esnumUsu(){
        string num;
        while (true){
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
};

>>>>>>> Stashed changes
#endif // USUARIO_DEFINED