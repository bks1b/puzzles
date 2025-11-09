type Positions = [([Int], Char)]
type Words = [([[Int]], String)]

dirs = [[1, 0], [0, 1]]

addDir :: Int -> [Int] -> [Int] -> [Int]
addDir c = curry $ map (\x -> (fst x) + c * (snd x)) . uncurry zip

isIntersection :: [[Int]] -> [Int] -> Bool
isIntersection locations x = notElem False $ map (\d -> elem (addDir 1 x d) locations || elem (addDir (-1) x d) locations) dirs

isStart :: [[Int]] -> [Int] -> [Int] -> Bool
isStart locations x d = (elem (addDir 1 x d) locations) && (notElem (addDir (-1) x d) locations)

getPositions :: Words -> Positions
getPositions = concat . map (uncurry zip)

sumDir :: [Int] -> Int
sumDir [x, y] = x + y

findSite :: [Int] -> [[[Int]]] -> [[Int]]
findSite l = fromJust . find (elem l)

allUnique :: Eq k => Eq a => [(k, a)] -> [k] -> Bool
allUnique vals keys = notElem False $ map (\k -> length (nub $ filter (\v -> fst v == k) vals) < 2) keys

-- !include ./99-io.hs