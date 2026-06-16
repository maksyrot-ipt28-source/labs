#include "FrameProcessor.hpp"

cv::Mat FrameProcessor::process(cv::Mat frame, ProcessMode mode) {
    cv::Mat result;
    switch (mode) {
        case ProcessMode::ORIGINAL:
            result = frame.clone();
            break;
        case ProcessMode::INVERT:
            cv::bitwise_not(frame, result);
            break;
        case ProcessMode::BLUR:
            cv::GaussianBlur(frame, result, cv::Size(15, 15), 0);
            break;
        case ProcessMode::CANNY:
            cv::cvtColor(frame, result, cv::COLOR_BGR2GRAY);
            cv::Canny(result, result, 50, 150);
            break;
        case ProcessMode::SOBEL:
            cv::cvtColor(frame, result, cv::COLOR_BGR2GRAY);
            cv::Sobel(result, result, CV_16S, 1, 0, 3);
            cv::convertScaleAbs(result, result);
            break;
        default:
            result = frame.clone();
            break;
    }
    return result;
}
