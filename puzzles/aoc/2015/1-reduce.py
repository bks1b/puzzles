from functools import reduce

def f(p2):
    return lambda inp: reduce(
        lambda x, c: x if p2 and x[0] == -1 else (x[0] + (1 if c[1] == '(' else -1), c[0] + 1),
        enumerate(inp),
        (0, 0)
    )[1 if p2 else 0]

part1 = f(False)
part2 = f(True)