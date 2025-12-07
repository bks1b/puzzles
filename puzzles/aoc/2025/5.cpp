// !include ../../util.cpp

auto read(std::string &inp) {
    std::vector<std::pair<ll, ll>> data;
    std::vector<ll> queries;
    bool second = false;
    for (auto &l : split_string(inp, '\n')) {
        if (l.size() == 0) second = true;
        else if (second) queries.push_back(std::stoll(l));
        else {
            auto points = split_string(l, '-');
            data.push_back({ std::stoll(points[0]), std::stoll(points[1]) });
        }
    }
    return std::pair { data, queries };
}

int part1(std::string &inp) {
    auto [data, queries] = read(inp);
    int sum = 0;
    for (ll q : queries) {
        int i = 0;
        while (i < data.size() && (q < data[i].first || q > data[i].second)) i++;
        sum += i < data.size();
    }
    return sum;
}

ll part2(std::string &inp) {
    auto [data, _] = read(inp);
    std::sort(data.begin(), data.end());
    ll sum = 0;
    for (int i = 0; i < data.size();) {
        auto [start, end] = data[i];
        int j = i + 1;
        while (j < data.size() && data[j].first <= end)
            end = std::max(end, data[j++].second);
        sum += end - start + 1;
        i = j;
    }
    return sum;
}