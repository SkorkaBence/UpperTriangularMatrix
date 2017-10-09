#include <iostream>
#include <fstream>

//#define RUN_TESTS

#ifdef RUN_TESTS
#include "tests.h"
#else

#include "Matrix/UpperTriangularMatrix.h"

#define print(x) std::cout << x
#define println(x) std::cout << x << std::endl
#define read(x) std::cin >> x
#define savefile(x) x + ".matrix"

void loadMatrix(sbl::UpperTriangularMatrix& matrix);
void saveMatrix(sbl::UpperTriangularMatrix& matrix);

int main() {
    int matrix_size;
    bool stoploop = false;

    println("Hello!");
    print("Matrix merete: ");
    read(matrix_size);

    sbl::UpperTriangularMatrix matrix(matrix_size);
    sbl::UpperTriangularMatrix m2(0);
    println("Matrix letrehozva!");

    while (!stoploop) {
        println("-=-=-= Fo Menu =-=-=-");
        println("1 - Matrix kiirasa");
        println("2 - Matrix betoltese");
        println("3 - Matrix mentese");
        println("4 - Matrix szorzasa egesz szammal");
        println("5 - Matrix osszeadasa matrixal");
        println("6 - Matrix szorzasa matrixal");
        println("0 - Kilepes");

        int input;
        read(input);

        switch (input) {
            case 1: // print
                println(matrix);
                break;
            case 2: // load
                loadMatrix(matrix);
                break;
            case 3: // save
                saveMatrix(matrix);
                break;
            case 4: // multiply with a number
                int num;
                print("Szorzas ennyivel: ");
                read(num);
                matrix *= num;
                break;
            case 5: // add a matrix
                loadMatrix(m2);
                matrix = matrix + m2;
                break;
            case 6: // multiply with a matrix
                loadMatrix(m2);
                matrix = matrix * m2;
                break;
            case 0: // exit
                stoploop = true;
                break;
        }
    }
}

void loadMatrix(sbl::UpperTriangularMatrix& matrix) {
    println("-=-=-= Betoltes =-=-=-");
    println("1 - Betoltes consolerol");
    println("2 - Betoltes filebol");
    println("0 - megsem");

    int r;
    read(r);

    switch (r) {
        case 1:
            matrix.readData(std::cin);
            break;
        case 2:
            std::string filename;
            println("Filenev?");
            read(filename);
            std::ifstream input(savefile(filename));
            if (input.is_open()) {
                matrix.readData(input);
            }
            break;
    }
}

void saveMatrix(sbl::UpperTriangularMatrix& matrix) {
    println("-=-=-= Mentes =-=-=-");
    println("Filenev?");
    std::string filename;
    read(filename);
    std::ofstream output(savefile(filename));
    if (output.is_open()) {
        matrix.writeData(output);
    }
}

#endif
