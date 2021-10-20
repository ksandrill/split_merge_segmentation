//
// Created by azari on 19.10.2021.
//

#include <QImage>
#include <iostream>
#include "TreeNode.h"
#include "../util/util.h"


void TreeNode::split(const QImage &image, int tolerance, int minRegionSize) {
    auto curNodeData = this->nodeData;
    auto halfXSize = curNodeData.sizeX / 2;
    auto halfYSize = curNodeData.sizeY / 2;
    auto xOffsetSize = halfXSize + curNodeData.sizeX % 2; // cuz halfSize can be trunced by integer division
    auto yOffsetSize = halfYSize + curNodeData.sizeY % 2;
    auto xOffsetStart = curNodeData.startX + halfXSize;
    auto yOffsetStart = curNodeData.startY + halfYSize;
    auto childrenData = std::array<RegionData, CHILD_NUMBER>{
            RegionData(curNodeData.startX, curNodeData.startY, halfXSize, halfYSize),/// top left
            RegionData(xOffsetStart, curNodeData.startY, xOffsetSize, halfYSize), /// top right
            RegionData(curNodeData.startX, yOffsetStart, halfXSize, yOffsetSize),///bottom left
            RegionData(xOffsetStart, yOffsetStart, xOffsetSize,
                       yOffsetSize)}; /// bottom right
//    for (auto i = 0; i < 4; ++i) {
//        std::cout << childrenData[i] << std::endl;
//    }
    for (auto i = 0; i < CHILD_NUMBER; ++i) {
        children[i] = addNode(image, childrenData[i], tolerance, minRegionSize);
    }


}

std::unique_ptr<TreeNode> TreeNode::addNode(const QImage &image, RegionData data, int tolerance, int minRegionSize) {
    ////static int node_counter = 0;
    ////std::cout << "add node" << std::endl;
    ///node_counter += 1;
    ///std::cout << "node counter:" << node_counter << std::endl;
    auto newNode = std::make_unique<TreeNode>(data);
    if (not newNode->isNodeHomogeneous(image, tolerance, minRegionSize)) {
        newNode->split(image, tolerance, minRegionSize);
    }
    return newNode;

}

bool TreeNode::isNodeHomogeneous(const QImage &image, int tolerance, int minRegionSize) {
    auto data = this->nodeData;
    auto startX = data.startX;
    auto startY = data.startY;
    auto xSize = data.sizeX;
    auto ySize = data.sizeY;
    if (xSize < minRegionSize or ySize < minRegionSize) {
        return true; /// limit of splitting
    }
    auto xEnd = startX + xSize;
    auto yEnd = startY + ySize;
    double minDist = MAX_RGB_DIST;
    double maxDist = MIN_RGB_DIST;
    for (auto x = startX; x < xEnd; ++x) {
        for (auto y = startY; y < yEnd; ++y) {
            auto curDist = rgbDistanceFromZeros(image, {x, y});
            minDist = std::min(minDist, curDist);
            maxDist = std::max(maxDist, curDist);
        }
    }
    return (maxDist - minDist) < tolerance;
}


TreeNode::TreeNode(RegionData data) : nodeData(data) {}

void TreeNode::makeTree(const QImage &image, int tolerance, int minRegionSize) {
    split(image, tolerance, minRegionSize);
}


void TreeNode::printTreeData() {
    std::cout << this->nodeData << std::endl;
    std::cout << "is leaf?" << this->isLeaf() << std::endl;
    for (const auto &i: this->children) {
        if (i != nullptr) {
            i->printTreeData();
        }
    }

}


void TreeNode::extractLeavesData(std::vector<RegionData> &regionLeavesData) {
    if (this->isLeaf()) {
        regionLeavesData.emplace_back(this->nodeData);
    }
    for (const auto &i: this->children) {
        if (i != nullptr) {
            i->extractLeavesData(regionLeavesData);
        }
    }


}

bool TreeNode::isLeaf() {
    bool isLeaf = true;
    for (const auto &i: this->children) {
        if (i != nullptr) {
            isLeaf = false;
        }
    }
    return isLeaf;
}

void TreeNode::treeToVector(std::vector<RegionData> &accVector) {
    accVector.emplace_back(this->nodeData);
    for (const auto &i: this->children) {
        if (i != nullptr) {
            i->treeToVector(accVector);
        }
    }


}
















