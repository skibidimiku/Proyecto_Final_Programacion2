#ifndef MULTA_DEFINED
#define MULTA_DEFINED

#include <iostream>
#include <fstream>
#include <cstring>
#include "Libro.h"
#include "Usuario.h"
#include "Ticket.h"

using namespace std;

class Multa{
private:
    int diaL=14, diaR=7, diaT=30;
    float preciL=20, preciR=10, preciT=50;

public:

    void setdiaL(int d){diaL=d;}
    void setdiaR(int d){diaR=d;}
    void setdiaT(int d){diaT=d;}
    void setPreciL(float p){ preciL = p; }
    void setPreciR(float p){ preciR = p; }
    void setPreciT(float p){ preciT = p; }

    int getdiaL(){ return diaL; }
    int getdiaR(){ return diaR; }
    int getdiaT(){ return diaT; }
    int getpreciL(){ return preciL; }
    int getpreciR(){ return preciR; }
    int getpreciT(){ return preciT; }

    int modificarcondi(int mod){
    Multa config;
    config.cargar();

    char resp;
    int dias = 0;
    float precio = 0;

    cout << "\n\t ¿Modificar dias? (s/n): ";
    cin >> resp;
    if(resp=='s' || resp=='S'){
        while(dias <= 0){
            cout << "\n\t Nuevos dias: ";
            cin>>dias;
        }
    }

    cout << "\n\t ¿Modificar precio? (s/n): ";
    cin >> resp;
    if(resp=='s' || resp=='S'){
        while(precio <= 0){
            cout << "\n\t Nuevo precio: ";
            cin >> precio;
        }
    }

    if(mod == 1){
        if(dias)   config.setdiaL(dias);
        if(precio) config.setPreciL(precio);
    }
    else if(mod == 2){
        if(dias)   config.setdiaR(dias);
        if(precio) config.setPreciR(precio);
    }
    else if(mod == 3){
        if(dias)   config.setdiaT(dias);
        if(precio) config.setPreciT(precio);
    }

    config.guardar();
    return 0;
}

    void guardar() {
        fstream f("multa.dat", ios::binary | ios::out);
        f.write(reinterpret_cast<char*>(this), sizeof(Multa));
        f.close();
    }

    void cargar() {
        fstream f("multa.dat", ios::binary | ios::in);
        if (f) {
            f.read(reinterpret_cast<char*>(this), sizeof(Multa));
            f.close();
        } else {
            // Si no existe, se crea con valores por defecto
            guardar();
        }
    }


    float getMulta(int id, int idtic){
        Multa config;
        config.cargar();   // lee multa.dat
        contenido* libro;
        Ticket ticket;
        Usuario usu;
        float multa=0.0;

        fstream archivo;
        archivo.open("datos.dat", ios::binary | ios::in | ios::out);
        if (!archivo) {
            cout << "\n\t El archivo Producto no se abrio correctamente.";
            cin.get();
            return 0.0;
        }

        fstream ticketFile("ticket.txt", ios::in | ios::app | ios::out);
        if (!ticketFile) {
            cout << "\n\t No se pudo crear/abrir ticket.dat";
            ticketFile.close();
            archivo.close();
            return 0.0;
        }

        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        if(!UsuArchivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            ticketFile.close();
            UsuArchivo.close();
            archivo.close();
            return 0.0;
        }

        // Leer ticket en formato espacio-separado: codigo nombre fechaPrestamo id fechaDevolucion idusu estado
        int codigo, idusu_tmp, estado_tmp, dia_tmp, mes_tmp, anio_tmp, idtic_tmp;
        char nombre_tmp[30];
        
        ticketFile.seekg(0, ios::beg);
        bool ticketEncontrado = false;
        while(ticketFile >> codigo >> nombre_tmp >> dia_tmp >> mes_tmp >> anio_tmp >> idtic_tmp >> idusu_tmp >> estado_tmp){
            if(idtic_tmp == idtic){
                ticket.setCodigo(codigo);
                ticket.setNombre(nombre_tmp);
                ticket.setId(idtic_tmp);
                ticket.setDiat(dia_tmp);
                ticket.setMest(mes_tmp);
                ticket.setAniot(anio_tmp);
                ticket.setIdusu(idusu_tmp);
                ticket.setEstado(estado_tmp);
                ticketEncontrado = true;
                break;
            }
        }
        
        if(!ticketEncontrado){
            cout << "\n\t No se encontro el ticket.";
            archivo.close();
            UsuArchivo.close();
            ticketFile.close();
            return 0.0;
        }

        UsuArchivo.seekg((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario));

        if (usu.getcantPrestamos()==0){
            archivo.close();
            UsuArchivo.close();
            ticketFile.close();
            return 0.0;
        }
        


        Libro tmp;
        archivo.seekg((ticket.getCodigo() - 1) * sizeof(Libro), ios::beg);
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
    
        libro = tmp2;

        int diasPermitidos;
        float precioDia;

        if (cat == 1) {           // Libro
            diasPermitidos = config.getdiaL();
            precioDia = config.getpreciL();
        }else if (cat == 2) {      // Revista
            diasPermitidos = config.getdiaR();
            precioDia = config.getpreciR();
        }else {                    // Tesis
            diasPermitidos = config.getdiaT();
            precioDia = config.getpreciT();
        }
        
        // Calcular diferencia de días entre fecha de préstamo y ahora (fecha de devolución)
        Fecha fechdev;
        Fecha fechpres(ticket.getDiat(), ticket.getmest(), ticket.getAniot());

        int dias = fechdev.diasEntre(fechpres);

        // Delegar el cálculo de la multa a la implementación concreta
        multa = libro->calcMulta(dias, diasPermitidos, precioDia);

        if(multa>0.0){
            usu.setEstatus(0); //bloquea al usuario
            // TODO: implementar setMulta en Usuario si es necesario 
            UsuArchivo.seekp((id - 1) * sizeof(Usuario), ios::beg);
            UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));
        }

        archivo.close();
        UsuArchivo.close();
        ticketFile.close();
        return multa;
    }

    float pagarMulta(int id){
        Usuario usu;
        int op;
        float pago=0.0;
        
        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        if(!UsuArchivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            UsuArchivo.close();
            return 0.0;
        }
        UsuArchivo.seekg((id-1) * sizeof(Usuario), ios::beg);
        UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario));

        if(usu.getMulta() == 0.0){
            cout << "\n\t No tienes multas pendientes." << endl;
            UsuArchivo.close();
            return 0.0;
        }

        cout << "\n\t Tu saldo actual es de: $" << usu.getDinero();
        cout << "\n\t Cuanto dinero quieres pagar de tu multa de: $" << usu.getMulta();
        cout << "\n\t [1] Pagar todo";
        cout << "\n\t [2] Pagar una cantidad especifica";
        cout << "\n\t [0] Salir";
        cout << "\n\t Opcion: ";
        cin >> op;

        while (op!=1 && op!=2 && op!=0){
            cout << "\n\t Opcion no valida. Intenta de nuevo.";
            cout << "\n\t Cuanto dinero quieres pagar de tu multa de $" << usu.getMulta() << ": $";
            cout << "\n\t [1] Pagar todo";
            cout << "\n\t [2] Pagar una cantidad especifica";
            cout << "\n\t [0] Salir";
            cout << "\n\t Opcion: ";
            cin >> op;
        }

        switch(op){
            case 1:
                if (usu.getDinero() < usu.getMulta()){
                    cout << "\n\t No tienes suficiente dinero para pagar toda tu multa." << endl;
                    break;
                }
                
                pago=usu.getMulta();
                usu.setDinero(-pago);
                usu.setMulta(-pago);
                cout << "\n\t Has pagado toda tu multa. Gracias!" << endl;
                usu.setEstatus(1); //desbloquea al usuario
                break;
            case 2:
                cout << "\n\t Tienes disponible: $" << usu.getDinero() << " para pagar tu multa.";
                cout << "\n\t Ingresa la cantidad que deseas pagar: $";
                cin >> pago;
                while (pago <= 0 || pago > usu.getMulta() || pago > usu.getDinero()){
                    cout << "\n\t Cantidad no valida. Ingresa la cantidad que deseas pagar: $";
                    cout << "\n\t Tienes disponible: $" << usu.getDinero() << " para pagar tu multa.";
                    cout << "\n\t Ingresa la cantidad que deseas pagar: $";
                    cin >> pago;
                }
                usu.setDinero(-pago);
                usu.setMulta(-pago);
                cout << "\n\t Has pagado $" << pago << " de tu multa. Gracias!" << endl;
                if (usu.getMulta() == 0.0){
                    usu.setEstatus(1); //desbloquea al usuario
                }
                break;
            case 0:
                cout << "\n\t No se realizo ningun pago." << endl;
                break;
        }
        
        UsuArchivo.seekp((usu.getMatricula() - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));
        UsuArchivo.close();
        return pago;
    }

    bool getSiMulta(int id){
        int codigo, idtic, idusu, dia, mes, anio;
        bool estado; // 1: activo 0: devuelto
        char nombre[30];
        Usuario usu;
        
        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        if(!UsuArchivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            UsuArchivo.close();
            return false;
        }
        UsuArchivo.seekg((id-1) * sizeof(Usuario), ios::beg);
        UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario));
        
        fstream ticketFile("ticket.txt", ios::in | ios::app | ios::out);
        if (!ticketFile) {
            cout << "\n\t No se pudo crear/abrir ticket.dat";
            ticketFile.close();
            UsuArchivo.close();
            return false;
        }

        fstream archivo("datos.dat", ios::binary | ios::in | ios::out);
        if (!archivo) {
            cout << "\n\t El archivo Producto no se abrio correctamente.";
            cin.get();
            ticketFile.close();
            UsuArchivo.close();
            return false;
        }

        int cantpres=0;
        float multa=0.0;

         while (ticketFile>> codigo >> nombre >> dia >> mes >> anio >> idtic >> idusu >> estado && cantpres < usu.getcantPrestamos()){
            if (idusu==id && estado==1){
                cantpres++;
                contenido* registro = nullptr;
                Libro tmp;
                archivo.seekg((codigo - 1) * sizeof(Libro), ios::beg);
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
                
                Multa config;
                config.cargar();

                Fecha fechdev;
                Fecha fechpres(dia, mes, anio);
                int dias = fechdev.diasEntre(fechpres);

                int diasPermitidos;
                float precioDia;

                if (cat == 1){
                    diasPermitidos = config.getdiaL();
                    precioDia = config.getpreciL();
                }else if (cat == 2){
                    diasPermitidos = config.getdiaR();
                    precioDia = config.getpreciR();
                }else{
                    diasPermitidos = config.getdiaT();
                    precioDia = config.getpreciT();
                }

                multa = registro->calcMulta(dias, diasPermitidos, precioDia);
                
                if (multa>0.0){
                    usu.setEstatus(0);

                    UsuArchivo.seekp((id - 1) * sizeof(Usuario), ios::beg);
                    UsuArchivo.write(reinterpret_cast<char*>(&usu), sizeof(Usuario));

                    archivo.close();
                    ticketFile.close();
                    UsuArchivo.close();
                    return true;
                }
            }
        }

        archivo.close();
        ticketFile.close();
        UsuArchivo.close();
        return false;
    }

    vector<int> gettickets(int id){
        vector<int> v(3, 0);
        Usuario usu;
        time_t tiempodeprestamo;
        time_t tiempodeDevolucion;
        bool estado; // 1: activo 0: devuelto
        int idtic, cantTic = 0, idusu, codigo;
        char nombre[30];

        fstream ticketFile("ticket.txt",  ios::in | ios::out);
        if (!ticketFile) {
            cout << "\n\t No se pudo crear/abrir ticket.dat";
            ticketFile.close();
            return v;
        }

        fstream UsuArchivo("Usuarios.dat", ios::binary | ios::in | ios::out);
        if(!UsuArchivo){
            cout << "\n\t El archivo no se abrio correctamente.";
            ticketFile.close();
            UsuArchivo.close();
            return v;
        }

        UsuArchivo.seekg((id - 1) * sizeof(Usuario), ios::beg);
        UsuArchivo.read(reinterpret_cast<char*>(&usu), sizeof(Usuario));

        if(usu.getcantPrestamos() == 0) return v;

        ticketFile.seekg(0, ios::beg);
        while(ticketFile >> codigo >> nombre >> tiempodeprestamo >> idtic >> tiempodeDevolucion >> idusu >> estado && usu.getcantPrestamos() > cantTic){
            if (idusu == id && usu.getidTic(cantTic) == idtic){
                cantTic++;
                if (cantTic == 1){
                    v[0]=codigo;
                } else if (cantTic == 2){
                    v[1]=codigo;
                } else if (cantTic == 3){
                    v[3]=codigo;
                }
            }
        }
        return v;
    }
};

#endif // MULTA_DEFINED