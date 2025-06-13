#pragma once
#include "Video.h"
#include <windows.h>
#include <shellapi.h>

class Capitulo : public Video {
public:
    Capitulo() : Video() {}

    Capitulo(std::string id, std::string name, float time, std::string genero, float grade, std::string URL)
        : Video(id, name, time, genero, grade, URL) {
    }

    const std::string mostrar() const override {
        return "Capitulo: " + name + ", Duración: " + std::to_string(time) + " mins";
    }

    void reproducir() {
        ShellExecute(0, 0, std::wstring(URL.begin(), URL.end()).c_str(), 0, 0, SW_SHOW);
    }
};
