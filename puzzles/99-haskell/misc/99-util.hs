-- !include ../../util.hs

type Pos = (Int, Int)
type Positions = [(Pos, Char)]
type Words = [([Pos], String)]

dirs = [(1, 0), (0, 1)]

addPos :: Int -> Pos -> Pos -> Pos
addPos c (x, y) = (x +) . (c *) *** (y +) . (c *)

-- does a given cell continue in both directions
isIntersection :: [Pos] -> Pos -> Bool
isIntersection ls x = all (\d -> any (flip elem ls . flip (flip addPos x) d) [-1, 1]) dirs

-- is a given cell the start of a row or column word
isStart :: [Pos] -> Pos -> Pos -> Bool
isStart ls x d = elem (addPos 1 x d) ls && notElem (addPos (-1) x d) ls

positions :: Words -> Positions
positions = concatMap $ uncurry zip

findSite :: Pos -> [[Pos]] -> [Pos]
findSite = (fromJust .) . find . elem

-- every key has only 1 corresponding unique value
allUnique :: (Eq a, Eq b) => (a -> b) -> [a] -> Bool
allUnique = (. nub) . ap (==) . nubBy . on (==)

-- !include ./99-io.hs