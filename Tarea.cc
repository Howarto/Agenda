/** @file Tarea.cc
    @brief Implementación de la clase Tarea.
 */

#include "Tarea.hh"

// Constructoras

Tarea::Tarea() {}

// Modificadoras

void Tarea::anadir_etiqueta(const string& etiqueta) {
    mapa_etiquetas.insert(make_pair(etiqueta, 0));
}

void Tarea::modificar_titulo(const string &titulo) {
    this->titulo = titulo;
}

void Tarea::borrar_etiqueta(const string &etiqueta) {
    mapa_etiquetas.erase(etiqueta);
}

void Tarea::borrar_todas_las_etiquetas() {
    this->mapa_etiquetas.clear();
}

// Consultoras

void Tarea::titulo_tarea(string &titulo) const {
    titulo = this->titulo;
}

bool Tarea::tiene_etiqueta(const string &etiqueta) const {
    map<string, bool>::const_iterator it = mapa_etiquetas.find(etiqueta);
    return it != mapa_etiquetas.end();
}

//Escritura

// Cuidado que ese espacio sí que importa, siempre estará ahí, pero para la última etiqueta
// no tiene por qué estar, lo quito gracias al uso de un booleano "primer"
void Tarea::escribir_etiquetas() const{
    map<string,bool>::const_iterator it;
    for (it = mapa_etiquetas.begin();
         it != mapa_etiquetas.end(); ++it) {
         cout << ' ' << it->first;
    }
    cout << endl;
}
