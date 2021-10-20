//
// Created by azari on 19.10.2021.
//

#include <iostream>
#include "RegionData.h"

RegionData::RegionData(int startX, int startY, int sizeX, int sizeY)
        : startX(startX), startY(startY), sizeX(sizeX), sizeY(sizeY) {}

Color RegionData::getColor(const QImage &image) const {
    auto xStart = this->startX;
    auto yStart = this->startY;
    auto xEnd = xStart + this->sizeX;
    auto yEnd = yStart + this->sizeY;
    int r = 0;
    int g = 0;
    int b = 0;
    int counter = 0;
    Color color{0, 0, 0};
    for (auto x = xStart; x < xEnd; ++x) {
        for (auto y = yStart; y < yEnd; ++y) {
            image.pixelColor(x, y).getRgb(&r, &g, &b);
            color.r += r;
            color.b += b;
            color.g += g;
            ++counter;
        }
    }
    color.r /= counter;
    color.b /= counter;
    color.g /= counter;

    return color;
}

std::ostream &operator<<(std::ostream &out, const RegionData &regionData) {
    std::cout << "start_x: " << regionData.startX << ", ";
    std::cout << "start_y: " << regionData.startY << ", ";
    std::cout << "size_x: " << regionData.sizeX << ", ";
    std::cout << "size_y: " << regionData.sizeY;
    return out;
}


