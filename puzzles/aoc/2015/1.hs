f :: Bool -> Int -> Int -> String -> Int
f False i n x | i == length x = n
f True i (-1) _ = i
f b i n x = f b (i + 1) (if (x !! i) == '(' then n + 1 else n - 1) x

part1 = show . f False 0 0
part2 = show . f True 0 0