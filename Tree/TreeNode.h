//
// Created by azari on 19.10.2021.
//

#ifndef SPLIT_MERGE_SEGMENTATION_TREENODE_H
#define SPLIT_MERGE_SEGMENTATION_TREENODE_H


#include <array>
#include <memory>
#include "../Region/RegionData.h"

namespace {
    constexpr int CHILD_NUMBER = 4; /// we have  here 4-tree,boys
    constexpr double MAX_RGB_DIST = 442; /// upper(sqrt( 255^2 + 255^2 + 255^2))
    constexpr double MIN_RGB_DIST = 0; /// sqrt(0^2 + 0^2 + 0^2)
}

class TreeNode {
private:
    RegionData nodeData;
    std::array<std::unique_ptr<TreeNode>, CHILD_NUMBER> children;

    void split(const QImage &image, int tolerance, int minRegionSize);

    static std::unique_ptr<TreeNode> addNode(const QImage &image, RegionData data, int tolerance, int minRegionSize);

    bool isNodeHomogeneous(const QImage &image, int tolerance, int minRegionSize = 1);

    bool isLeaf();

public:
    void makeTree(const QImage &image, int tolerance, int minRegionSize);

    explicit TreeNode(RegionData data);

    void extractLeavesData(std::vector<RegionData> &regionLeavesData);

    void treeToVector(std::vector<RegionData> &accVector);

    void printTreeData();

};


#endif //SPLIT_MERGE_SEGMENTATION_TREENODE_H
