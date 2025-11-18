const int N = 5;

bool has_bingo(int *board, bool *marked) {
    for (int i = 0; i < N; i++) {
        bool full_row = true;
        bool full_col = true;
        for (int j = 0; j < N; j++) {
            full_row = full_row && marked[N * i + j];
            full_col = full_col && marked[i + N * j];
        }
        if (full_row || full_col) return true;
    }
    return false;
}

int get_score(int *board, bool *marked) {
    int s = 0;
    for (int i = 0; i < N * N; i++)
        if (!marked[i])
            s += board[i];
    return s;
}

void solve(FILE *inp, bool p2) {
    int *drawn = NULL;
    int drawn_len = 0;
    do {
        drawn = realloc(drawn, ++drawn_len * sizeof(int));
        fscanf(inp, "%d", drawn + drawn_len - 1);
    } while (getc(inp) != '\n');
    int **boards = NULL;
    int boards_len = 0;
    while (getc(inp) != EOF) {
        boards = realloc(boards, ++boards_len * sizeof(int*));
        boards[boards_len - 1] = malloc(N * N * sizeof(int*));
        for (int i = 0; i < N * N; i++)
            fscanf(inp, "%d", boards[boards_len - 1] + i);
        getc(inp);
    }
    bool *has_won = calloc(boards_len, sizeof(bool));
    bool **marked = malloc(boards_len * sizeof(bool*));
    for (int i = 0; i < boards_len; i++)
        marked[i] = calloc(N * N, sizeof(bool));
    int score = 0;
    for (int i = 0; i < drawn_len; i++)
        for (int j = 0; j < boards_len && (p2 || !score); j++) {
            for (int k = 0; k < N * N; k++)
                marked[j][k] = marked[j][k] || boards[j][k] == drawn[i];
            if (!has_won[j] && has_bingo(boards[j], marked[j])) {
                has_won[j] = true;
                score = drawn[i] * get_score(boards[j], marked[j]);
            }
        }
    free(drawn);
    for (int i = 0; i < boards_len; i++) {
        free(boards[i]);
        free(marked[i]);
    }
    free(boards);
    free(marked);
    free(has_won);
    printf("%d\n", score);
}

void part1(FILE *file) {
    solve(file, false);
}

void part2(FILE *file) {
    solve(file, true);
}