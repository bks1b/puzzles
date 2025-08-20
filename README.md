# Usage

Run `node . <path> <inputs...>` to run a puzzle. The path is relative to `puzzles`, and input paths are relative to `inputs/<path>`.

The file is inserted into a predefined file to reduce boilerplate, then compiled and/or executed based on its extension.

The file is expected to have a function which takes the input string as its only parameter. By default, it's expected to be called `result`.

Lines which match `!include <path>` are replaced with the file's content at the given path (relative to the current file), and this is repeated recursively. This is useful for sharing functions between different files.

Advent of Code support:
- Files are expected to have functions called `part1` and `part2`, and paths are expected to match `aoc/<year>/<day>[description].<ext>`
- The `-p` flag determines which part is used (`-p=1` by default, or `-p=2`)
- The `--sub` flag submits the result
- Input arguments are not resolved by path, instead they refer to example code blocks:
  - `<n>` reads the `n`th code block (excluding inline)
  - `<n>i` reads the `n`th code block (including inline)
  - `inp` reads the puzzle input (this is the default input if no arguments are given)
- An `AOC_TOKEN` entry is expected in `.env` to access puzzle inputs and part 2 descriptions, and submit solutions

Examples:
- `node . aoc/2015/1-loop.cpp 4i 5i inp -p=1 --sub`
- `node . 99-haskell/misc/99-permutations.hs 99-1.txt 99-2.txt 99-3.txt 99-4.txt`

# Structure

The `src/dirs` directory optionally defines input and output handling for each puzzle directory.

The `src/languages` directory defines compilation/execution and input reading for each supported language.