#include "CameraProvider.hpp"
#include "FrameProcessor.hpp"
#include "KeyProcessor.hpp"
#include "Display.hpp"

int main() {
    CameraProvider cam;
    Display disp;
    FrameProcessor proc;
    KeyProcessor keys;
    ProcessMode mode = ProcessMode::ORIGINAL;

    while (mode != ProcessMode::QUIT) {
        cv::Mat frame = cam.getFrame();
        if (frame.empty()) break;

        frame = proc.process(frame, mode);
        disp.show(frame);

        mode = keys.handleKey(cv::waitKey(1), mode);
    }
    return 0;
}
