f :: Int -> Int
f = subtract 2 . flip div 3

f2 :: Int -> Int
f2 0 = 0
f2 x = ap (+) f2 . max 0 . f $ x

solve :: Bool -> String -> String
solve = (. map read . lines) . (.) (show . sum) . map . bool f f2