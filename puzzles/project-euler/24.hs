n = 1000000
arr = [0..9]

permute :: Int -> Int -> [Int] -> [Int]
permute _ _ a@[x] = a
permute f k a = x : permute (div f $ length a - 1) (mod k f) (delete x a)
    where x = a !! div k f

result _ = concat $ map show $ permute (product [1..length arr - 1]) (n - 1) arr