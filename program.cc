/**
  * @mainpage Gestor de tareas.
  *
  * En esta implementación se ejecuta una agenda donde se pueden realizar diferentes acciones sobre ella.
  * Se podrán modificar, insertar y consultar diferentes tareas de una forma rápida y simple.
  */

/** @file program.cc
    @brief Archivo principal donde se ejecuta todo el programa.
 */

// includes que hay que quitar para que doxygen genere buenos diagramas:
/*
// */
#include "comanda.hh"
#include "utils"
#include "Agenda.hh"

// Diego: Recordatorio: Preguntar a Borja sobre la eficiencia del código y también acerca de la expresion si metemos una comanda
// que diga " ? () ", eso es una expresión considerada correcta?

/**
 * @brief Función llamada desde la función principal main que revisa las entradas y escoje
 * qué funciones aplicar de las diferentes clases para lograr una salida pertinente.
 * \pre "comanda" es una entrada válida.
 * \post Se han ejecutado las pertinentes acciones según las tareas requeridas (mirar enunciado de la práctica).
 */
void opciones(Agenda &agenda, Comanda &comanda) {
    if (comanda.es_insercio()) { //Introducir tareas
        agenda.opcion_insercion(comanda);
    }
    else if (comanda.es_rellotge()) { //todas las relacionadas con el reloj
        agenda.opcion_reloj(comanda);
    }
    else if (comanda.es_passat()) { //todas las tareas pasadas
        agenda.escribir_tareas_pasadas();
    }
    else if (comanda.es_consulta()) { //empiezan con interrognte: todas o algunas de las futuras
        agenda.opcion_consulta(comanda);
    }
    else if (comanda.es_modificacio()) { //empieza en numero y no le sigue un -
        agenda.opcion_modificacion(comanda);
    }
    else if (comanda.es_esborrat()){  //opcion de borrado
        agenda.opcion_borrado(comanda);
    }
}

/**
 * @brief Programa principal.
 */
int main() {
    Agenda agenda;
    Comanda comanda;
    bool b;
    bool salida = comanda.llegir(b);
    while (salida) {
        if (b) opciones(agenda, comanda);
        salida = comanda.llegir(b);
    }

}
