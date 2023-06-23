# PCA Example

This repository contains an example of Principal Component Analysis (PCA) implemented in C++ using the Eigen library.

## Environment Setup

Make sure you have CMake and Python 3 installed on your system before following the steps below.

## Compilation and Execution

1. Open a Linux terminal.

2. Navigate to the root directory of the project.

3. Run the following command to configure the project with CMake:

   ```shell
   cmake CMakeLists.txt
   ```
   
4. Next, compile the pca_test.cpp program by providing the number of points to generate (N) as an argument. For example, to generate 100 points, execute the following command:
   ```./cmake_eigen 100
   ```
   This will compile the source code and generate a text file pca_data.txt that contains the matrix of points and the eigenvector calculated using PCA.
5. To visualize the plot with the point cloud and the eigenvector, run the following command:
   ```python3 pca_example.py
   ```
   This will open a window displaying the graphical representation of the points and the eigenvector in a 3D space.



## Contributions  
Feel free to adapt and modify the content of the `README.md` file according to your needs, adding more details about the project and providing any other relevant information.

