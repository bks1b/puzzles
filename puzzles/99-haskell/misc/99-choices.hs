type Intersection = (Pos, [[Pos]])
type Possibilities = [(String, String, Intersection)]

-- efficiently filters choice functions
choices :: [[a]] -> ([a] -> Bool) -> [[a]] -> [[a]]
choices (x : xs) f = choices xs f . concatMap (\y -> filter f $ map (: y) x)
choices _ _ = id

-- pairs of words which are possible at a given intersection
possibilities :: [String] -> Intersection -> Possibilities
possibilities words i@(l, s) = concatMap (\w1 -> map (w1,, i) $ filter ((w1 !! i1 ==) . (!! i2)) m2) m1 where
    -- index of intersection in each word
    [i1, i2] = map (uncurry (+) . addPos (-1) l . head) s
    [m1, m2] = map (flip filter words . eqLength) s

assignedWords :: Possibilities -> Words
assignedWords = concatMap (\(w1, w2, (_, s)) -> zip s [w1, w2])

-- every word is assigned to at most 1 site, and every location is assigned to at most 1 char
verifyChoice :: Positions -> Words -> Bool
verifyChoice predef ls = allUnique snd ls && allUnique fst (predef ++ positions ls)

resultF locations predef words = map assignedWords $ choices
    (map (possibilities words) intersections)
    (verifyChoice predef . assignedWords)
    [[]] where
    sites = map (\d -> map (flip (site locations) d) $ filter (flip (isStart locations) d) locations) dirs
    intersections = map (ap (,) $ flip map sites . findSite) $ filter (isIntersection locations) locations

-- !include ./99-util.hs