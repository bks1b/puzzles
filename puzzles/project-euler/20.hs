import Data.Char

n = 100

result _ = show $ sum $ map digitToInt $ show $ product [1..n]