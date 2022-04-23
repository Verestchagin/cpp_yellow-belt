#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
    Matrix(){
        n = 0;
        m = 0;
    }

    Matrix(const int& num_rows, const int& num_cols){
        n = num_rows;
        m = num_cols;
    }

    void reset(const int& new_n, const int& new_m) {
        n = new_n;
        m = new_m;

    }

private:
    int n;
    int m;
    vector<vector<int>> matrx;
};

istream& operator>> (ostream& stream, const Matrix& x) {
    int n, m;

}

istream& operator<< (ostream& stream, const Matrix& x) {
    int n, m;

}
// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

int main() {
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}
