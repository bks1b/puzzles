import Data.List (uncons)
import Data.Bool (bool)
import Data.Maybe (fromJust)
import Control.Monad (ap)

insertAt :: Int -> a -> [a] -> [a]
insertAt 0 = (:)
insertAt i = (uncurry (:) .) . (. fromJust . uncons) . fmap . insertAt (i - 1)

orderings :: Int -> [[Int]]
orderings 1 = [[1]]
orderings n = concat $ zipWith
    ((. ap bool reverse [0..n - 1]) . map . flip (flip insertAt n))
    (orderings $ n - 1)
    (cycle [False, True])

main :: IO [()]
main = getLine >>= liftA2 (>>)
    (print . length)
    ((sequence .) $ map $ putStrLn . unwords . map show)
    . orderings . read