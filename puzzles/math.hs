import Data.Array (Array, (!))
import Data.Array.ST

-- !include ./util.hs

divisors :: Int -> [Int]
divisors n = n : filter ((== 0) . mod n) [1..div n 2]

isSquare :: Int -> Bool
isSquare = ap (==) $ join (*) . intSqrt

isPrime = lengthEq 2 . divisors

primes = fix (\f (x : xs) -> x : f (filter ((0 /=) . flip mod x) xs)) [2..]

sieveA :: Int -> Array Int Bool
sieveA n = runSTArray $ newArray (1, len) True >>= \arr ->
    forM_ [1..len] (\i -> (readArray arr i >>=) . flip when
        $ forM_ [3 * i + 1, 5 * i + 2..len]
        $ flip (writeArray arr) False)
    >> return arr
    where len = div (n - 1) 2