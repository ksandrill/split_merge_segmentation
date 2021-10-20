//
// Created by azari on 20.10.2021.
//

#include <QImage>
#include <iostream>
#include "splitMergeSegmentation.h"
#include "Tree/TreeNode.h"
#include "Region/Region.h"
#include <memory>
#include <map>
#include <random>

Color getGroupColor(const std::vector<Region> &regionGroup) {
    auto regionsCount = int(regionGroup.size());
    auto color = Color(0, 0, 0);
    for (const auto &region: regionGroup) {
        color += region.getColor();
    }
    color /= regionsCount;
    return color;
}

QImage segmentation(const QImage &inputImage, const std::map<int, std::vector<Region>> &groupsMap) {
    auto outputImage = inputImage.copy();
    for (const auto &[group_id, regionGroup]: groupsMap) {
        auto groupColor = getGroupColor(regionGroup);
        for (const auto &region: regionGroup) {
            auto[startX, startY, sizeX, sizeY] = region.extractRegionData();
            auto endX = startX + sizeX;
            auto endY = startY + sizeY;
            for (auto x = startX; x < endX; ++x) {
                for (auto y = startY; y < endY; ++y) {
                    outputImage.setPixelColor(x, y, QColor(groupColor.r, groupColor.g, groupColor.b).rgb());
                }
            }
        }
    }
    return outputImage;
}

QImage RandomColorSegmentation(const QImage &inputImage, const std::map<int, std::vector<Region>> &groupsMap) {
    auto outputImage = inputImage.copy();
    std::random_device rd;
    std::mt19937 mersenne(rd());
    for (const auto &[group_id, regionGroup]: groupsMap) {
        auto r = int(mersenne() % 256);
        auto g = int(mersenne() % 256);
        auto b = int(mersenne() % 256);
        auto groupColor = Color(r, g, b);
        for (const auto &region: regionGroup) {
            auto[startX, startY, sizeX, sizeY] = region.extractRegionData();
            auto endX = startX + sizeX;
            auto endY = startY + sizeY;
            for (auto x = startX; x < endX; ++x) {
                for (auto y = startY; y < endY; ++y) {
                    outputImage.setPixelColor(x, y, QColor(groupColor.r, groupColor.g, groupColor.b).rgb());
                }
            }
        }
    }
    return outputImage;
}


void mergeRegions(std::vector<Region> &regionVector, double simDiff, int maxIter) {
    auto regionsCount = regionVector.size();
    bool isMerged;
    int counter = 0;
    do {
        if (counter % 10 == 0) {
            std::cout << "merge iter: " << counter << std::endl;
        }
        counter += 1;
        isMerged = false;
        for (auto i = 0; i < regionsCount; ++i) {
            for (auto j = 0; j < regionsCount; ++j) {
                if (regionVector[i].isSimilarRegion(regionVector[j], simDiff) and
                    regionVector[i].isNeighborRegion(regionVector[j])) {
                    regionVector[j].setGroupId(regionVector[i].getGroupId());
                    isMerged = true;
                }

            }
        }
    } while (isMerged and counter != maxIter);

}

std::vector<Region> getRegionVector(const QImage &inputImage, const std::vector<RegionData> &leavesDataVector) {
    auto leavesCount = leavesDataVector.size();
    auto regionVector = std::vector<Region>();
    for (auto i = 0; i < leavesCount; ++i) {
        regionVector.emplace_back(Region(leavesDataVector[i], leavesDataVector[i].getColor(inputImage), i));
    }
    return regionVector;
}


QImage splitMergeSeg::ImgSplitMergeSeg(const QImage &inputImage, int tolerance, int minRegSize, double simDiff,
                                       int maxIter,
                                       bool randomGroupColors) {
    auto quadTree = std::make_unique<TreeNode>(RegionData(0, 0, inputImage.width(), inputImage.height()));
    quadTree->makeTree(inputImage, tolerance, minRegSize);
    std::cout << "tree created" << std::endl;
    auto leavesDataVector = std::vector<RegionData>();
    quadTree->extractLeavesData(leavesDataVector);
    auto regionVector = getRegionVector(inputImage, leavesDataVector);
    std::cout << "regions created" << std::endl;
    std::cout << "regions number: " << regionVector.size() << std::endl;
    mergeRegions(regionVector, simDiff, maxIter);
    std::cout << "regions merged" << std::endl;
    auto groupsMap = std::map<int, std::vector<Region>>();
    for (auto region: regionVector) {
        groupsMap[region.getGroupId()].emplace_back(region);
    }
    auto outputImage = randomGroupColors ? RandomColorSegmentation(inputImage, groupsMap) : segmentation(inputImage,
                                                                                                         groupsMap);
    return outputImage;


}


QImage splitMergeSeg::imgSplitSeg(const QImage &inputImage, int tolerance, int minRegSize) {
    auto quadTree = std::make_unique<TreeNode>(RegionData(0, 0, inputImage.width(), inputImage.height()));
    quadTree->makeTree(inputImage, tolerance, minRegSize);
    std::cout << "tree created" << std::endl;
    auto leavesDataVector = std::vector<RegionData>();
    quadTree->extractLeavesData(leavesDataVector);
    auto regionVector = getRegionVector(inputImage, leavesDataVector);
    std::cout << "regions created" << std::endl;
    std::cout << "regions number: " << regionVector.size() << std::endl;
    auto outputImage = inputImage.copy();
    for (const auto &region: regionVector) {
        auto[startX, startY, sizeX, sizeY] = region.extractRegionData();
        auto color = region.getColor();
        auto endX = startX + sizeX;
        auto endY = startY + sizeY;
        for (auto x = startX; x < endX; ++x) {
            for (auto y = startY; y < endY; ++y) {
                outputImage.setPixelColor(x, y, QColor(color.r, color.g, color.b).rgb());
            }
        }
    }
    return outputImage;
}
