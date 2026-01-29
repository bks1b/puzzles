#include <iostream>
#include <algorithm>

const char *KEYBOARD[] = {
    "qwertyuiop[",
    "asdfghjkl;",
    "zxcvbnm,"
};

int main() {
    bool offsets[] = { true, true, true };
    std::string result[] = { "", "", "" };
    char c;
    while ((c = std::cin.get()) != EOF) {
        int row = 0;
        int col = 0;
        while (row < 3 && KEYBOARD[row][col] != c)
            if (KEYBOARD[row][++col] == '\0') {
                col = 0;
                row++;
            }
        if (row == 3) {
            std::cout << "0\n";
            return 0;
        }
        if (!col) offsets[2] = false;
        if (KEYBOARD[row][col + 1] == '\0') offsets[0] = offsets[1] = false;
        else if (KEYBOARD[row][col + 2] == '\0') offsets[0] = false;
        for (int i = 0; i < 3; i++)
            if (offsets[i])
                result[i] += KEYBOARD[row][col + 1 - i];
    }
    std::cout << (offsets[0] + offsets[1] + offsets[2]) << "\n";
    std::sort(result, result + 3);
    for (int i = 0; i < 3; i++)
        if (offsets[i])
            std::cout << result[i] << "\n";
    return 0;
}