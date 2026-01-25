-- !include ../../sudoku.hs

readGrid :: String -> String
readGrid = filter (flip elem $ '0' : values) . map (\x -> if x == '.' then '0' else x)

showGrid :: String -> String
showGrid = intercalate "\n" . tail . concat
    . zipWith ((. (: []) . joinRow) . (:) . emptyRow) cycled
    . iterate (drop size)
    where
        cycled = concat $ replicate blockSize $ True : replicate (blockSize - 1) False
        joinRow = tail . concat . zipWith ((. (' ' :) . (: " ")) . id . bool id ('|' :)) cycled
        emptyRow = uncurry intercalate . fmap (replicate blockSize . replicate (3 * blockSize)) . bool ("|", ' ') ("+", '-')

result = intercalate "\n\n\n" . map showGrid . solve . readGrid