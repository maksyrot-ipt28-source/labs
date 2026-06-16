#include "FrameProcessor.hpp"
#include <iostream>

FrameProcessor::FrameProcessor() {
    try {
        net = cv::dnn::readNetFromCaffe("deploy.prototxt", "res10_300x300_ssd_iter_140000.caffemodel");
        netLoaded = !net.empty();
    } catch (...) {
        netLoaded = false;
    }
}

cv::Mat FrameProcessor::process(cv::Mat frame, ProcessMode mode) {
    cv::Mat result = frame.clone();
    if (mode == ProcessMode::FACE && netLoaded) {
        cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300), cv::Scalar(104.0, 177.0, 123.0));
        net.setInput(blob);
        cv::Mat detections = net.forward();
        cv::Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());
        for(int i = 0; i < detectionMat.rows; i++) {
            float confidence = detectionMat.at<float>(i, 2);
            if(confidence > 0.5) {
                int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
                int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
                int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
                int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
                cv::rectangle(result, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);
            }
        }
    } else if (mode == ProcessMode::INVERT) {
        cv::bitwise_not(frame, result);
    }
    return result;
}
