// !include ../../util.cpp

const int W = 50;
const int H = 6;
const int T = 5;
const std::unordered_map<ll, char> CHARS = {
    { 210797862ll, 'C' },
    { 34642991ll, 'F' },
    { 504398881ll, 'L' },
    { 504405039ll, 'E' },
    { 211068198ll, 'O' },
    { 138553905ll, 'Y' },
    { 243467310ll, 'S' }
};

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
    std::string res;
    for (int x = 0; x < W; x += T) {
        ll r = 0;
        for (int y = 0; y < H; y++)
            for (int dx = 0; dx < T; dx++)
                r |= screen[x + dx][y] << (y * T + dx);
        res += CHARS.find(r)->second;
    }
    return res;
}