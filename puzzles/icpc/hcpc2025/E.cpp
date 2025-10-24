#include <iostream>
#include <algorithm>
#include <set>

std::string rotate(std::string &str, int w, int h) {
    std::string result = "";
    for (int x = w - 1; x >= 0; x--)
        for (int y = 0; y < h; y++)
            result.push_back(str[y * w + x]);
    return result;
}

int main() {
    int inp_rows, inp_cols;
    std::cin >> inp_rows >> inp_cols;
    auto lines = new std::string[inp_rows];
    int win_w = -1, win_h = -1;
    // win_w: second index of '#' in the second column
    // win_h: second index of a column with only '#'s
    for (int i = 0; i < inp_rows; i++) {
        std::cin >> lines[i];
        if (lines[i][1] == '#' && win_h < 0 && i > 0) win_h = i - 1;
        if (i == 1) win_w = std::distance(
            lines[i].begin() + 1,
            std::find(lines[i].begin() + 1, lines[i].end(), '#')
        );
    }
    int cols = (inp_cols - 1) / (win_w + 1);
    int rows = (inp_rows - 1) / (win_h + 1);
    auto windows = new std::string[rows * cols]();
    for (int y = 0; y < rows; y++)
        for (int dy = 1 + y * (win_h + 1); dy <= win_h + y * (win_h + 1); dy++)
            for (int x = 0; x < cols; x++)
                windows[y * cols + x] += std::string(
                    lines[dy].begin() + x * (win_w + 1) + 1,
                    lines[dy].begin() + (x + 1) * (win_w + 1)
                );
    delete[] lines;
    // represent each pattern with the rotation which results in the "smallest" string
    std::set<std::string> patterns;
    for (int i = 0; i < rows * cols; i++) {
        auto r1 = rotate(windows[i], win_w, win_h);
        auto r2 = rotate(r1, win_h, win_w);
        patterns.insert(win_w == win_h
            ? std::min({ windows[i], r1, r2, rotate(r2, win_w, win_h) })
            : std::min({ windows[i], r2 }));
    }
    delete[] windows;
    std::cout << patterns.size() << "\n";
    return 0;
}