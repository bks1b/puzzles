import Data.Char

-- !include ../util.hs

n = 9

prefixConcat = curry $ not . null . fst . until
    (uncurry $ (. null) . (||) . null)
    (uncurry $ \(y : ys) -> first (bool [] ys . (== y)) . splitAt (length y))

result _ = map intToDigit $ fromJust
    $ find (any
        (uncurry $ prefixConcat . flip map [2..] . (map digitToInt .) . (show .) . (*) . readL)
        . init . tail . splits)
    $ permutationsLex $ reverse [1..n]