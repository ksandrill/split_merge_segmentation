//
// Created by azari on 19.10.2021.
//

#include <iostream>
#include "Color.h"

Color::Color(int r, int g, int b) : r(r), g(g), b(b) {

}

std::ostream &operator<<(std::ostream &out, const Color &color) {
    out << "r: " << color.r << ", ";
    out << "g: " << color.g << ", ";
    out << "b: " << color.b;
    return out;
}

Color &Color::operator/=(int val) {
    this->r /= val;
    this->g /= val;
    this->b /= val;
    return *this;
}

Color &Color::operator+=(const Color &other) {
    this->r += other.r;
    this->g += other.g;
    this->b += other.b;
    return *this;
}



