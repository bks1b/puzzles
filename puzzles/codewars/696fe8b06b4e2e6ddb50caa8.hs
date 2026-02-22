module EnglishRuler where

draw t n = concat $ concatMap (\i -> zipWith (++) ticks $ (' ' : show i ++ "\n") : (if i < n then repeat "\n" else [])) [0..n]
    where ticks = iterate (\a@(x : xs) -> ('-' : x) : xs ++ a) ["-"] !! (t - 1)