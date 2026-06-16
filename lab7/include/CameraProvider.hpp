#pragma once
#include <opencv2/opencv.hpp>

class CameraProvider {
public:
    CameraProvider();
    ~CameraProvider();
    cv::Mat getFrame();
private:
    cv::VideoCapture cap;
};
