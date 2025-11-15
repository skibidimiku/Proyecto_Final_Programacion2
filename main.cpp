#include <fstream>
#include <iostream>
#include "Usuario.h"
#include "CrearCascaron.h"
#include "SetLibro.h"
#include "DemostrarLibro.h"
#include "Libro.h"
#include "ModificarLibro.h"
#include "EliminarLibro.h"
#include "generarTicket.h"

using namespace std;

int main(){
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

            case 0: cout << "\n\t Saliendo del programa...\n";
                break;
            default: cout << "\n\t Opcion invalida.\n";
                break;
        }
    }while(selec != 0);
    return 0;
}