//
// Created by azari on 19.10.2021.
//

#include "util.h"

double rgbDistance(const QImage &image, const std::pair<int, int> &pos1, const std::pair<int, int> &pos2) {
    auto color1 = image.pixelColor(pos1.first, pos1.second);
    auto color2 = image.pixelColor(pos2.first, pos2.second);
    int r1, g1, b1;
    int r2, g2, b2;
    color1.getRgb(&r1, &g1, &b1);
    color2.getRgb(&r2, &g2, &b2);
    return sqrt(pow(r1 - r2, 2) + pow(g1 - g2, 2) + pow(b1 - b2, 2));
}

double rgbDistance(const Color &color1, const Color &color2) {
    return sqrt(pow(color1.r - color2.r, 2) + pow(color1.g - color2.g, 2) + pow(color1.b - color2.b, 2));


}

double rgbDistanceFromZeros(const QImage &image, const std::pair<int, int> &pos1) {
    auto color1 = image.pixelColor(pos1.first, pos1.second);
    int r1, g1, b1;
    color1.getRgb(&r1, &g1, &b1);
    return sqrt(pow(r1, 2) + pow(g1, 2) + pow(b1, 2));
}

double rgbDistanceFromZeros(const Color &color) {
    return sqrt(pow(color.r, 2) + pow(color.g, 2) + pow(color.b, 2));
}