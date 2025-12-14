#ifndef FECHA_DEFINED
#define FECHA_DEFINED

#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

using namespace std;

class Fecha {
private:
    int dia;
    int mes;
    int anio;

    // Convierte la fecha a time_t
    time_t aTimeT() const {
        tm t = {};
        t.tm_mday = dia;
        t.tm_mon  = mes - 1;     // 0-11
        t.tm_year = anio - 1900; // desde 1900
        t.tm_hour = 0;
        t.tm_min  = 0;
        t.tm_sec  = 0;
        return mktime(&t);
    }

public:
    // Fecha actual
    Fecha() {
        auto ahora = chrono::system_clock::now();
        time_t tiempo = chrono::system_clock::to_time_t(ahora);
        tm* f = localtime(&tiempo);

        dia  = f->tm_mday;
        mes  = f->tm_mon + 1;
        anio = f->tm_year + 1900;
    }

    //getters de la clase fecha
    int getDia(){ return dia; }
    int getmes(){ return mes; }
    int getAnio(){ return anio; }

    void setfecha(int d, int m, int a){ dia=d; mes=m; anio=a; }

    // Fecha personalizada
    Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}

    void mostrar() const {
        cout << "\t " << dia << "/" << mes << "/" << anio << endl;
    }

    // ===== Días entre dos fechas =====
    int diasEntre(const Fecha& f) const {
        double segundos = difftime(aTimeT(), f.aTimeT());
        return abs(segundos / (60 * 60 * 24));
    }

};

#endif 