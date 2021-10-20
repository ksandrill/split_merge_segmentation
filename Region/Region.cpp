//
// Created by azari on 19.10.2021.
//

#include <iostream>
#include "Region.h"
#include "../util/util.h"

Region::Region(RegionData data, Color color, int groupId) : regionData(data), color(color), groupId(groupId) {}

std::ostream &operator<<(std::ostream &out, const Region &region) {
    out << "region: {" << std::endl;
    out << "group_id: " << region.groupId << std::endl;
    out << "region_data:" << std::endl;
    out << region.regionData << std::endl;
    out << "region_color:" << std::endl;
    out << region.color << std::endl << "}";
    return out;
}

bool Region::isNeighborRegion(const Region &otherRegion) const {
    if (this->groupId == otherRegion.groupId) {
        return false;
    }
    if (this->isEmbedded(otherRegion.regionData) or otherRegion.isEmbedded(this->regionData)) {
//        std::cout << "ready to merge" << std::endl;
//        std::cout << otherRegion << std::endl;
//        std::cout << *this << std::endl;
//
        return true;
    }

    return false;
}


std::tuple<int, int, int, int> Region::extractRegionData() const {
    return {this->regionData.startX, this->regionData.startY, this->regionData.sizeX, this->regionData.sizeY};
}

bool Region::isSimilarRegion(const Region &otherRegion, double similarityDiff) const {
    return rgbDistance(this->color, otherRegion.color) < similarityDiff;
}

void Region::setGroupId(int groupId) {
    Region::groupId = groupId;
}

int Region::getGroupId() const {
    return groupId;
}

const RegionData &Region::getRegionData() const {
    return regionData;
}

void Region::setRegionData(const RegionData &regionData) {
    Region::regionData = regionData;
}

const Color &Region::getColor() const {
    return color;
}

void Region::setColor(const Color &color) {
    Region::color = color;
}

bool Region::isEmbedded(const RegionData &otherData) const {
    ////suppose that otherRegion >= then  thisRegion
    auto[xStartThis, yStartThis, xSizeThis, ySizeThis] = this->extractRegionData();
    auto xEndThis = xStartThis + xSizeThis;
    auto yEndThis = yStartThis + ySizeThis;
    auto xStartOther = otherData.startX;
    auto yStartOther = otherData.startY;
    auto xSizeOther = otherData.sizeX;
    auto ySizeOther = otherData.sizeY;
    auto xEndOther = xStartOther + xSizeOther;
    auto yEndOther = yStartOther + ySizeOther;
    auto isEmbedded = false;
    if (yEndThis == yStartOther or yStartThis == yEndOther) { /// top touch or bottom touch included diagonal regions
        if (xEndThis >= xStartOther and xStartThis <= xEndOther) {
            isEmbedded = true;
        }
    }
    if (xEndThis == xStartOther or xStartThis == xEndOther) { ///left touch or right touch excluded diagonal regions
        if (yStartThis >= yStartOther and yEndThis <= yEndOther) {
            isEmbedded = true;
        }
    }


    return isEmbedded;
}







