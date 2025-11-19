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

}