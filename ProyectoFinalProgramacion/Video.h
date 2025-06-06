#include <string>
#pragma once
class Video
{
protected:
    std::string id;
    std::string name;
    float time;
    std::string genero;
    float grade;
    std::string URL;
public:
    Video() : id(""), name(""), time(0.0), genero(""), grade(0.0), URL("") {}
    Video(std::string id, std::string name, float time, std::string genero, float grade, std::string URL) : id(id), name(name), time(time), genero(genero), grade(grade), URL(URL) {}

    virtual const std::string mostrar() const = 0;

    float getGrade() {
        return grade;
    }

    std::string getName() {
        return name;
    }

};

