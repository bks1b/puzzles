#include <iostream>

const char *RESULTS[] = { "UNFINISHED", "DRAW", "OLGA", "XENIYA" };

int get_state(int corner, int *board, int size) {
    auto get_same = [&](int a, int b, int c) {
        return board[corner + a] == board[corner + b] && board[corner + a] == board[corner + c]
            && board[corner + a] > 0 ? board[corner + a] : 0;
    };
    auto _or = [](int a, int b) { return a ? a : b; };
    // diagonals
    int won_by = _or(
        get_same(0, size + 1, 2 * size + 2),
        get_same(2, size + 1, 2 * size)
    );
    // columns and rows
    for (int d = 0; d < 3 && !won_by; d++)
        won_by = _or(
            get_same(d, size + d, 2 * size + d),
            get_same(size * d, size * d + 1, size * d + 2)
        );
    if (won_by) return won_by;
    for (int dx = 0; dx < 3; dx++)
        for (int dy = 0; dy < 3; dy++)
            if (board[corner + size * dy + dx] == -1)
                return -1;
    return 0;
}

int main() {
    // -1: unset, 0: whitespace (overwrite), 1: Olga, 2: Xeniya
    int board[81];
    char c;
    int i = 0;
    while ((c = getchar()) != EOF) {
        board[i] = c == '.' ? -1 : c == 'O' ? 1 : c == 'X' ? 2 : 0;
        if (board[i]) i++;
    }
    // -1: unfinished, 0: draw, 1: Olga, 2: Xeniya
    int board_states[9];
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            board_states[3 * y + x] = get_state(27 * y + 3 * x, board, 9);
    std::cout << RESULTS[get_state(0, board_states, 3) + 1] << "\n";
    return 0;
}