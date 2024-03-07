#include "opencv2/opencv.hpp"

#pragma once

enum class DETECTION_POS {
    RIGHT,
    LEFT,
    NONE
};

DETECTION_POS object_detection(const cv::Mat& img, int threshold_value, int max_value, int box_width);