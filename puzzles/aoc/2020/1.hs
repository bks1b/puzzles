prod :: Int -> Int -> [Int] -> Maybe Int
prod 0 t x = if elem t x then Just t else Nothing
prod _ _ [] = Nothing
prod d t (x : xs) = case prod (d - 1) (t - x) xs of
    Just y -> Just $ x * y
    Nothing -> prod d t xs

solve :: Int -> String -> String
solve n = show . fromJust . prod n 2020 . map read . lines

part1 = solve 1
part2 = solve 2