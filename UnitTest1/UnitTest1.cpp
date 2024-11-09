#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "..//PDC_LAB_6/source.cpp" // �������� ��������� ������ ����� � �����

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

            // ������� �������� ���� input.txt � ���������� ������
            std::ofstream outFile(filename);
            outFile << "4 5\n1 2\n2 3\n3 4\n4 1\n2 4\n";
            outFile.close();

            // ��������� ������� ���������� �����
            loadGraph(filename, n, m, edges);

            // ����������, �� ������� ������ �� ���� �������� � ����� �������
            Assert::AreEqual(n, 4);
            Assert::AreEqual(m, 5);
            Assert::IsNotNull(edges);  // ��������, �� ����� �������� �� � ������

            // ���������� ����������� ������� �����
            Assert::AreEqual(edges[0][0], 1);
            Assert::AreEqual(edges[0][1], 2);

            // ��������� ���'���
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

            // ��������� ����������� �������� ����
            std::ofstream outFile(filename);
            outFile << "4 -5\n1 2\n2 3\n";
            outFile.close();

            // ����������, �� ������� ������� ������� ��� ����������� �����
            loadGraph(filename, n, m, edges);

            // ����������, �� ������� ������ � ������� ����� �� ���������
            Assert::AreEqual(n, 0);  // n �� ���� 0, �� ��� ���������
            Assert::AreEqual(m, 0);  // m �� ���� 0, �� ��� ���������
            Assert::IsNull(edges);   // ����� ����� �� ���� null, �� ���� ��������� �����
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

            // ��������� ������� ��������
            int** adjacencyMatrix = buildAdjacencyMatrix(n, m, edges);

            // ���������� ����������� ������� ��������
            Assert::AreEqual(adjacencyMatrix[0][1], 1);
            Assert::AreEqual(adjacencyMatrix[1][0], 1);
            Assert::AreEqual(adjacencyMatrix[1][2], 1);
            Assert::AreEqual(adjacencyMatrix[2][1], 1);
            Assert::AreEqual(adjacencyMatrix[0][3], 1);
            Assert::AreEqual(adjacencyMatrix[3][0], 1);
            Assert::AreEqual(adjacencyMatrix[1][3], 1);
            Assert::AreEqual(adjacencyMatrix[3][1], 1);

            // ��������� ���'���
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

            // ��������� ������� ������������
            int** incidenceMatrix = buildIncidenceMatrix(n, m, edges);

            // ���������� ����������� ������� ������������
            Assert::AreEqual(incidenceMatrix[0][0], 1);
            Assert::AreEqual(incidenceMatrix[1][0], -1);
            Assert::AreEqual(incidenceMatrix[1][1], 1);
            Assert::AreEqual(incidenceMatrix[2][1], -1);
            Assert::AreEqual(incidenceMatrix[2][2], 1);
            Assert::AreEqual(incidenceMatrix[3][2], -1);

            // ��������� ���'���
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
