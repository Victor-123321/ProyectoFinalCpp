#pragma once
#include "Video.h"
#include "Temporada.h"
#include <vector>
class Serie : public Video {
private:
    std::vector<Temporada> temporadas;

public:
    Serie() : Video() {}

    Serie(std::string id, std::string name, float time, std::string genero, float grade, std::string URL)
        : Video(id, name, time, genero, grade, URL) {
    }

    void agregarTemporada(const Temporada& temporada) {
        temporadas.push_back(temporada);
    }

    const std::string mostrar() const override {
        std::string info = "Serie: " + name + "\n";
        for (const auto& temporada : temporadas) {
            info += "  Temporada " + std::to_string(temporada.getNumeroTemporada()) + ":\n";
            for (const auto& capitulo : temporada.getCapitulos()) {
                info += "    - " + capitulo.mostrar() + "\n";
            }
        }
        return info;
    }

    std::string getName() {
        return name;
    }

};

