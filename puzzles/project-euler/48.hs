n = 1000
m = 10 ^ 10

modExp :: Integer -> Integer -> Integer
modExp _ 0 = 1
modExp b e = if mod e 2 > 0 then mod (b * r) m else r where r = modExp (mod (b * b) m) (div e 2)

result _ = show $ foldl (\a k -> mod (a + modExp k k) m) 0 [1..n]