#include <iostream>
#include <stack>
#include <queue>

int main() {
    int n;
    std::cin >> n;
    if (std::cin.get() == '\r') std::cin.get();
    std::stack<int> left;
    std::queue<int> right;
    int robot = -1;
    for (int i = 0; i < n; i++) {
        char c = std::cin.get();
        if (c == 'R') robot = i;
        if (c == '*') {
            if (robot > -1) right.push(i);
            else left.push(i);
        }
    }
    int steps = 0;
    int count = 0;
    while (!(left.empty() && right.empty()) && (left.empty() || right.empty() || 2 * robot != left.top() + right.front())) {
        count++;
        if (left.empty() || (!right.empty() && 2 * robot > left.top() + right.front())) {
            steps += right.front() - robot;
            robot = right.front();
            right.pop();
        } else {
            steps += robot - left.top();
            robot = left.top();
            left.pop();
        }
    }
    std::cout << steps << " " << count << "\n";
    return 0;
}