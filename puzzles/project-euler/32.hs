-- !include ../util.hs

n = 9

subsets :: [Int] -> [[[Int]]]
subsets a@[x] = [[[]], [a]]
subsets (x : xs) = ([[]] :) $ (++ [[x : xs]])
    $ map (\(a, b) -> map (x :) a ++ b) $ zip s $ tail s
    where s = subsets xs

eq :: ([Int], [Int]) -> Int -> Bool
eq (a, b) = (==) $ readL a * readL b

validPerms :: [Int] -> Int
validPerms s = foldr
    (\r -> (+) $ if any (\q -> any (flip eq r . flip splitAt q) range) rest then r else 0)
    0 $ map readL $ permutations s where
    rest = permutations $ filter (flip notElem s) [1..n]
    range = [1..n - length s - 1]

result _ = show $ foldl' (\a -> (a +) . foldl' (\b -> (b +) . validPerms) 0) 0
    $ drop (div n 2) $ subsets [1..n]