isSquare :: Int -> Bool
isSquare n = s * s == n where s = floor $ sqrt $ fromIntegral n