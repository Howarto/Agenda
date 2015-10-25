/** @file Reloj.hh
    @brief Clase Reloj
 */

#ifndef RELOJ_HH
#define RELOJ_HH

// includes que hay que quitar para que doxygen genere buenos diagramas:
/*
// */
#include <iostream>

using namespace std;

/** @class Reloj
    @brief Representa un reloj que contiene una fecha y una hora de un cierto momento.
 */

class Reloj {


private:


    string hora;
    string fecha;

    /* Inv de representación: hora y fecha son reales de la forma **:** y **.**.**   */

public:


    // Constructoras


    /** @brief Constructora por defecto
     *  \pre Cierto
     *  \post Se crea un objeto Reloj */
    Reloj();


    // Modificadoras

    /** @brief Cambia la hora del p.i
     *  \pre  Es una hora real de la forma **:** .
     *  \post La "hora" del p.i queda modificada.
     */
    void cambiar_hora(const string &hora);


    /**
     * @brief Cambia la fecha del p.i por la pasada como parámetro.
     * \pre Es una fecha real de la forma **.**.** .
     * \post La fecha del p.i queda modificada, ahora es igual a "fecha".
     */
    void cambiar_fecha(const string &fecha);


    // Consultoras


    /**
     * @brief Compara el p.i con otro reloj, dice si es igual, menor o mayor.
     * \pre Cierto.
     * \post Devuelve un 0 si el reloj del p.i es igual a "reloj", un 1 si es mayor y un -1 si es menor.
     */
    int cmp(const Reloj &reloj) const;


    // En las dos siguientes funciones es válido devolver un vector de char como puede ser una string
    // debido a que una fecha y una hora no tienen una longitud demasiado grande.
    /**
     * @brief Retorna la hora del reloj.
     * \pre Después de ser creado el reloj, se le ha asignado una hora con el formato **:** .
     * \post Retorna una string igual a la hora del p.i
     */
    string get_hora() const;


    /**
     * @brief Retorna la fecha del reloj.
     * \pre Después de ser creado el reloj, se le ha asignado una fecha con el formato **.**.** .
     * \post Retorna una string igual a la fecha del p.i
     */
    string get_fecha() const;


    // Escritura


    /**
     * @brief Escribe por pantalla, en una sola línea, sin espaciados ni nada más, la hora que tiene el reloj.
     * \pre El p.i tiene una hora con formato **:** .
     * \post Printa por pantalla la hora del p.i.
     */
    void escribir_hora() const;


    /**
     * @brief Escribe por pantalla, en una sola línea, sin espaciados ni nada más, la fecha que tiene el reloj.
     * \pre El p.i tiene una fecha con formato **.**.** .
     * \post Printa por pantalla la fecha del p.i .
     */
    void escribir_fecha() const;


    // Funciones auxiliares


    // Las siguientes funciones son necesarias para que el diccionario de la agenda pueda ordenar las tareas
    // según el reloj.
    /**
     * @brief Función auxiliar que crea operador lógico de "menor que" para la clase Reloj.
     * \pre El reloj tiene una fecha y hora válidas.
     * \post True en caso de que el reloj del p.i tenga una fecha previa
     *  al del reloj pasado como parámetro
     */
    bool operator<(const Reloj &reloj_cmp) const;

    /**
     * @brief Función auxiliar que crea operador lógico de "igual que" para la clase Reloj.
     * Reloj ordenado.
     * \pre El reloj tiene una fecha y hora válidas.
     * \post True en caso de que el reloj del p.i tenga una fecha igual
     *  al del reloj pasado como parámetro.
     */
    bool operator==(const Reloj &reloj_cmp) const;

    /**
     * @brief Función auxiliar que crea operador lógico de "mayor que" para la clase Reloj.
     * \pre El reloj tiene una fecha y hora válidas.
     * \post True en caso de que el reloj del p.i tenga una fecha mayor
     *  al del reloj pasado como parámetro.
     */
    bool operator>(const Reloj &reloj_cmp) const;


};

#endif // RELOJ_HH

