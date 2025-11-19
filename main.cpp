#include <fstream>
#include <iostream>
#include <ctime>
#include "Usuario.h"
#include "CrearCascaron.h"
#include "SetLibro.h"
#include "DemostrarLibro.h"
#include "Libro.h"
#include "ModificarLibro.h"
#include "EliminarLibro.h"
#include "generarTicket.h"
#include "Menus_Ayuda.h"

using namespace std;
void menu_Administrador();
void menu_Usuario();

int main(){
    int op, id, tipo_menu=0;
    time_t tiempodeinicio;
    time(&tiempodeinicio);
    char* fecha=ctime(&tiempodeinicio);
    cout<<"La fecha es: " << fecha;
    Usuario usuario;

    do{
        cout << "\n---------------------------------------------------------";
        cout << "\n\t\t\t ---> Menu De Inicio <---";
        cout << "\n\t [1] Crear cascaron.";
        cout << "\n\t [2] Iniciar secion.";
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
                menu_Administrador();
            }else if(tipo_menu == 0){
                menu_Usuario();
            }
            
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

void menu_Administrador(){
    int selec;
    do{
        cout << "\n---------------------------------------------------------";
        cout << "\n\t\t\t ---> MENU <---";
        cout << "\n\t [1] Crear cascaron.";
        cout << "\n\t [2] Ingresar nuevo producto";
        cout << "\n\t [3] Mostrar productos";
        cout << "\n\t [4] Modificar algun producto";
        cout << "\n\t [5] Eliminar algun producto";
        cout << "\n\t [6] Registrar venta (Generar ticket)";
        cout << "\n\t [7] Mostrar Total Ventas (Tickets)";
        cout << "\n\t [8] Mostrar menu de ayuda.";
        cout << "\n\t [0] Salir";
        cout << "\n\n\t Elige una opcion: ";
        cin >> selec;

        switch(selec){
            case 1: creaCascaron();
            break;
            
            case 2: SetLibro();
            break;
            
            case 3: DemonstrarLibro();
            break;   
            
            case 4: ModificarLibro();
            break;     
            
            case 5: EliminarLibro();
            break;
            
            case 6: {
                int cantidad=0;
                Libro libro; 
                if(GenerarTicketVenta(libro, cantidad) == 0); 
            }
                break;


            case 7: 
                //MostrarTotalVentas();
            break;

            case 8:
                mostrar_Ayuda_Administrador();
                break;

            case 0: cout << "\n\t Saliendo del programa...\n";
                break;
            default: cout << "\n\t Opcion invalida.\n";
                break;
        }
    }while(selec != 0);
}

void menu_Usuario(){
    
}