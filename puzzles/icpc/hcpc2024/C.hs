import Control.Monad

readN = read :: String -> Int

insertAt :: [a] -> a -> Int -> [a]
insertAt x e 0 = e : x
insertAt (x : xs) e i = x : insertAt xs e (i - 1)

orderings :: Int -> [[Int]]
orderings 1 = [[1]]
orderings n = concat
    $ map (\(i, o) ->
        map (insertAt o n) $ [r, s] !! (mod i 2))
    $ zip [0..] $ orderings (n - 1)
    where r = [0..n - 1]; s = reverse r

main :: IO [()]
main = getLine
    >>= (return . orderings . readN)
    >>= (\x -> print (length x)
        >> sequence (map (putStrLn . unwords . map show) x))