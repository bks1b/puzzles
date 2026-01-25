import Data.Char (digitToInt)

n = 100

result _ = show $ sum $ map digitToInt $ show $ product [1..n]