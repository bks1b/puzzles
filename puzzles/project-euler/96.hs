-- !include ../sudoku.hs

readAll :: [String] -> [[String]]
readAll (x : xs) = map (\x -> if x == '0' then [] else [x]) (concat a) : readAll b
    where (a, b) = splitAt 9 xs
readAll _ = []

result = show . sum . map (readN . concat . take 3 . head . solve) . readAll . lines