cmake_minimum_required(VERSION 2.8)
project( midas_cpp_car_example )

find_package( OpenCV REQUIRED )
find_package( CppLinuxSerial REQUIRED)

set(TENSORFLOW_LIBRARY_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/tensorflow_src/bazel-bin/tensorflow/lite/libtensorflowlite.so" )
set(TENSORFLOW_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/tensorflow_include")
set(FLATBUFFERS_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/flatbuffers_include")

include_directories( ${OpenCV_INCLUDE_DIRS} ${TENSORFLOW_INCLUDE_DIR} ${FLATBUFFERS_INCLUDE_DIR})

add_subdirectory(lib/midas_cpp)
add_subdirectory(lib/object_detection)
add_subdirectory(opencv_example)

link_libraries(${OpenCV_LIBS})

