n = 1000

multiplesBelow :: Int -> Int -> Int
multiplesBelow n k = k * (((n - 1) `div` k) * ((n - 1) `div` k + 1)) `div` 2

result _ = show $ multiplesBelow n 3 + multiplesBelow n 5 - multiplesBelow n 15

{-
Sum of multiples of @k@ below @n@:

sum_(j=1)^(floor((n-1)/k)) jk=k(floor((n-1)/k)(floor((n-1)/k)+1))/2

Multiples of @3@ or @5@:

|"multiples of " 3|+|"multiples of " 5|-|"multiples of " 3*5|
-}