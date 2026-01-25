-- !include ./98-util.hs

-- at least 1 zero followed by x ones, total length n
partitions :: [Int] -> Int -> [[Int]]
partitions (x : xs) n = concatMap (\i -> map ((replicate i 0 ++) . (replicate x 1 ++)) $ partitions xs (n - x - i)) [1..n - x]
partitions _ n = [replicate n 0]

-- remove possibilities which no longer match the grid
filterConstraints :: Game -> Game
filterConstraints game = game {
    constraints = map (\c -> c {
        possibilities = filter (\p -> all (\(a, b) -> b < 0 || a == b) $ zip p $ constraintTarget game c) $ possibilities c
    }) $ constraints game
}

-- fill cells which only have 1 possible value according to a constraint
fillCertain :: Game -> (Int, Game)
fillCertain game = foldr (\(c, (i, v)) -> (***) (+ 1) $ flip (setCell $ idxBy (snd $ size game) $ swapIf c (i, idx c)) v) (0, game)
    $ concatMap (\c -> map ((c,) . fmap (head . head))
        $ filter (lengthEq 1 . nub . map head . snd)
        $ zip [0..snd (swapIf c $ size game) - 1]
        $ iterate (map tail) $ possibilities c)
    $ constraints game

solve :: Game -> [Game]
solve game = if any (null . possibilities) $ constraints changed
    then []
    else case elemIndex (-1) $ grid changed of
        Just unknown -> if changes == 0
            then concatMap (solve . setCell unknown changed) [0, 1]
            else solve changed
        _ -> [changed]
    where (changes, changed) = fillCertain $ filterConstraints game

createGame :: [[[Int]]] -> Game
createGame [rows, cols] = Game {
    rows = rows,
    cols = cols,
    grid = replicate (uncurry (*) len) (-1),
    size = len,
    constraints = concatMap (\(c, a) -> zipWith (\v i -> Constraint {
        idx = i,
        isCol = c,
        possibilities = map tail $ partitions v $ (if c then fst else snd) len + 1
    }) a [0..]) [(False, rows), (True, cols)]
} where len = (length rows, length cols)

result = intercalate "\n\n\n" . map show . solve . createGame . read