#include <tuple>
#include <deque>
#include <functional>

// !include ../../util.cpp

class Intcode {
    public:
        std::deque<int> input;
        std::vector<ll> values;
        Intcode(std::string &text, std::deque<int> i, std::unordered_map<int, ll> predef = {}): input(i) {
            for (auto s : split_string(text, ','))
                values.push_back(predef.contains(values.size()) ? predef[values.size()] : std::stol(s));
            opcodes = {
                { [](ll *v) { return v[0] + v[1]; }, OpType::Write, 3 },
                { [](ll *v) { return v[0] * v[1]; }, OpType::Write, 3 },
                { [this](ll *_) { int x = input.front(); input.pop_front(); return x; }, OpType::Write, 1 },
                { [](ll *v) { return v[0]; }, OpType::Output, 1 },
                { [this](ll *v) { idx = v[0] == 0 ? idx + 3 : v[1]; return 0; }, OpType::Index, 2 },
                { [this](ll *v) { idx = v[0] == 0 ? v[1] : idx + 3; return 0; }, OpType::Index, 2 },
                { [](ll *v) { return v[0] < v[1] ? 1 : 0; }, OpType::Write, 3 },
                { [](ll *v) { return v[0] == v[1] ? 1 : 0; }, OpType::Write, 3 },
                { [this](ll *v) { relative_base += v[0]; return 0; }, OpType::None, 1 }
            };
        }
        std::vector<ll> step(int until = 0) {
            std::vector<ll> output;
            while (idx < values.size() && (!until || output.size() < until)) { 
                std::string instr = std::to_string(values[idx]);
                pad_start(instr, 5, '0');
                int op_i = std::stoi(std::string(1, instr[3]) + instr[4]) - 1;
                if (op_i < 0 || op_i >= opcodes.size()) break;
                auto [op_f, op_type, op_len] = opcodes[op_i];
                auto get_idx = [this, &instr](int j) {
                    return values[idx + j + 1] + (instr[2 - j] == '2' ? relative_base : 0);
                };
                ll *args = new ll[op_len];
                for (int j = 0; j < op_len; j++) args[j] = instr[2 - j] == '1'
                    ? values[idx + j + 1]
                    : get_idx(j) >= values.size()
                        ? 0
                        : values[get_idx(j)];
                ll val = op_f(args);
                delete[] args;
                if (op_type == OpType::Write) {
                    int w_i = get_idx(op_len - 1);
                    if (w_i >= values.size()) values.resize(w_i + 1, 0);
                    values[w_i] = val;
                }
                if (op_type == OpType::Output) output.push_back(val);
                if (op_type != OpType::Index) idx += op_len + 1;
            }
            return output;
        }
    private:
        enum class OpType { Write, Index, Output, None };
        std::vector<std::tuple<std::function<ll(ll*)>, OpType, int>> opcodes;
        int relative_base = 0;
        int idx = 0;
};