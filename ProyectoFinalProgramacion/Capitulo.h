#pragma once
#include "Video.h"

class Capitulo : public Video {
public:
    Capitulo() : Video() {}

    Capitulo(std::string id, std::string name, float time, std::string genero, float grade, std::string URL)
        : Video(id, name, time, genero, grade, URL) {
    }

    const std::string mostrar() const override {
        return "Capitulo: " + name + ", Duración: " + std::to_string(time) + " mins";
    }
};

