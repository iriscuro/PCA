cmake_minimum_required(VERSION 3.12)
project("PCA_example")

set(CMAKE_CXX_STANDARD 11)

# Encuentra la librer�a Eigen
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})

# Agrega los archivos fuente
add_executable(pca_test src/pca_test.cpp src/pca.h)

# Enlaza la librer�a Eigen
target_link_libraries(pca_test Eigen3::Eigen)