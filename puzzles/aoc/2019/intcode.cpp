#include <tuple>
#include <functional>

// !include ../../util.cpp

std::vector<long> intcode(std::string &text, std::vector<int> input, std::unordered_map<int, long> predef = {}, bool ret_vals = false) {
    int relative_base = 0;
    int i = 0;
    std::vector<std::tuple<std::function<long(long*)>, std::string, int>> ops = {
        { [](long *v) { return v[0] + v[1]; }, "write", 3 },
        { [](long *v) { return v[0] * v[1]; }, "write", 3 },
        { [&input](long *_) { int x = input[0]; input.erase(input.begin()); return x; }, "write", 1 },
        { [](long *v) { return v[0]; }, "out", 1 },
        { [&i](long *v) { i = v[0] == 0 ? i + 3 : v[1]; return 0; }, "idx", 2 },
        { [&i](long *v) { i = v[0] == 0 ? v[1] : i + 3; return 0; }, "idx", 2 },
        { [](long *v) { return v[0] < v[1] ? 1 : 0; }, "write", 3 },
        { [](long *v) { return v[0] == v[1] ? 1 : 0; }, "write", 3 },
        { [&relative_base](long *v) { relative_base += v[0]; return 0; }, "", 1 }
    };
    std::vector<long> values;
    for (auto s : split_string(text, ','))
        values.push_back(predef.contains(values.size()) ? predef[values.size()] : std::stol(s));
    std::vector<long> output;
    int j = 0;
    while (i < values.size()) {
        std::string instr = std::to_string(values[i]);
        pad_start(instr, 5, '0');
        int op_i = std::stoi(std::string(1, instr[3]) + instr[4]) - 1;
        if (op_i < 0 || op_i >= ops.size()) break;
        auto [op_f, op_type, op_len] = ops[op_i];
        auto get_idx = [&values, &instr, i, relative_base](int j) {
            return values[i + j + 1] + (instr[2 - j] == '2' ? relative_base : 0);
        };
        long args[op_len];
        for (int j = 0; j < op_len; j++) args[j] = instr[2 - j] == '1'
            ? values[i + j + 1]
            : get_idx(j) >= values.size()
                ? 0
                : values[get_idx(j)];
        long val = op_f(args);
        if (op_type == "write") {
            int w_i = get_idx(op_len - 1);
            if (w_i >= values.size()) values.resize(w_i + 1, 0);
            values[w_i] = val;
        }
        if (op_type == "out") output.push_back(val);
        if (op_type != "idx") i += op_len + 1;
    }
    return ret_vals ? values : output;
}