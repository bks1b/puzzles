f :: Int -> Int -> Bool -> String -> Int
f _ n False [] = n
f i (-1) True _ = i
f i n p2 (x : xs) = f (i + 1) (if x == '(' then n + 1 else n - 1) p2 xs

solve = (show .) . f 0 0