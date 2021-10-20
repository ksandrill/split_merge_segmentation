//
// Created by azari on 19.10.2021.
//

#ifndef SPLIT_MERGE_SEGMENTATION_REGION_H
#define SPLIT_MERGE_SEGMENTATION_REGION_H


#include "RegionData.h"
#include "Color.h"

class Region {
private:
    RegionData regionData;
    Color color;
    int groupId;



public:
    Region(RegionData data, Color color, int groupId);

    friend std::ostream &operator<<(std::ostream &out, const Region &region);


    void setGroupId(int groupId);

    [[nodiscard]] const RegionData &getRegionData() const;

    void setRegionData(const RegionData &regionData);

    [[nodiscard]] const Color &getColor() const;

    void setColor(const Color &color);

    [[nodiscard]] int getGroupId() const;

    [[nodiscard]] bool isSimilarRegion(const Region &otherRegion, double similarityDiff) const;

    [[nodiscard]] bool isNeighborRegion(const Region &otherRegion) const;

    [[nodiscard]] std::tuple<int, int, int, int> extractRegionData() const;
    bool isEmbedded(const RegionData &otherData) const;

};


#endif //SPLIT_MERGE_SEGMENTATION_REGION_H
