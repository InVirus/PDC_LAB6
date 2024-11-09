#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "..//PDC_LAB_6/source.cpp" // Включіть заголовок вашого файлу з кодом

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphTests
{
    TEST_CLASS(GraphTests)
    {
    public:
        TEST_METHOD(TestLoadGraphValid)
        {
            int n, m;
            int** edges = nullptr;
            std::string filename = "test_input.txt";

            // Створіть тестовий файл input.txt з коректними даними
            std::ofstream outFile(filename);
            outFile << "4 5\n1 2\n2 3\n3 4\n4 1\n2 4\n";
            outFile.close();

            // Викликаємо функцію зчитування графа
            loadGraph(filename, n, m, edges);

            // Перевіряємо, що кількість вершин та рядів елементів у масиві коректні
            Assert::AreEqual(n, 4);
            Assert::AreEqual(m, 5);
            Assert::IsNotNull(edges);  // Перевірка, що масив елементів не є пустим

            // Перевіряємо правильність першого ребра
            Assert::AreEqual(edges[0][0], 1);
            Assert::AreEqual(edges[0][1], 2);

            // Звільняємо пам'ять
            for (int i = 0; i < m; ++i) {
                delete[] edges[i];
            }
            delete[] edges;
        }

        TEST_METHOD(TestLoadGraphInvalid)
        {
            int n, m;
            int** edges = nullptr;
            std::string filename = "invalid_input.txt";

            // Створюємо некоректний тестовий файл
            std::ofstream outFile(filename);
            outFile << "4 -5\n1 2\n2 3\n";
            outFile.close();

            // Перевіряємо, що функція видасть помилку для некоректних даних
            loadGraph(filename, n, m, edges);

            // Перевіряємо, що кількість вершин і кількість ребер не змінюються
            Assert::AreEqual(n, 0);  // n має бути 0, бо дані некоректні
            Assert::AreEqual(m, 0);  // m має бути 0, бо дані некоректні
            Assert::IsNull(edges);   // Масив ребер має бути null, бо немає коректних даних
        }

        TEST_METHOD(TestBuildAdjacencyMatrix)
        {
            int n = 4, m = 5;
            int** edges = new int* [m];
            edges[0] = new int[2] {1, 2};
            edges[1] = new int[2] {2, 3};
            edges[2] = new int[2] {3, 4};
            edges[3] = new int[2] {4, 1};
            edges[4] = new int[2] {2, 4};

            // Створюємо матрицю суміжності
            int** adjacencyMatrix = buildAdjacencyMatrix(n, m, edges);

            // Перевіряємо правильність матриці суміжності
            Assert::AreEqual(adjacencyMatrix[0][1], 1);
            Assert::AreEqual(adjacencyMatrix[1][0], 1);
            Assert::AreEqual(adjacencyMatrix[1][2], 1);
            Assert::AreEqual(adjacencyMatrix[2][1], 1);
            Assert::AreEqual(adjacencyMatrix[0][3], 1);
            Assert::AreEqual(adjacencyMatrix[3][0], 1);
            Assert::AreEqual(adjacencyMatrix[1][3], 1);
            Assert::AreEqual(adjacencyMatrix[3][1], 1);

            // Звільняємо пам'ять
            for (int i = 0; i < n; ++i) {
                delete[] adjacencyMatrix[i];
            }
            delete[] adjacencyMatrix;

            for (int i = 0; i < m; ++i) {
                delete[] edges[i];
            }
            delete[] edges;
        }

        TEST_METHOD(TestBuildIncidenceMatrix)
        {
            int n = 4, m = 5;
            int** edges = new int* [m];
            edges[0] = new int[2] {1, 2};
            edges[1] = new int[2] {2, 3};
            edges[2] = new int[2] {3, 4};
            edges[3] = new int[2] {4, 1};
            edges[4] = new int[2] {2, 4};

            // Створюємо матрицю інцидентності
            int** incidenceMatrix = buildIncidenceMatrix(n, m, edges);

            // Перевіряємо правильність матриці інцидентності
            Assert::AreEqual(incidenceMatrix[0][0], 1);
            Assert::AreEqual(incidenceMatrix[1][0], -1);
            Assert::AreEqual(incidenceMatrix[1][1], 1);
            Assert::AreEqual(incidenceMatrix[2][1], -1);
            Assert::AreEqual(incidenceMatrix[2][2], 1);
            Assert::AreEqual(incidenceMatrix[3][2], -1);

            // Звільняємо пам'ять
            for (int i = 0; i < n; ++i) {
                delete[] incidenceMatrix[i];
            }
            delete[] incidenceMatrix;

            for (int i = 0; i < m; ++i) {
                delete[] edges[i];
            }
            delete[] edges;
        }
    };
}
