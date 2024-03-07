add_library(midas midas.h midas.cpp)

target_link_libraries(midas
    ${TENSORFLOW_LIBRARY_DIR}
)
target_include_directories(midas PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${TENSORFLOW_INCLUDE_DIR}")