#include <iostream>
#include <fstream>

using namespace std;

void loadGraph(const string& filename, int& n, int& m, int**& edges) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    inputFile >> n >> m;

    // Перевірка на некоректні значення кількості вершин і ребер
    if (n <= 0 || m <= 0) {
        cout << "Invalid number of vertices or edges." << endl;
        n = 0; // Оновлюємо n і m для коректної обробки в тестах
        m = 0;
        return;
    }

    edges = new int* [m];
    for (int i = 0; i < m; ++i) {
        edges[i] = new int[2];
        inputFile >> edges[i][0] >> edges[i][1];

        if (edges[i][0] <= 0 || edges[i][1] <= 0) {
            cout << "Invalid edge data: " << edges[i][0] << " " << edges[i][1] << endl;
            // Звільняємо ресурси, якщо виникає помилка
            for (int j = 0; j < i; ++j) {
                delete[] edges[j];
            }
            delete[] edges;
            edges = nullptr;  // Вказуємо, що немає коректних даних
            return;
        }
    }

    inputFile.close();
}

int** buildAdjacencyMatrix(int n, int m, int** edges) {
    int** adjacencyMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        adjacencyMatrix[i] = new int[n]();
    }
    for (int i = 0; i < m; ++i) {
        int v = edges[i][0] - 1;
        int u = edges[i][1] - 1;
        adjacencyMatrix[v][u] = 1;
        adjacencyMatrix[u][v] = 1; 
    }

    return adjacencyMatrix;
}

int** buildIncidenceMatrix(int n, int m, int** edges) {
    int** incidenceMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        incidenceMatrix[i] = new int[m]();
    }

    for (int i = 0; i < m; ++i) {
        int v = edges[i][0] - 1;
        int u = edges[i][1] - 1;
        incidenceMatrix[v][i] = 1;
        incidenceMatrix[u][i] = -1;
    }

    return incidenceMatrix;
}

void displayMatrix(int** matrix, int rows, int cols, const string& matrixName, const string& outputFile) {
    ofstream outFile(outputFile, ios::app);
    if (!outFile.is_open()) {
        cout << "Error opening output file: " << outputFile << endl;
        return;
    }

    cout << matrixName << ":\n";
    outFile << matrixName << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
            outFile << matrix[i][j] << " ";
        }
        cout << endl;
        outFile << endl;
    }
    outFile.close();
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    int n, m;
    int** edges = nullptr;
    string inputFile, outputFile;

    cout << "Enter input file: ";
    cin >> inputFile;
    cout << "Enter output file: ";
    cin >> outputFile;

    loadGraph(inputFile, n, m, edges);
    if (n <= 0 || m <= 0 || edges == nullptr) {
        cout << "Invalid graph data" << endl;
        return 1;
    }

    int** adjacencyMatrix = buildAdjacencyMatrix(n, m, edges);
    int** incidenceMatrix = buildIncidenceMatrix(n, m, edges);

    displayMatrix(adjacencyMatrix, n, n, "Matrix sumizhnosti", outputFile);
    displayMatrix(incidenceMatrix, n, m, "Matrix incydentnosti", outputFile);

    freeMatrix(adjacencyMatrix, n);
    freeMatrix(incidenceMatrix, n);

    for (int i = 0; i < m; ++i) {
        delete[] edges[i];
    }
    delete[] edges;

    return 0;
}
