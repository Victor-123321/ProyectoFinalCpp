#pragma once
#include <string>
#include <vector>
#include <ostream>

class Video {
protected:
    std::string id;
    std::string name;
    float time;
    std::string genero;
    std::vector<float> Calificaciones;
    std::string URL;

public:
    Video() : id(""), name(""), time(0.0), genero(""), Calificaciones(), URL("") {}
    Video(std::string id, std::string name, float time, std::string genero, const std::vector<float>& calificaciones, std::string URL)
        : id(id), name(name), time(time), genero(genero), Calificaciones(calificaciones), URL(URL) {
    }

    virtual const std::string mostrar() const = 0;
    virtual void reproducir() const = 0;

    bool AñadirCalificaciones(float calificacion);
    float SacarPromedio() const;
    std::string getName() const { return name; }
    std::string getGenero() const { return genero; }
    std::string getURL() const { return URL; }
    void setGrade(float newGrade) { AñadirCalificaciones(newGrade); }

    friend std::ostream& operator<<(std::ostream& os, const Video& video);
};

inline std::ostream& operator<<(std::ostream& os, const Video& video) {
    os << video.mostrar();
    return os;
}

inline bool Video::AñadirCalificaciones(float calificacion) {
    if (calificacion >= 0.0 && calificacion <= 5.0) {
        Calificaciones.push_back(calificacion);
        return true;
    }
    return false;
}

inline float Video::SacarPromedio() const {
    if (Calificaciones.empty()) {
        return 0.0;
    }
    float suma = 0.0;
    for (float cal : Calificaciones) {
        suma += cal;
    }
    return suma / (float)(Calificaciones.size());
}