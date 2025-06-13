#pragma once
#include "Video.h"
#include <tchar.h>
#include <windows.h>
#include <shellapi.h>

class Pelicula : public Video {
public:
    Pelicula() : Video() {}

    Pelicula(std::string id, std::string name, float time, std::string genero, const std::vector<float>& calificaciones, std::string URL)
        : Video(id, name, time, genero, calificaciones, URL) {
    }

    const std::string mostrar() const override {
        return "Pelicula: " + name + " (" + genero + "), Duracion: " + std::to_string(time) + " mins, Calificacion: " + std::to_string(SacarPromedio());
    }

    void reproducir() const override {
        size_t convertedChars = 0;
        wchar_t wURL[MAX_PATH];
        mbstowcs_s(&convertedChars, wURL, getURL().c_str(), getURL().length() + 1);
        HINSTANCE result = ShellExecute(0, L"open", wURL, 0, 0, SW_SHOW);
        if ((intptr_t)result <= 32) {
            std::cerr << "Error al reproducir el video: " << getURL() << ", Código: " << (intptr_t)result << std::endl;
        }
    }
};