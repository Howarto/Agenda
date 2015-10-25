/** @file Tarea.hh
    @brief Clase Tarea
 */

#ifndef TAREA_HH
#define TAREA_HH

// includes que hay que quitar para que doxygen genere buenos diagramas:
/*
// */
#include <iostream>
#include <map>

using namespace std;

/** @class Tarea
 *  @brief Representa una tarea. La tarea tiene un título y puede tener etiquetas asociadas a ella.
 */

class Tarea {

private:


    string titulo;
    map< string, bool> mapa_etiquetas;

    /* Invariante de representacion:
     * -El mapa de etiquetas siempre esta ordenado lexicográficamente
     * - Definimos una etiqueta como válida a toda etiqueta que tenga la forma #[palabra] y "palabra"
     *   sólo contiene letras.
    */


public:


    //Constructoras


    /**
     * @brief Crea una tarea vacía.
     * \pre Cierto.
     * \post Crea una tarea vacía.
     */
    Tarea();


    //Modificadoras


    /**
     * @brief Añade etiqueta a la lista de etiquetas de la tarea
     * \pre "etiqueta" es válida.
     * \post Si "etiqueta" no pertenecía a la tarea, ahora sí pertenece. No hace nada en caso contrario.
     */
    void anadir_etiqueta(const string& etiqueta);


    /**
     * @brief "título" se convierte en el nuevo título de la tarea.
     * \pre Cierto.
     * \post "título" se convierte en el nuevo título de la tarea.
     */
    void modificar_titulo(const string &titulo);


    /**
     * @brief Borra una etiqueta específica de una tarea. En caso de que la etiqueta especificada no se encuentre
     * dentro de la tarea se mostrará por pantalla el mensaje "No s'ha realitzat".
     * \pre Cierto.
     * \post Si etiqueta forma parte de la tarea, etiqueta deja de formar parte de la tarea.
     *       En caso contrario se escribe en pantalla el mensaje "No s'ha realitzat".
     */
    void borrar_etiqueta(const string &etiqueta);


    /**
     * @brief Borra todas las etiquetas de la tarea.
     * \pre Cierto.
     * \post La tarea queda con el diccionario de tareas vacío.
     */
    void borrar_todas_las_etiquetas();


    //Consultoras


    /**
     * @brief Se modifica la string pasada como parámetro dejándola igual al título de la tarea.
     * \pre Cierto.
     * \post "titulo" contiene el título de la tarea.
     */
    void titulo_tarea(string &titulo) const;


    /**
     * @brief Retorna true si la etiqueta del parametro pertenece a la tarea, y false en caso contrario.
     * \pre cierto.
     * \post true si la etiqueta del parametro pertenece a la tarea y false en caso contrario.
     */
    bool tiene_etiqueta(const string &etiqueta) const;


    /**
     * @brief Retorna true si la tarea tiene una o mas etiquetas y false en caso contrario.
     * \pre Cierto.
     * \post True si la tarea tiene una o mas etiquetas y false en caso contrario.
     */
    bool hay_etiquetas() const;


    // Escritura


    /**
     * @brief Escribe en el canal de salida todas las etiquetas que tiene la tarea.
     * \pre Cierto.
     * \post Se ha escrito por el canal de salida todas las etiquetas de la tarea. Cada una
     * tiene un espacio delante antes de ser escritas.
     */
    void escribir_etiquetas() const;


};



#endif // TAREA_HH
