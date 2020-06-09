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
    // переменная - флаг , если она содержит 0 - то считынные данные - есть матрица
    // инача считанные данные есть слау
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

    // иф выполняется если наша фотка - есть матрица
    string str;
    string temp = "";
    ifstream fin(filenamenew);
    double digit;
    // числа в матрице
    vector <vector <double>> matrix;
    // думерный вектор - наша матрица состоящая из чисел
    vector <double> time;
    // временный вектор, который поможет заполнить двумерный вектор
    vector <char> name;
    // cюда будем кидать имена перменных
    int m = 0;
    // число строк матрицы 
    int n = 0;
    // число стоблцов
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
                            // когда считали число , увелиичили столбцов на +1
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
        cout << "Вы ввели матрицу" << endl;
        cout << "Размеры матрицы: " << m << " строк и " << n << " столбцов" << endl;
        print_matrix(matrix, m, n);
        matrix = step_matrix(matrix, m, n);
        cout << " Ранг матрицы равен = " << rang_matrix(matrix, m, n) << endl;
        if (check_det(matrix, m, n) == 1)
        {
            cout << "Определитель данной матрицы был посчитан, он равен  " << det_matrix(matrix, m, n);
        }
        else
        {
            cout << "Ошибка :( , нельзя посчитать определитель данной матрицы";
        }
    }
    else
        {
            // елсе  выполняется если наша фотка - есть слау
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
                            else if ((test_c != '=') && (test_c != ' '))
                            {
                                digit = atoi(temp.c_str());
                                k++;
                                // когда считали число , увелиичили столбцов на +1
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
                cout << "Вы ввели слау, результат считывания" << endl;
                print_slau(matrix, name, m, n);
                cout << "Решим данную систему методом Крамера" << endl;
                std::vector <double> solutions;
                solutions = Kramer(matrix, name, m, n);
            }
        }
    fin.close();

    return 0;
}