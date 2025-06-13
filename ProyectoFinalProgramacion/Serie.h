#pragma once
#include "Video.h"
#include <vector>
#include "Temporada.h"

class Serie : public Video {
private:
    std::vector<Temporada> temporadas;

public:
    Serie() : Video() {}
    Serie(std::string id, std::string name, float time, std::string genero, const std::vector<float>& calificaciones, std::string URL)
        : Video(id, name, time, genero, calificaciones, URL) {
    }

    const std::string mostrar() const override {
        return "Serie: " + name + " (" + genero + "), Duracion promedio: " + std::to_string(time) + " mins, Calificacion: " + std::to_string(SacarPromedio());
    }

    void reproducir() const override {
        std::cout << "Reproduciendo serie: " << name << std::endl;
    }

    void agregarTemporada(const Temporada& temp) {
        temporadas.push_back(temp);
    }

    const std::vector<Temporada>& getTemporadas() const {
        return temporadas;
    }
};