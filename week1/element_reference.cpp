#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

template <typename T1, typename T2>
T2& GetRefStrict(map<T1, T2>& m, T1 key) {
    try{
        return m.at(key);
    }
    catch (exception& ex) {
        throw runtime_error("No such key");
    }
}

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue

    return 0;
}
