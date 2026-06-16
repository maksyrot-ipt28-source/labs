#include "KeyProcessor.hpp"

ProcessMode KeyProcessor::handleKey(int key, ProcessMode currentMode) {
    switch (key) {
        case 'o': return ProcessMode::ORIGINAL;
        case 'i': return ProcessMode::INVERT;
        case 'b': return ProcessMode::BLUR;
        case 'c': return ProcessMode::CANNY;
        case 's': return ProcessMode::SOBEL;
        case 27:
        case 'q': return ProcessMode::QUIT;
        default:  return currentMode;
    }
}
