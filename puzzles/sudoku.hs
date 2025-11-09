-- !include ./sudoku-util.hs

-- row, column, block of a given cell
getConnected :: [String] -> Int -> [Int]
getConnected grid i = map getIdx $ concat [[(cx, j), (j, cy), (bx + mod j blockSize, by + div j blockSize)] | j <- blockIndices] where
    (cx, cy) = getPos i
    (bx, by) = getBlock i

-- possible indices of a value
getPossibleCells :: [String] -> String -> [Int]
getPossibleCells grid v = indices \\ (concat $ map (\i -> if grid !! i == v then getConnected grid i else if grid !! i == "" then [] else [i]) indices)

-- possible values of an index
getPossibleValues :: [String] -> Int -> [String]
getPossibleValues grid i = if grid !! i == "" then values \\ (map (grid !!) $ getConnected grid i) else []

setCell :: [String] -> Int -> String -> [String]
setCell grid i v = [if j == i then v else grid !! j | j <- indices]

-- [grid] if solved, otherwise deduce or brute force then recurse
solve :: [String] -> [[String]]
solve grid = if isNothing firstUnknown
    then [changed]
    else if grid == changed
        then concat $ map (solve . setCell changed (fromJust firstUnknown)) $ getPossibleValues changed $ fromJust firstUnknown
        else solve changed
    where
        -- values for which only 1 index is possible in a "region"
        changedByValues = foldl (\g v -> let possible = getPossibleCells g v in foldl
            (\h (i, f) -> let a = filter (\j -> f j == i) possible in if length a == 1 then setCell h (a !! 0) v else h) g
            $ concat $ map (\i -> map (i, ) [getBlockIdx, fst . getPos, snd . getPos]) blockIndices) grid values
        -- indices for which only 1 value is possible
        changed = foldl (\g i -> let v = getPossibleValues g i in if length v == 1 then setCell g i $ v !! 0 else g) changedByValues indices
        firstUnknown = elemIndex "" changed