//
// Created by azari on 20.10.2021.
//

#ifndef SPLIT_MERGE_SEGMENTATION_SPLITMERGESEGMENTATION_H
#define SPLIT_MERGE_SEGMENTATION_SPLITMERGESEGMENTATION_H
namespace splitMergeSeg {
    QImage ImgSplitMergeSeg(const QImage &inputImage, int tolerance, int minRegSize, double simDiff, int maxIter,
                            bool randomGroupColors);

    QImage imgSplitSeg(const QImage &inputImage, int tolerance, int minRegSize);
}

#endif //SPLIT_MERGE_SEGMENTATION_SPLITMERGESEGMENTATION_H
