cmake_minimum_required(VERSION 3.10)
project(cv_app)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(include)

# Список всіх файлів, які ми створили
add_executable(cv_app 
    src/main.cpp 
    src/CameraProvider.cpp 
    src/FrameProcessor.cpp 
    src/KeyProcessor.cpp 
    src/Display.cpp
)

target_link_libraries(cv_app ${OpenCV_LIBS})
