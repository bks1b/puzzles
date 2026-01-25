readN = read :: String -> Int

replaceFirst :: Eq a => [a] -> a -> a -> [a]
replaceFirst (x : xs) a b = if x == a then b : xs else x : replaceFirst xs a b

main :: IO ()
main = do
    n <- getLine >>= return . readN
    (first, last) <- getLine >>= return . splitAt n . map readN . words
    let (a, b) = (maximum first, minimum last)
    let eq = sum first == sum last
    putStrLn $ if a == b && eq
        then "-1"
        else unwords $ map show $ if eq
            then replaceFirst first a b ++ replaceFirst last b a
            else first ++ last