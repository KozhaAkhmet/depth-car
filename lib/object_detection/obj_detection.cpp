#include "obj_detection.h"

DETECTION_POS object_detection(const cv::Mat& img, int threshold_value, int max_value, int box_width) {
    cv::Mat grayscaleImage;
    cv::resize(img, grayscaleImage, cv::Size(120, 120), 0, 0, cv::INTER_CUBIC);

    cv::cvtColor(grayscaleImage, grayscaleImage, cv::COLOR_BGR2GRAY);

    cv::threshold(grayscaleImage, grayscaleImage, threshold_value, max_value,
                  cv::THRESH_BINARY);

    int height = (grayscaleImage.cols) / 2;                // Height of the rectangle
    int begining = (grayscaleImage.cols - box_width) / 2;  // x-coordinate of the top-left corner of the rectangle

    // Create a rectangle (ROI) using the specified parameters
    cv::Rect leftRec(begining, 0, box_width / 2, height);
    cv::Rect rightRec(begining + box_width / 2, 0, box_width / 2, height);

    cv::rectangle(grayscaleImage, leftRec, cv::Scalar(255), 1);
    cv::rectangle(grayscaleImage, rightRec, cv::Scalar(255), 1);

    // Crop the image using the ROI
    cv::Mat leftArea = grayscaleImage(leftRec);
    cv::Mat rightArea = grayscaleImage(rightRec);

    cv::imshow("Blobs", grayscaleImage);

    int leftAreaValue = cv::countNonZero(leftArea);
    int rightAreaValue = cv::countNonZero(rightArea);

    if (rightAreaValue > leftAreaValue) {
        std::cout << "right" << std::endl;
        return DETECTION_POS::RIGHT;
    } else if (rightAreaValue < leftAreaValue) {
        std::cout << "left" << std::endl;
        return DETECTION_POS::LEFT;
    } else {
        std::cout << "None" << std::endl;
        return DETECTION_POS::NONE;
    }
}