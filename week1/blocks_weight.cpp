#include <iostream>

using namespace std;

int main() {
    uint n;
    uint16_t r;
    cin >> n >> r;
    uint64_t w, h, d;
    uint64_t m = 0;
    for (size_t i = 0; i < n; ++i){
        cin >> w >> h >> d;
        m += w * h * d * r;
    }
    cout << m;
    return 0;
}
