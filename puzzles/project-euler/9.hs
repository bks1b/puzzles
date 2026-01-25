-- !include ../math.hs

n = 1000

f :: Int -> Int -> Int
f c d = if isSquare d
    then div (c * n * n) 2 - c * c * n
    else f (c + 1) (d + 2 * (c + n) + 1)

result _ = show $ f c (c * c + 2 * n * c - n * n)
    where c = floor $ fromIntegral n * (sqrt 2 - 1)

{-
<math>
{
a+b+c=x
a^2+b^2=c^2
}

Squaring the first equation:

a^2+b^2+c^2+2ab+2ac+2bc=x^2 => ab=x^2/2-cx

Rewriting the system of equations and taking @a@ as the smaller solution:

{
ab=x^2/2-cx
a+b=x-c
}
=> a=(x-c-sqrt((x+c)^2-2x^2))/2

Minimizing and maximizing @a@:

(x-c)^2=(x+c)^2-2x^2 => c=x/2
(x+c)^2-2x^2=0 => c=x(sqrt2-1)

Therefore the solution is @cx^2/2-c^2x@ where @x(sqrt2-1)<c<x/2@ and @(x-c-sqrt((x+c)^2-2x^2))/2 in NN@.
The difference of consecutive discriminants is @2(x+c)+1@.
-}