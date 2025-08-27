n = 4000000

f :: (Int, Int) -> Int -> Int
f (a, b) i = if mod i 3 == 0 && a + 2 * b > n
    then div (a + b - 1) 2
    else f (b, a + b) (i + 1)

result _ = show $ f (1, 2) 2

{-
<math>
F_(n+3)=F_(n+2)+F_(n+1)=2F_(n+1)+F_n
n -= m (mod 3) => F_n-=F_m (mod 2)

Since @F_0=1@, @F_1=2@, @F_2=3@, the even valued terms are @F_(3k+1)@:

sum_(k=0)^n F_(3k+1)=1/2 sum_(k=0)^n (F_(3k+3)-F_(3k))=(F_(3n+3)-1)/2
-}