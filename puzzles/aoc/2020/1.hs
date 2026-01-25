prod :: Int -> Int -> [Int] -> Maybe Int
prod t 0 = find (== t)
prod t d = join . fmap (uncurry $ \x -> ap (flip maybe (Just . (x *)) . prod t d) $ prod (t - x) (d - 1)) . uncons

solve :: Bool -> String -> String
solve = (. map read . lines) . (.) (show . fromJust) . prod 2020 . bool 1 2