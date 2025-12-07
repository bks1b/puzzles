intSqrt :: Int -> Int
intSqrt = floor . sqrt . fromIntegral

isSquare :: Int -> Bool
isSquare n = s * s == n where s = intSqrt n

splitOn :: Char -> String -> [String]
splitOn c = (\(a, b) -> case b of { (_ : r) -> a : splitOn c r; _ -> [a] }) . span (/= c)