#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include "Pelicula.h"
#include "Serie.h"
#include "Temporada.h"
#include "Capitulo.h"

using namespace std;

// Función para limpiar la pantalla
void limpiarPantalla() {
    system("cls"); // Para Windows; usar "clear" en Linux/Mac
}

// Función para validar entrada numérica
bool validarEntradaNumerica(int& opcion, int min, int max) {
    cin >> opcion;
    if (cin.fail() || opcion < min || opcion > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Por favor, ingrese un número entre " << min << " y " << max << ".\n";
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

// Función para validar entrada de calificación
bool validarCalificacion(float& calificacion) {
    cin >> calificacion;
    if (cin.fail() || calificacion < 0.0 || calificacion > 5.0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Calificación inválida. Debe estar entre 0.0 y 5.0.\n";
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

// Función para mostrar el menú
void mostrarMenu() {
    cout << "===== SERVICIO DE STREAMING =====\n";
    cout << "1. Cargar archivo de datos\n";
    cout << "2. Mostrar videos por calificación o género\n";
    cout << "3. Mostrar episodios de una serie con cierta calificación\n";
    cout << "4. Mostrar películas con cierta calificación\n";
    cout << "5. Calificar un video\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opción: ";
}

// Función para cargar datos desde un archivo CSV
void cargarArchivo(vector<Video*>& catalogo, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo " << nombreArchivo << ".\n";
        return;
    }

    // Limpiar catálogo existente
    for (Video* v : catalogo) {
        delete v;
    }
    catalogo.clear();

    string linea;
    Serie* serieActual = nullptr;
    Temporada* temporadaActual = nullptr;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string tipo, id, nombre, genero, url, temp;
        float duracion, calificacion;
        int numTemporada;

        getline(ss, tipo, ',');
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, temp, ',');
        duracion = stof(temp);
        getline(ss, genero, ',');
        getline(ss, temp, ',');
        calificacion = stof(temp);
        getline(ss, url, ',');

        if (tipo == "Pelicula") {
            catalogo.push_back(new Pelicula(id, nombre, duracion, genero, calificacion, url));
        }
        else if (tipo == "Serie") {
            serieActual = new Serie(id, nombre, duracion, genero, calificacion, url);
            catalogo.push_back(serieActual);
        }
        else if (tipo == "Temporada" && serieActual) {
            numTemporada = stoi(nombre); // El campo 'nombre' contiene el número de temporada
            temporadaActual = new Temporada(numTemporada);
            serieActual->agregarTemporada(*temporadaActual);
        }
        else if (tipo == "Capitulo" && temporadaActual) {
            temporadaActual->agregarCapitulo(Capitulo(id, nombre, duracion, genero, calificacion, url));
        }
    }
    archivo.close();
    cout << "Archivo cargado exitosamente.\n";
}

// Función para mostrar videos por calificación o género
void mostrarVideosPorCriterio(const vector<Video*>& catalogo) {
    int opcion;
    cout << "1. Filtrar por calificación\n2. Filtrar por género\nSeleccione una opción: ";
    if (!validarEntradaNumerica(opcion, 1, 2)) return;

    if (opcion == 1) {
        float calificacion;
        cout << "Ingrese la calificación mínima (0.0 a 5.0): ";
        if (!validarCalificacion(calificacion)) return;
        for (Video* v : catalogo) {
            if (v->getGrade() >= calificacion) {
                cout << v->mostrar() << endl;
            }
        }
    }
    else {
        string genero;
        cout << "Ingrese el género: ";
        getline(cin, genero);
        for (Video* v : catalogo) {
            if (v->getGenero() == genero) {
                cout << v->mostrar() << endl;
            }
        }
    }
}

// Función para mostrar episodios de una serie con cierta calificación
void mostrarEpisodiosSerie(const vector<Video*>& catalogo) {
    cout << "Series disponibles:\n";
    for (size_t i = 0; i < catalogo.size(); ++i) {
        if (dynamic_cast<Serie*>(catalogo[i])) {
            cout << i << ") " << catalogo[i]->getName() << endl;
        }
    }
    cout << "Seleccione el índice de la serie: ";
    int indice;
    if (!validarEntradaNumerica(indice, 0, catalogo.size() - 1)) return;

    Serie* serie = dynamic_cast<Serie*>(catalogo[indice]);
    if (!serie) {
        cout << "Índice no corresponde a una serie.\n";
        return;
    }

    float calificacion;
    cout << "Ingrese la calificación mínima (0.0 a 5.0): ";
    if (!validarCalificacion(calificacion)) return;

    cout << serie->mostrar();
    // Filtrar episodios por calificación
    // Nota: Necesitaríamos acceso a los capítulos, lo cual requiere modificar Serie.h para exponer temporadas
}

// Función para mostrar películas con cierta calificación
void mostrarPeliculasCalificacion(const vector<Video*>& catalogo) {
    float calificacion;
    cout << "Ingrese la calificación mínima (0.0 a 5.0): ";
    if (!validarCalificacion(calificacion)) return;

    for (Video* v : catalogo) {
        if (Pelicula* p = dynamic_cast<Pelicula*>(v)) {
            if (p->getGrade() >= calificacion) {
                cout << p->mostrar() << endl;
            }
        }
    }
}

// Función para calificar un video
void calificarVideo(vector<Video*>& catalogo) {
    cout << "Videos disponibles:\n";
    for (size_t i = 0; i < catalogo.size(); ++i) {
        cout << i << ") " << catalogo[i]->getName() << endl;
    }
    cout << "Seleccione el índice del video a calificar: ";
    int indice;
    if (!validarEntradaNumerica(indice, 0, catalogo.size() - 1)) return;

    float calificacion;
    cout << "Ingrese la nueva calificación (0.0 a 5.0): ";
    if (!validarCalificacion(calificacion)) return;

    catalogo[indice]->setGrade(calificacion);
    cout << "Video calificado exitosamente.\n";
}

int main() {
    vector<Video*> catalogo;
    int opcion = 0;

    while (opcion != 0) {
        mostrarMenu();
        if (!validarEntradaNumerica(opcion, 0, 5)) continue;

        limpiarPantalla();

        switch (opcion) {
        case 1:
            cout << "Ingrese el nombre del archivo (ej. videos.csv): ";
            string nombreArchivo;
            getline(cin, nombreArchivo);
            cargarArchivo(catalogo, nombreArchivo);
            break;

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

        case 0:
            cout << "Saliendo del sistema...\n";
            break;

        default:
            cout << "Opción no válida.\n";
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
