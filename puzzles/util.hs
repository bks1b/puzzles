intSqrt :: Int -> Int
intSqrt = floor . sqrt . fromIntegral

isSquare :: Int -> Bool
isSquare n = s * s == n where s = intSqrt n