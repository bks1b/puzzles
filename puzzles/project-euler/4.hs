-- !include ../util.hs

n = 3

powers :: Int -> [Int]
powers 0 = []
powers k = [10 ^ k - 1, 10 ^ k - 2..10 ^ (k - 1)]

result _ = fromJust $ find
    ((\r -> any (\k -> mod r k == 0 && 10 ^ (n - 1) <= div r k && 10 ^ n > div r k) $ powers n) . readN)
    $ concat $ concatMap
        (\k -> map
            (ap (++) reverse . show)
            (powers k)
            : map
                ((\x -> map ((++ reverse x) . (x ++) . (: [])) ['9', '8'..'0']) . show)
                (powers $ k - 1))
        [n, n - 1..1]