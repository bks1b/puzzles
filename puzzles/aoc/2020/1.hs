import Data.List
import Data.Maybe

f :: Int -> Int -> [Int] -> Maybe Int
f 0 t x = if elem t x then Just t else Nothing
f _ _ [] = Nothing
f d t (x : xs) = case f (d - 1) (t - x) xs of
    Just y -> Just $ x * y
    Nothing -> f d t xs

g :: Int -> String -> String
g n = show . fromJust . f n 2020 . map read . lines

part1 = g 1
part2 = g 2