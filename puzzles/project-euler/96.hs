-- !include ../sudoku.hs

readAll :: [String] -> [String]
readAll = maybe [] (uncurry (:) . (***) concat readAll . splitAt 9 . snd) . uncons

result = show . sum . map (read . take 3 . head . solve) . readAll . lines