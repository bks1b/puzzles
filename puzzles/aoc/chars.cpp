#include <functional>

const int CHAR_W = 5;
const int H = 6;
const std::unordered_map<ll, char> CHARS = {
    { 210797862ll, 'C' },
    { 34642991ll, 'F' },
    { 504398881ll, 'L' },
    { 504405039ll, 'E' },
    { 211068198ll, 'O' },
    { 138553905ll, 'Y' },
    { 243467310ll, 'S' },
    { 307399849ll, 'K' },
    { 307471655ll, 'R' }
};

std::string get_str(int len, std::function<bool(int, int)> f) {
    std::string str;
    for (int x = 0; x < len * CHAR_W; x += CHAR_W) {
        ll key = 0;
        for (int y = 0; y < H; y++)
            for (int dx = 0; dx < CHAR_W; dx++)
                key |= f(x + dx, y) << (y * CHAR_W + dx);
        str.push_back(CHARS.find(key)->second);
    }
    return str;
}