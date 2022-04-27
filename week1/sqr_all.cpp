#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

// Предварительное объявление шаблонных функций
template<typename T>
T Sqr(T x);

template <typename T> vector<T>
Sqr (const vector<T>& x);

template <typename T1, typename T2> map<T1, T2>
Sqr (const map<T1, T2>& x);

template <typename T1, typename T2> pair<T1, T2>
Sqr (const pair<T1, T2>& x);

template <typename T>
vector<T> Sqr(const vector<T>& x) {
    vector<T> y;
    for (const auto& item : x){
        y.push_back(Sqr(item));
    }
    return y;
}

template <typename T1, typename T2>
map<T1, T2> Sqr(const map<T1, T2>& x) {
    map<T1, T2> y;
    for (const auto& item : x){
        y[item.first] = Sqr(item.second);
    }
    return y;
}

template <typename T1, typename T2>
pair<T1, T2> Sqr(const pair<T1, T2>& x) {
    return {Sqr(x.first), Sqr(x.second)};
}

// Объявляем шаблонные функции
template <typename T>
T Sqr(T x) {
    return x * x;
}

int main() {
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }

    return 0;
}
