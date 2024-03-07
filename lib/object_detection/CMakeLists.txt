add_library(obj_detection obj_detection.h obj_detection.cpp)

target_link_libraries(obj_detection
${OpenCV_LIBS}
)

target_include_directories(obj_detection PUBLIC "${OpenCV_INCLUDE_DIRS}" "${CMAKE_CURRENT_SOURCE_DIR}")