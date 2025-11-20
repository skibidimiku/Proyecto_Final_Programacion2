#include <iostream>
using namespace std;

int mostrar_Ayuda_Inicio(){
    int a;

    do {
        cout << "\n---------------------------------------------------------";
        cout << "\n\t [1] Crear cascaron.";
        cout << "\n\t [2] Iniciar secion.";
        cout << "\n\t [3] Registrarse.";
        cout << "\n\t [4] Mostrar menu de ayuda.";
        cout << "\n\t [5] Salir.";
        cout << "\n\t [0] Salir del modo ayuda.";


        cout << "\n\n\t Elige una opcion del menu de inicio que quieres que se te explique: ";
        cin >> a;

        switch (a) {
            case 1:
                cout << "\n\t -> Crear cascaron: Esta opcion crea un archivo binario llamado 'datos.dat' que almacenara la informacion de los libros.";
                break;
            case 2:
                cout << "\n\t -> Iniciar secion: Esta opcion permite a los usuarios y admins registrados iniciar sesion en el sistema.";
                break;
            case 3:
                cout << "\n\t -> Registrarse: Esta opcion permite a nuevos usuarios registrarse en el sistema proporcionando su informacion ya sea como admin o usuario.";
                break;
            case 4:
                cout << "\n\t -> Mostrar menu de ayuda: Esta opcion muestra el menu de ayuda   en el que estas donde puedes obtener informacion sobre las diferentes opciones.";
                break;
            case 5:
                cout << "\n\t -> Salir: Esta opcion te permite salir del menu de inicio y del programa completo.";
                break;
            case 0:
                cout << "\n\t Saliendo del modo ayuda...";
                break;
            default:
                cout << "\n\t Opcion invalida. Por favor, elige una opcion valida.";
                break;
        }

    }while (a != 0);
    
    return 0;
}


int mostrar_Ayuda_Administrador(){
    int a;
     do{
        cout << "\n---------------------------------------------------------";
        cout << "\n\t [1] Crear cascaron.";
        cout << "\n\t [2] Ingresar nuevo producto";
        cout << "\n\t [3] Mostrar productos";
        cout << "\n\t [4] Modificar algun producto";
        cout << "\n\t [5] Eliminar algun producto";
        cout << "\n\t [6] Registrar prestamo (Generar ticket)";
        cout << "\n\t [7] Mostrar Total prestamos (Tickets)";
        cout << "\n\t [8] Mostrar menu de ayuda.";
        cout << "\n\t [9] Salir";
        cout << "\n\t [0] Salir del modo ayuda.";
        cout << "\n\n\t Elige una opcion: ";
        cin >> a;

        switch(a){
            case 1:
                cout << "\n\t -> Crear cascaron: Esta opcion crea un archivo binario llamado 'datos.dat' que almacenara la informacion de los libros.";
                break;
            case 2:
                cout << "\n\t -> Ingresar nuevo producto: Esta opcion permite agregar un nuevo producto al archivo binario 'datos.dat'.";
                break;
            case 3:
                cout << "\n\t -> Mostrar productos: Esta opcion muestra todos los productos almacenados en el archivo binario 'datos.dat'.";
                break;   
            case 4: 
                cout << "\n\t -> Modificar algun producto: Esta opcion permite modificar la informacion de un producto existente en el archivo binario 'datos.dat'.";
                break;     
            case 5:
                cout << "\n\t -> Eliminar algun producto: Esta opcion permite eliminar un producto existente en el archivo binario 'datos.dat'.";
                break;
            case 6:
                cout << "\n\t -> Registrar prestamo (Generar ticket): Esta opcion permite registrar la prestamo de un producto y generar un ticket de prestamo.";
                break;
            case 7:
                cout << "\n\t -> Mostrar Total prestamos (Tickets): Esta opcion muestra el total de prestamos realizadas y los tickets generados.";
                break;
            case 8:
                cout << "\n\t -> Mostrar menu de ayuda: Esta opcion muestra el menu de ayuda en el que puedes obtener informacion sobre las diferentes opciones.";
                break;
            case 0:
                cout << "\n\t Saliendo del modo ayuda...";
                break;
            default:
                cout << "\n\t Opcion invalida. Por favor, elige una opcion valida.";
                break;
        }
    }while(a != 0);

    return 0;
}