//Compilar en linux: g++ -std=c++11 -I /usr/include/eigen3 pca_test.cpp -o pca_test

#include <iostream>
#include <fstream>
#include <random>
#include "pca.h"

#include <experimental/filesystem>

using namespace std;
namespace fs = std::experimental::filesystem;

// Función para generar una matriz con puntos aleatorios distribuidos en forma de mariposa
Eigen::MatrixXf generarFigura(int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 2 * M_PI);

    Eigen::MatrixXf figura(n, 3);
    for (int i = 0; i < n; ++i)
    {
        float x = static_cast<float>(i - n / 2);
        float theta1 = dis(gen);
        float theta2 = dis(gen);
        float y = x * std::sin(theta1);
        float z = x * std::sin(theta2);

        figura(i, 0) = x;
        figura(i, 1) = y;
        figura(i, 2) = z;
    }

    return figura;
}




int main(int argc, char* argv[])
{
    
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << "(matrix size) m x 3 e.g. 10 x 3" << std::endl;
        return EXIT_FAILURE;
    }
    
    int m = std::stoi(argv[1]);
    
    // Generar puntos aleatorios en pca_data_matrix
    Eigen::MatrixXf pca_data_matrix = generarFigura(m);
    /*
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-5.0, 5.0);

    Eigen::Matrix<float, Eigen::Dynamic, 3> pca_data_matrix(m, 3);
    for (int i = 0; i < pca_data_matrix.rows(); ++i)
    {
        for (int j = 0; j < pca_data_matrix.cols(); ++j)
        {
            pca_data_matrix(i, j) = dis(gen);
        }
    }
    */
    // Guardar la matriz en un archivo de texto
    std::ofstream outfile("pca_data.txt");
    if (outfile.is_open())
    {
        outfile << "Puntos:\n";
        for (int i = 0; i < pca_data_matrix.rows(); ++i)
        {
            for (int j = 0; j < pca_data_matrix.cols(); ++j)
            {
                outfile << pca_data_matrix(i, j) << " ";
            }
            outfile << std::endl;
        }

        pca_t<float> pca;
        pca.set_input(pca_data_matrix);
        pca.compute();

        Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> eigen_vectors = pca.get_eigen_vectors();
        Eigen::Matrix<float, Eigen::Dynamic, 1> first_eigenvector = eigen_vectors.col(0);

        // Escribir el primer eigenvector en el archivo
        outfile << "Vector Director:\n";
        for (int i = 0; i < first_eigenvector.rows(); ++i)
        {
            outfile << first_eigenvector(i) << " ";
        }
        outfile << std::endl;

        outfile.close();
        std::cout << "Matriz y Vector Director guardados en pca_data.txt" << std::endl;
    }
    else
    {
        std::cerr << "No se pudo abrir el archivo pca_data.txt" << std::endl;
        return EXIT_FAILURE;
    }

    // Realizar el cálculo de PCA
    pca_t<float> pca;
    pca.set_input(pca_data_matrix);
    pca.compute();

    std::cout
        << "Input Matrix:      \n" << pca.get_input_matrix() << std::endl << std::endl
        << "Centered Matrix:   \n" << pca.get_centered_matrix() << std::endl << std::endl
        << "Covariance Matrix: \n" << pca.get_covariance_matrix() << std::endl << std::endl
        << "Projection Matrix: \n" << pca.get_projection_matrix() << std::endl << std::endl
        << "Mean Matrix:       \n" << pca.get_mean() << std::endl << std::endl
        << "Eigen Values:      \n" << pca.get_eigen_values() << std::endl << std::endl
        << "Eigen Vectors:     \n" << pca.get_eigen_vectors() << std::endl << std::endl;

    const auto& reprojection = pca.reprojection();
    auto error = (pca_data_matrix - reprojection).norm();


    std::cout
        << "Reprojected Matrix:\n" << reprojection << std::endl << std::endl
        << std::fixed
        << "Error:             \n" << error << std::endl << std::endl;

    return EXIT_SUCCESS;
}

