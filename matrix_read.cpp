#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
using namespace std;

int main(int argc, char* argv[]) {


    setlocale(LC_ALL, "Russian");

    string result_name = initilization();
    string filenamenew = result_name;
    string openfirst = result_name;
    //---
    int itisslau = 0;
    // variable-flag, if it contains 0-then the read data is a matrix
    // otherwise, the read data is Slough
    string test;
    char test_c;
    ifstream first(openfirst);
    if (!first.is_open())
    {
        cout << "Error reading from file1";
    }
    else
    {
        while (!first.eof())
        {
            test = "";
            getline(first, test);
            if (test != "")
            {
                for (int i = 0; i < test.length(); i++)
                {
                    test_c = test[i];
                    if (test_c == 'o' || test_c == 'O' || test_c == 'о' || test_c == 'О')
                    {
                        test_c = '0';
                    }
                    if ((isalpha(test_c)))
                    {
                        itisslau++;
                    }
                }
            }
        }

    }
    first.close();

    // the condition "if" is met if our photo is a matrix
    string str;
    string temp = "";
    ifstream fin(filenamenew);
    double digit;
    // digits in matrix
    vector <vector <double>> matrix;
    // a two-dimensional vector is our matrix consisting of numbers
    vector <double> time;
    // a temporary vector that will help fill in a two-dimensional vector
    vector <char> name;
    // here we will throw the names of the variables
    int m = 0;
    // number of rows in the matrix
    int n = 0;
    // numbers of columns
    int k = 0;

    if (itisslau == 0)
    {

        if (!fin.is_open())
        {
            cout << "Error reading from file1";
        }
        else
        {
            while (!fin.eof())
            {
                str = "";
                getline(fin, str);
                if (str != "")
                {
                    m++;

                    for (int i = 0; i < str.length(); i++)
                    {
                        test_c = str[i];
                        if (test_c == 'o' || test_c == 'О')
                        {
                            test_c = '0';
                        }
                        if (test_c != ' ')
                        {
                            temp = temp + test_c;
                        }
                        else
                        {
                            digit = atoi(temp.c_str());
                            k++;
                            // when the number was counted, the columns were increased by +1
                            time.push_back(digit);
                            temp.clear();
                        }

                    }
                    k++;
                    digit = atoi(temp.c_str());
                    time.push_back(digit);
                    temp.clear();
                    matrix.push_back(time);
                    time.clear();
                    n = k;
                    k = 0;


                }
            }

        }
        cout << "You entered a matrix" << endl;
        cout << "sizes of  matrix: " << m << " rows and " << n << " columns" << endl;
        print_matrix(matrix, m, n);
        matrix = step_matrix(matrix, m, n);
        cout << " rang of matrix is equal = " << rang_matrix(matrix, m, n) << endl;
        if (check_det(matrix, m, n) == 1)
        {
            cout << "determinant of this matrix was counted, one equal  " << det_matrix(matrix, m, n);
        }
        else
        {
            cout << "Mistake :( , impossible to count determinant of this matrix";
        }
    }
    else
        {
            // the condition is met if picture is system of lineal algebraic equations
            if (!fin.is_open())
            {
                cout << "Error reading from file1";
            }
            else
            {
                while (!fin.eof())
                {
                    str = "";
                    getline(fin, str);
                    if (str != "")
                    {
                        m++;

                        for (int i = 0; i < str.length(); i++)
                        {
                            test_c = str[i];
                            if (test_c == 'o' || test_c == 'О')
                            {
                                test_c = '0';
                            }
                            if ((test_c != ' ') && !(isalpha(test_c)) && (test_c != '='))
                            {
                                temp = temp + test_c;
                            }
                            else if (test_c != '=')
                            {
                                digit = atoi(temp.c_str());
                                k++;
                                // when the number was counted, the columns were increased by +1
                                time.push_back(digit);
                                temp.clear();
                                if (isalpha(str[i]))
                                {
                                    name.push_back(str[i]);
                                }
                            }

                        }
                        k++;
                        digit = atoi(temp.c_str());
                        time.push_back(digit);
                        temp.clear();
                        matrix.push_back(time);
                        time.clear();
                        n = k;
                        k = 0;


                    }
                }
                cout << "you entered a matrix, result is" << endl;
                print_slau(matrix, name, m, n);
                cout << "we count up this SLAE by method of Kramer" << endl;
                std::vector <double> solutions;
                solutions = Kramer(matrix, name, m, n);
            }
        }
    fin.close();

    return 0;
}