type Intersection = ([Int], [[Int]], [[Int]])
type Possibilities = [(String, String, Intersection)]

-- efficiently filters choice functions
getChoices :: [[a]] -> ([a] -> Bool) -> [a] -> [[a]]
getChoices [] f r = [r]
getChoices (x : xs) f r = concat $ map (\y -> if f $ r ++ [y] then getChoices xs f $ r ++ [y] else []) x

-- pairs of words which are possible at a given intersection
getPossibilities :: [String] -> Intersection -> Possibilities
getPossibilities words i@(l, s1, s2) = filter (\(a, b, _) -> length a == len1 && length b == len2 && a !! pos1 == b !! pos2) $ [(w1, w2, i) | w1 <- words, w2 <- words]
    where [(len1, pos1), (len2, pos2)] = map (\s -> (length s, sumDir $ addDir (-1) l (s !! 0))) [s1, s2]

getAssignedWords :: Possibilities -> Words
getAssignedWords = concat . map (\(w1, w2, (_, s1, s2)) -> [(s1, w1), (s2, w2)])

-- every location is assigned at most 1 char, and every word is assigned at most to 1 site
verifyChoice :: [[Int]] -> Positions -> [String] -> Possibilities -> Bool
verifyChoice locations predef words choice = allUnique (predef ++ (getPositions assigned)) locations && allUnique (map swap assigned) words
    where assigned = getAssignedWords choice

resultF words locations predef = map getAssignedWords $ getChoices possibilities (verifyChoice locations predef words) [] where
    [sitesX, sitesY] = map (\d -> map (\x -> getSite locations x d) $ filter (\x -> isStart locations x d) locations) dirs
    intersections = map (\l -> (l, findSite l sitesX, findSite l sitesY)) $ filter (isIntersection locations) locations
    possibilities = map (getPossibilities words) intersections

-- !include ./99-util.hs