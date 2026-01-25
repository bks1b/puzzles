-- !include ../../util.hs

isRepeated :: String -> Int -> Bool
isRepeated n r = (n ==) $ concat $ replicate r $ take (length n `div` r) n

sumRange :: Bool -> [Int] -> Int
sumRange p2 [a, b] = sum $ filter
    ((\n -> any (isRepeated n) $ bool [2] [2..length n] p2) . show)
    [a..b + 1]

solve :: Bool -> String -> String
solve p2 = show . sum . map (sumRange p2 . map read . splitOn '-') . splitOn ','