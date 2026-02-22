queens :: Int -> [[Int]]
queens = flip (.) (enumFromTo 1 &&& flip (!!)) $ uncurry $ flip id
    . flip iterate [[]]
    . concatMap
    . flip (\l -> map (: l) . filter (\y ->
        notElem y l && all (uncurry (/=) . fmap (abs . (y -))) (zip [1..] l)) . (\\ l))

result = show . length . queens . read