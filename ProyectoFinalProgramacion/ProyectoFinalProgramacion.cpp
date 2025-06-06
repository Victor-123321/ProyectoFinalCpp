#include <iostream>
#include <vector>
#include <limits>
#include "Pelicula.h"
#include "Serie.h"
#include "Temporada.h"
#include "Capitulo.h"

using namespace std;

void limpiarPantalla() {
    cout << "\n\n";
}

void mostrarMenu() {
    cout << "===== SERVICIO DE STREAMING =====\n";
    cout << "1. Ver todas las peliculas\n";
    cout << "2. Ver todas las series\n";
    cout << "3. Ver episodios de una serie\n";
    cout << "4. Ver los videos mejor calificados\n";
    cout << "5. Ver los videos peor calificados\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opcion: ";
}

void submenuVideo(Video* video) {
    int opcion = 0;
    while (opcion != 3) {
        cout << "\nAcciones para: " << video->getName() << "\n";
        cout << "1. Ver informacion\n";
        cout << "2. Reproducir\n";
        cout << "3. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            cout << video->mostrar() << "\n";
            break;
        case 2:
            cout << "Reproduciendo: " << video->getName() << "...\n";
            break;
        case 3:
            return;
        default:
            cout << "Opcion invalida.\n";
            break;
        }
    }
}

int main() {
    vector<Video*> catalogo;

    // Peliculas
    catalogo.push_back(new Pelicula("P001", "Matrix", 120.0, "Accion", 4.8, "url1"));
    catalogo.push_back(new Pelicula("P002", "Soul", 95.0, "Drama", 4.1, "url2"));
    catalogo.push_back(new Pelicula("P003", "Morbius", 105.0, "Accion", 2.3, "url3"));

    // Serie
    Serie* breakingBad = new Serie("S001", "Breaking Bad", 0.0, "Drama", 4.9, "url4");

    Temporada t1(1);
    t1.agregarCapitulo(Capitulo("C001", "Piloto", 58.0, "Drama", 4.7, "url5"));
    t1.agregarCapitulo(Capitulo("C002", "Cats in the Bag...", 48.0, "Drama", 4.5, "url6"));

    Temporada t2(2);
    t2.agregarCapitulo(Capitulo("C003", "Seven Thirty-Seven", 47.0, "Drama", 4.9, "url7"));

    breakingBad->agregarTemporada(t1);
    breakingBad->agregarTemporada(t2);

    catalogo.push_back(breakingBad);

    int opcion = 0;
    while (opcion != 6) {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        limpiarPantalla();

        switch (opcion) {
        case 1:
            cout << "==== PELICULAS ====" << endl;
            for (size_t i = 0; i < catalogo.size(); ++i) {
                if (dynamic_cast<Pelicula*>(catalogo[i])) {
                    cout << i << ") " << catalogo[i]->getName() << endl;
                }
            }
            cout << "Seleccione el indice de la pelicula (o -1 para volver): ";
            int idxP;
            cin >> idxP;
            if (idxP >= 0 && idxP < catalogo.size() && dynamic_cast<Pelicula*>(catalogo[idxP])) {
                submenuVideo(catalogo[idxP]);
            }
            break;

        case 2:
            cout << "==== SERIES ====" << endl;
            for (size_t i = 0; i < catalogo.size(); ++i) {
                if (dynamic_cast<Serie*>(catalogo[i])) {
                    cout << i << ") " << catalogo[i]->getName() << endl;
                }
            }
            cout << "Seleccione el indice de la serie (o -1 para volver): ";
            int idxS;
            cin >> idxS;
            if (idxS >= 0 && idxS < catalogo.size() && dynamic_cast<Serie*>(catalogo[idxS])) {
                submenuVideo(catalogo[idxS]);
            }
            break;

        case 3:
            cout << "==== EPISODIOS DE SERIE ====" << endl;
            for (size_t i = 0; i < catalogo.size(); ++i) {
                if (dynamic_cast<Serie*>(catalogo[i])) {
                    cout << i << ") " << catalogo[i]->getName() << endl;
                }
            }
            cout << "Seleccione el indice de la serie: ";
            int indice;
            cin >> indice;
            if (indice >= 0 && indice < catalogo.size()) {
                Serie* s = dynamic_cast<Serie*>(catalogo[indice]);
                if (s) {
                    cout << s->mostrar();
                }
                else {
                    cout << "Indice no corresponde a una serie.\n";
                }
            }
            else {
                cout << "Indice fuera de rango.\n";
            }
            break;

        case 4:
            cout << "==== VIDEOS MEJOR CALIFICADOS (> 4.5) ====" << endl;
            for (Video* v : catalogo) {
                if (v->getGrade() >= 4.5) {
                    cout << v->getName() << endl;
                }
            }
            break;

        case 5:
            cout << "==== VIDEOS PEOR CALIFICADOS (< 3.0) ====" << endl;
            for (Video* v : catalogo) {
                if (v->getGrade() < 3.0) {
                    cout << v->getName() << endl;
                }
            }
            break;

        case 6:
            cout << "Saliendo del sistema..." << endl;
            break;

        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
            break;
        }
        cout << "\nPresione ENTER para continuar...";
        cin.ignore();
        cin.get();
        limpiarPantalla();
    }

    // Liberar memoria
    for (Video* v : catalogo) {
        delete v;
    }

    return 0;
}
