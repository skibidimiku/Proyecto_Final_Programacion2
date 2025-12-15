#include <fstream>
#include <iostream>
#include <ctime>
#include <cctype>
#include <vector>
#include "Usuario.h"
#include "fecha.h"
#include "CrearCascaron.h"
#include "SetUsuario.h"
#include "ticketDevolucion.h"
#include "SetLibro.h"
#include "DemostrarLibro.h"
#include "Libro.h"
#include "multa.h"
#include "ModificarLibro.h"
#include "EliminarLibro.h"
#include "generarTicket.h"
#include "menus_Ayuda.h"
#include "FuncionesAux.h"


using namespace std;
void menu_Administrador(int id);
void menu_Usuario(int id);
void corte();
int esnum();

int c=0,  cdev=0;
float Multa_corte=0.0;

int main(){
    int op, id, tipo_menu=0;
    time_t tiempodeinicio;
    time(&tiempodeinicio);
    char* fecha=ctime(&tiempodeinicio);
    cout<<"La fecha es: " << fecha;
    cout << tiempodeinicio;
    Usuario usuario;

    do{
        cout << "\n---------------------------------------------------------";
        cout << "\n\t\t\t ---> Menu De Inicio <---";
        cout << "\n\t [1] Crear cascaron.";
        cout << "\n\t [2] Iniciar sesion.";
        cout << "\n\t [3] Registrarse.";
        cout << "\n\t [4] Mostrar menu de ayuda.";
        cout << "\n\t [0] Salir.";
        cout << "\n\n\t Elige una opcion: ";
        op = esnum();

        switch (op)
        {
        case 1:
            creaCascaron();
            break;
            
        case 2:
            cout << "\n\t Dame la matricula del usuario: ";
            id = esnum();
            tipo_menu=usuario.iniciarSecion(id);
            if (tipo_menu == 1){
                menu_Administrador(id);
            }else if(tipo_menu == 0){
                menu_Usuario(id);
            }
            
            break;

        case 3:
            SetUsuario();
            break;
        
        case 4:
            mostrar_Ayuda_Inicio();
            break;

        default:
            cout << "\n\n\t La opcion no existe.";
            break;
        }

    }while(op != 0); 

    time_t tiempodefin;
    time(&tiempodefin);
    long double  duracion = difftime(tiempodefin, tiempodeinicio);
    cout << "la diferencia de tiempo es de: " << duracion << " segundos." << endl;

    return 1;
}

void menu_Administrador(int id){
    int selec, otrid, cua;
    vector<int> ids;
    Usuario Usua;
    Multa multaObj;
    
    do{
        cout << "\n----------------------------------------------------------------------------------------";
        cout << "\n\t ---> Menu De Administrador <---";
        cout << "\n\t [1] Ingresar nuevo producto";
        cout << "\t [2] Mostrar productos";
        cout << "\t [3] Modificar algun producto";
        cout << "\n\t [4] Eliminar algun producto";
        cout << "\t [5] Registrar usuario";
        cout << "\t [6] Elminar usuario";
        cout << "\n\t [7] Corte del dia.";
        cout << "\t [8] Ajustar condidiones de prestamo.";
        cout << "\t [9] Mostrar menu de ayuda.";
        cout << "\n\t [10] Prestamos activos.";
        cout << "\t [11] Top Prestmos.";
        cout << "\t [12] Mostrar menu de ayuda.";

        cout << "\n\t [0] Salir";
        cout << "\n\n\t Elige una opcion: ";
        selec = esnum();

        switch(selec){
            case 1: SetLibro();
            break;
            
            case 2: DemonstrarLibro();
            break;
            
            case 3: ModificarLibro();
            break;   
            
            case 4: EliminarLibro();
            break;     
            
            case 5: SetUsuario();
            break;
            
            case 6: 
            cout << "\n\t Dame la matricula del usuario: ";
            otrid = esnum();
            ids= multaObj.gettickets(otrid);
            Usua.BajaUsuario(otrid, ids);
            break;

            case 7: corte();
            break;

            case 8: 
            cout << "\n\t 1) Libro \t 2) Resista \t 3)Tesis";
            cout << "\n\t Dame la que quieras modificar: ";
            cua = esnum();
            while (cua < 1 && cua > 3){
                cout << "\n\t Dame la que quieras modificar: ";
                cua = esnum();
            }
            

            multaObj.modificarcondi(cua);
            break;

            case 9: usuariosMorosos();
            break;

            case 10: prestamosActivos();
            break;

            case 11: topMatPrestamos();
            break;

            case 12: mostrar_Ayuda_Administrador();
            break;

            case 0: cout << "\n\t Saliendo al menu inicial...\n";
                break;
            default: cout << "\n\t Opcion invalida.\n";
                break;
        }
    }while(selec != 0);
}

void menu_Usuario(int id){
    int selec;
    Usuario Usua;
    Multa multaObj;
    float din;

    if (multaObj.getSiMulta(id)){
        cout << "\n\t Tienes una multa pendiente, no puedes realizar prestamos hasta pagarla y devolver el libro si no lo devolviste." << endl;
    }
    
    
    do{
        cout << "\n----------------------------------------------------------------------------------------";
        cout << "\n\t ---> Menu De Usuario <---";
        cout << "\n\t [1] Mostrar productos";
        cout << "\t [2] Pedir prestamo de libro";
        cout << "\t [3] Devolver libro";
        cout << "\n\t [4] Mostrar mis datos";
        cout << "\t [5] Pagar multa";
        cout << "\t [6] Explorar mis tickets";
        cout << "\n\t [7] Depositar dinero.";
        cout << "\t [8] Mostrar menu de ayuda.";
        cout << "\t [0] Salir";
        cout << "\n\n\t Elige una opcion: ";
        selec = esnum();

        switch(selec){
            case 1: DemonstrarLibro();
            break;
            
            case 2:  if(GenerarTicketPrestamo(Usua, id) == 0) c++;
            break;
            
            case 3: if(GenerarTicketDevolucion(Usua, id)) cdev++;
            break;   
            
            case 4: Usua.printUsuario(id);
            break;     
            
            case 5: Multa_corte = multaObj.pagarMulta(id); 
                break;
            
            
            case 6: 
                Ticket ti;
                ti.imprimirTicket(id);
            break;

            case 7: 
                cout << "\n\t Dame la cantidad a depositar: ";
                cin >> ws;
                cin >> din;
                while (din < 1){
                    cout << "\n\t Dame la cantidad a depositar: ";
                    cin >> din;
                }
                Usua.depositarDin(id, din);

            case 8: 
                mostrar_Ayuda_Usuario();
            break;

            case 0: cout << "\n\t Saliendo al menu inicial...\n";
                break;
            default: cout << "\n\t Opcion invalida.\n";
                break;
        }
    }while(selec != 0);
}

void corte(){
    if (c == 0 && cdev == 0 && Multa_corte == 0){
        cout << "\n\t No ha pasado ni una operacion.";
        return; 
    }
    
    if (c > 0){
        cout << "\n\t Se han prestado [" << c << "] libros en esta secion." ;
    }

    if (Multa_corte > 0){
        cout << "\n\t Se han recolectado $" << Multa_corte << " por multas en esta secion." ;
    }
    
    if (cdev > 0){
        cout << "\n\t Se han regresado [" << cdev << "] prestamos en esta secion." ;
    }
    
    
}

int esnum(){
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