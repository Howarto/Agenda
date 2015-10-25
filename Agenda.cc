/** @file Agenda.cc
    @brief Implementación de la clase Agenda.
 */

#include "Agenda.hh"

// Auxiliares

void Agenda::escribir_datos_por_orden(const map<Reloj, Tarea>::iterator &it) {
    string titulo;
    it->second.titulo_tarea(titulo);
    cout << titulo << ' ';
    it->first.escribir_fecha();
    cout << ' ';
    it->first.escribir_hora();
    it->second.escribir_etiquetas();
}


void Agenda::evitar_etiqueta(const string &s, int inicio, int &final) {
    while (s[inicio] != '.' and s[inicio] != ',' and s[inicio] != ')') {
        ++inicio;
    }
    final = inicio;
}


void Agenda::evitar_expresion(const string &s, int &pos) {
    int cuenta = 1;
    while (cuenta > 0) {
        if (s[pos] == '(') ++cuenta;
        else if (s[pos] == ')') --cuenta;
        ++pos;
    }
}


bool Agenda::tratar_expresion(const string &s, int &pos, map<Reloj, Tarea>::iterator &it) {
    if (s[pos] == '#') {
        int final;
        evitar_etiqueta(s, pos, final);
        string etiqueta = s.substr(pos, final-pos);
        pos = final;
        return it->second.tiene_etiqueta(etiqueta);
    }
    else { //es un paréntesis
        ++pos;
        bool b1 = tratar_expresion(s, pos, it);
        char c = s[pos];
        if (c == '.') {
            ++pos;
            // Optimización para no tratar cuando no hace falta
            if (not b1) {
                if (s[pos] == '#') {
                    int final;
                    evitar_etiqueta(s, pos, final);
                    pos = final;
                }
                else {
                    ++pos;
                    evitar_expresion(s, pos);
                }
                ++pos;
                return b1;
            }
            else {
                bool b2 = tratar_expresion(s, pos, it);
                ++pos;
                return b2;
            }
        }
        else {  // ,
            ++pos;
            // Optimización para no tratar cuando no hace falta
            if (b1) {
                if (s[pos] == '#') {
                    int final;
                    evitar_etiqueta(s, pos, final);
                    pos = final;
                }
                else {
                    ++pos;
                    evitar_expresion(s, pos);
                }
                ++pos;
                return b1;
            }
            else {
                bool b2 = tratar_expresion(s, pos, it);
                ++pos;
                return b2;
            }
        }
    }
}


// Constructoras


Agenda::Agenda() {
    reloj.cambiar_hora("00:00");
    reloj.cambiar_fecha("20.04.15");
    vector< map< Reloj, Tarea>::iterator> menu(0);
}


// Modificadoras

void Agenda::modificar_reloj(const Reloj &reloj_modificado) {
    if (reloj_modificado.cmp(this->reloj) == -1) {
        mensaje_error();
    }
    else {
        reloj = reloj_modificado;
    }
}


void Agenda::modificar_reloj_tarea(int i, const Reloj &reloj_para_tarea) {
    i = i - 1;  // Ya que empiezan las tareas desde la número 1.
    if (i < 0 or i >= menu.size()) mensaje_error();
    else {
        map< Reloj, Tarea>::iterator it;
        it = menu[i];
        // En caso de que se vaya a modificar no se puede ponerle una hora igual al de otra
        // tarea ya existente tampoco
        map< Reloj, Tarea>::const_iterator it_posible_tarea = mapa.find(reloj_para_tarea);
        if (it != mapa.end() and it_posible_tarea == mapa.end()) {
            Tarea tarea;
            tarea = it->second;
            mapa.erase(it);
            mapa.insert(make_pair(reloj_para_tarea, tarea));
            menu[i] = mapa.find(reloj_para_tarea);
        }
        else mensaje_error();
    }
}


void Agenda::opcion_insercion(Comanda &comanda) {
    Tarea tarea;
    Reloj reloj_tarea = reloj;
    tarea.modificar_titulo(comanda.titol());
    reloj_tarea.cambiar_hora(comanda.hora());

    if (comanda.nombre_dates() > 0) {
        reloj_tarea.cambiar_fecha(comanda.data(1));
    }

    if (reloj_valido(reloj_tarea)) {

        map<Reloj, Tarea>::iterator it = mapa.find(reloj_tarea);

        if (it == mapa.end()) {
            // En caso de que se hayan introducido etiquetas se insertan en la tarea.
            int cantidad_etiquetas = comanda.nombre_etiquetes();
            for (int i = 1; i <= cantidad_etiquetas; ++i) {
                tarea.anadir_etiqueta(comanda.etiqueta(i));
            }
            // Se inserta la tarea en el map.
            mapa.insert(make_pair(reloj_tarea, tarea));
        }
        else mensaje_error();
    }
    else mensaje_error();

}


void Agenda::opcion_reloj(Comanda &comanda) {
    if (comanda.nombre_dates() > 0 or comanda.te_hora()) {
        Reloj nuevo_reloj = reloj;
        if (comanda.nombre_dates() == 1) {
            nuevo_reloj.cambiar_fecha(comanda.data(1));
        }
        if (comanda.te_hora()) {
            nuevo_reloj.cambiar_hora(comanda.hora());
        }
        modificar_reloj(nuevo_reloj);
    }
    else {
        reloj.escribir_fecha();
        cout << ' ';
        reloj.escribir_hora();
        cout << endl;
    }

}


void Agenda::opcion_consulta(Comanda &comanda) {
    if (comanda.te_expressio() and comanda.nombre_dates() == 0) {
            menu.clear();
            map< Reloj, Tarea>::iterator it = mapa.find(reloj);

            if (it == mapa.end()) it = mapa.upper_bound(reloj);

            int numero_de_tarea = 1;
            while (it != mapa.end()) {
                int pos = 0;
                if (tratar_expresion(comanda.expressio(), pos, it)) {
                    menu.push_back(it);
                    cout << numero_de_tarea << ' ';
                    escribir_datos_por_orden(it);
                    ++numero_de_tarea;
                }
                ++it;
            }
    }
    else if (comanda.nombre_dates() > 0) {
        string data1 = comanda.data(1);
        string data2;

        if (comanda.nombre_dates() > 1) data2 = comanda.data(2);
        else data2 = data1;


        /* 1r cas: data1 > data2 o (data1 and data2 < data_interna) => no hace nada el programa
         * 2n cas: data1 < data_interna and data2 >= data_interna => Se escriben aquellas tareas entre el presente y data2
         * 3r cas: data1 = data2 => se escribe todas aquellas tareas del mismo día.
         * 4t cas: data1 >= data_interna and data2 >= data1 => Se escribe el intervalo de forma normal.
         * Esto quiere decir que con que trate el 2, 3 y 4 caso ya me va bien. Som-hi!
         */

        if (fecha_cmp_igual_que(data1, data2)) {     // 3r cas
            if (comanda.te_expressio()) {
                menu.clear();
                Reloj reloj_data1, reloj_data2;
                reloj_data1.cambiar_fecha(data1);
                reloj_data1.cambiar_hora("00:00");
                reloj_data2.cambiar_fecha(data2);
                reloj_data2.cambiar_hora("23:59");

                map< Reloj, Tarea>::iterator it;
                if (not reloj_valido(reloj_data1)) {    // Caso en el que toque el mismo día y sea anterior a la hora
                    it = mapa.find(reloj);
                    if (it == mapa.end()) it = mapa.upper_bound(reloj);
                }
                else {
                    it = mapa.find(reloj_data1);
                    if (it == mapa.end()) it = mapa.upper_bound(reloj_data1);
                }
                map< Reloj, Tarea>::iterator it2 = mapa.upper_bound(reloj_data2);


                int numero_de_tarea = 1;
                while (it != it2) {
                    int pos = 0;
                    if (tratar_expresion(comanda.expressio(), pos, it)) {
                        menu.push_back(it);
                        cout << numero_de_tarea << ' ';
                        escribir_datos_por_orden(it);
                        ++numero_de_tarea;
                    }
                    ++it;
                }
            }
            else {
                Reloj reloj_data1, reloj_data2;
                reloj_data1.cambiar_fecha(data1);
                reloj_data1.cambiar_hora("00:00");
                reloj_data2.cambiar_fecha(data2);
                reloj_data2.cambiar_hora("23:59");

                map< Reloj, Tarea>::iterator it;
                if (not reloj_valido(reloj_data1)) {    // Caso en el que toque el mismo día y sea anterior a la hora
                    it = mapa.find(reloj);
                    if (it == mapa.end()) it = mapa.upper_bound(reloj);
                }
                else {
                    it = mapa.find(reloj_data1);
                    if (it == mapa.end()) it = mapa.upper_bound(reloj_data1);
                }
                map< Reloj, Tarea>::iterator it2 = mapa.upper_bound(reloj_data2);

                if (comanda.nombre_etiquetes() > 0)
                    escribir_intervalo_de_tareas_con_etiqueta(it, it2, comanda.etiqueta(1));
                else escribir_intervalo_de_tareas(it, it2);
            }
        }
        else {
            string fecha_reloj_interno = reloj.get_fecha();
            // 2n cas
            if (fecha_cmp_menor_igual_que(data1, fecha_reloj_interno)) {      // Si llega aquí sé que data!=data2

                if (fecha_cmp_menor_igual_que(fecha_reloj_interno, data2)) {

                    if (comanda.te_expressio()) {
                        menu.clear();
                        Reloj reloj_data2;
                        reloj_data2.cambiar_fecha(data2);
                        reloj_data2.cambiar_hora("23:59");

                        map< Reloj, Tarea>::iterator it = mapa.find(reloj);
                        if (it == mapa.end()) it = mapa.upper_bound(reloj);
                        map< Reloj, Tarea>::iterator it2 = mapa.upper_bound(reloj_data2);

                        int numero_de_tarea = 1;
                        while (it != it2) {
                            int pos = 0;
                            if (tratar_expresion(comanda.expressio(), pos, it)) {
                                menu.push_back(it);
                                cout << numero_de_tarea << ' ';
                                escribir_datos_por_orden(it);
                                ++numero_de_tarea;
                            }
                            ++it;
                        }
                    }
                    else {
                        Reloj reloj_data2;
                        reloj_data2.cambiar_fecha(data2);
                        reloj_data2.cambiar_hora("23:59");

                        map< Reloj, Tarea>::iterator it = mapa.find(reloj);
                        if (it == mapa.end()) it = mapa.upper_bound(reloj);
                        map< Reloj, Tarea>::iterator it2 = mapa.upper_bound(reloj_data2);
                        if (comanda.nombre_etiquetes() == 1)

                        escribir_intervalo_de_tareas_con_etiqueta(it, it2, comanda.etiqueta(1));
                        else escribir_intervalo_de_tareas(it, it2);
                    }
                }

            }
            else {
                // data1 > fecha_reloj_interno
                // 4t cas
                if (fecha_cmp_menor_igual_que(data1, data2)) {
                    if (comanda.te_expressio()) {
                        menu.clear();
                        Reloj reloj_data1, reloj_data2;
                        reloj_data1.cambiar_fecha(data1);
                        reloj_data1.cambiar_hora("00:00");
                        reloj_data2.cambiar_fecha(data2);
                        reloj_data2.cambiar_hora("23:59");

                        map< Reloj, Tarea>::iterator it = mapa.find(reloj_data1);
                        if (it == mapa.end()) it = mapa.upper_bound(reloj_data1);
                        map< Reloj, Tarea>::iterator it2 = mapa.upper_bound(reloj_data2);


                        int numero_de_tarea = 1;
                        while (it != it2) {

                            int pos = 0;
                            if (tratar_expresion(comanda.expressio(), pos, it)) {
                                menu.push_back(it);
                                cout << numero_de_tarea << ' ';
                                escribir_datos_por_orden(it);
                                ++numero_de_tarea;
                            }
                            ++it;
                        }
                    }
                    else {
                        menu.clear();
                        Reloj reloj_data1, reloj_data2;
                        reloj_data1.cambiar_fecha(data1);
                        reloj_data1.cambiar_hora("00:00");
                        reloj_data2.cambiar_fecha(data2);
                        reloj_data2.cambiar_hora("23:59");

                        map< Reloj, Tarea>::iterator it = mapa.find(reloj_data1);
                        if (it == mapa.end()) it = mapa.upper_bound(reloj_data1);
                        map< Reloj, Tarea>::iterator it2 = mapa.upper_bound(reloj_data2);

                        if (comanda.nombre_etiquetes() == 1)
                            escribir_intervalo_de_tareas_con_etiqueta(it, it2, comanda.etiqueta(1));
                        else escribir_intervalo_de_tareas(it, it2);

                    }
                }
            }

        }
    }
    else if (comanda.nombre_etiquetes() > 0) { //hay una etiqueta pero ninguna fecha
        consulta_etiqueta(comanda.etiqueta(1));
    }
    else { //todas las tareas futuras
        escribir_tareas_futuras();
    }
}


void Agenda::opcion_modificacion(Comanda &comanda) {

    int numero_tarea = comanda.tasca();

    if (numero_tarea < 1 or numero_tarea > menu.size()) mensaje_error();
    else if (menu[numero_tarea - 1] != mapa.end()) {
        Reloj nuevo_reloj;
        consultar_reloj_tasca_iesima(numero_tarea, nuevo_reloj);
        if (reloj_valido(nuevo_reloj)) {    // para el caso de estar modificando el reloj interno de la agenda y no tratar tareas pasadas

            //cambios de reloj, fecha o ambas
            if (comanda.nombre_dates() > 0 or comanda.te_hora()) {
                Reloj reloj_tarea;
                consultar_reloj_tasca_iesima(numero_tarea, reloj_tarea);
                if (reloj_tarea.cmp(nuevo_reloj) == -1 or
                        reloj_tarea.cmp(nuevo_reloj) == 0) {

                    if (comanda.nombre_dates() > 0) {
                        nuevo_reloj.cambiar_fecha(comanda.data(1));
                    }
                    if (comanda.te_hora()) {
                        nuevo_reloj.cambiar_hora(comanda.hora());
                    }
                    if (reloj_valido(nuevo_reloj)) {    // aquí comparo ya el reloj que tendría la tarea si se modificase por el nuevo valor...
                        int nombre_etiquetes = comanda.nombre_etiquetes();
                        for (int i = 1; i <= nombre_etiquetes; ++i) {
                             insertar_etiqueta_a_tarea_iesima(numero_tarea, comanda.etiqueta(i));
                         }

                         if (comanda.te_titol()) {
                             modificar_titulo_tarea_iesima(numero_tarea, comanda.titol());
                         }

                         // La línea siguiente va al final por cómo se ordena el map, una vez se modifica el reloj se reordena
                         // auto"mágicamente", así que si se pusiese antes podría no estar modificando la tarea que quiero realmente...
                         modificar_reloj_tarea(numero_tarea, nuevo_reloj);
                    }
                    else mensaje_error();
                }
            }
            else {
                int nombre_etiquetes = comanda.nombre_etiquetes();
                for (int i = 1; i <= nombre_etiquetes; ++i) {
                    insertar_etiqueta_a_tarea_iesima(numero_tarea, comanda.etiqueta(i));
                }

                if (comanda.te_titol()) {
                    modificar_titulo_tarea_iesima(numero_tarea, comanda.titol());
                }
            }
        }
        else mensaje_error();
    }
    else mensaje_error();
}


void Agenda::opcion_borrado(Comanda &comanda) {
    int numero_tarea = comanda.tasca();
    string tipo_borrado = comanda.tipus_esborrat();
    if (tipo_borrado == "etiquetes") {
        eliminar_todas_etiquetas_tarea(numero_tarea);
    }
    else if (tipo_borrado == "etiqueta") {
        eliminar_etiqueta_a_tarea_iesima(numero_tarea, comanda.etiqueta(1));
    }
    else { //borrar una tarea
        eliminar_iesima_tarea(numero_tarea);
    }
}


void Agenda::eliminar_iesima_tarea(int i) {
    i = i - 1;
    if (i < 0 or i >= menu.size()) mensaje_error();
    else {
        map< Reloj, Tarea>::iterator it;
        it = menu[i];
        // Compruebo dos cosas, que no haya sido marcado como inválido anteriormente y que tenga la tarea
        // un reloj que no sea del pasado.
        if (it != mapa.end() and reloj_valido(it->first)) mapa.erase(it);
        else mensaje_error();
        // Modifico el elemento para que si se vuelve a tratar sepa que ya no es válido.
        menu[i] = mapa.end();
    }
}


void Agenda::eliminar_etiqueta_a_tarea_iesima(int i, const string &etiqueta) {
    i = i - 1;  // Ya que las tareas empiezan por 1.
    if (i < 0 or i >= menu.size()) mensaje_error();
    else {
        map< Reloj, Tarea>::iterator it;
        it = menu[i];
        if (it != mapa.end()) {
            if (not it->second.tiene_etiqueta(etiqueta) or
                    not reloj_valido(it->first)) mensaje_error();
            else (it->second).borrar_etiqueta(etiqueta);
        }
        else mensaje_error();
    }
}


void Agenda::eliminar_todas_etiquetas_tarea(int i) {
    i = i - 1;  // Ya que las tareas empiezan por 1.
    if (i < 0 or i >= menu.size()) mensaje_error();
    else {
        map< Reloj, Tarea>::iterator it;
        it = menu[i];
        if (reloj_valido(it->first)) (it->second).borrar_todas_las_etiquetas();
        else mensaje_error();
    }
}


void Agenda::modificar_titulo_tarea_iesima(int i, const string &titulo) {
    i = i - 1;  // Ya que las tareas empiezan por 1.
    if (i < 0 or i >= menu.size()) mensaje_error();
    else {
        map< Reloj, Tarea>::iterator it;
        it = menu[i];
        if (it != mapa.end()) {
            (it->second).modificar_titulo(titulo);
        }
    }
}


void Agenda::insertar_etiqueta_a_tarea_iesima(int i, const string &etiqueta) {
    i = i - 1;  // Ya que las tareas empiezan por 1.
    if (i < 0 or i >= menu.size()) mensaje_error();
    else {
        map< Reloj, Tarea>::iterator it;
        it = menu[i];
        // No hay que tirar mensaje de error en el siguiente condicional según el enunciado.
        if (it != mapa.end()) {
            (it->second).anadir_etiqueta(etiqueta);
        }
    }
}


// Consultoras


void Agenda::consultar_reloj_tasca_iesima(int i, Reloj &reloj) const {
    i = i - 1;  // Ya que las tareas empiezan por 1.
    map< Reloj, Tarea>::iterator it;
    it = menu[i];
    reloj = it->first;
}


void Agenda::consulta_etiqueta(string etiqueta) {
    menu.clear();
    map< Reloj, Tarea>::iterator it = mapa.find(reloj);
    if (it == mapa.end()) it = mapa.upper_bound(reloj);
    int numero_de_tarea = 1;
    while (it != mapa.end()) {
        if (it->second.tiene_etiqueta(etiqueta)) {
            menu.push_back(it);
            cout << numero_de_tarea << ' ';
            escribir_datos_por_orden(it);
            ++numero_de_tarea;
        }
        ++it;
    }
}


bool Agenda::reloj_valido(const Reloj &reloj) const {
    int b = this->reloj.cmp(reloj);
    return b == -1 or b == 0;
}


bool Agenda::fecha_cmp_menor_igual_que(const string &fecha1, const string &fecha2) {
    for (int i = 6; i >= 0; i = i - 3) {
        if (fecha1[i] > fecha2[i]) return false;
        else if (fecha1[i] < fecha2[i]) return true;
        else if (fecha1[i + 1] > fecha2[i + 1]) return false;
        else if (fecha1[i + 1] < fecha2[i + 1]) return true;
    }
    return true;
}


bool Agenda::fecha_cmp_igual_que(const string &fecha1, const string &fecha2) {
    for (int i = 6; i >= 0; i = i - 3) {
        if (fecha1[i] > fecha2[i]) return false;
        else if (fecha1[i] < fecha2[i]) return false;
        else if (fecha1[i + 1] > fecha2[i + 1]) return false;
        else if (fecha1[i + 1] < fecha2[i + 1]) return false;
    }
    return true;
}


// Escritura


void Agenda::escribir_tareas_futuras() {
    menu.clear();
    map< Reloj, Tarea>::iterator it = mapa.find(reloj);
    if (it == mapa.end()) it = mapa.upper_bound(reloj);

    int numero_de_tarea = 1;
    while (it != mapa.end()) {
        menu.push_back(it);
        cout << numero_de_tarea << ' ';
        escribir_datos_por_orden(it);
        ++numero_de_tarea;
        ++it;
    }

}


void Agenda::escribir_tareas_pasadas() {
    menu.clear();
    map< Reloj, Tarea>::iterator it;
    map< Reloj, Tarea>::iterator it_parada = mapa.find(reloj);
    if (it_parada == mapa.end()) it_parada = mapa.upper_bound(reloj);
    int numero_de_tarea = 1;
    for (it = mapa.begin();
         it != it_parada; ++it) {
        menu.push_back(it);
        cout << numero_de_tarea << ' ';
        escribir_datos_por_orden(it);
        ++numero_de_tarea;
    }
}


void Agenda::escribir_intervalo_de_tareas(map< Reloj, Tarea>::iterator inicio, map< Reloj, Tarea>::iterator final) {
    menu.clear();   // Limpio el menú...
    int numero_de_tarea = 1;
    while (inicio != final) {
        menu.push_back(inicio);
        cout << numero_de_tarea << ' ';
        escribir_datos_por_orden(inicio);
        ++numero_de_tarea;
        ++inicio;
    }
}


void Agenda::escribir_intervalo_de_tareas_con_etiqueta(map< Reloj, Tarea>::iterator inicio,
                                                       map< Reloj, Tarea>::iterator final, const string &etiqueta) {

    menu.clear();
    int numero_de_tarea = 1;
    while (inicio != final) {
        if (inicio->second.tiene_etiqueta(etiqueta)) {
            menu.push_back(inicio);
            cout << numero_de_tarea << ' ';
            escribir_datos_por_orden(inicio);
            ++numero_de_tarea;
        }
        ++inicio;
    }

}
