import Control.Monad (replicateM_)

f [y, x] = (m - 1) ^ 2 + m + (x - y) * (2 * mod m 2 - 1) where m = max x y

main = readLn >>= flip replicateM_ (getLine >>= print . f . map read . words)