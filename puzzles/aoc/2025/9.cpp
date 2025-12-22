// !include ../../util.cpp

typedef std::vector<std::pair<ll, ll>> points_t;

bool no_edges(points_t &points, ll left, ll top, ll right, ll bottom) {
    for (int i = 0; i < points.size(); i++) {
        auto [x, y] = points[i];
        auto [next_x, next_y] = points[(i + 1) % points.size()];
        if (x > next_x) std::swap(x, next_x);
        if (y > next_y) std::swap(y, next_y);
        if (x == next_x
            ? left < x && x < right && std::max(y, top) < std::min(next_y, bottom)
            : top < y && y < bottom && std::max(x, left) < std::min(next_x, right))
            return false;
    }
    return true;
}

ll solve(std::string &inp, bool p2) {
    points_t points;
    for (auto &line : split_string(inp, '\n')) {
        auto parts = split_string(line, ',');
        points.push_back({ std::stoll(parts[0]), std::stoll(parts[1]) });
    }
    ll max_area = 0;
    for (int i = 0; i < points.size(); i++)
        for (int j = i + 1; j < points.size(); j++) {
            auto [left, top] = points[i];
            auto [right, bottom] = points[j];
            if (right < left) std::swap(right, left);
            if (bottom < top) std::swap(bottom, top);
            ll area = (right - left + 1) * (bottom - top + 1);
            if (area > max_area && (!p2 || no_edges(points, left, top, right, bottom)))
                max_area = area;
        }
    return max_area;
}