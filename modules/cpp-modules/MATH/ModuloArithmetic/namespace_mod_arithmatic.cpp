namespace ModuloArithmetic {
pair<long long, long long> extended_gcd(long long a, long long b) {
    if (b == 0) return{1, 1};
    pair<long long, long long> pr = extended_gcd(b, a % b);
    return {pr.second, pr.first - (a / b)*pr.second};
}
long long hcf(long long a, long long b) {
    if (a == 0 || b == 0) return max(a, b);
    pair<long long, long long> pr = extended_gcd(a, b);
    return (a * pr.first + b * pr.second);
}
long long lcm(long long a, long long b) {
    return (a * b) / (__gcd(a, b));
}
long long gcd(long long a, long long b) {
    return __gcd(a, b);
}
long long modSub(long long a, long long b, long long mod) {
    return ((a % mod - b % mod + mod) % mod);
}
long long modMul(long long a, long long b, long long mod) {
    return ((a % mod) * (b % mod)) % mod;
}
long long modAdd(long long a, long long b, long long mod) {
    return ((a % mod) + (b % mod)) % mod;
}
long long modInv(long long a, long long mod) {
    long long x, y;
    pair<long long, long long> pr = extended_gcd(a, mod);
    x = pr.first;
    y = pr.second;
    long long g = (a * x + mod * y);
    if (g != 1) {
        cerr << "modular inverse does not exist , gcd != 1" << endl;
        exit(0);
        return -1;
    }
    // adding m to avoid negative value of x
    long long res = (x % mod + mod) % mod;
    return res;
}
long long modDiv(long long a, long long b, long long mod) {
    a = a % mod;
    // if(a==0) return 0;
    long long inv = modInv(b, mod);
    long long res = (inv * a) % mod;
    return res;
}
long long power(long long x, unsigned long long y, long long p)
{
    long long res = 1;
    x = x % p; // Update x if it is more than or
    if (x == 0) return 0; // In case x is divisible by p;
    while (y > 0) {
        if (y & 1) res = modMul(res, x, p);
        y = y >> 1; // y = y/2
        x = modMul(x, x, p);
    }
    return res;
}
long long powersum(long long a,long long b,long long mod){
    if(b==0) return 1;
    if(b%2 == 0){
        long long prevsm=powersum(a,b-1,mod);
        long long first=1;
        long long second=modMul(a,prevsm,mod);
        long long sm=modAdd(first,second,mod);
        return sm;
    }
    long long base2=(b-1)/2;
    long long sm=0;
    long long halfsm=powersum(a,base2,mod);
    long long k=power(a,base2+1,mod);

    long long first=halfsm;
    long long second=modMul(k,first,mod);
    sm=modAdd(first,second,mod);
    return sm;
}
long long get_primitive_root (long long p) {
    vector<long long> fact;
    long long phi = p - 1,  n = phi;
    for (long long i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (long long res = 2; res <= p; ++res) {
        bool ok = true;
        for (size_t i = 0; i < fact.size() && ok; ++i)
            ok &= power (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}
long long get_root_power(long long num) {
    vector<long long> powers(63);
    for (long long i = 0; i < 63; i++) {
        powers[i] = (1LL << i);
    }
    for (long long i = 62; i >= 0; i--) {
        if (num % powers[i] == 1) return i;
    }
    return -1;
}
};