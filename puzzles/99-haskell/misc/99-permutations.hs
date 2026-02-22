perms :: [a] -> ([(a, b)] -> Bool) -> [(a, b)] -> [b] -> [[(a, b)]]
perms (x : xs) f r = concatMap (uncurry $ ap (bool (const []) . perms xs f) f . (: r) . (x,)) . holes
perms _ _ r = const [r]

-- every word is in a site which matches its length, and every location is assigned to at most 1 char
verifyPermutation :: Positions -> Words -> Bool
verifyPermutation predef ls = all (uncurry eqLength) ls && allUnique fst (predef ++ positions ls)

resultF locations predef = perms
    (concatMap (\x -> map (site locations x) $ filter (isStart locations x) dirs) locations)
    (verifyPermutation predef)
    []

-- !include ./99-util.hs