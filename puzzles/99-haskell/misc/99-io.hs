getLocations :: String -> Int -> Int -> ([[Int]], Positions)
getLocations [] _ _ = ([], [])
getLocations ('\n' : xs) x y = getLocations xs 0 (y + 1) 
getLocations (s : xs) x y = ((if s == ' ' then [] else [[x, y]]) ++ a, (if elem s ". " then [] else [([x, y], s)]) ++ b) where (a, b) = getLocations xs (x + 1) y

getSite :: [[Int]] -> [Int] -> [Int] -> [[Int]] 
getSite a x d = if elem next a then x : getSite a next d else [x] where next = addDir 1 x d

readInput :: String -> ([String], String)
readInput x = case find (\i -> (take 2 $ drop i x) == "\n\n") [0..length x - 1] of
    Just i -> (lines $ take i x, drop (i + 2) x)
    Nothing -> error "Double linebreak expected"

printOutput :: String -> Int -> Int -> Positions -> String
printOutput "" _ _ _ = ""
printOutput ('\n' : cs) x y r = '\n' : (printOutput cs 0 (y + 1) r)
printOutput (c : cs) x y result = (case find (\r -> fst r == [x, y]) result of
    Just r -> snd r
    Nothing -> c) : (printOutput cs (x + 1) y result)

resultF :: [String] -> [[Int]] -> Positions -> [Words]
result inp = drop 2 $ concat $ map (\x -> "\n\n" ++ (printOutput framework 0 0 $ (++) predef $ getPositions $ x)) $ resultF words locations predef where
    (words, framework) = readInput inp
    (locations, predef) = getLocations framework 0 0