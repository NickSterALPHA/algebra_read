//#define CATCH_CONFIG_MAIN
#include "functions.h"
//#include "catch.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


TEST_CASE("test for matrix of 2 orders")
{
	std::vector<std::vector<double>> mat{ {1,2}, {3,4} };
	std::vector<std::vector<double>> new_mat{ {1,2}, {0,-2} };
	mat = step_matrix(mat, 2, 2);
	int rang = rang_matrix(mat, 2, 2);
	REQUIRE(mat == new_mat);
	REQUIRE(rang == 2);
}


TEST_CASE("test for matrix of 3 orders")
{
	std::vector<std::vector<double>> mat{ {1,-1, 2}, {2, -2, 4}, {-1, 1, -1} };
	std::vector<std::vector<double>> new_mat{ {1,-1,2}, {0, 0, 1}, {0, 0, 0} };
	mat = step_matrix(mat, 3, 3);
	int rang = rang_matrix(mat, 3, 3);
	REQUIRE(mat == new_mat);
	REQUIRE(rang == 2);
}

TEST_CASE("second test for matrix of 3 orders")
{
	std::vector<std::vector<double>> mat{ {1,-1, 2}, {2, -2, 4}, {-1, 1, -2} };
	std::vector<std::vector<double>> new_mat{ {1,-1, 2}, {0, 0, 0}, {0, 0, 0} };
	mat = step_matrix(mat, 3, 3);
	int rang = rang_matrix(mat, 3, 3);
	REQUIRE(mat == new_mat);
	REQUIRE(rang == 1);
}


TEST_CASE("solution to SLAE with 2 variables")
{
	std::vector<std::vector<double>> mat {{2, -4, -6},{2, 1, 4}};
	std::vector<double> solutions;
	solutions = Kramer(mat, {'x', 'y'}, 2, 3);
	std::vector<double> request = {1, 2};
	REQUIRE(solutions == request);
}

TEST_CASE("solution to SLAE with 3 variables")
{
	std::vector<std::vector<double>> mat {{5, -5, -4, 0},{3, -1, 3, 0}, {1, 7, -1, 0}};
	std::vector<double> solutions;
	solutions = Kramer(mat, {'x', 'y', 'z'}, 3, 4);
	std::vector<double> request = {0, 0, 0};
	REQUIRE(solutions == request);
}
TEST_CASE("no solutions")
{
	std::vector<std::vector<double>> mat {{7, -2, -1, 2},{6, -4, -5, 3}, {1, 2, 4, 5}};
	std::vector<double> solutions;
	solutions = Kramer(mat, {'x', 'y', 'z'}, 3, 4);
	std::vector<double> request = {-1};
	REQUIRE(solutions == request);
}

TEST_CASE("very much solutions")
{
	std::vector<std::vector<double>> mat {{1, -2, -1, 3, 2},{-2, 1, 3, -2, -3}, {2, -1, -2, 1, 2}, {3, -3, -2, 3, 3}};
	std::vector<double> solutions;
	solutions = Kramer(mat, {'a', 'b', 'c', 'd'}, 4, 5);
	std::vector<double> request = {0};
	REQUIRE(solutions == request);
}