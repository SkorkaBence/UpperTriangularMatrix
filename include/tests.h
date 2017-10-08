#include <iostream>
#include <sstream>
#include <fstream>

#define CATCH_CONFIG_MAIN

#include "Storage/Vector.h"
#include "Matrix/UpperTriangularMatrix.h"
#include "Numbers/InfInt.h"

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

TEST_CASE("Vector push", "[vector]") {
    sbl::vector<int> v;

    for (int i = 0; i < 15; i++) {
        v.push_back(i);
    }

    for (int i = 0; i < 15; i++) {
        REQUIRE( v[i] == i );
    }
}

TEST_CASE("Vector pop", "[vector]") {
    sbl::vector<int> v;

    for (int i = 0; i < 15; i++) {
        v.push_back(i);
    }

    for (int i = 0; i < 5; i++) {
        v.pop_back();
    }

    for (int i = 0; i < 15; i++) {
        if (i < 10) {
            REQUIRE( v[i] == i );
        } else {
            REQUIRE_THROWS( v[i] );
        }
    }
}

TEST_CASE("Vector resize with data", "[vector]") {
    sbl::vector<int> v;

    for (int i = 0; i < 15; i++) {
        v.push_back(i);
    }

    v.resize(20);

    for (int i = 0; i < 15; i++) {
        REQUIRE( v[i] == i );
    }

    v.resize(10);

    for (int i = 0; i < 15; i++) {
        if (i < 10) {
            REQUIRE( v[i] == i );
        } else {
            REQUIRE_THROWS( v[i] );
        }
    }
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
            number_type temp;

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
            number_type temp;
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
            number_type temp;

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
            number_type temp1, temp2;
            REQUIRE_NOTHROW( temp1 = res(x, y) );
            REQUIRE_NOTHROW( temp2 = correctmult(x, y) );
            REQUIRE( temp1 == temp2 );
        }
    }
}

TEST_CASE("Number creation", "[infint]") {
    sbl::InfInt a = 8;
    REQUIRE( a == 8 );
}

TEST_CASE("2^100", "[infint]") {
    sbl::InfInt a = 1;
    for (int i = 0; i < 100; i++) {
        a = a * 2;
    }
    REQUIRE( a.toString() == "1267650600228229401496703205376");
}

TEST_CASE("3^1463", "[infint]") {
    sbl::InfInt a = 1;
    for (int i = 0; i < 1463; i++) {
        a = a * 3;
    }
    REQUIRE( a.toString() == "106756826398240832148635272185668669030096504887041790681067437553363321772977659234912243264833262986252720759608094680223602219338961352336960404406055077895400358354829200160259745623821286893741267010602665280878788879625238057367634011087065210980709448690052197724024462927350474862592766436691381141201627014093099563717968387989970779405326771329333797942356107730632585912102871653297052335845812531222580422300265415071105694799379652537456496050758098230591493506106891568612860737751639389393860390941229226037276972234886152346101466408648260401951152130909718404756933237555681414314793318295386817501519488964584813574084737830969525992721401152146515636990027866764868627705872212427");
}
