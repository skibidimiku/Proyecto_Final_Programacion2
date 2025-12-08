#include <fstream>
#include <iostream>
#include <ctime>
#include "Usuario.h"
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


using namespace std;
void menu_Administrador(int id);
void menu_Usuario(int id);

int c=0;
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
        cin >> op;

        switch (op)
        {
        case 1:
            creaCascaron();
            break;
            
        case 2:
            cout << "\n\t Dame la matricula del usuario: ";
            cin >> id;
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
    int selec;
    Usuario Usua;
    
    do{
        cout << "\n---------------------------------------------------------";
        cout << "\n\t ---> Menu De Administrador <---";
        cout << "\n\t [1] Ingresar nuevo producto";
        cout << "\n\t [2] Mostrar productos";
        cout << "\n\t [3] Modificar algun producto";
        cout << "\n\t [4] Eliminar algun producto";
        cout << "\n\t [5] Registrar usuario";
        cout << "\n\t [6] ";
        cout << "\n\t [7] Mostrar menu de ayuda.";
        cout << "\n\t [0] Salir";
        cout << "\n\n\t Elige una opcion: ";
        cin >> selec;

        switch(selec){
            case 1: SetLibro();
            break;
            
            case 2: DemonstrarLibro();
            break;
            
            case 3: ModificarLibro();
            break;   
            
            case 4: EliminarLibro();
            break;     
            
            case 5:
                SetUsuario();
                break;
            
            case 6: 
            break;

            case 7: 
                //MostrarTotalVentas();
            break;

            case 8:
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

    if (multaObj.getSiMulta(id)){
        cout << "\n\t Tienes una multa pendiente, no puedes realizar prestamos hasta pagarla." << endl;
    }
    
    
    do{
        cout << "\n---------------------------------------------------------";
        cout << "\n\t ---> Menu De Usuario <---";
        cout << "\n\t [1] Mostrar productos";
        cout << "\n\t [2] Pedir prestamo de libro";
        cout << "\n\t [3] Devolver libro";
        cout << "\n\t [4] Mostrar mis datos";
        cout << "\n\t [5] Pagar multa";
        cout << "\n\t [6] Explorar mis tickets";
        cout << "\n\t [7] Mostrar menu de ayuda.";
        cout << "\n\t [0] Salir";
        cout << "\n\n\t Elige una opcion: ";
        cin >> selec;

        switch(selec){
            case 1: DemonstrarLibro();
            break;
            
            case 2:  if(GenerarTicketPrestamo(Usua, id) == 0) c++;
            break;
            
            case 3: GenerarTicketDevolucion(Usua, id);
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
                //MostrarTotalVentas();
            break;

            case 0: cout << "\n\t Saliendo al menu inicial...\n";
                break;
            default: cout << "\n\t Opcion invalida.\n";
                break;
        }
    }while(selec != 0);
}