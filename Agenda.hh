/** @file Agenda.hh
    @brief Clase Agenda
 */

#ifndef AGENDA_HH
#define AGENDA_HH

// includes que hay que quitar para que doxygen genere buenos diagramas:
/*
// */
#include <map>
#include <vector>
#include <list>
#include "utils"
#include "comanda.hh"

#include "Reloj.hh"
#include "Tarea.hh"


/** @class Agenda
    @brief Representa una agenda. Ésta administra (crea, modifica, elimina, consulta) tareas mediante la clase Comanda teniendo así como
    referencia la cantidad de tareas, el orden temporal de las mismas y el tiempo actual.
 */

class Agenda {

private:

    Reloj reloj;
    map<Reloj, Tarea> mapa;
    vector< map< Reloj, Tarea>::iterator> menu;

    // Inv de representación de la clase: "mapa" siempre se encuentra ordenado por fecha y hora, en orden creciente,
    // "reloj" siempre es una fecha igual o posterior a 20.04.15 a las 00:00h.

    // Auxiliares

    /**
     * @brief Escribe los siguientes datos: título de la tarea [espacio] fecha [espacio] hora [espacio] etiquetas (si las hay)
     * \pre el iterador pasado por parámetro es válido.
     * \post escribe los datos apuntada por "it": título de la tarea [espacio] fecha [espacio] hora [espacio] etiquetas (si las hay) por pantalla.
     */
    static void escribir_datos_por_orden(const map<Reloj, Tarea>::iterator &it);


    /**
     * @brief Calcula la posición final de la etiqueta que empieza en s[inicio] dentro de una string.
     * \pre s[inicio] = '#' , s es una expresión válida y 0 <= inicio <= s.size()-1 .
     * \post "final" tiene la posición siguiente en s al final de la etiqueta.
     */
    static void evitar_etiqueta(const string &s, int inicio, int &final);


    /**
     * @brief Recalcula el valor de "pos" para que se encuentre en una posición posterior a
     * la expresión que empieza en s[pos].
     * \pre "pos" es una posición existente en s[0..s.size()-1] en la que s[pos] es la siguiente
     * posición del paréntesi de una expresión.
     * \post "pos" queda modificado de forma que s[pos-1] es el cierre de la expresión tratada al inicio.
     */
    static void evitar_expresion(const string &s, int &pos);


    /**
     * @brief Trata una expresión booleana de forma que devuelve true o false dependiendo de si
     * una tarea cumple o no la expresión "s".
     * \pre "s" es una expresión válida, el iterador apunta a una tarea que queremos tratar y
     * "pos" tiene el valor de la posición de inicio de la expresión a tratar.
     * \post Se devuelve true en caso de que la tarea apuntada por "it" cumpla la expresión que empieza en s[pos]
     * y false en caso contrario.
     */
    bool tratar_expresion(const string &s, int &pos, map<Reloj, Tarea>::iterator &it);


    // Modificadoras


    /**
     * @brief Modifica el reloj del p.i en caso de que "reloj_modificado" sea un reloj
     * considerado válido, si no se muestra el mensaje "No s'ha realitzat".
     * \pre Cierto
     * \post Se ha modificado el reloj interno de la agenda por el reloj pasado
     * como parámetro, sólo si éste era válido, es decir, que fuese del presente
     * o del futuro, en caso contrario se muestra el mensaje "No s'ha realitzat".
     */
    void modificar_reloj(const Reloj &reloj_modificado);


    /**
     * @brief Modifica el reloj de una tarea.
     * \pre El reloj para la tarea tiene que ser válido, es decir,
     * que sea igual o posterior al reloj interno del p.i
     * \post Se modifica el reloj de la tarea en el caso de que se haya introducido
     * una "i" válida que se refiera a algún elemento del menú de usuario, en caso
     * contrario se muestra "No s'ha realitzat".
     */
    void modificar_reloj_tarea(int i, const Reloj &reloj_para_tarea);


    /**
     * @brief Elimina la iésima tarea del menú.
     * \pre Cierto.
     * \post La iésima tarea es eliminada siempre y cuando sea una tarea presente o futura y
     * la i se encuentre entre 1 y el tamaño del menú que se muestra al usuario,
     * en caso contrario se muestra "No s'ha realitzat".
     */
    void eliminar_iesima_tarea(int i);


    /**
     * @brief Elimina la etiqueta de una tarea.
     * \pre Cierto.
     * \post La etiqueta de la tarea iésima contenida por el p.i queda eliminada, en
     * caso de que la i sea un valor contenido entre 1 y el tamaño del menú, "etiqueta"
     * se encuentre en la tarea iésima y que sea una tarea presente o futura,
     * en caso contrario se muestra por pantalla "No s'ha realitzat".
     */
    void eliminar_etiqueta_a_tarea_iesima(int i, const string &etiqueta);


    /**
     * @brief Elimina todas las etiquetas de una tarea.
     * \pre Cierto
     * \post La tarea iésima quedará vacía en cuanto a etiquetas siempre y cuando la i tenga un valor
     * entre 1 y el tamaño del menú.
     */
    void eliminar_todas_etiquetas_tarea(int i);

    /**
     * @brief Modifica el título de una tarea.
     * \pre La tarea iésima tiene que pertenecer al presente o futuro.
     * \post El título de la tarea iésima del p.i queda cambiado por "titulo" en caso
     * de que i se encuentre entre 1 y el tamaño del menú. En caso contrario se muestra
     * por pantalla "No s'ha realitzat".
     */
    void modificar_titulo_tarea_iesima(int i, const string &titulo);


    /**
     * @brief Inserta una etiqueta a una tarea
     * \pre La tarea iésima pertenece al presente o futuro.
     * \post Se añade una etiqueta a la tarea iésima si la i se encuentra
     * con un valor entre 1 y el tamaño del menú.
     */
    void insertar_etiqueta_a_tarea_iesima(int i, const string &etiqueta);


    // Consultoras


    /**
     * @brief Modifica el parámetro pasado por referencia y lo hace igual al reloj de la tarea.
     * \pre i es un entero válido, es decir, es un número del menú.
     * \post "reloj" queda modificado y ahora contiene el reloj de la tarea iésima en caso
     * de que i haya sido correcto, si no, mostrará un mensaje de error.
     */
    void consultar_reloj_tasca_iesima(int i, Reloj &reloj) const;


    /**
     * @brief Se printarán todas las tareas desde el presente hacia el futuro con la etiqueta en cuestión.
     * \pre Cierto.
     * \post Se printarán todas las tareas desde el presente hacia el futuro con la etiqueta en cuestión.
     */
    void consulta_etiqueta(string etiqueta);


    /**
     * @brief Dice si el reloj que entra como parámetro es válido para modificar el actual reloj interno del p.i
     * \pre Son relojes con fecha y hora válidas.
     * \post Retorna true si el reloj pasado como parámetro es válido para insertar en el p.i, es decir, forma
     * parte del presente o del futuro, nunca del pasado.
     */
    bool reloj_valido(const Reloj &reloj) const;


    /**
     * @brief Compara dos fechas y dice si "fecha1" es igual o más pequeña que "fecha2"
     * \pre Son fechas con formato **.**.** y reales.
     * \post Retorna true si "fecha1" es menor o igual que "fecha2".
     */
    static bool fecha_cmp_menor_igual_que(const string &fecha1, const string &fecha2);


    /**
     * @brief Compara dos fechas y dice si "fecha1" es igual que "fecha2"
     * \pre Son fechas con formato **.**.** y reales.
     * \post Retorna true si "fecha1" es igual que "fecha2".
     */
    static bool fecha_cmp_igual_que(const string &fecha1, const string &fecha2);


    // Escritura


    /**
     * @brief Escribe todas las tareas futuras por pantalla.
     * \pre Cierto.
     * \post Printa por pantalla todas las tareas futuras.
     */
    void escribir_tareas_futuras();


    /**
     * @brief Escribe todas las tareas contenidas en el intervalo [it1, it2)
     * \pre Los iteradores tienen una posición real de "mapa" donde ambos representan un intervalo
     * [inicio, final).
     * \post Se printan todas las tareas contenidas en el intervalo [it1, it2).
     */
    void escribir_intervalo_de_tareas(map< Reloj, Tarea>::iterator inicio, map< Reloj, Tarea>::iterator final);


    /**
     * @brief Escribe todas las tareas contenidas en el intervalo [it1, it2)
     * \pre Los iteradores tienen una posición real de "mapa" donde ambos representan un intervalo
     * [inicio, final).
     * \post Se printan todas las tareas con la etiqueta "etiqueta" contenidas en el intervalo [it1, it2).
     */
    void escribir_intervalo_de_tareas_con_etiqueta(map< Reloj, Tarea>::iterator inicio,
                                                   map< Reloj, Tarea>::iterator final, const string &etiqueta);

public:


    // Constructora


    /**
     * @brief Constructora por defecto, crea un objeto Agenda con hora "00:00" y fecha "20.04.15".
     * \pre Cierto.
     * \post Se crea una instancia de Agenda.
     */
    Agenda();


    /**
     * @brief Realiza la accion de tipo insercion de tareas
     * \pre "comanda" es del tipo insercion
     * \post se ha realizado la opcion de insercion de comanda
     */
    void opcion_insercion(Comanda &comanda);


    /**
     * @brief Realiza acciones de consulta y modificacion del reloj interno de la agenda.
     * \pre "comanda" es del tipo reloj
     * \post se ha realizado la accion de reloj de comanda siempre y cuando ésta fuese válida(enunciado de la práctica).
     */
    void opcion_reloj(Comanda &comanda);


    /**
     * @brief Realiza acciones de consulta de tareas mostrando un menú como
     * respuesta a la consulta.
     * \pre "comanda" es del tipo consulta, pero no de pasado
     * \post se ha realizado la accion de consulta de comanda siempre y cuando ésta fuese válida(enunciado de la práctica).
     */
    void opcion_consulta(Comanda &comanda);


    /**
     * @brief Realiza acciones de modificaciones de tareas
     * \pre "comanda" es del tipo modificacion de tareas
     * \post se ha realizado la accion de modificado de comanda siempre y cuando ésta fuese válida(enunciado de la práctica).
     */
    void opcion_modificacion(Comanda &comanda);


    /**
     * @brief realiza acciones de borrado
     * \pre comanda es del tipo borrado
     * \post se ha realizado la accion de borrado de comanda siempre y cuando ésta fuese válida(enunciado de la práctica).
     */
    void opcion_borrado(Comanda &comanda);


    /**
     * @brief Escribe un menú con todas las tareas del pasado.
     * \pre Cierto
     * \post Se printa por pantalla todas las tareas pasadas.
     */
    void escribir_tareas_pasadas();


};


#endif // AGENDA_HH

