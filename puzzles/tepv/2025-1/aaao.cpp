#include <iostream>

const char *MGH = "aeiouy";

bool mgh(char c) {
    const char *p = MGH;
    while (*p && c != *p) p++;
    return !!*p;
}

int main() {
    char c;
    while ((c = getchar()) != EOF)
        if (mgh(tolower(c))) std::cout << c;
    std::cout << "\n";
    return 0;
}