-- !include ../util.hs

d = 2

simplify :: Int -> Int -> Maybe Int
simplify n m = case foldr delete (show n) (show m) of
    [] -> Nothing
    x -> let n2 = read x in
        if n == n2 || (mod n 10 == 0 && n2 == div n 10)
            then Nothing
            else Just n2

result _ = show $ div denom (gcd num denom) where
    list = concat $ map
        (\n -> map (n,) $ filter
            (\m -> any (\[n2, m2] -> n * m2 == n2 * m) $ sequence [simplify n m, simplify m n])
            [n + 1..10 ^ d - 1])
        [10 ^ (d - 1)..10 ^ d - 1]
    num = product $ map fst list
    denom = product $ map snd list