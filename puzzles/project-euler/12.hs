-- !include ../util.hs

n = 500

f :: Int -> Int -> Int -> Int
f p1 p2 i
    | p1 * p2 > n = (i - 2) * (i - 1) `div` 2
    | otherwise = f p2 (length $ divisors $ div i $ 2 - mod i 2) (i + 1)

result _ = show $ f 1 1 1