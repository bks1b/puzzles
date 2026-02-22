import Control.Arrow ((***))
import Control.Monad (replicateM_)

nth = (flip mod 10 .) . (!!) . iterate (flip div 10)

len n = n * 10 ^ n - div (10 ^ n - 1) 9

f x = uncurry nth $ (10 ^ n +) *** (n -) $ divMod (x - len n - 1) (n + 1)
    where n = last $ takeWhile ((x >=) . len) [0..]

main = readLn >>= flip replicateM_ (readLn >>= print . f)

{-
The concatenation of all @k@ digit numbers (@[10^(k-1), 10^k-1]@) has length @k(10^k-10^(k-1))@.
Therefore, the concatenation of all numbers up to @n@ digits has length:

<math>
sum_(k=1)^n k(10^k-10^(k-1))=sum_(k=1)^n (k10^k-(k-1)10^(k-1)-10^(k-1))=n10^n-(10^n-1)/9=:f(n)

Given a position @x@, let @n@ be largest such that @x>=f(n)@.
Then, the answer is the @(x-f(n)-1) mod (n+1)@-th digit of @10^n+floor((x-f(n)-1)/(n+1))@.
-}