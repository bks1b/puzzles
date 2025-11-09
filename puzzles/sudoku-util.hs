-- !include ./util.hs

values = map show [1..9]

size = length values
blockSize = intSqrt size
indices = [0..size * size - 1]
blockIndices = [0..size - 1]

getPos :: Int -> (Int, Int)
getPos i = (mod i size, div i size)

getIdx :: (Int, Int) -> Int
getIdx (x, y) = x + y * size

getBlock :: Int -> (Int, Int)
getBlock i = (f x, f y) where
    (x, y) = getPos i
    f c = blockSize * (div c blockSize)

getBlockIdx :: Int -> Int
getBlockIdx i = x + y * blockSize where (x, y) = getBlock i