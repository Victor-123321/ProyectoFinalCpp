#pragma once
#include <vector>
#include "Capitulo.h"

class Temporada {
private:
    int numeroTemporada;
    std::vector<Capitulo> capitulos;

public:
    Temporada() : numeroTemporada(0) {}

    Temporada(int numero) : numeroTemporada(numero) {}

    void agregarCapitulo(const Capitulo& cap) {
        capitulos.push_back(cap);
    }

    int getNumeroTemporada() const {
        return numeroTemporada;
    }

    const std::vector<Capitulo>& getCapitulos() const {
        return capitulos;
    }
};

