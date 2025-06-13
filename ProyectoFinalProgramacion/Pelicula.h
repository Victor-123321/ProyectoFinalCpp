#pragma once
#include "Video.h"
#include <windows.h>
#include <shellapi.h>

class Pelicula : public Video
{
public:
    Pelicula() : Video() {}

    Pelicula(std::string id, std::string name, float time, std::string genero, float grade, std::string URL)
        : Video(id, name, time, genero, grade, URL) {
    }

    const std::string mostrar() const override {
        return "Pelicula: " + name + " (" + genero + "), Duraci�n: " + std::to_string(time) + " mins, Calificaci�n: " + std::to_string(grade);
    }

    void reproducir() {
        // Reemplazar por la url de la pelicula en netflix
        ShellExecute(0, 0, L"http://www.google.com", 0, 0, SW_SHOW);
    }

};

