-- !include ../sudoku.hs

readAll :: [String] -> [String]
readAll = fromMaybe [] . fmap (uncurry (:) . (***) concat readAll . splitAt 9 . snd) . uncons

result = show . sum . map (readN . take 3 . head . solve) . readAll . lines