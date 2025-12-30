-- !include ../util.hs

n = 2000000

result _ = show $ foldr (\i -> (+) $ if primes ! i then 2 * i + 1 else 0) 2 [1..div (n - 1) 2]
    where primes = sieveA n