readInput :: [String] -> ([Pos], Positions)
readInput = foldr (\(y, l) -> flip (foldr $ \(x, s) -> let p = (x, y) in (***)
    (if s == ' ' then id else (p :))
    (if elem s ". " then id else ((p, s) :))) $ zip [0..] l) ([], []) . zip [0..]

-- builds the cells of a site in a given direction
site :: [Pos] -> Pos -> Pos -> [Pos]
site a x d = (x :) $ if elem next a
    then site a next d
    else []
    where next = addPos 1 x d

splitInput :: String -> ([String], [String])
splitInput = (***) lines (lines . drop 2) . fromJust
    . find ((== "\n\n") . take 2 . snd) . splits

showOutput :: Positions -> [String] -> String
showOutput p = intercalate "\n" . zipWith
    (\y -> zipWith (\x -> flip (flip maybe snd) $ find ((== (x, y)) . fst) p) [0..])
    [0..]

resultF :: [Pos] -> Positions -> [String] -> [Words]
result = uncurry (\framework -> intercalate "\n\n"
    . map (flip showOutput framework . positions)
    . uncurry resultF (readInput framework))
    . swap . splitInput