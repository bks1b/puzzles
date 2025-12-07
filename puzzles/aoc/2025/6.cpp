// !include ../../util.cpp

ll part1(std::string &inp) {
    auto lines = split_string(inp, '\n');
    std::string ops;
    for (char c : lines.back())
        if (c != ' ') ops.push_back(c);
    lines.pop_back();
    ll *cols = new ll[ops.size()];
    for (int i = 0; i < ops.size(); i++)
        cols[i] = ops[i] == '*';
    for (auto &line : lines) {
        auto nums = match_ints(line);
        for (int i = 0; i < ops.size(); i++)
            cols[i] = ops[i] == '*' ? cols[i] * nums[i] : cols[i] + nums[i];
    }
    ll sum = 0;
    for (int i = 0; i < ops.size(); i++) sum += cols[i];
    delete[] cols;
    return sum;
}

ll part2(std::string &inp) {
    auto lines = split_string(inp, '\n');
    std::string ops;
    for (char c : lines.back())
        if (c != ' ') ops.push_back(c);
    lines.pop_back();
    ll sum = 0;
    int op_i = ops.size();
    ll acc = -1;
    for (int i = lines[0].size() - 1; i >= 0; i--) {
        if (acc < 0) acc = ops[--op_i] == '*';
        int num = 0;
        for (int j = 0; j < lines.size(); j++)
            if (lines[j][i] != ' ')
                num = num * 10 + (lines[j][i] - '0');
        if (!num) {
            sum += acc;
            acc = -1;
        } else acc = ops[op_i] == '*' ? acc * num : acc + num;
    }
    return sum + acc;
}