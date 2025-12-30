import Data.Char

n = 13

f :: String -> [Int] -> [Int]
f (x : xs) = (\(a, b) -> f xs (map ((*) $ digitToInt x) (1 : a) ++ b)) . splitAt (n - 1)
f _ = id

result = show . maximum . drop (n - 1) . flip f [] . concat . lines