const int DIGITS[] = {
    0b1110111, 0b0010010, 0b1011101, 0b1011011, 0b0111010,
    0b1101011, 0b1101111, 0b1010010, 0b1111111, 0b1111011
};
const int DIGIT_COUNT = 10;
const int SEGMENT_COUNT = 7;
const int OUTPUT = 4;

bool match_pattern(int pat, int digit, int *assigned) {
    for (int i = 0; i < SEGMENT_COUNT; i++)
        if (assigned[i] > -1 && ((pat >> i) ^ (digit >> assigned[i])) & 1)
            return false;
    return true;
}

bool backtrack(int *patterns, int *assigned, int next) {
    if (next == SEGMENT_COUNT) return true;
    for (int i = 0; i < DIGIT_COUNT; i++) {
        int j = 0;
        while (j < DIGIT_COUNT && !match_pattern(patterns[i], DIGITS[j], assigned)) j++;
        if (j == DIGIT_COUNT) return false;
    }
    for (int i = 0; i < SEGMENT_COUNT; i++) {
        int j = 0;
        while (j < next && assigned[j] != i) j++;
        if (j < next) continue;
        assigned[next] = i;
        if (backtrack(patterns, assigned, next + 1)) return true;
        assigned[next] = -1;
    }
    return false;
}

int read_digit(FILE *inp, char *c) {
    int r = 0;
    while ((*c = getc(inp)) != ' ' && *c != '\n' && *c != EOF)
        r |= 1 << ('a' - *c + SEGMENT_COUNT - 1);
    return r;
}

void solve(FILE *inp, bool p2) {
    int sum = 0;
    char last_char;
    do {
        int patterns[DIGIT_COUNT];
        for (int i = 0; i < DIGIT_COUNT; i++) patterns[i] = read_digit(inp, &last_char);
        int assigned[SEGMENT_COUNT];
        for (int i = 0; i < SEGMENT_COUNT; i++)
            assigned[i] = -1;
        backtrack(patterns, assigned, 0);
        getc(inp);
        getc(inp);
        int num = 0;
        for (int i = 0; i < OUTPUT; i++) {
            int r = read_digit(inp, &last_char);
            int dig = 0;
            while (!match_pattern(r, DIGITS[dig], assigned)) dig++;
            if (p2) num = num * 10 + dig;
            else num += dig == 1 || dig == 4 || dig == 7 || dig == 8;
        }
        sum += num;
    } while (last_char != EOF);
    printf("%d\n", sum);
}

void part1(FILE *inp) {
    return solve(inp, false);
}

void part2(FILE *inp) {
    return solve(inp, true);
}