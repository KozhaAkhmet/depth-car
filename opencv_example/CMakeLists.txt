project( opencv_example )

add_executable( opencv_example opencv_example.cpp )

target_link_libraries( opencv_example ${OpenCV_LIBS} ${TENSORFLOW_LIBRARY_DIR} obj_detection midas CppLinuxSerial::CppLinuxSerial)

#link_libraries(${OpenCV_LIBS})

