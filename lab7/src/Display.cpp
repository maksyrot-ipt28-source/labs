#include "Display.hpp"

void Display::show(cv::Mat frame) {
    cv::imshow("Lab 7 - Face Detection", frame);
}
