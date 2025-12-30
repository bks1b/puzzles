-- !include ../util.hs

f :: Int -> Int -> Int
f n k = if mod n k == 0 && isPrime k
    then k
    else f n (k - 1)

result s = show $ f (read s) $ intSqrt $ read s