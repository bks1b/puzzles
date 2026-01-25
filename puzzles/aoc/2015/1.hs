f :: Int -> Int -> Bool -> String -> Int
f i (-1) True _ = i
f i n p2 (x : xs) = f (i + 1) (if x == '(' then n + 1 else n - 1) p2 xs
f _ n False _ = n

solve = (show .) . f 0 0