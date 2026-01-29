intSqrt = floor . sqrt . fromIntegral
intLog = log . fromIntegral
intLogBase b = logBase (fromIntegral b) . fromIntegral

splits = zip . inits <*> tails

idxBy :: Int -> (Int, Int) -> Int
idxBy x = uncurry (+) . fmap (* x)

lengthEq :: Int -> [a] -> Bool
lengthEq n (_ : xs)
    | n > 0 = lengthEq (n - 1) xs
    | otherwise = False
lengthEq n _ = n == 0

eqLength :: [a] -> [b] -> Bool
eqLength (_ : xs) (_ : ys) = eqLength xs ys
eqLength [] [] = True
eqLength _ _ = False

setAt :: Int -> a -> [a] -> [a]
setAt 0 = (. tail) . (:)
setAt i = (. fromJust . uncons) . (uncurry (:) .) . fmap . setAt (i - 1)

splitOn :: Char -> String -> [String]
splitOn c = uncurry ((. maybe [] (splitOn c . snd) . uncons) . (:)) . span (/= c)