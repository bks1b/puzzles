// !include ../../util.cpp
// !include ../chars.cpp

const int W = 50;

bool *access(bool (*screen)[H], bool row, int a, int b) {
    return row ? screen[a] + b : screen[b] + a;
}

int get_screen(bool (*screen)[H], std::string &inp) {
    int lit = 0;
    for (auto &line : split_string(inp, '\n')) {
        auto instr = split_string(line, ' ');
        if (instr[0] == "rect") {
            std::vector<int> dim;
            for (auto &s : split_string(instr[1], 'x'))
                dim.push_back(std::stoi(s));
            for (int i = 0; i < dim[0]; i++)
                for (int j = 0; j < dim[1]; j++)
                    if (!screen[i][j]) {
                        screen[i][j] = true;
                        lit++;
                    }
        } else {
            bool row = instr[1] == "row";
            int dim = row ? W : H;
            auto nums = split_string(split_string(line, '=')[1], ' ');
            int target = std::stoi(nums[0]);
            int rot = std::stoi(nums[2]) % dim;
            bool *temp = new bool[rot];
            for (int i = dim - 1; i >= 0; i--) {
                auto p = access(screen, row, i, target);
                if (i >= dim - rot) temp[i - dim + rot] = *p;
                *p = i >= rot
                    ? *access(screen, row, i - rot, target)
                    : temp[i];
            }
            delete[] temp;
        }
    }
    return lit;
}

int part1(std::string &inp) {
    bool screen[W][H] = {};
    return get_screen(screen, inp);
}

std::string part2(std::string &inp) {
    bool screen[W][H] = {};
    get_screen(screen, inp);
    return get_str(W / CHAR_W, [screen](int x, int y) {
        return screen[x][y];
    });
}