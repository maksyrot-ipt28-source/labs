#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include "KeyProcessor.hpp"

class FrameProcessor {
public:
    FrameProcessor();
    cv::Mat process(cv::Mat frame, ProcessMode mode);
private:
    cv::dnn::Net net;
    bool netLoaded;
};
