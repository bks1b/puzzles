-- !include ../math.hs

n = 20

result _ = show $ foldr (\x -> (*) $ x ^ floor (intLogBase x n)) 1 $ takeWhile (< n) primes