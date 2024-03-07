#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "tensorflow/lite/error_reporter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "midas.h"

MidasDepthEstimator::MidasDepthEstimator() : input_height(0),
                                             input_width(0),
                                             input_channels(0),
                                             output_height(0),
                                             output_width(0)
{
}

void MidasDepthEstimator::initializeModel(const char *model_path, size_t thread_num)
{
    tflite::ops::builtin::BuiltinOpResolver op_resolver;
    tflite::ErrorReporter *error_reporter = nullptr; // Initialize the error reporter

    std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile(model_path, error_reporter);

    if (!model)
    {
        // Handle the case where the model couldn't be loaded
        std::cerr << "Error: Model file not found or could not be loaded." << std::endl;
        return;
    }

    tflite::InterpreterBuilder interpreter_builder(*model, op_resolver);
    interpreter = std::make_unique<tflite::Interpreter>();
    interpreter_builder(&interpreter);
    interpreter->SetNumThreads(thread_num);
    interpreter->AllocateTensors();

    getModelInputDetails();
    getModelOutputDetails();
}

void MidasDepthEstimator::getModelInputDetails()
{
    const auto input_indices = interpreter->inputs();
    const auto input_tensor = interpreter->tensor(input_indices[0]);
    const auto input_dims = input_tensor->dims;
    input_height = input_dims->data[1];
    input_width = input_dims->data[2];
    input_channels = input_dims->data[3];
}

void MidasDepthEstimator::getModelOutputDetails()
{
    const auto output_indices = interpreter->outputs();
    const auto output_tensor = interpreter->tensor(output_indices[0]);
    const auto output_dims = output_tensor->dims;
    output_height = output_dims->data[1];
    output_width = output_dims->data[2];
}

void MidasDepthEstimator::prepareInputForInference(cv::Mat &img)
{
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    cv::resize(img, img, cv::Size(input_width, input_height), 0, 0, cv::INTER_CUBIC);
    img.convertTo(img, CV_32FC3);

    cv::Mat mean_image(cv::Size(input_width, input_height), CV_32FC3, cv::Scalar(0.485, 0.456, 0.406));
    cv::Mat std_image(cv::Size(input_width, input_height), CV_32FC3, cv::Scalar(0.229, 0.224, 0.225));

    img = (img / 255.0 - mean_image) / std_image;

    std::memcpy(interpreter->typed_input_tensor<float>(0), img.ptr<float>(0), input_height * input_width * 3 * sizeof(float));
}

cv::Mat MidasDepthEstimator::estimateDepth(cv::Mat image)
{
    prepareInputForInference(image);

    interpreter->Invoke();

    cv::Mat raw_disparity(output_height, output_width, CV_32F, interpreter->typed_output_tensor<float>(0));

    cv::normalize(raw_disparity, raw_disparity, 0, 255, cv::NORM_MINMAX, CV_8U);
    cv::applyColorMap(raw_disparity, raw_disparity, cv::COLORMAP_MAGMA);

    return raw_disparity;
}