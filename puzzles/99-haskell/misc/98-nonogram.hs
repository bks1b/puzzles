!include ./98-util.hs

-- at least 1 zero followed by x ones, total length n
getPartitions :: [Int] -> Int -> [[Int]]
getPartitions [] n = [replicate n 0]
getPartitions (x : xs) n = concat [map ((replicate i 0 ++ replicate x 1) ++) $ getPartitions xs (n - x - i) | i <- [1..n - x]]

-- remove possibilities which no longer match the grid
filterConstraints :: Game -> Game
filterConstraints game = game {
    constraints = map (\c -> c {
        possibilities = filter (\p -> all (\(a, b) -> b < 0 || a == b) $ zip p $ getConstraintTarget game c) $ possibilities c
    }) $ constraints game
}

-- fill cells which only have 1 possible value according to a constraint
fillCertain :: Game -> Game
fillCertain game = foldl (\g (c, i) -> setCell g ((cFlip c cellIdx) g i $ idx c) $ (possibilities c) !! 0 !! i) game
    $ concat
    $ map (\c -> map (\i -> (c, i))
    $ filter (\i -> (length $ nub $ map (!! i) $ possibilities c) == 1) [0..(cFlip c size) game False True])
    $ constraints game

-- [] if unsolvable, [result] if solved, otherwise deduce or brute force then recurse
solve :: Game -> [Game]
solve game = if any (\c -> length (possibilities c) < 1) $ constraints changed
    then []
    else if isNothing firstUncertain
        then [changed]
        else if game == changed
            then concat $ map (solve . setCell changed (fromJust firstUncertain)) [0, 1]
            else solve changed
    where
        changed = fillCertain $ filterConstraints game
        firstUncertain = elemIndex (-1) $ grid changed

createGame :: [[[Int]]] -> Game
createGame [rows, cols] = Game {
    rows = rows,
    cols = cols,
    grid = replicate (length cols * length rows) (-1),
    constraints = concat $ map (\c -> let a = if c then cols else rows in [Constraint {
        idx = i,
        isCol = c,
        possibilities = map tail $ getPartitions (a !! i) $ (length $ if c then rows else cols) + 1
    } | i <- [0..length a - 1]]) [False, True]
}

result = init . init . concat . map (\g -> show g ++ "\n\n") . solve . createGame . read