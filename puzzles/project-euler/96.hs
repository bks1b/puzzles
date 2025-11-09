-- !include ../sudoku.hs

readAll :: [String] -> [[String]]
readAll [] = []
readAll (x : xs) = (map (\x -> if x == '0' then "" else [x]) $ concat $ take 9 xs) : (readAll $ drop 9 xs)

result = show . sum . map (\x -> read ((concat . take 3 . head . solve) x) :: Int) . readAll . lines