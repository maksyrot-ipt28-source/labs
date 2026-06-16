#include "CameraProvider.hpp"
#include <iostream>

CameraProvider::CameraProvider() {
    // Відкриваємо відеофайл замість вебкамери
    cap.open("test_video.mp4");
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file!" << std::endl;
    }
}

CameraProvider::~CameraProvider() {
    cap.release();
}

cv::Mat CameraProvider::getFrame() {
    cv::Mat frame;
    cap >> frame;
    // Якщо відео закінчилось, перекручуємо його на початок (loop)
    if (frame.empty()) {
        cap.set(cv::CAP_PROP_POS_FRAMES, 0);
        cap >> frame;
    }
    return frame;
}
