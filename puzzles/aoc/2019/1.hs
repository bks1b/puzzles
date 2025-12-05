f :: Int -> Int
f x = div x 3 - 2

f2 :: Int -> Int
f2 0 = 0
f2 x = v + f2 v where v = if f x >= 0 then f x else 0

sumF :: (Int -> Int) -> String -> String
sumF x = show . sum . map x . map read . lines

part1 = sumF f
part2 = sumF f2