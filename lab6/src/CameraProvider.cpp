#include "CameraProvider.hpp"
#include <iostream>

CameraProvider::CameraProvider() {
    cap.open("test_video.mp4");
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open video file!" << std::endl;
    }
}

CameraProvider::~CameraProvider() {
    if (cap.isOpened()) {
        cap.release();
    }
}

cv::Mat CameraProvider::getFrame() {
    cv::Mat frame;
    cap >> frame;
    return frame;
}
