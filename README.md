# Usage

Run `node . <path> [inputs...] [flags...]` to run a puzzle.
The path is relative to `/puzzles`, and input paths are relative to `/inputs/<path>`.

The following modes are supported:
- Default: runs the code for each input file and prints the output
  - `--test` flag: compares each output to a local file (found by replacing the input extension with `.ans`)
    - `--quiet` flag: only prints the result of each comparison
- Interactive testing: if the input file ends with `_test.js`, the given `.js` file can write stdin to, and read stdout from the file before the suffix any number of times using the `runTest` function
  - `--quiet` flag: suppresses the I/O of the interactions

Directories can specify whether to use predefined boilerplate, or to use standalone files.
- Standalone files can read the input from stdin.
- In case of boilerplate, the file is expected to have a function which takes the input string as its only parameter, and returns the result in any format. By default, it is expected to be called `result`.
  - In case of C, the function takes a `FILE*` and prints the result.

Lines which match `!include <path>` inside a comment are replaced with the file's content at the given path (relative to the current file), and this is repeated recursively.
This is useful for sharing functions between different files.

## Advent of Code

Files are expected to have functions called `part1` and `part2`, and paths are expected to match `aoc/<year>/<day>[description].<ext>`.
An `AOC_TOKEN` entry is expected in `.env` to access puzzle inputs and part 2 descriptions, and submit solutions.
- The `-p` flag determines which part is used (`-p=1` by default, or `-p=2`)
- The `--sub` flag submits the result

Input arguments are not resolved by path, instead they refer to example code blocks:
- `<n>` reads the `n`th code block (excluding inline)
- `<n>i` reads the `n`th code block (including inline)
- `inp` reads the puzzle input (this is the default input if no arguments are given)

# Structure

The `src/dirs` directory optionally defines input and output handling for each puzzle directory.

The `src/languages` directory defines the execution commands and boilerplate code for each supported language.