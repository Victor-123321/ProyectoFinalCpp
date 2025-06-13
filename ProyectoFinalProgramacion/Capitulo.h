#pragma once
#include "Video.h"
#include <tchar.h>
#include <windows.h>
#include <shellapi.h>

class Capitulo : public Video {
public:
    Capitulo() : Video() {}

    Capitulo(std::string id, std::string name, float time, std::string genero, float grade, std::string URL)
        : Video(id, name, time, genero, grade, URL) {
    }

    const std::string mostrar() const override {
        return "Capitulo: " + name + ", Duracion: " + std::to_string(time) + " mins";
    }

    void reproducir() {
        // Reemplazar por la url de la pelicula en netflix
        ShellExecute(0, 0, _T("http://www.google.com"), 0, 0, SW_SHOW);
        // ShellExecute(0, 0, std::wstring(URL.begin(), URL.end()).c_str(), 0, 0, SW_SHOW);
        //Este es el codigo anterior que cambie (Genarinh0) checa eso victor
    }
};
