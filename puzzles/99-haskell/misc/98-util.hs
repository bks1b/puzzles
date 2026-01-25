-- !include ../../util.hs

data Constraint = Constraint {
    idx :: Int,
    isCol :: Bool,
    possibilities :: [[Int]]
}

data Game = Game {
    rows :: [[Int]],
    cols :: [[Int]],
    size :: (Int, Int),
    grid :: [Int],
    constraints :: [Constraint]
}

instance Show Game where
    show game = intercalate "\n" $ (++)
        -- cells and inputs of each row
        (zipWith ((. map (bool "_|" "X|" . (> 0)) . take (snd $ size game))
            . (.) (('|' :) . concat)
            . flip (++) . map ((' ' :) . show))
            (rows game)
            $ iterate (drop $ snd $ size game)
            $ grid game)
        -- inputs of each column
        (map (concatMap $ (' ' :) . maybe " " (show . fst) . uncons)
            $ takeWhile (not . all null)
            $ iterate (map $ drop 1)
            $ cols game)

swapIf :: Constraint -> (a, a) -> (a, a)
swapIf = bool id swap . isCol

constraintTarget :: Game -> Constraint -> [Int]
constraintTarget game c = if isCol c
    then unfoldr (\g -> if null g then Nothing else Just (g !! idx c, drop colSize g)) $ grid game
    else take colSize $ drop (idx c * colSize) $ grid game
    where colSize = snd $ size game

setCell :: Int -> Game -> Int -> Game
setCell i game v = game { grid = setAt i v $ grid game }