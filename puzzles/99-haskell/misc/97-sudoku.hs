-- !include ../../sudoku.hs

readGrid :: String -> [String]
readGrid [] = []
readGrid (x : xs) = (if x == '.' then [""] else if elem [x] values then [[x]] else []) ++ readGrid xs

showGrid :: [String] -> String
showGrid grid = init $ concat $ map ((++ "\n") . tail . init . init) $ init $ concat [
    concat [let v = grid !! (getIdx (x, y)) in
        " " ++ v ++ " " ++ (if mod (x + 1) blockSize == 0 then "|" else "") | x <- blockIndices]
    : let [c1, c2] = if mod (y + 1) blockSize == 0 then "-+" else " |" in
        [concat $ replicate blockSize $ (replicate (3 * blockSize) c1) ++ [c2]]
    | y <- blockIndices]

result = init . init . init . concat . map ((++ "\n\n\n") . showGrid) . solve . readGrid