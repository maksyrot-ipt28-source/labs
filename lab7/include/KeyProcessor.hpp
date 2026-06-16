#pragma once
enum class ProcessMode { ORIGINAL, INVERT, BLUR, CANNY, SOBEL, FACE, QUIT };
class KeyProcessor {
public:
    ProcessMode handleKey(int key, ProcessMode currentMode);
};
