-- !include ../math.hs

result = show . fromJust . (\n -> find (liftA2 (&&) ((== 0) . mod n) isPrime) [intSqrt n, intSqrt n - 1..]) . read