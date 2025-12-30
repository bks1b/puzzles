n = 1000

carryDigits :: [Int] -> [Int]
carryDigits a@[x] = if x > 9 then [mod x 10, div x 10] else a
carryDigits (x : xs) = mod x 10 : carryDigits (head xs + div x 10 : tail xs)

result _ = show $ sum $ (!! n) $ iterate (carryDigits . map (2 *)) [1]