n = 1000

f :: (Integer, Integer) -> Int -> Int
f (a, b) i = if length (show b) == n
    then i
    else f (b, a + b) (i + 1)

result _ = show $ f (1, 2) 3