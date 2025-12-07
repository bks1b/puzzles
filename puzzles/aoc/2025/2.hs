-- !include ../../util.hs

isRepeated :: String -> Int -> Bool
isRepeated n r = (n ==) . concat $ replicate r $ take (length n `div` r) n

sumRange :: Bool -> [Int] -> Int
sumRange p2 [a, b] = sum $ filter
    (\n -> any (isRepeated $ show n) (if p2 then [2..length $ show n] else [2]))
    [a..b + 1]

solve :: Bool -> String -> String
solve p2 = show . sum . map (sumRange p2 . map read . splitOn '-') . splitOn ','