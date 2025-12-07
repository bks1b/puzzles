// !include ../../util.cpp

const int RANGE = 100;
const int START = 50;

int solve(std::string &inp, bool p2) {
    int count = 0;
    int dial = START;
    for (auto &line : split_string(inp, '\n')) {
        int step = ((line[0] == 'R') * 2 - 1) * std::stoi(std::string(line.begin() + 1, line.end()));
        if (p2) {
            count -= !dial && line[0] == 'L';
            count += std::abs(dial += step) / RANGE;
            count += dial <= 0;
            dial = (dial % RANGE + RANGE) % RANGE;
        } else count += !(dial = ((dial + step) % RANGE + RANGE) % RANGE);
    }
    return count;
}