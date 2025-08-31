data Constraint = Constraint {
    idx :: Int,
    isCol :: Bool,
    possibilities :: [[Int]]
} deriving Eq

data Game = Game {
    rows :: [[Int]],
    cols :: [[Int]],
    grid :: [Int],
    constraints :: [Constraint]
} deriving Eq

instance Show Game where
    show game = init $ concat (
        [
            -- cells and inputs of each row
            "|"
            ++ concat [(if (grid game) !! (cellIdx game x y) > 0 then "X" else "_") ++ "|" | x <- [0..size game False True]]
            ++ concat (map (\r -> " " ++ show r) $ (rows game) !! y) ++ "\n"
            | y <- [0..size game True False]
        ] ++ [
            -- inputs of each column
            " "
            ++ (concat $ map (\c -> (if j < length c then show $ c !! j else " ") ++ " ") $ cols game)
            ++ "\n"
            | j <- [0..(maximum $ map length $ cols game) - 1]
        ])

cFlip :: Constraint -> (Game -> a -> a -> b) -> (Game -> a -> a -> b)
cFlip c f = (if isCol c then flip else id) . f

size :: Game -> Bool -> Bool -> Int
size game r _ = (length $ (if r then rows else cols) game) - 1

cellIdx :: Game -> Int -> Int -> Int
cellIdx game x y = x + y * (length $ cols game)

-- row or column
getConstraintTarget :: Game -> Constraint -> [Int]
getConstraintTarget game c = [(grid game) !! ((cFlip c cellIdx) game i (idx c)) | i <- [0..(cFlip c size) game False True]]

setCell :: Game -> Int -> Int -> Game
setCell game i v = game {
    grid = [if j == i then v else (grid game) !! j | j <- [0..length (grid game) - 1]]
}