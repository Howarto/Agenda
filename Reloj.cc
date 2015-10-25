/** @file Reloj.cc
    @brief Implementación de la clase Reloj.
 */

#include "Reloj.hh"

// Constructoras

Reloj::Reloj() {}


// Modificadoras

void Reloj::cambiar_hora(const string &hora) {
    this->hora = hora;
}

void Reloj::cambiar_fecha(const string &fecha) {
    this->fecha = fecha;
}

int Reloj::cmp(const Reloj &reloj) const {
    // Primero reviso que estén en la misma fecha...
    // Las posiciones de la string fecha que hay en reloj me interesan
    // la 0, 3 y 6. Empezaré por las 6, perteneciente al primer dígito
    // de los decimales del año.
    for (int i = 6; i >= 0; i = i - 3) {
        if (this->fecha[i] > reloj.fecha[i]) return 1;
        else if (this->fecha[i] < reloj.fecha[i]) return -1;
        else if (this->fecha[i + 1] > reloj.fecha[i + 1]) return 1;
        else if (this->fecha[i + 1] < reloj.fecha[i + 1]) return -1;

    }
    // Si llega hasta aquí es porque tienen misma fecha, miremos la hora
    for (int i = 0; i <= 3; i = i + 3) {
        if (this->hora[i] > reloj.hora[i]) return 1;
        else if (this->hora[i] < reloj.hora[i]) return -1;
        else if (this->hora[i + 1] > reloj.hora[i + 1]) return 1;
        else if (this->hora[i + 1] < reloj.hora[i + 1]) return -1;
    }

    return 0;
}

string Reloj::get_hora() const {
    return this->hora;
}

string Reloj::get_fecha() const {
    return this->fecha;
}


// Escritura

void Reloj::escribir_hora() const {
    cout << this->hora;
}

void Reloj::escribir_fecha() const {
    cout << this->fecha;
}

// Funciones auxiliares

bool Reloj::operator <(const Reloj &reloj_cmp) const{
    // Primero reviso que estén en la misma fecha...
    // Las posiciones de la string fecha que hay en reloj me interesan
    // la 0, 3 y 6. Empezaré por las 6, perteneciente al primer dígito
    // de los decimales del año.
    for (int i = 6; i >= 0; i = i - 3) {
        if (fecha[i] > reloj_cmp.fecha[i]) return false;
        else if (fecha[i] < reloj_cmp.fecha[i]) return true;
        else if (fecha[i + 1] > reloj_cmp.fecha[i + 1]) return false;
        else if (fecha[i + 1] < reloj_cmp.fecha[i + 1]) return true;
    }
    // Si llega hasta aquí es porque tienen misma fecha, miremos la hora
    for (int i = 0; i <= 3; i = i + 3) {
        if (hora[i] > reloj_cmp.hora[i]) return false;
        else if (hora[i] < reloj_cmp.hora[i]) return true;
        else if (hora[i + 1] > reloj_cmp.hora[i + 1]) return false;
        else if (hora[i + 1] < reloj_cmp.hora[i + 1]) return true;
    }
    return false;
}
bool Reloj::operator ==(const Reloj &reloj_cmp) const{
    // Primero reviso que estén en la misma fecha...
    // Las posiciones de la string fecha que hay en reloj me interesan
    // la 0, 3 y 6. Empezaré por las 6, perteneciente al primer dígito
    // de los decimales del año.
    for (int i = 6; i >= 0; i = i - 3) {
        if (fecha[i] > reloj_cmp.fecha[i]) return false;
        else if (fecha[i] < reloj_cmp.fecha[i]) return false;
        else if (fecha[i + 1] > reloj_cmp.fecha[i + 1]) return false;
        else if (fecha[i + 1] < reloj_cmp.fecha[i + 1]) return false;
    }
    // Si llega hasta aquí es porque tienen misma fecha, miremos la hora
    for (int i = 0; i <= 3; i = i + 3) {
        if (hora[i] > reloj_cmp.hora[i]) return false;
        else if (hora[i] < reloj_cmp.hora[i]) return false;
        else if (hora[i + 1] > reloj_cmp.hora[i + 1]) return false;
        else if (hora[i + 1] < reloj_cmp.hora[i + 1]) return false;
    }
    return true;
}
bool Reloj::operator >(const Reloj &reloj_cmp) const{
    // Primero reviso que estén en la misma fecha...
    // Las posiciones de la string fecha que hay en reloj me interesan
    // la 0, 3 y 6. Empezaré por las 6, perteneciente al primer dígito
    // de los decimales del año.
    for (int i = 6; i >= 0; i = i - 3) {
        if (fecha[i] > reloj_cmp.fecha[i]) return true;
        else if (fecha[i] < reloj_cmp.fecha[i]) return false;
        else if (fecha[i + 1] > reloj_cmp.fecha[i + 1]) return true;
        else if (fecha[i + 1] < reloj_cmp.fecha[i + 1]) return false;
    }
    // Si llega hasta aquí es porque tienen misma fecha, miremos la hora
    for (int i = 0; i <= 3; i = i + 3) {
        if (hora[i] > reloj_cmp.hora[i]) return true;
        else if (hora[i] < reloj_cmp.hora[i]) return false;
        else if (hora[i + 1] > reloj_cmp.hora[i + 1]) return true;
        else if (hora[i + 1] < reloj_cmp.hora[i + 1]) return false;
    }
    return false;
}
