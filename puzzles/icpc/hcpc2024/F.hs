{-# LANGUAGE LambdaCase #-}

import Data.List
import Data.Maybe
import Control.Monad

n = 3

diagonal = zipWith (flip (!!)) [0..]

rowState :: [Int] -> Maybe Int
rowState = (\case [y] | y > 0 -> Just y; _ -> Nothing) . nub

state :: [[Int]] -> Int
state x = fromMaybe (fromMaybe 0 $ find (== -1) $ concat x) $ join $ find isJust states where
    states = map (rowState . diagonal) [x, reverse x] ++ concatMap (map rowState) [x, transpose x]

split :: [a] -> [[a]]
split [] = []
split x = uncurry (:) . fmap split . splitAt n $ x

-- gets read in reverse because of (:), which is fine because of symmetry
groupVertically = foldl' (zipWith $ flip (:)) $ replicate n []
cell = subtract 1 . fromJust . flip elemIndex "._OX"
board = (. split) $ map $ groupVertically . map (map (map cell) . split)

main :: IO ()
main = replicateM (n * n) getLine >>= 
    putStrLn . (["UNFINISHED", "DRAW", "OLGA", "XENIYA"] !!)
    . (+ 1) . state . map (map state) . board