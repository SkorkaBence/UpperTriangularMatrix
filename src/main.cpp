#include <iostream>

#include "Matrix/UpperTriangularMatrix.h"

#define print(x) std::cout << x
#define println(x) std::cout << x << std::endl
#define read(x) std::cin >> x

int main() {
    int matrix_size;
    bool stoploop = false;

    println("Hello!");
    print("Mekkora legyen a matrix? /Nem ellenorzott input/ ");
    read(matrix_size);

    UpperTriangularMatrix matrix(matrix_size);
    println("Matrix letrehozva!");

    while (!stoploop) {
        println("-=-=-= Fo Menu =-=-=-");
        println("1 - Matrix kiirasa");
        println("2 - Matrix randomizalasa");
        println("3 - Matrix szorzasa egesz szammal");
        println("4 - Matrix osszeadasa matrixal");
        println("5 - Matrix szorzasa matrixal");
        println("0 - Kilepes");

        int input;
        read(input);

        switch (input) {
            case 1: // print
                println(matrix);
                break;
            case 2: // randomize
                break;
            case 3: // multiply with a number
                break;
            case 4: // add a matrix
                break;
            case 5: // multiply with a matrix
                break;
            case 0: // exit
                stoploop = true;
                break;
        }
    }
}
