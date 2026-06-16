#pragma once
#include <opencv2/opencv.hpp>
#include "KeyProcessor.hpp"

class FrameProcessor {
public:
    cv::Mat process(cv::Mat frame, ProcessMode mode);
};
