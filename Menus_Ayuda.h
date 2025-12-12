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
        cout << "\n\t [1] Ingresar nuevo producto";
        cout << "\n\t [2] Mostrar productos";
        cout << "\n\t [3] Modificar algun producto";
        cout << "\n\t [4] Eliminar algun producto";
        cout << "\n\t [5] Registrar usuario";
        cout << "\n\t [6] ";
        cout << "\n\t [7] Mostrar menu de ayuda.";
        cout << "\n\t [8] Salir";
        cout << "\n\t [0] Salir del modo ayuda.";

        cout << "\n\n\t Elige una opcion del menu de administrador que quieres que se te explique: ";
        cin >> a;

        switch(a){
            case 1: 
                cout << "\n\t -> Ingresar nuevo producto: Esta opcion permite al administrador agregar nuevos libros al sistema proporcionando detalles como titulo, categoria, autor y ejemplares totales.";
                break;
            case 2: 
                cout << "\n\t -> Mostrar productos: Esta opcion permite al administrador ver una lista de todos los libros registrados en el sistema junto con sus detalles.";
                break;
            case 3: 
                cout << "\n\t -> Modificar algun producto: Esta opcion permite al administrador modificar la informacion de un libro existente en el sistema.";
                break;   
            case 4: 
                cout << "\n\t -> Eliminar algun producto: Esta opcion permite al administrador eliminar un libro existente del sistema.";
                break;    
            case 5:
                cout << "\n\t -> Registrar usuario: Esta opcion permite al administrador registrar nuevos usuarios en el sistema.";
                break;
            case 6: 
            break;

            case 7: 
                cout << "\n\t -> Mostrar menu de ayuda: Esta opcion muestra el menu de ayuda en el que estas donde puedes obtener informacion sobre las diferentes opciones.";
                break;
            case 8:
                cout << "\n\t Salir: Esta opcion te permite salir del menu de administrador.";
                break;

            case 0: cout << "\n\t Saliendo del modo ayuda...\n";
                break;
            default: cout << "\n\t Opcion invalida. Por favor, elige una opcion valida.\n";
                break;
        }
    }while(a != 0);

    return 0;
}

int mostrar_Ayuda_Usuario(){
    int a;

     
    do{
        cout << "\n---------------------------------------------------------";
        cout << "\n\t [1] Mostrar productos";
        cout << "\n\t [2] Pedir prestamo de libro";
        cout << "\n\t [3] Devolver libro";
        cout << "\n\t [4] Mostrar mis datos";
        cout << "\n\t [5] Pagar multa";
        cout << "\n\t [6] Explorar mis tickets";
        cout << "\n\t [7] Mostrar menu de ayuda.";
        cout << "\n\t [8] Salir";
        cout << "\n\t [0] Salir del modo ayuda.";

       cout << "\n\n\t Elige una opcion del menu de usuario que quieres que se te explique: ";
        cin >> a;

        switch(a){
            case 1: 
                cout << "\n\t -> Mostrar productos: Esta opcion permite al usuario ver una lista de todos los libros registrados en el sistema junto con sus detalles.";
                break;
            case 2: 
                cout << "\n\t -> Pedir prestamo de libro: Esta opcion permite al usuario solicitar un prestamo de un libro disponible en el sistema.";
                break;
            case 3: 
                cout << "\n\t -> Devolver libro: Esta opcion permite al usuario devolver un libro que ha prestado previamente.";
                break;   
            case 4: 
                cout << "\n\t -> Mostrar mis datos: Esta opcion permite al usuario ver y actualizar su informacion personal registrada en el sistema.";
                break;
            case 5: 
                cout << "\n\t -> Pagar multa: Esta opcion permite al usuario pagar cualquier multa pendiente asociada a su cuenta.";
                break;
            case 6: 
                cout << "\n\t -> Explorar mis tickets: Esta opcion permite al usuario ver una lista de todos los tickets de prestamo que ha generado.";
                break;    
            case 7: 
                cout << "\n\t -> Mostrar menu de ayuda: Esta opcion muestra el menu de ayuda en el que estas donde puedes obtener informacion sobre las diferentes opciones.";
                break; 
            case 8: 
                cout << "\n\t Salir: Esta opcion te permite salir del menu de usuario.";
                break;
            case 0: cout << "\n\t Saliendo del modo ayuda...\n";
                break;
            default: cout << "\n\t Opcion invalida. Por favor, elige una opcion valida.\n";
                break;
        }
    }while(a != 0);

    return 0;
}