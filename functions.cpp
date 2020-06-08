#include <tesseract/baseapi.h>
#include "functions.h"
#include <leptonica/allheaders.h>
#include <algorithm>
#include <vector>
#include <string>


std::vector<std::vector <double>> swipe_column(std::vector<std::vector <double>> matrix, int m, int n, int k, int l)
{
    // ������� , ������������ ��������� ������, � ������� ���������� ������� k � l
    // ��������� ��������� ������, ����� �����, ����� ��������, ������� k, ������� l
    double temp;
    for (int i = 0; i < m; i++)
    {
        std::swap(matrix[i][k], matrix[i][l]);
    }
    return matrix;


}

std::vector<std::vector <double>> delete_last_column(std::vector<std::vector <double>> matrix, int m, int n)
{
    // ������� , ������������ ��������� ������, � ������� , ��� ������ ��������� �������
    // ��������� ��������� ������, ����� ����� , ����� ��������
    for (int i = 0; i < m; i++)
    {
        matrix.at(i).erase(matrix.at(i).begin() + n - 1);
    }
    return matrix;
}
void print_slau(std::vector<std::vector <double>> matrix, std::vector <char> name, int m, int n)
{
    // ������� ���������� ����
    // ��������� ��������� ������ ����� ,������ �������� ���������, ����� �����, ����� ��������
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j < n - 2)
            {
                std::cout << matrix[i][j] << name[j] << "+";
            }
            if (j == n - 2)
            {
                std::cout << matrix[i][j] << name[j];
            }
            if (j == n - 1)
            {
                std::cout << "= " << matrix[i][j];
            }
        }
        std::cout << std::endl;
    }
}

void print_matrix(std::vector<std::vector <double>> matrix, int m, int n)
{
    // ������� ���������� ��������� ������
    // ��������� - ��������� ������, ����� ����� ,����� ��������
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << matrix[i][j] << "    ";
        }
        std::cout << std::endl;
    }
}
int find_nozero(std::vector<std::vector <double>> matrix, int m, int n, int i, int j)
{
    // ������� ��������� ������ >= i c ��������� ��������� � ������ ������� j
    // ��������� ��������� ������,����� �����, ����� ��������, ������ i-��, ������� j-��
    for (int l = i; l < m; l++)
    {
        if (matrix[l][j] != 0)
        {
            return l;
        }
    }
    return -1;
    // �� ������� ������ >= i � ��������� ��������� � ������ ������� j

}

void swipe_string(std::vector<std::vector <double>>& matrix, int m, int n, int k, int l)
{
    // ������� ������ ������ l � � �������
    // ��������� ������ �� �������, ����� ����� , ����� ��������, k -�� ������, l-�� ������
    double temp;
    for (int j = 0; j < n; j++)
    {
        temp = matrix[l][j];
        matrix[l][j] = matrix[k][j];
        matrix[k][j] = temp;
    }
    if (l != k)
    {
        std::cout << "�������� ������ �������" << std::endl;
        print_matrix(matrix, m, n);
    }
}
void subtraction_strings(std::vector<std::vector <double>>& matrix, int m, int n, int k, int l, int j)
{
    // �������, ������� �������� �� �-�� ������ l -�� ������� �� ������� j, ��� �����
    // � j -�� ������� � �-�� ������ ��� ������� 0
    // ��������� ������ ��������� 
    double multiplier = matrix[k][j] / matrix[l][j];
    for (int f = j; f < n; f++)
    {
        matrix[k][f] = matrix[k][f] - matrix[l][f] * multiplier;
    }
    std::cout << "���������� ��������� �����" << std::endl;
    print_matrix(matrix, m, n);

}
std::vector<std::vector <double>> step_matrix(std::vector<std::vector <double>> matrix, int m, int n)
{
    // ���������� �������, ����������� � ������������ ����
    // ��������� ������� , ����� ����� ,����� ��������
    int l;
    int i = 0;

    for (int j = 0; j < n; j++)
    {
        l = find_nozero(matrix, m, n, i, j);
        if (l != -1)
        {
            swipe_string(matrix, m, n, i, l);
            for (int f = i + 1; f < m; f++)
            {
                subtraction_strings(matrix, m, n, f, i, j);
            }
            i++;
        }
    }
    return matrix;
}
int rang_matrix(std::vector<std::vector <double>> matrix, int m, int n)
{
    // c������ ���� , ������� , ������ ��� ���� ����� �������� �����
    // � �������� ��������� ������ ���� ����������� �������!!!!!
    // ��������� ������� , ����� �����, ����� ��������
    int k = 0;
    // ������� ��������� ��������� � ������
    int rang = 0;
    // ������� ����� �� ������� �����

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] != 0)
            {
                k++;
            }
        }
        if (k > 0)
        {
            rang++;
        }
        k = 0;
        // �������� �������
    }
    return rang;
}
bool check_det(std::vector<std::vector <double>> matrix, int m, int n)
{
    // ���������� 1 - ��� - ���� ��������� ������������ � ������
    // ���������� 0 - ���� - ���� �� ���������� ������������ � �������
    // ��������� ��������� ������, ����� ����� , ����� ��������
    if (m == n)
    {
        return 1;
    }

    return 0;
}
double det_matrix(std::vector<std::vector <double>> matrix, int m, int n)
{
    // c������ ������������ ������� , ������ ������������ ��������� �� ��������� 
    // � �������� ��������� ������ ���� ����������� �������!!!!!
    // ��������� ������� , ����� �����, ����� ��������
    double p = 1;
    for (int i = 0; i < n; i++)
    {
        p = p * matrix[i][i];
    }
    return p;
}
vector <double> Kramer(vector<vector <double>> matrix, vector <char> name, int m, int n)
{
    // вычисляет решения слау методом крамером
    // принимает двумерный вектор(который состоит из коэф слау + свободных членов)
    // вектор состоящий из названий переменных, число строк матрицы , число столбцов матрицы
    // вовзращает вектор строку решений

    vector <double> solutions;
    if (!(check_det(matrix, m, n - 1)))
    {
        cout << "Ошибка нельзя посчитать методом крамера";
    }
    else 
    {
        vector <vector<double>> temp;
        vector <vector<double>> time;
        temp = delete_last_column(matrix, m, n);
        cout << "Привдем главную матрицу к ступенчатому виду, чтобы посчитать определитель" << endl;
        temp = step_matrix(temp, m, n - 1);
        double det_general = det_matrix(temp, m, n - 1);
        double det;
        if (det_general != 0)
        {
            for (int i = 0; i < m; i++)
            {
                time = swipe_column(matrix, m, n, i, n - 1);
                time = delete_last_column(time, m, n);
                cout << "Привдем матрицу переменной " << name[i] << " к ступенчатому виду, чтобы посчитать определитель" << endl;
                time = step_matrix(time, m, n - 1);
                det = det_matrix(time, m, n - 1);
                if (i == m - 1)
                {
                    cout << name[i] << "=" << det / det_general;
                    solutions.push_back(det / det_general);

                }
                else
                {
                    cout << name[i] << "=" << det / det_general << endl;
                    solutions.push_back(det / det_general);
                }
            }
        }
        else 
        {
            int alldeterminat = 0; 
            // число нулевых детерминатов 
            for (int i = 0; i < m; i++)
            {
                time = swipe_column(matrix, m, n, i, n - 1);
                time = delete_last_column(time, m, n);
                cout << "Привдем матрицу переменной " << name[i] << " к ступенчатому виду, чтобы посчитать определитель" << endl;
                time = step_matrix(time, m, n - 1);
                det = det_matrix(time, m, n - 1);
                if (det == 0)
                {
                    alldeterminat++;
                }
            }
            if (alldeterminat == m)
            {
                cout << "система линейных уравнений имеет бесчисленное множество решений";
                solutions.push_back(0);
            }
            if (alldeterminat == 0)
            {
                cout << "система линейных уравнений решений не имеет";
                solutions.push_back(-1);
            }

        }
        
        
    }
    return solutions;
}

string initilization()
{
    // создает текстовый файл, в котором хранится текст с картинки
    // возвращает название текстового файла 
    string pathImage;
    getline(std::cin, pathImage);
    tesseract::TessBaseAPI tessApi;
    tessApi.Init(NULL, "eng");
    const char* pathImage_char = pathImage.c_str();
    PIX* pix = pixRead(pathImage_char);// считываем картинку из файла с именем,
    // переданным первым аргументом, это функционал Leptonica
    tessApi.SetImage(pix);// говорим tesseract, что распознавать нужно эту картинку
    char* text = tessApi.GetUTF8Text();//распознаём
    string text_string = string(text);
    //генерируем имя файла в который будет записан распознанный текст
    string fileName = "";
    long prefixLength;
    int last = pathImage.find('.');
        fileName = pathImage.substr(0, last);
        reverse(begin(fileName), end(fileName));
        int position = 0;
        for (int i = 0; i < fileName.length(); i++)
        {
            if (fileName[i] == '\\')
            {
                position = i;
                break;
            }
        }
        fileName = fileName.substr(0, position);
        reverse(begin(fileName), end(fileName));
        fileName = fileName + ".txt\0";
    ofstream ofs;
    ofs.open(fileName, ios::out );
    ofs.close();
    ofstream fs;
    fs.open(fileName, ios::out);
    if (!fs.is_open())
    {
        cout << "Ошибка открытия" << fileName;
    }
    else
    {
        fs << text_string << "\n";
    }
    fs.close();
    pixDestroy(&pix);
    return fileName;
}