carryDigits :: [Int] -> [Int]
carryDigits [] = []
carryDigits (x : xs) = if x > 9 then x - 10 : carryDigits (if length xs > 0 then head xs + 1 : tail xs else [1]) else x : carryDigits xs

getExpDigits :: Int -> [Int]
getExpDigits 1 = [2]
getExpDigits n = carryDigits $ map (2 *) $ getExpDigits (n - 1)

result _ = show $ sum $ getExpDigits 1000