#include "functions.h"
#include <algorithm>
#include <leptonica/allheaders.h>
#include <string>
#include <tesseract/baseapi.h>
#include <vector>

std::vector<std::vector<double>>
swipe_column(std::vector<std::vector<double>> matrix, int m, int n, int k,
             int l) {
  // function return twodimensional vector with changed columns k and l 
  // get 2-dimensional vector, numbers of rows, columns, column k and l
  for (int i = 0; i < m; i++) {
    std::swap(matrix[i][k], matrix[i][l]);
  }
  return matrix;
}

std::vector<std::vector<double>>
delete_last_column(std::vector<std::vector<double>> matrix, int m, int n) {
 // function return 2dimensional vector with deleted last column
 //get matrix, numbers of rows and col
 for (int i = 0; i < m; i++) {
    matrix.at(i).erase(matrix.at(i).begin() + n - 1);
  }
  return matrix;
}
void print_slau(const std::vector<std::vector<double>> &matrix, std::vector<char> name,
                int m, int n) {
  //function print system of lineal algebraic equations
  //get matrix, vector of names of variables, numbers of rows and col 
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (j < n - 2) {
        std::cout << matrix[i][j] << name[j] << "+";
      }
      if (j == n - 2) {
        std::cout << matrix[i][j] << name[j];
      }
      if (j == n - 1) {
        std::cout << "= " << matrix[i][j];
      }
    }
    std::cout << std::endl;
  }
}

void print_matrix(const std::vector<std::vector<double>> &matrix, int m, int n) {
  // function prints matrix
  // get matrix, numbers of rows and col
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << matrix[i][j] << "    ";
    }
    std::cout << std::endl;
  }
}
int find_nozero(const std::vector<std::vector<double>> &matrix, int m, int n, int i,
                int j) {
  // func returns row with number >=i with not-zero element in col j
  //get matrix, numbers of rows, col and i-row and j-col
  for (int l = i; l < m; l++) {
    if (matrix[l][j] != 0) {
      return l;
    }
  }
  return -1;
  // not found row with number >= i with non-zero element in col j
}

void swipe_string(std::vector<std::vector<double>> &matrix, int m, int n, int k,
                  int l) {
  // func changes rows l and k
  for (int j = 0; j < n; j++) {
    std::swap(matrix[l][j], matrix[k][j]);
  }
  if (l != k) {
    std::cout << "Change rows" << std::endl;
    print_matrix(matrix, m, n);
  }
}
void subtraction_strings(std::vector<std::vector<double>> &matrix, int m, int n,
                         int k, int l, int j) {
  // a function that subtracts from the K-th row the l-th starting from column j, so that
  // in the j-th column in the K-th row was the element 0
  // accepts a two-dimensional reference
  double multiplier = matrix[k][j] / matrix[l][j];
  for (int f = j; f < n; f++) {
    matrix[k][f] = matrix[k][f] - matrix[l][f] * multiplier;
  }
  std::cout << "substract rows" << std::endl;
  print_matrix(matrix, m, n);
}
std::vector<std::vector<double>> step_matrix(std::vector<std::vector<double>> matrix, int m, int n) {
  // function returns a step matrix
  // get matrix, numbers of rows and col
  int l;
  int i = 0;

  for (int j = 0; j < n; j++) {
    l = find_nozero(matrix, m, n, i, j);
    if (l != -1) {
      swipe_string(matrix, m, n, i, l);
      for (int f = i + 1; f < m; f++) {
        subtraction_strings(matrix, m, n, f, i, j);
      }
      i++;
    }
  }
  return matrix;
}
int rang_matrix(const std::vector<std::vector<double>> &matrix, int m, int n) {
  // counts the rank of the matrix, while counting the number of non-zero rows
  // the argument must be a step matrix!!!!!
  // accepts a matrix, the number of rows, and the number of columns
  int k = 0;
  // counter non-zero in row
  int rang = 0;
  // count number of non-zero row

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] != 0) {
        k++;
      }
    }
    if (k > 0) {
      rang++;
    }
    k = 0;
    // zero counter
  }
  return rang;
}
bool check_det(const std::vector<std::vector<double>> &matrix, int m, int n) {
  // returns 1-true - if there is a determinant for the matrix 
  // returns 0-false - if there is no determinant for the matrix 
  // accepts a two-dimensional vector, number of rows , number of columns
  if (m == n) {
    return 1;
  }

  return 0;
}
double det_matrix(const std::vector<std::vector<double>> &matrix, int m, int n) {
  // calculates Slough solutions using the Kramer method
  // accepts a two-dimensional vector (which consists of the Slough coef + free terms) 
  // a vector consisting of variable names, the number of matrix rows , and the number of matrix columns
  // returns a vector string of solutions
  double p = 1;
  for (int i = 0; i < n; i++) {
    p = p * matrix[i][i];
  }
  return p;
}
std::vector<double> Kramer(const std::vector<std::vector<double>> &matrix, std::vector<char> name, int m,
                      int n) {
  // calculates Slough solutions using the Kramer method
  // accepts a two-dimensional vector (which consists of the Slough coef + free terms)
  // a vector consisting of variable names, the number of matrix rows , and the number of matrix columns
  // returns a vector string of solutions
  std::vector<double> solutions;
  if (!(check_det(matrix, m, n - 1))) {
    std::cout << "impossible to count by Kramer method";
  } else {
    std::vector<std::vector<double>> temp;
    std::vector<std::vector<double>> time;
    temp = delete_last_column(matrix, m, n);
    std::cout << "We reduce the main matrix to a stepwise form to calculate "
            "determinant"
         << std::endl;
    temp = step_matrix(temp, m, n - 1);
    double det_general = det_matrix(temp, m, n - 1);
    double det;
    if (det_general != 0) {
      for (int i = 0; i < m; i++) {
        time = swipe_column(matrix, m, n, i, n - 1);
        time = delete_last_column(time, m, n);
        std::cout << "Here is the matrix of the variable " << name[i]
<< "to a stepwise view to calculate the determinant" << std::endl;
        time = step_matrix(time, m, n - 1);
        det = det_matrix(time, m, n - 1);
        if (i == m - 1) {
          std::cout << name[i] << "=" << det / det_general;
          solutions.push_back(det / det_general);

        } else {
          std::cout << name[i] << "=" << det / det_general << std::endl;
          solutions.push_back(det / det_general);
        }
      }
    } else {
      int alldeterminat = 0;
      // number of nonzero determinants
      for (int i = 0; i < m; i++) {
        time = swipe_column(matrix, m, n, i, n - 1);
        time = delete_last_column(time, m, n);
        std::cout << "Here is the matrix of the variable " << name[i]
<< "to a stepwise view to calculate the determinant" << std::endl;
        time = step_matrix(time, m, n - 1);
        det = det_matrix(time, m, n - 1);
        if (det == 0) {
          alldeterminat++;
        }
      }
      if (alldeterminat == m) {
        std::cout << "the system of linear equations has innumerable sets "
                "decisions";
        solutions.push_back(0);
      }
      if (alldeterminat == 0) {
        std::cout << "SLAE haven't solutions";
        solutions.push_back(-1);
      }
    }
  }
  return solutions;
}

std::string initilization() {
  // creates a text file that stores text from an image
  // returns the name of the text file
  std::string pathImage;
  getline(std::cin, pathImage);
  tesseract::TessBaseAPI tessApi;
  tessApi.Init(NULL, "eng");
  const char *pathImage_char = pathImage.c_str();
  PIX *pix = pixRead(pathImage_char); // reading an image from a file with the name,
// passed the first argument, this is The leptonica functionality
  tessApi.SetImage(pix); // we say tesseract that he should found this picture
  char *text = tessApi.GetUTF8Text(); // we recognize
  std::string text_string = std::string(text);
  // generating the name of the file where the recognized text will be written
  std::string fileName = "";
  long prefixLength;
  int last = pathImage.find('.');
  fileName = pathImage.substr(0, last);
  reverse(begin(fileName), end(fileName));
  int position = 0;
  for (int i = 0; i < fileName.length(); i++) {
    if (fileName[i] == '\\') {
      position = i;
      break;
    }
  }
  fileName = fileName.substr(0, position);
  reverse(begin(fileName), end(fileName));
  fileName = fileName + ".txt\0";
  std::ofstream ofs;
  ofs.open(fileName, std::ios::out);
  ofs.close();
  std::ofstream fs;
  fs.open(fileName, std::ios::out);
  if (!fs.is_open()) {
    std::cout << "mistake of opening" << fileName;
  } else {
    fs << text_string << "\n";
  }
  fs.close();
  pixDestroy(&pix);
  return fileName;
}