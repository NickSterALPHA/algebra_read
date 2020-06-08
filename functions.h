#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

std::vector<std::vector <double>> swipe_column(std::vector<std::vector <double>> matrix, int m, int n, int k, int l);

std::vector<std::vector <double>> delete_last_column(std::vector<std::vector <double>> matrix, int m, int n);

void print_slau(std::vector<std::vector <double>> matrix, std::vector <char> name, int m, int n);

void print_matrix(std::vector<std::vector <double>> matrix, int m, int n);

int find_nozero(std::vector<std::vector <double>> matrix, int m, int n, int i, int j);

void swipe_string(std::vector<std::vector <double>>& matrix, int m, int n, int k, int l);

void subtraction_strings(std::vector<std::vector <double>>& matrix, int m, int n, int k, int l, int j);

std::vector<std::vector <double>> step_matrix(std::vector<std::vector <double>> matrix, int m, int n);

int rang_matrix(std::vector<std::vector <double>> matrix, int m, int n);

bool check_det(std::vector<std::vector <double>> matrix, int m, int n);

double det_matrix(std::vector<std::vector <double>> matrix, int m, int n);

std::vector<double> Kramer(std::vector<std::vector <double>> matrix, std::vector <char> name, int m, int n);

char* buffer_realloc(char* buf, size_t oldSize, size_t newSize);

std::istream& getline(std::istream& is, char*& buffer);

std::string initilization();
