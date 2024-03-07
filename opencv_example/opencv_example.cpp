#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include <CppLinuxSerial/SerialPort.hpp>
#include "opencv2/imgproc.hpp"

#include "midas.h"
#include "obj_detection.h"

using namespace mn::CppLinuxSerial;

template <typename R>
bool is_ready(std::future<R> const& f) { return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready; }

//Senging the json format data to Arduino via serial port.
void send_to_port(mn::CppLinuxSerial::SerialPort& serPort, const DETECTION_POS& pos) {
    std::string data;

    if (pos == DETECTION_POS::LEFT) {
        // Turn Right
        data = "{\"direction\":\"d\",\"speed\":120}";
        serPort.Write(data);
    } else if (pos == DETECTION_POS::RIGHT) {
        // Turn Left
        data = "{\"direction\":\"a\",\"speed\":120}";
        serPort.Write(data);
    } else if (pos == DETECTION_POS::NONE) {
        // Stop
        data = "{\"direction\":\"p\",\"speed\":120}";
        serPort.Write(data);
    }
}

int main() {
    const char* model_path = "models/midasModel.tflite";
    MidasDepthEstimator depth;

    depth.initializeModel(model_path, 4);

    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 256);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 256);

    cap.set(cv::CAP_PROP_FPS, 5);
    cap.set(cv::CAP_PROP_BUFFERSIZE, 2);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the camera." << std::endl;
        return -1;
    }

    SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_9600);
    serialPort.SetTimeout(100);
    serialPort.Open();
    
    // Being sure that we give enough time to estailish connection with Arduino via serial port
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    cv::Mat frame;
    cv::Mat depth_img;

    // The thresh holds for counting pixels from binary image. depthThreshold is the "layer" from the depth image which become binary (white and black) image.
    int depthThreshold = 120.0;
    int max = 1000;

    auto boundFunction = std::bind(&MidasDepthEstimator::estimateDepth, &depth, std::placeholders::_1);
    bool fut_status = true;
    std::future<cv::Mat> fut;

    while (true) {
        cap >> frame;
        cv::rotate(frame, frame, cv::ROTATE_90_CLOCKWISE);
	      // cv::imshow("Real Image", frame);
        if (fut_status) {
            // Running the camera capture asynchronously
            fut = std::async(std::launch::async, boundFunction, std::ref(frame));
            fut_status = false;
        }
        if (is_ready(fut)) {
            
            // Getting the future ( Camera capture).
            fut_status = true;
            depth_img = fut.get();

            // Calculating the position
            DETECTION_POS pos = object_detection(depth_img, depthThreshold, max, 120);
            
            //Sending the results to the Arduino
            send_to_port(serialPort,pos);

            cv::imshow("Depth Image", depth_img);
        }

        if (cv::waitKey(1) == 'q') {
            serialPort.Close();
            cap.release();
            break;
        }
    }
    serialPort.Close();
    cap.release();

    return 0;
}