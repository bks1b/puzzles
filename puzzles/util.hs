import Data.Function
import Control.Monad
import Data.Array (Array)
import Data.Array.ST

readN = read :: String -> Int
readL = readN . concat . map (show :: Int -> String)

intSqrt = floor . sqrt . fromIntegral
intLog = log . fromIntegral
intLogBase b = logBase (fromIntegral b) . fromIntegral

divisors :: Int -> [Int]
divisors n = n : filter ((== 0) . mod n) [1..div n 2]

isSquare :: Int -> Bool
isSquare n = s * s == n where s = intSqrt n

isPrime = null . drop 2 . divisors

primes = fix (\f (x : xs) -> x : f (filter ((0 /=) . flip mod x) xs)) [2..]

sieveA :: Int -> Array Int Bool
sieveA n = runSTArray $ newArray (1, len) True >>= \arr ->
    (forM_ [1..len] $ \i -> (readArray arr i >>=) . flip when
        $ forM_ [3 * i + 1, 5 * i + 2..len]
        $ flip (writeArray arr) False)
    >> return arr
    where len = div (n - 1) 2

splitOn :: Char -> String -> [String]
splitOn c = (\(a, b) -> case b of
    (_ : r) -> a : splitOn c r
    _ -> [a]) . span (/= c)