n = 1000

carryDigits :: [Int] -> [Int]
carryDigits a@[x] = if x > 9 then [mod x 10, div x 10] else a
carryDigits (x : y : ys) = mod x 10 : carryDigits (y + div x 10 : ys)

result _ = show $ sum $ (!! n) $ iterate (carryDigits . map (2 *)) [1]