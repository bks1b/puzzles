-- !include ../math.hs

f :: Int -> Int -> Int
f n k = if mod n k == 0 && isPrime k
    then k
    else f n (k - 1)

result = show . ap f intSqrt . read