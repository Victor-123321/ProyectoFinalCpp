#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include "Pelicula.h"
#include "Serie.h"
#include "Temporada.h"
#include "Capitulo.h"

// Tuve que poner esto porque visual studio se pone tontito
// y quiere hacerle override al numeric_limits<max> con su propia función

// gracias microsoft
#undef max

using namespace std;

// Funcion para limpiar la pantalla
void limpiarPantalla() {
    system("cls"); // Para Windows; usar "clear" en Linux/Mac
}

bool validarEntradaNumerica(int& opcion, int min, int maximo) {
    cin >> opcion;
    if (cin.fail() || opcion < min || opcion > maximo) {
        cin.clear();
        // hacemos que ignoremos todo hasta que no sea salto de linea
        // puro andar ignorando
        // como mi novia
        //
        // tengo sueño
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Por favor, ingrese un numero entre " << min << " y " << maximo << ".\n";
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

bool validarCalificacion(float& calificacion) {
    cin >> calificacion;
    if (cin.fail() || calificacion < 0.0 || calificacion > 5.0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Calificacion invalida. Debe ser numérica y estar entre 0.0 y 5.0.\n";
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

void mostrarMenu() {
    cout << "===== Chafaflix =====\n";
    cout << "1. Cargar archivo de datos\n";
    cout << "2. Mostrar videos por calificacion o genero\n";
    cout << "3. Mostrar episodios de una serie con cierta calificacion\n";
    cout << "4. Mostrar peliculas con cierta calificacion\n";
    cout << "5. Calificar un video\n";
    cout << "6. Wachar un video\n";
    cout << "0. Ya me voy senores, se acabo este baile\n";
    cout << "Seleccione una opcion: ";
}

void cargarArchivo(vector<Video*>& catalogo, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo " << nombreArchivo << ".\n";
        return;
    }

    for (Video* v : catalogo) {
        delete v;
    }
    catalogo.clear();

    string linea;
    string tipo, id, nombre, genero, url, temp, serie, temporada, calificacionesStr;
    float duracion;
    int numTemporada;
    Serie* serieActual = nullptr;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, tipo, ',');

        if (tipo == "Pelicula") {
            getline(ss, id, ',');
            getline(ss, nombre, ',');
            getline(ss, temp, ',');
            duracion = temp.empty() ? 0.0f : stof(temp);
            getline(ss, genero, ',');
            getline(ss, calificacionesStr, ',');
            vector<float> calificaciones;
            if (!calificacionesStr.empty()) {
                stringstream califStream(calificacionesStr);
                string calif;
                while (getline(califStream, calif, ';')) { // Use semicolon to separate ratings
                    try {
                        float rating = stof(calif);
                        if (rating >= 0.0 && rating <= 5.0) {
                            calificaciones.push_back(rating);
                        }
                    }
                    catch (const std::exception& e) {
                        cout << "Error al convertir calificacion: " << calif << endl;
                    }
                }
            }
            getline(ss, url, ',');
            catalogo.push_back(new Pelicula(id, nombre, duracion, genero, calificaciones, url));
            cout << "Cargada Pelicula: " << nombre << endl;
        }
        else if (tipo == "Serie") {
            getline(ss, id, ',');
            getline(ss, nombre, ',');
            getline(ss, temp, ',');
            duracion = temp.empty() ? 0.0f : stof(temp);
            getline(ss, genero, ',');
            getline(ss, calificacionesStr, ',');
            vector<float> calificaciones;
            if (!calificacionesStr.empty()) {
                stringstream califStream(calificacionesStr);
                string calif;
                while (getline(califStream, calif, ';')) {
                    try {
                        float rating = stof(calif);
                        if (rating >= 0.0 && rating <= 5.0) {
                            calificaciones.push_back(rating);
                        }
                    }
                    catch (const std::exception& e) {
                        cout << "Error al convertir calificacion: " << calif << endl;
                    }
                }
            }
            getline(ss, url, ',');
            serieActual = new Serie(id, nombre, duracion, genero, calificaciones, url);
            catalogo.push_back(serieActual);
            cout << "Cargada Serie: " << nombre << endl;
        }
        else if (tipo == "Temporada" && serieActual) {
            getline(ss, id, ',');
            getline(ss, nombre, ',');
            getline(ss, temp, ',');
            try {
                numTemporada = stoi(temp);
            }
            catch (const std::exception& e) {
                cout << "Error al convertir el numero de temporada: " << temp << endl;
                continue;
            }
            getline(ss, genero, ',');
            getline(ss, temp, ',');
            getline(ss, url, ',');
            serieActual->agregarTemporada(Temporada(numTemporada));
            cout << "Cargada Temporada " << numTemporada << " de " << nombre << endl;
        }
        else if (tipo == "Capitulo" && serieActual) {
            getline(ss, serie, ',');
            getline(ss, temporada, ',');
            getline(ss, id, ',');
            getline(ss, nombre, ',');
            getline(ss, temp, ',');
            duracion = temp.empty() ? 0.0f : stof(temp);
            getline(ss, genero, ',');
            getline(ss, calificacionesStr, ',');
            vector<float> calificaciones;
            if (!calificacionesStr.empty()) {
                stringstream califStream(calificacionesStr);
                string calif;
                while (getline(califStream, calif, ';')) {
                    try {
                        float rating = stof(calif);
                        if (rating >= 0.0 && rating <= 5.0) {
                            calificaciones.push_back(rating);
                        }
                    }
                    catch (const std::exception& e) {
                        cout << "Error al convertir calificacion: " << calif << endl;
                    }
                }
            }
            getline(ss, url, ',');
            // Obtener la ultima temporada de la serie actual
            const vector<Temporada>& temporadas = serieActual->getTemporadas();
            if (!temporadas.empty()) {
                Temporada& ultimaTemporada = const_cast<Temporada&>(temporadas.back());
                ultimaTemporada.agregarCapitulo(Capitulo(id, nombre, duracion, genero, calificaciones, url));
                cout << "Cargado Capitulo: " << nombre << " (Temporada " << ultimaTemporada.getNumeroTemporada() << ")" << endl;
            }
            else {
                cout << "Error: No hay temporadas disponibles para agregar el capitulo " << nombre << endl;
            }
        }
        else {
            cout << "Tipo de registro invalido o contexto incorrecto: " << tipo << endl;
            continue;
        }
    }
    archivo.close();
    cout << "Archivo cargado exitosamente.\n";
}

void mostrarVideosPorCriterio(const vector<Video*>& catalogo) {
    int opcion;
    cout << "1. Filtrar por calificacion\n2. Filtrar por genero\nSeleccione una opcion: ";
    if (!validarEntradaNumerica(opcion, 1, 2)) return;

    if (opcion == 1) {
        float calificacion;
        cout << "Ingrese la calificacion minima (0.0 a 5.0): ";
        if (!validarCalificacion(calificacion)) return;
        for (Video* v : catalogo) {
            if (Pelicula* p = dynamic_cast<Pelicula*>(v)) {
                if (p->SacarPromedio() >= calificacion) {
                    cout << *p << endl; // Usar << en lugar de mostrar()
                }
            }
            else if (Serie* s = dynamic_cast<Serie*>(v)) {
                bool mostrarSerie = false;
                // Verificar si la serie o algun capitulo cumple con la calificacion
                if (s->SacarPromedio() >= calificacion) {
                    mostrarSerie = true;
                }
                for (const Temporada& t : s->getTemporadas()) {
                    for (const Capitulo& c : t.getCapitulos()) {
                        if (c.SacarPromedio() >= calificacion) {
                            mostrarSerie = true;
                            break;
                        }
                    }
                }
                if (mostrarSerie) {
                    cout << "Serie: " << s->getName() << endl;
                    for (const Temporada& t : s->getTemporadas()) {
                        cout << "  Temporada " << t.getNumeroTemporada() << ":\n";
                        for (const Capitulo& c : t.getCapitulos()) {
                            if (c.SacarPromedio() >= calificacion) {
                                cout << "    - " << c << ", Calificacion: " << c.SacarPromedio() << endl; // Usar << para Capitulo
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        string genero;
        cout << "Ingrese el genaro: ";
        getline(cin, genero);
        for (Video* v : catalogo) {
            if (Pelicula* p = dynamic_cast<Pelicula*>(v)) {
                if (p->getGenero() == genero) {
                    cout << *p << endl; // AQUI ESTA LA SOBRECARGA
                }
            }
            else if (Serie* s = dynamic_cast<Serie*>(v)) {
                bool mostrarSerie = false;
                if (s->getGenero() == genero) {
                    mostrarSerie = true;
                }
                for (const Temporada& t : s->getTemporadas()) {
                    for (const Capitulo& c : t.getCapitulos()) {
                        if (c.getGenero() == genero) {
                            mostrarSerie = true;
                            break;
                        }
                    }
                }
                if (mostrarSerie) {
                    cout << "Serie: " << s->getName() << endl;
                    for (const Temporada& t : s->getTemporadas()) {
                        cout << "  Temporada " << t.getNumeroTemporada() << ":\n";
                        for (const Capitulo& c : t.getCapitulos()) {
                            if (c.getGenero() == genero) {
                                cout << "    - " << c << ", Calificacion: " << c.SacarPromedio() << endl; // Usar << para Capitulo
                            }
                        }
                    }
                }
            }
        }
    }
}

void mostrarEpisodiosSerie(const vector<Video*>& catalogo) {
    cout << "Series disponibles:\n";
    for (size_t i = 0; i < catalogo.size(); ++i) {
        if (dynamic_cast<Serie*>(catalogo[i])) {
            cout << i << ") " << catalogo[i]->getName() << endl;
        }
    }
    cout << "Seleccione el indice de la serie: ";
    int indice;
    if (!validarEntradaNumerica(indice, 0, catalogo.size() - 1)) return;

    Serie* serie = dynamic_cast<Serie*>(catalogo[indice]);
    if (!serie) {
        cout << "Indice no corresponde a una serie.\n";
        return;
    }

    float calificacion;
    cout << "Ingrese la calificacion minima (0.0 a 5.0): ";
    if (!validarCalificacion(calificacion)) return;

    cout << "Serie: " << serie->getName() << endl; // Mostrar nombre de la serie
    for (const Temporada& t : serie->getTemporadas()) {
        cout << "  Temporada " << t.getNumeroTemporada() << ":\n";
        for (const Capitulo& c : t.getCapitulos()) {
            if (c.SacarPromedio() >= calificacion) {
                cout << "    - " << c << ", Calificacion: " << c.SacarPromedio() << endl; // Usar << para Capitulo
            }
        }
    }
}

void mostrarPeliculasCalificacion(const vector<Video*>& catalogo) {
    float calificacion;
    cout << "Ingrese la calificacion minima (0.0 a 5.0): ";
    if (!validarCalificacion(calificacion)) return;

    for (Video* v : catalogo) {
        if (Pelicula* p = dynamic_cast<Pelicula*>(v)) {
            if (p->SacarPromedio() >= calificacion) {
                cout << *p << endl; // wuuu sobrecarga 
            }
        }
    }
}

// Calificar video
void calificarVideo(vector<Video*>& catalogo) {
    cout << "Videos disponibles:\n";
    for (size_t i = 0; i < catalogo.size(); ++i) {
        cout << i << ") " << catalogo[i]->getName() << endl;
    }
    cout << "Seleccione el indice del video a calificar: ";
    int indice;
    if (!validarEntradaNumerica(indice, 0, catalogo.size() - 1)) return;

    float calificacion;
    cout << "Ingrese la nueva calificacion (0.0 a 5.0): ";
    if (!validarCalificacion(calificacion)) return;

    catalogo[indice]->setGrade(calificacion);
    cout << "Video calificado exitosamente.\n";
}

int main() {
    vector<Video*> catalogo;
    int opcion = 1;

    while (opcion != 0) {
        mostrarMenu();
        if (!validarEntradaNumerica(opcion, 0, 6)) continue;

        limpiarPantalla();

        switch (opcion) {
        case 1:
        {
            cout << "Ingrese el nombre del archivo (ej. videos.csv): ";
            string nombreArchivo;
            getline(cin, nombreArchivo);
            cargarArchivo(catalogo, nombreArchivo);
            break;
        }

        case 2:
            mostrarVideosPorCriterio(catalogo);
            break;

        case 3:
            mostrarEpisodiosSerie(catalogo);
            break;

        case 4:
            mostrarPeliculasCalificacion(catalogo);
            break;

        case 5:
            calificarVideo(catalogo);
            break;

        case 6:
        {
            cout << "Videos disponibles:\n";
            for (size_t i = 0; i < catalogo.size(); ++i) {
                cout << i << ") " << catalogo[i]->getName() << endl;
            }
            cout << "Seleccione el indice del video a reproducir: ";
            int indice;
            if (!validarEntradaNumerica(indice, 0, catalogo.size() - 1)) break;

            Pelicula* pelicula = dynamic_cast<Pelicula*>(catalogo[indice]);
            if (pelicula) {
                pelicula->reproducir();
                break;
            }

            Serie* serie = dynamic_cast<Serie*>(catalogo[indice]);
            if (serie) {
                cout << "Es una serie. Seleccione temporada y capitulo:\n";
                auto& temporadas = serie->getTemporadas();
                for (size_t i = 0; i < temporadas.size(); ++i) {
                    cout << "  Temporada " << temporadas[i].getNumeroTemporada() << " (" << i << ")\n";
                }
                cout << "Temporada: ";
                int tIndex;
                if (!validarEntradaNumerica(tIndex, 0, temporadas.size() - 1)) break;

                const auto& capitulos = temporadas[tIndex].getCapitulos();
                for (size_t j = 0; j < capitulos.size(); ++j) {
                    cout << "    Capitulo " << j << ": " << capitulos[j].getName() << endl;
                }
                cout << "Capitulo: ";
                int cIndex;
                if (!validarEntradaNumerica(cIndex, 0, capitulos.size() - 1)) break;

                capitulos[cIndex].reproducir();
                break;
            }

            cout << "Tipo de video no reconocido.\n";
            break;
        }

        case 0:
            cout << "Saliendo del sistema...\n";
            break;

        default:
            cout << "Opcion no valida.\n";
            break;
        }
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        limpiarPantalla();
    }

    // Liberar memoria
    for (Video* v : catalogo) {
        delete v;
    }

    return 0;
}