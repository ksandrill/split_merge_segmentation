//
// Created by azari on 19.10.2021.
//

#ifndef SPLIT_MERGE_SEGMENTATION_REGIONDATA_H
#define SPLIT_MERGE_SEGMENTATION_REGIONDATA_H


#include <QImage>
#include "Color.h"

class RegionData {
public:
    int startX;
    int startY;
    int sizeX;
    int sizeY;
    RegionData(int startX, int startY, int sizeX, int sizeY);
    friend std::ostream &operator<<(std::ostream &out, const RegionData &regionData);
    RegionData() = default;
    Color getColor(const QImage &image) const;
};


#endif //SPLIT_MERGE_SEGMENTATION_REGIONDATA_H
