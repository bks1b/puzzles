const int n = 16;

long result(std::string _) {
    long sum = 0;
    for (long i = 1; i * i < std::pow(10, n); i++) {
        long sq = i * i;
        std::string str = std::to_string(sq);
        for (int j = 1; j < str.size(); j++) {
            if (str[j] != '0' && i == std::stol(str.substr(0, j)) + std::stol(str.substr(j))) {
                sum += i * i;
                break;
            }
        }
    }
    return sum;
}