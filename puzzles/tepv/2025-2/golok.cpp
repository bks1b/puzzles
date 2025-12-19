#include <iostream>

int main() {
    int count;
    std::cin >> count;
    int score[] = { 0, 0 };
    int streak[] = { 0, 0 };
    int eq_count = 1;
    int max_streak = 0;
    while (count--) {
        int team;
        std::cin >> team;
        team--;
        if (score[team] < score[1 - team] || streak[team]) streak[team]++;
        if (++score[team] > score[1 - team] && streak[team]) max_streak = std::max(max_streak, streak[team]);
        streak[1 - team] = 0;
        if (score[team] == score[1 - team]) eq_count++;
    }
    std::cout << score[0] << " " << score[1] << "\n"
        << eq_count << "\n"
        << max_streak << "\n";
    return 0;
}