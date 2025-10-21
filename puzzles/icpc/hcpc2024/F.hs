import Data.List
import Data.Maybe

n = 3

diagonal 1 = diagonal 0 . reverse
diagonal 0 = map (uncurry (!!)) . flip zip [0..]

getRowState :: [Int] -> Maybe Int
getRowState x = case nub x of
    [y] | y > 0 -> Just y
    _ -> Nothing

getState :: [[Int]] -> Int
getState x = case listToMaybe $ catMaybes states of
    Just n -> n
    Nothing -> if elem (-1) $ concat x then -1 else 0
    where
        states = concat [
            map (getRowState . flip diagonal x) [0, 1],
            map getRowState x,
            map getRowState (transpose x)]

split :: [a] -> [[a]]
split [] = []
split x = take n x : split (drop n x)

-- gets read in reverse because of (:), which is fine because of symmetry
groupVertically = foldl (curry $ map (uncurry $ flip (:)) . uncurry zip) (replicate n [])
getCell = (+ (-1)) . fromJust . flip elemIndex "._OX"
getBoard = map (groupVertically . map (map (map (getCell)) . split)) . split

main :: IO ()
main = (sequence $ replicate (n * n) getLine) >>= (
    putStrLn . (["UNFINISHED", "DRAW", "OLGA", "XENIYA"] !!) . (+ 1)
    . getState . map (map getState) . getBoard)