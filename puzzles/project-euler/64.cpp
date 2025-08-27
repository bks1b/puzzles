const int n = 10000;

int result(std::string _) {
    int count = 0;
    for (int i = 2; i <= n; i++) {
        int sqrt = std::sqrt(i);
        if (sqrt * sqrt == i) continue;
        int c = 1;
        int a = sqrt;
        int j = 0;
        do {
            c = (i - a * a) / c;
            a = -a;
            while (a + c <= sqrt) a += c;
            j++;
        } while (c != 1 || a != sqrt);
        if (j % 2 > 0) count++;
    }
    return count;
}

/*
The start:

align {
sqrt(x)=s_0+(c_0/(sqrt(x)-a_0))^-1
=floor(sqrt(x))+(sqrt(x)-floor(sqrt(x)))
=floor(sqrt(x))+(1/(sqrt(x)-floor(sqrt(x))))^-1
c_0=1
s_0=floor(sqrt(x))
a_0=floor(sqrt(x))
}

The iteration:

align {
c_i/(sqrt(x)-a_i)=s_(i+1)+(c_(i+1)/(sqrt(x)-a_(i+1)))^-1
=(c_i*sqrt(x)+c_i*a_i)/(x-a_i^2)
=(sqrt(x)+a_i)/((x-a_i^2)/c_i)
=k+(sqrt(x)+a_i-k*(x-a_i^2)/c_i)/((x-a_i^2)/c_i)
=k+(((x-a_i^2)/c_i)/(sqrt(x)+a_i-k*(x-a_i^2)/c_i))^-1
c_(i+1)=(x-a_i^2)/c_i
s_(i+1)=k
a_(i+1)=k*c_(i+1)-a_i
}

Pick the greatest @k@ such that @a_(i+1)=<floor(sqrt(x))@.
*/