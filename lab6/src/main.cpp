#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Display.hpp"
#include <iostream>

int main() {
    CameraProvider camera;
    KeyProcessor keyProcessor;
    FrameProcessor frameProcessor;
    Display display("Lab 6 - OpenCV Video Processor");

    ProcessMode currentMode = ProcessMode::ORIGINAL;

    std::cout << "Controls:\n";
    std::cout << " 'o' - Original\n 'i' - Invert\n 'b' - Blur\n 'c' - Canny Edge\n 's' - Sobel\n 'q' or ESC - Quit\n";

    while (true) {
        cv::Mat frame = camera.getFrame();
        if (frame.empty()) {
            std::cerr << "Empty frame grabbed!" << std::endl;
            break;
        }

        cv::Mat processedFrame = frameProcessor.process(frame, currentMode);
        display.show(processedFrame);

        // Чекаємо 30 мілісекунд (це дає ~30 FPS). Якщо натиснута клавіша, обробляємо її.
        int key = cv::waitKey(30);
        if (key != -1) {
            currentMode = keyProcessor.handleKey(key, currentMode);
            if (currentMode == ProcessMode::QUIT) {
                break;
            }
        }
    }
    return 0;
}
