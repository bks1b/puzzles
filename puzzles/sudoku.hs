-- !include ./util.hs

values = ['1'..'9']

size = length values
blockSize = intSqrt size
indices = [0..size * size - 1]
blockIndices = [0..size - 1]

pos = swap . flip divMod size
block = (. pos) . join (***) $ (blockSize *) . flip div blockSize

-- row, column, block of a given cell
connected :: Int -> [Int]
connected = map (idxBy size)
    . (\((cx, cy), (bx, by)) -> concatMap
        (flip map [(cx,), (, cy), liftA2 (,) ((bx +) . flip mod blockSize) ((by +) . flip div blockSize)] . flip id)
        blockIndices)
    . (&&&) pos block

-- possible indices of a value
possibleCells :: Char -> String -> [Int]
possibleCells v = (indices \\) . concat . flip (zipWith $ \case
    ((== v) -> True) -> connected
    '0' -> const []
    _ -> (: [])) indices

-- possible values of an index
possibleValues :: String -> Int -> String
possibleValues grid = (values \\) . map (grid !!) . connected

equivalences :: [(Int -> Bool, Char)]
equivalences = concatMap (flip map values . (,)) $ concatMap
    (\f -> map ((. f) . (==)) blockIndices)
    [idxBy blockSize . block, fst . pos, snd . pos]

-- prevent incorrect inputs from getting solved
solve :: String -> [String]
solve grid = if all (\(v, i) -> v == '0' || all (\j -> i == j || grid !! j /= v) (connected i)) $ zip grid indices
    then solveCorrect grid
    else []

-- [grid] if solved, otherwise deduce or brute force then recurse
solveCorrect :: String -> [String]
solveCorrect grid = case elemIndex '0' changed of
    Just unknown -> if changes == 0
        then concatMap (solveCorrect . flip (setAt unknown) changed) $ possibleValues changed unknown
        else solveCorrect changed
    _ -> [changed]
    where
        -- values for which only 1 index is possible in a "region"
        changedByValues = foldr (\(f, v) -> join ((. filter f . possibleCells v . snd)
            $ \case
                [i] -> (+ 1) *** setAt i v
                _ -> id))
            (0, grid) equivalences
        -- indices for which only 1 value is possible
        (changes, changed) = foldr (\i -> join ((. snd)
            $ \case
                ((== '0') . (!! i) -> False) -> id
                (flip possibleValues i -> [v]) -> (+ 1) *** setAt i v
                _ -> id))
            changedByValues indices