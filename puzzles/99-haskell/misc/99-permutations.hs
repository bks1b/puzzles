-- efficiently filters permutations
getPermutations :: Eq a => [a] -> ([a] -> Bool) -> [a] -> [[a]]
getPermutations [] f r = [r]
getPermutations a f r = concat $ map (\x -> if f $ r ++ [x] then getPermutations (filter (/= x) a) f $ r ++ [x] else []) a

-- every word is in a site which matches its length, and every location is assigned at most 1 char
verifyPermutation :: [[[Int]]] -> Positions -> [[Int]] -> [String] -> Bool
verifyPermutation sites predef locations p = (notElem False $ map (\(a, b) -> length a == length b) $ zip sites p) && allUnique positions locations
    where positions = predef ++ (getPositions $ zip sites p)

resultF words locations predef = map (zip sites) $ getPermutations words (verifyPermutation sites predef locations) []
    where sites = concat $ map (\x -> map (getSite locations x) $ filter (isStart locations x) dirs) locations

!include ./99-util.hs