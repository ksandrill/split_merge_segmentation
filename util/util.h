//
// Created by azari on 19.10.2021.
//

#ifndef SPLIT_MERGE_SEGMENTATION_UTIL_H
#define SPLIT_MERGE_SEGMENTATION_UTIL_H

#include <QImage>
#include "../Region/Color.h"

double rgbDistance(const QImage &image, const std::pair<int, int> &pos1, const std::pair<int, int> &pos2);

double rgbDistance(const Color &color1, const Color &color2);


double rgbDistanceFromZeros(const QImage &image, const std::pair<int, int> &pos1);

double rgbDistanceFromZeros(const Color &color);

#endif //SPLIT_MERGE_SEGMENTATION_UTIL_H
