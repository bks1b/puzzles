-- !include ../util.hs

n = 3

powers :: Int -> [Int]
powers 0 = []
powers k = [10 ^ k - 1, 10 ^ k - 2..10 ^ (k - 1)]

result _ = fromJust $ find (\p -> let r = readN p in any
    (\k -> mod r k == 0 && 10 ^ (n - 1) <= div r k && 10 ^ n > div r k)
    $ powers n)
    $ concat $ concat $ map
    (\k -> map
        (\x -> show x ++ reverse (show x))
        (powers k)
        : map
            (\x -> map ((++ reverse (show x)) . (show x ++) . (: [])) ['9', '8'..'0'])
            (powers $ k - 1))
    [n, n - 1..1]