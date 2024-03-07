
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "tensorflow/lite/interpreter.h"

#pragma once

class MidasDepthEstimator
{
private:
    std::unique_ptr<tflite::Interpreter> interpreter;
    int input_height;
    int input_width;
    int input_channels;
    int output_height;
    int output_width;
    cv::Mat normalized_disparity;

    void getModelInputDetails();
    void getModelOutputDetails();
    void prepareInputForInference(cv::Mat &image);

public:
    MidasDepthEstimator();
    void initializeModel(const char *model_path, size_t thread_num = 1);
    cv::Mat estimateDepth(cv::Mat image);
};