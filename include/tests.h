#include <iostream>
#include <sstream>
#include <fstream>

#define CATCH_CONFIG_MAIN

#include "Storage/Vector.h"
#include "Matrix/UpperTriangularMatrix.h"

#include "Catch/catch.hpp"

TEST_CASE("Vector fill", "[vector]") {
    sbl::vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    REQUIRE( v.size() == 10 );
    REQUIRE( v[2] == 2 );
    REQUIRE( v[7] == 7 );
}

TEST_CASE("Vector resize", "[vector]") {
    sbl::vector<int> v;
    v.resize(15);

    REQUIRE( v.size() == 15 );
}

TEST_CASE("Matrix creation", "[matrix]") {
    sbl::UpperTriangularMatrix m(2);
    std::stringstream stream;
    m.writeData(stream);
    REQUIRE( stream.str() == "2 0 0 0" );
}

TEST_CASE("Accessing valid matrix positions", "[matrix]") {
    sbl::UpperTriangularMatrix m(15);

    for (int x = 0; x < 15; x++) {
        for (int y = 0; y <= x; y++) {
            REQUIRE_NOTHROW( m(x, y) == 0 );
        }
    }
}

TEST_CASE("Accessing invvalid matrix positions", "[matrix]") {
    sbl::UpperTriangularMatrix m(15);

    for (int x = 0; x < 15; x++) {
        for (int y = x + 1; y < 15; y++) {
            REQUIRE_THROWS( m(x, y) );
        }
    }
}

TEST_CASE("Matrix multiplication with number", "[matrix]") {
    sbl::UpperTriangularMatrix m1(0);
    std::ifstream in1("3.matrix");
    m1.readData(in1);

    // precheck
    REQUIRE( m1(0, 0) == 1 );
    REQUIRE( m1(1, 0) == 2 );
    REQUIRE( m1(2, 0) == 3 );
    REQUIRE( m1(1, 1) == 4 );
    REQUIRE( m1(2, 1) == 5 );
    REQUIRE( m1(2, 2) == 6 );

    // multiply
    REQUIRE_NOTHROW( m1 *= 2 );

    // reusult
    REQUIRE( m1(0, 0) == 2 );
    REQUIRE( m1(1, 0) == 4 );
    REQUIRE( m1(2, 0) == 6 );
    REQUIRE( m1(1, 1) == 8 );
    REQUIRE( m1(2, 1) == 10 );
    REQUIRE( m1(2, 2) == 12 );
}

TEST_CASE("Matrix addition", "[matrix]") {
    sbl::UpperTriangularMatrix m1(0);
    std::ifstream in1("4_1.matrix");
    m1.readData(in1);

    sbl::UpperTriangularMatrix m2(0);
    std::ifstream in2("4_2.matrix");
    m2.readData(in2);

    sbl::UpperTriangularMatrix res(0);

    // precheck
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y <= x; y++) {
            int temp;

            REQUIRE_NOTHROW( temp = m1(x, y) );
            REQUIRE( temp == y + 1 );

            REQUIRE_NOTHROW( temp = m2(x, y) );
            REQUIRE( temp == x + 1 );
        }
    }

    // add
    REQUIRE_NOTHROW( res = m1 + m2 );

    // reusult
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y <= x; y++) {
            int temp;
            REQUIRE_NOTHROW( temp = res(x, y) );
            REQUIRE( temp == x + y + 2 );
        }
    }
}

TEST_CASE("Matrix multiplication", "[matrix]") {
    sbl::UpperTriangularMatrix m1(0);
    std::ifstream in1("4_1.matrix");
    m1.readData(in1);

    sbl::UpperTriangularMatrix m2(0);
    std::ifstream in2("4_2.matrix");
    m2.readData(in2);

    sbl::UpperTriangularMatrix res(0);

    sbl::UpperTriangularMatrix correctmult(0);
    std::ifstream in3("4_mult_correct.matrix");
    correctmult.readData(in3);

    // precheck
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y <= x; y++) {
            int temp;

            REQUIRE_NOTHROW( temp = m1(x, y) );
            REQUIRE( temp == y + 1 );

            REQUIRE_NOTHROW( temp = m2(x, y) );
            REQUIRE( temp == x + 1 );
        }
    }

    // multiply
    REQUIRE_NOTHROW( res = m1 * m2 );

    // reusult
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y <= x; y++) {
            int temp1, temp2;
            REQUIRE_NOTHROW( temp1 = res(x, y) );
            REQUIRE_NOTHROW( temp2 = correctmult(x, y) );
            REQUIRE( temp1 == temp2 );
        }
    }
}
