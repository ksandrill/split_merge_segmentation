//
// Created by azari on 19.10.2021.
//

#ifndef SPLIT_MERGE_SEGMENTATION_COLOR_H
#define SPLIT_MERGE_SEGMENTATION_COLOR_H


class Color {
public:
    int r;
    int g;
    int b;

    Color(int r, int g, int b);

    friend std::ostream &operator<<(std::ostream &out, const Color &color);

    Color &operator+=(const Color &other);

    Color &operator/=(int val);


};


#endif //SPLIT_MERGE_SEGMENTATION_COLOR_H
