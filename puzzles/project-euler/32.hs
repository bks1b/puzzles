-- !include ../util.hs

n = 9

subsets :: [Int] -> [[[Int]]]
subsets a@(x : xs) = ([[]] :) $ (++ [[a]])
    $ ap (zipWith $ (++) . map (x :)) tail
    $ subsets xs
subsets _ = []

eq :: ([Int], [Int]) -> Int -> Bool
eq = (==) . uncurry (on (*) readL)

validPerms :: [Int] -> Int
validPerms s = foldr
    ((\r -> (+) $ if any (\q -> any (flip eq r . flip splitAt q) range) rest then r else 0) . readL)
    0 $ permutations s where
    rest = permutations $ filter (flip notElem s) [1..n]
    range = [1..n - length s - 1]

result _ = show $ foldl' (foldl' (\b -> (b +) . validPerms)) 0 $ drop (div n 2) $ subsets [1..n]