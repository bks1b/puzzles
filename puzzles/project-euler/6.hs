n = 100

result _ = show $ foldr (\i -> (+) $ i * i * (i - 1)) 0 [1..n]