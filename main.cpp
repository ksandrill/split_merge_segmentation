#include <QApplication>
#include <QLabel>
#include "splitMergeSegmentation.h"

namespace {
    constexpr int TOLERANCE = 90;  ////diff between min rgb distance (Euclidean) and max  from zero at region for Homogeneous criterion
    constexpr int MIN_REGION_SIZE = 6;/// min region size for what we would check Homogeneous criterion
    constexpr double SIM_DIF = 20;
    constexpr int MAX_ITER = 200;
    constexpr bool IS_RANDOM_COLOR = false;
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto label = std::make_unique<QLabel>();
    auto img = QImage("../pictures/Lenna.png");
    img = img.convertToFormat(QImage::Format_RGB32);
    img = splitMergeSeg::ImgSplitMergeSeg(img, TOLERANCE, MIN_REGION_SIZE, SIM_DIF, MAX_ITER, IS_RANDOM_COLOR);
    label->setPixmap(QPixmap::fromImage(img));

    label->show();
    return QApplication::exec();
}
