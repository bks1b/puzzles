-- !include ../util.hs

n = 9999

f ((i, d) : xs) = (f xs +) $ if elem (d, i) xs then i + d else 0
f _ = 0

result _ = show $ f $ map (\i -> (i, sum (divisors i) - i)) [1..n]