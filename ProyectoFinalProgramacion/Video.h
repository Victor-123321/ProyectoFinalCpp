#pragma once
#include <string>

class Video {
protected:
    std::string id;
    std::string name;
    float time;
    std::string genero;
    float grade;
    std::string URL;

public:
    Video() : id(""), name(""), time(0.0), genero(""), grade(0.0), URL("") {}
    Video(std::string id, std::string name, float time, std::string genero, float grade, std::string URL)
        : id(id), name(name), time(time), genero(genero), grade(grade), URL(URL) {}

    virtual const std::string mostrar() const = 0; // Metodo virtual puro para polimorfismo
    virtual void reproducir() = 0; // Metodo virtual puro para reproduccion

    float getGrade() const { return grade; }
    std::string getName() const { return name; }
    std::string getGenero() const { return genero; }
    void setGrade(float newGrade) { grade = newGrade; }
};
