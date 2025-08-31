#include <random>

const int w = 16;
const int h = 9;
const int count = 70;

std::random_device rd;
std::mt19937 mt(rd());

std::string result(std::string _) {
    std::uniform_int_distribution<int> dist(0, w * h - 1);
    int filled = 0;
    std::vector<std::vector<int>> grid(h, std::vector<int>(w, 0));
    while (filled < count) {
        int rand = dist(mt);
        auto cell = grid[rand / w].begin() + (rand % w);
        if (*cell == 0) {
            *cell = 1;
            filled++;
        }
    }
    std::string str = "[";
    // rows and columns
    for (int d = 0; d < 2; d++) {
        int dw = d > 0 ? h : w;
        int dh = w + h - dw;
        str += "[";
        for (int i = 0; i < dh; i++) {
            str += "[";
            // i-th row or column
            std::vector<int> vec;
            if (d > 0) {
                for (auto &r : grid) vec.push_back(r[i]);
            } else vec = grid[i];
            // get lengths of consecutive 1s
            for (int j = 0; j < dw; j++) {
                if (vec[j] != 1) continue;
                int k = j + 1;
                while (k < dw && vec[k] == 1) k++;
                str += std::to_string(k - j) + ",";
                j = k;
            }
            if (str.back() == ',') str.pop_back();
            str += "],";
        }
        str.pop_back();
        str += "],";
    }
    str.pop_back();
    str += "]";
    std::ofstream file("inputs/99-haskell/misc/98.txt");
    file << str;
    file.close();
    return str;
}