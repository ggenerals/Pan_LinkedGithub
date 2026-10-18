# 序言

## 一些注意事项

- 本文使用 $P$ 表示所有质数所构成的集合。
- 这些模板特别傻逼，大部分都不太可用，最好别吵。
- 我们在本文的最后面加入了香椿时代完整版，建议观看。

# 数学

## 中国剩余定理

当 $m_1,m_2,\cdots,m_n$ 两两互质，且
$$
\begin{cases}x\equiv a_1\pmod{m_1}\\x\equiv a_2\pmod{m_2}\\\cdots\\x\equiv a_i\pmod{m_i}\\\cdots\\x\equiv a_n\pmod{m_n}\end{cases}
$$
令 $M=\operatorname{lcm}(m_1,\cdots,m_n)=\prod_{i=1}^{n} m_i$，$M_i=\frac{M}{m_i}$，有特解
$$
x=\left(\sum\limits_{i=1}^n a_i M_i\times (M_i^{-1}\bmod m_i)\right)\bmod M
$$

ex_CRT 代码：

```cpp
//exCRT，注意可能爆long long
int gcd(int a, int b){
    return b ? gcd(b, a % b) : a;
}
void exgcd(int a, int b, int &x, int &y){
    if(!b) return x = 1, y = 0, void();
    exgcd(b, a % b, y, x), y -= a / b * x;
}
int get(int a, int b, int c){
    int x, y, d = gcd(a, b);
    exgcd(a, b, x, y);
    x = x * c / d, y = y * c / d;
    return x;
}
int exCRT(int n, int *a, int *b){   // x=b (mod a)
    for(int i = 2; i <= n; i++){
        int x=get(b[i - 1], -b[i], a[i] - a[i - 1]), d = gcd(b[i - 1], b[i]);
        d = b[i - 1] * b[i] / d;
        a[i] = ((a[i - 1] + x * b[i - 1] % d) % d + d) % d, b[i] = d;
    }
    return a[n];
}
```

## 欧拉函数

定义式：
$$
\varphi(n)=\sum_{i=1}^{n-1} [\gcd(i,n)=1]
$$
$$
\varphi(n)=n\prod_{p|n,p \in \text{P}}\frac{p-1}{p}
$$
性质：
$$
\forall p \in \text{P},\varphi(p)=p-1
$$
$$
\forall a|x,\varphi(ax)=a\varphi(x)
$$
$$
\forall p\in \text{P},\varphi(p^k)=p^k-p^{k-1}=p^{k-1}(p-1)
$$
扩展欧拉定理：
$$
a^b\equiv\begin{cases}a^b\bmod n&b<\varphi(n)\\a^{b\bmod \varphi(n)+\varphi(n)}\bmod n&b\ge \varphi(n)\end{cases}
$$

$O(\sqrt n)$ 求单点欧拉函数：见原根部分 ola 函数。

## 欧拉数

定义：$1\sim n$ 的排列中，具有 $m$ 个上升的排列数量。
$$
E(n,m)=(n-m)E(n-1,m-1)+(m+1)E(n-1,m)
$$
特别的，$E(n,0)=1,E(n,n+k)=E(0,0)=0$。

## 分拆数

定义：自然数 $n$ 写成递降正整数和的表示的方案数
$$
p(n,k)=p(n-1,k-1)+p(n-k,k)
$$
分拆数的生成函数：
$$
\prod_{i=1}^\infty \frac1{1-x^i}
$$

互异分拆数/奇拆分数：
$$
pd(n,k)=pd(n-k,k-1)+pd(n-k,k)
$$


## 可重集排列组合

### 可重集排列数

$$
P(n;c_1,c_2,\cdots,c_k)=\frac{n!}{c_1!c_2!\cdots c_k!}
$$

其中 $n$ 表示元素种数，$c_i$ 表示第 $i$ 种元素的个数。

---

- 无限可重组合：每种元素数量无限；
- 有限可重组合：每种元素数量有上限。

### 无限可重组合
问题：有 $k$ 种不同元素，每种可选任意次，从中选 $n$ 个元素，不考虑顺序的方案数。

隔板：$n$ 个小球+$k$ 个虚拟小球，有 $n+k-1$ 个空位，得到 $k$ 段区间，方案数为 ${n+k-1}\choose{k-1}$。

如果至少选一个，方案数为 ${n-1}\choose{k-1}$。
### 有限可重组合
问题：有 $k$ 种不同元素，第 $i$ 种至多选 $c_i$ 次，从中选 $n$ 个元素，不考虑顺序的方案数。

方案数：
$$
\sum_{S \subseteq \{1,2,\cdots,n\}}(-1)^{|S|}{{n+k-1-\sum\limits_{i\in S}(c_i+1)}\choose{k-1}}
$$

## 常用组合公式

### 二项式定理：

$$
(a+b)^n=\sum_{i=0}^n{n\choose i} a^ib^{n-i}
$$

推广：
$$
\left(\sum_{i=1}^n a_i\right)^k=\sum_{k_1+k_2+\cdots +k_n=k}\frac{k!}{k_1!k_2!\cdots k_n!}a_1^{k_1}a_2^{k_2}\cdots a_n^{k_n}
$$

### 广义二项式定理

广义二项式定理：
$$
(1+x)^{\alpha}=\sum_{n=0}^{\infty}{\alpha\choose n}x^n
$$
其中：
$$
{\alpha\choose n}=\frac{\alpha^{\underline n}}{n!}=\frac{\alpha(\alpha-1)\cdots(\alpha-n+1)}{n!}
$$
推论：
$$
\dfrac1{(1-x)^k}=\sum_{n=0}^\infty {n+k-1\choose k-1}x^n
$$

### 吸收恒等式

$$
{n\choose k}=\dfrac nk{{n-1}\choose{k-1}}
$$

### 上指标求和
$$
\sum_{i=0}^n {i\choose m}={{n+1}\choose {m+1}}
$$

## 范德蒙德卷积

$$
\sum_{k=0}^r{n\choose k}{m\choose{r-k}}={{n+m}\choose r}
$$

例如：
$$
\sum_{k_1,k_2}{A\choose {k_1}}{B\choose {k_2}}[C\le k_1-k_2\le D]=\sum_{B+C\le k+k_1\le B+D^{*}}{{A+B}\choose{k+k_1}}
$$

### 范德蒙德卷积推论

定义 $k=B-k_2$，则 $B+C\le k_1+k\le B+D$，而 $\dbinom B{k_2}=\dbinom Bk$，式子变成了
$$
\sum_{B+C\le k+k_1\le B+D^{*}}\sum_{k_1}\dbinom A{k_1}\dbinom Bk
$$
$^{*}$：这里直接枚举了 $k+k_1$。

注意到里面两个组合数相乘可以范德蒙德卷积，则
$$
\sum_{B+C\le k+k_1\le B+D^{*}}\dbinom{A+B}{k+k_1}
$$
这样就把一个 $O(n^2)$ 的柿子变成了一个 $O(n)$ 的柿子，而且这个式子可以使用前缀和优化计算，时间复杂度可以降低至 $O(n)-O(1)$。

## Lucas 定理

$$
C(n,k)\equiv \prod C(n_i,k_i)\pmod p
$$

本质上说明了组合数是可以进行 $p$ 进制拆分的。 

$$
Lucas(n,k,p)=\begin{cases}1&k=0\\C(n\bmod p,k \bmod p)\times Lucas(n/p,k/p,p)\bmod p&\text{otherwise.}\end{cases}
$$

### exLucas 定理

1.  **分解 $p$**：得到素因子幂 $q_1^{e_1}, \dots, q_k^{e_k}$。
2.  **对每个 $q_i^{e_i}$**：
    a. 计算 $E = c_{q_i}(n) - c_{q_i}(m) - c_{q_i}(n-m)$。
    b. 若 $E \ge e_i$，则 $A_i = 0$。
    c. 否则，计算 $f(n), f(m), f(n-m) \bmod q_i^{e_i}$。
    d. 计算 $f(m)$ 和 $f(n-m)$ 的逆元。
    e. $A_i = q_i^E \cdot f(n) \cdot \text{inv}(f(m)) \cdot \text{inv}(f(n-m)) \bmod q_i^{e_i}$。
3.  **CRT 合并**：
    求解方程组 $x \equiv A_i \pmod{q_i^{e_i}}$。
    $$x = \sum A_i \cdot M_i \cdot \text{inv}(M_i, m_i) \pmod p$$
    其中 $M_i = p / m_i$。

```cpp
/*
exLucas Template
Usage: ll ans = exlucas(n, m, P);
*/
typedef long long ll;
// ================= BASIC MATH =================
ll gcd(ll a, ll b){ return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b){ return a / gcd(a, b) * b; }
void exgcd(ll a, ll b, ll &x, ll &y){
    if(!b) { x = 1, y = 0; return; }
    exgcd(b, a % b, y, x), y -= a / b * x;
    return ;
}
ll inv(ll a, ll mod) {
    ll x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}
ll qpow(ll x, ll y, ll mod) {
    ll res = 1; 
    x %= mod;
    while(y){
        if(y & 1) res = res * x % mod;
        x = x * x, y >>= 1;
    }
    return res;
}
// ================= EXLUCAS CORE =================
// Calculate n! mod p^k, excluding factors of p
// Returns pair<value, count_of_p>
pair<ll, ll> factorial_ex(ll n, ll p, ll pk) {
    if (n == 0) return {1, 0};
    static map<pair<ll, ll>, ll> memo_prod;
    auto key = make_pair(p, pk);
    ll prod = 1;
    for (int i = 1; i < pk; ++i)
        if (i % p != 0)
            prod = prod * i % pk;
    ll groups = n / pk;
    ll remainder = n % pk;
    ll res_prod = qpow(prod, groups, pk);
    for (int i = 1; i <= remainder; ++i)
        if (i % p != 0)
            res_prod = res_prod * i % pk;
    auto sub = factorial_ex(n / p, p, pk);
    ll total_prod = res_prod * sub.first % pk;
    ll total_count = sub.second + n / p;
    return {total_prod, total_count};
}
// Calculate C(n, m) mod p^k
ll comb_mod_pk(ll n, ll m, ll p, ll pk) {
    if (m > n) return 0;
    auto fn = factorial_ex(n, p, pk);
    auto fm = factorial_ex(m, p, pk);
    auto fnm = factorial_ex(n - m, p, pk);
    ll numerator = fn.first;
    ll denominator = fm.first * fnm.first % pk;
    ll inv_denom = inv(denominator, pk);
    ll val = numerator * inv_denom % pk;
    ll cnt_p = fn.second - fm.second - fnm.second;
    if (cnt_p >= log(pk) / log(p)) { 
        int k = 0; 
        ll tmp = pk;
        while(tmp % p == 0) tmp /= p, k++;
        if (cnt_p >= k) return 0;
    }
    val = val * qpow(p, cnt_p, pk) % pk;
    return val;
}
ll crt_merge(ll a1, ll m1, ll a2, ll m2) {
    ll g = gcd(m1, m2);
    if ((a2 - a1) % g != 0) return -1; 
    ll lcm_val = m1 / g * m2;
    ll rhs = (a2 - a1) / g;
    ll m1_red = m1 / g, m2_red = m2 / g;
    ll inv_m1 = inv(m1_red, m2_red);
    ll k1 = rhs % m2_red * inv_m1 % m2_red;
    if (k1 < 0) k1 += m2_red;
    ll x = a1 + k1 * m1;
    return x % lcm_val;
}
ll exlucas(ll n, ll m, ll P) {
    if (m > n) return 0;
    if (m == 0 || m == n) return 1;
    ll cur_mod = 1;
    ll cur_ans = 0;
    bool first = true;
    ll temp_P = P;
    for (ll p = 2; p * p <= temp_P; ++p) {
        if (temp_P % p == 0) {
            ll pk = 1;
            while(temp_P % p == 0)
                pk *= p, temp_P /= p;
            ll res_pk = comb_mod_pk(n, m, p, pk);
            if(first){
                cur_ans = res_pk;
                cur_mod = pk;
                first = false;
            }
            else{
                cur_ans = crt_merge(cur_ans, cur_mod, res_pk, pk);
                cur_mod = lcm(cur_mod, pk);
            }
        }
    }
    if(temp_P > 1){
        ll p = temp_P;
        ll pk = p;
        ll res_pk = comb_mod_pk(n, m, p, pk);
        if(first){
            cur_ans = res_pk;
            cur_mod = pk;
        }
        else{
            cur_ans = crt_merge(cur_ans, cur_mod, res_pk, pk);
            cur_mod = lcm(cur_mod, pk);
        }
    }
    return cur_ans;
}
```

## Prufer 序列

```cpp
const int N = 5e6 + 10;
int fa[N], deg[N], prufer[N];
void to_prufer(int n){
	int cur;
	for(int i = 1; i <= n; i++){
		if(deg[i]==1){
			cur=i;
			break;
		}
    }
	int lf = cur;
	for(int i = 1; i <= n - 2; i++){
		int f = fa[lf];
		prufer[i] = f, deg[f]--;
		if(deg[f] == 1 && f < cur){ lf = f; continue;}
		cur++;
		while(deg[cur] != 1) cur++;
		lf = cur;
	}
    return ;
}
void to_tree(int n){
	int cur;
	for(int i = 1; i <= n; i++) deg[i] = 1;
	for(int i = 1; i <= n - 2; i++) deg[prufer[i]]++;
	for(int i = 1; i <= n; i++)
		if(deg[i] == 1){
			cur = i;
			break;
		}
	int lf = cur, cnt = 0;
	for(int i = 1; i <= n - 2; i++){
		int f = fa[lf] = prufer[i];
		deg[f]--;
		if(deg[f] == 1 && f < cur){ lf = f; continue;}
		cur++;
		while(deg[cur] != 1) cur++;
		lf = cur;
	}
	fa[lf] = n;
    return ;
}
int main(){
    int n, m;
    cin >> n >> m;
    if(m == 1){
        for(int i = 1; i <= n - 1; i++) 
            cin >> fa[i], deg[i]++, deg[fa[i]]++;
        to_prufer(n);
    }
    else {
        for(int i = 1; i <= n - 2; i++) 
            cin >> prufer[i];
        to_tree(n);       
    }
    return 0;
}
```

主函数中 $m=1$ 为树转 $\text{Prufer}$，$m=2$ 为 $\text{Prufer}$ 转树。

### Cayley 定理推广

对于 $n$ 个节点的树，有标号，且 $i$ 的度数为 $d_i$，则这样的无根树数量为：
$$
\frac{(n-2)!}{\prod\limits_{i=1}^n (d_i-1)!}
$$

## 卡特兰数

$$
\begin{align*}
C_{n+1}&=\sum_{i=0}^{n} C_iC_{n-i} \\
&=\frac{4n+2}{n+2}C_n\\
\end{align*}
$$
$$
\begin{align*}
C_n&={{2n}\choose n}-{{2n}\choose {n-1}} \\
&=\frac{1}{n+1}{{2n}\choose n}=\frac{(2n)!}{(n+1)!n!}
\end{align*}
$$

## BSGS/exBSGS

用途：求满足 $a^x\equiv b\pmod p$ 的最小自然数 $x$。

```cpp
int qpow(int a, int b, int mod){
	int ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod, b >>= 1;
	}
	returna ans;
}
int BSGS(int a, int b, int p){
	unordered_map<int, int> mp;
	int m = sqrt(p) + 1, val = qpow(a, m, p), cur = b % p;
	for(int B = 0; B <= m; B++){
		mp[cur] = B;
		cur = cur * a % p;
	}
	val = qpow(a, m, p);
	cur = val;
	for(int A = 1; A <= m; A++){
		if(mp[cur]) return A * m - mp[cur];
		cur = cur * val % p;
	}
	return -1;
}
int exgcd(int a, int b, int &x, int &y){}
	if(b == 0){
		x = 1, y = 0;
		return a;
	}
	int xx, yy, d = exgcd(b, a % b, xx, yy);
	x = yy,	y = xx - (a / b) * yy;
	return d;
}
int exBSGS(int a, int b, int p){
	b = (b % p + p) % p;
	a = (a % p + p) % p; 
    if(1 % p == b % p) return 0; 
	int x, y, d = exgcd(a, p, x, y);
	if(d > 1){
		if(b % d) return -114514;
		exgcd(a / d, p / d, x, y);
		return exBSGS(a, b / d * x % (p / d), p / d) + 1;
	}
	return BSGS(a, b, p);
}
```

函数说明：

- `BSGS(a,b,p)` 求解 $p$ 与 $a$ 互质时的答案。时间复杂度 $O(\sqrt p)$。
- `exBSGS(a,b,p)` 求解任意情况下的答案。时间复杂度 $O(\log p+\sqrt p)$。

## 广义容斥原理

设有全集 $U$，$n$ 中性质 $P_1,P_2,\cdots,P_n$。

记 $\alpha(k)$ 表示**恰好**拥有 $k$ 种性质的元素个数。

记 $\beta(k)$ 表示：任选 $k$ 种性质，$\beta(k)$ 表示对于每一组性质，同时至少满足这 $k$ 个性质的数之和。形式化表述为：
$$
\beta(k)=\sum_{\substack{S\subseteq\{1,2,\cdots,n\},\\|S|=k}}\left|\bigcap_{i\in S}A_i\right|
$$
其中，$A_i$ 表示满足性质 $P_i$ 的元素构成的集合。不难发现，对于一个有 $m$ 种性质的元素，对 $\beta(k)$ 的贡献为 $m\choose k$。$\beta(0)=|U|$。

使用 $\alpha$ 也可以表示 $\beta$：

$$
\beta(k)=\sum_{i=k}^n{i\choose k}\alpha(i)
$$
广义容斥原理：

$$
\alpha(k)=\sum_{i=k}^n(-1)^{i-k}{i\choose k}\beta(i)
$$
证明：算贡献，套用组合恒等式，二项式定理，化简分类讨论即可证明。

令 $k=0$，则：

$$
\alpha(0)=\sum_{i=0}^n(-1)^i\beta(i)
$$

## 二项式反演

若 $f,g$ 满足：
$$
f_n=\sum_{i=0}^n{n\choose i}g_i
$$
则：
$$
g_n=\sum_{i=0}^n(-1)^{n-i}{n\choose i}f_i
$$
反之亦然。

---

若 $f,g$ 满足：
$$
f_k=\sum_{i=k}^n{i\choose k}g_i
$$
则：
$$
g_k=\sum_{i=k}^n(-1)^{i-k}{i\choose k}f_i
$$
反之亦然。

---

若 $f_{x,y}$ 和 $g_{i,j}$ 满足：
$$
f_{x,y}=\sum_{i=x}^n\sum_{j=y}^m {i\choose x}{j\choose y}g_{i,j}
$$
则：
$$
g_{x,y}=\sum_{i=x}^n\sum_{j=y}^m(-1)^{i-x+j-y} {i\choose x}{j\choose y}f_{i,j}
$$

## 斯特林数相关

### 第一类斯特林数

递推公式：
$$
{n\brack k}=(n-1){n-1 \brack k}+{n-1 \brack k-1}
$$

### 第二类斯特林数

递推公式：
$$
{n\brace k}={n-1\brace k-1}+k{n-1\brace k}
$$
通项公式：
$$
{n\brace k}=\frac 1{k!}\sum_{i=0}^k(-1)^i{k\choose i}(k-i)^n
$$

### 斯特林数的正交性

$$
[n=m]=\sum_{i=m}^n(-1)^{n-i}{n\brace i}{i\brack m}
$$

### 普通幂，下降幂，上升幂转化

$$
\begin{align}
n^k&=\sum_{i=0}^n {k\brace i}i!{n\choose i}=\sum_{i=0}^k{k\brace i}n^{\underline i}\\
n^{\underline k}&=\sum_{i=0}^k(-1)^{k-i}{k\brack i}n^i\\
n^{\overline k}&=\sum_{i=0}^k{k\brack i}n^i
\end{align}
$$

### 斯特林反演

若 $f_n$ 满足：
$$
f_k=\sum_{i=k}^n{i\brace k}g_i
$$
则：
$$
g_k=\sum_{i=k}^n(-1)^{i-k}{i\brack k}f_i
$$
组合意义：
- $g_i$：将元素划分为恰好 $i$ 个非空、有标号组的方案数。
- $f_i$：将元素先划分为若干小段，再组合为 $i$ 个非空大类。

## 莫比乌斯反演

若
$$
F(n)=\sum_{n|d}f(d)
$$
则
$$
f(n)=\sum_{n|d}\mu(d/n)F(d)
$$
如：
$$
\sum_{d|n}\mu(d)=[n=1]
$$

## 杜教筛公式

$$
S(n)=H(n)-\sum_{d=2}^ng(d)\cdot S\left(\left\lfloor \frac nd\right\rfloor\right)
$$

常用的：

1.
$$
\mu^2(d)=\sum_{k^2|d}\mu(k)
$$
2.
$$
d(ij)=\sum_{x|i}\sum_{y|j}[\gcd(x,y)=1]
$$
3.
$$
\varphi(ij)=\frac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}
$$
4.
$$
\gcd(i,j)=\sum_{d|i,d|j}\varphi(d)
$$

杜教筛代码：

```cpp
#define int long long
const int N = 1e7 + 10;
int m, q[12], phi[N], mul[N], p[N >> 3], tot;
bool vis[N];
unordered_map<int, int> rephi, remul;
void init(){
    phi[1] = mul[1] = 1;
    for(int i = 2; i <= m; i++){
        if(!vis[i]) p[++tot] = i, phi[i] = i - 1, mul[i] = -1;
        for(int j = 1, tmp; j <= tot && (tmp = i * p[j]) <= m; j++){
            vis[tmp] = 1;
            if(i % p[j]) phi[tmp] = phi[i] * (p[j] - 1), mul[tmp] = -mul[i];
            else {
                phi[tmp] = phi[i] * p[j], mul[tmp] = 0;
                break;
            }
        }
    }
    for(int i = 2; i <= m; i++) phi[i] += phi[i - 1], mul[i] += mul[i - 1];
    return ;
}
int calc_phi(int x){
    if(x <= m) return phi[x];
    if(rephi.count(x)) return rephi[x];
    int res=(x * (x + 1)) >> 1;
    for(int l = 2, r; l <= x; l = r + 1) 
        r = x / (x / l), res -= calc_phi(x / l) * (r - l + 1);
    return rephi[x] = res;
}
int calc_mul(int x){
    if(x <= m) return mul[x];
    if(remul.count(x)) return remul[x];
    int res = 1;
    for(int l = 2, r; l <= x; l = r + 1) 
        r = x / (x / l), res -= calc_mul(x / l) * (r - l + 1);
    return remul[x] = res;
}
void solve(int x){
    cout << calc_phi(x) << " " << calc_mul(x) << "\n";
    return ;
}
signed main(){
    int T, mx=0;
    cin >> T;
    for(int i = 1; i <= T; i++) cin >> q[i], mx = max(mx, q[i]);
    m=pow(T * mx, 2.0 / 3.0), init();
    for(int i = 1; i <= T; i++) solve(q[i]);
    return 0;
}
```

## 常见生成函数的封闭形式

### OGF

- $a_n=1$（无限选 $1$ 种物品）它的封闭形式为 $\dfrac{1}{1-x}$。
- $a_n=c^n$（等比数列）它的封闭形式为 $\dfrac1{1-cx}$。
- $a_n=n+1$（两层卷积）它的封闭形式为 $\dfrac1{(1-x)^2}$
- $a_n={n+k-1\choose k-1}$（k 种物品无限选）它的封闭形式为 $\dfrac 1{(1-x)^k}$。
- $a_n=F_n$，其中 $F_n$ 是斐波那契数列（递推数列）它的封闭形式 $\dfrac x{1-x-x^2}$。
- $a_n=C_n$，其中 $C_n$ 是卡特兰数（格路计数）它的封闭形式为 $\dfrac{1-\sqrt{1-4x}}{2x}$。

### EGF

- $a_n=1$（一种元素无限选）$e^x$
- $a_n=c^n$（带权重的排列）$e^{cx}$
- $a_n=n!$（全排列）$\frac1{1-x}$
- $a_n=D_n$，$D_x$ 是错排（无不动点排列）$\frac{e^{-x}}{1-x}$
- $a_n=B_n$，$B_n$ 是贝尔数（集合划分数）$e^{e^x-1}$

还有几个稍微特别的约束：
- 至少选一个 $e^x-1$。
- 选偶/奇数个
  - 偶数：$\frac{e^x+e^{-x}}{2}=\sum_{n=0}^\infty\frac{x^{2n}}{(2n)!}$
  - 奇数：$\frac{e^x-e^{-x}}{2}=\sum_{n=0}^\infty\frac{x^{2n+1}}{(2n+1)!}$

定义 $\exp$ 操作如下：
- 设 $\hat F(x)$ 是单个连通块的 EGF。
- 则 $\exp\left(\hat F(x)\right)$ 定义为若干个连通块组成的整体的 EGF。

## 拉格朗日插值

$$
f(x)=\sum_{i=1}^ny_i\prod_{j\ne i}\frac{x-x_j}{x_i-x_j}
$$

## 多项式全家桶模板

> **特性**: 自定义 NTT 模数 / 复数 FFT / 逆+Ln+Exp+Sqrt+Divmod+Sin/Cos/Arcsin/Arctan  
> **注意**: 单位根单次预处理优化。

### 1. FFT (复数域卷积)

**文件名**: `fft.cpp`  
**用途**: 高精度乘法、非模数卷积、信号处理

```cpp
/*
FFT Template (Complex Field)
Usage: auto c = fft_conv(a, b);
*/
using db = double;
using ll = long long;
const db PI = acos(-1.0);
struct Complex{
    db r, i;
    Complex(db _r = 0, db _i = 0) : r(_r), i(_i) {}
    Complex operator + (const Complex &o) const { return {r + o.r, i + o.i}; }
    Complex operator - (const Complex &o) const { return {r - o.r, i - o.i}; }
    Complex operator * (const Complex &o) const { return {r * o.r - i * o.i, r * o.i + i * o.r}; }
};
void fft(vector<Complex> &a, bool invert){
    int n = a.size();
    for(int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for(int len = 2; len <= n; len <<= 1){
        db ang = 2 * PI / len * (invert ? -1 : 1);
        Complex wlen(cos(ang), sin(ang));
        for(int i = 0; i < n; i += len){
            Complex w(1, 0);
            for(int j = 0; j < len / 2; j++){
                Complex u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v, a[i + j + len / 2] = u - v;
                w = w * wlen;
            }
        }
    }
    if(invert) for(auto &x : a) x.r /= n;
    return ;
}
vector<ll> fft_conv(const vector<ll> &a, const vector<ll> &b) {
    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)(a.size() + b.size())) n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa, 0), fft(fb, 0);
    for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i];
    fft(fa, 1);
    vector<ll> res(n);
    for (int i = 0; i < n; i++) res[i] = llround(fa[i].r);
    return res;
}
```

### 2. NTT + 多项式全家桶 (任意模数)

**文件名**: `poly_mod.cpp`  
**用途**: 组合数学、生成函数、任意 NTT 友好模数下的完整多项式运算

```cpp
typedef long long ll;
const ll mod = 998244353, G = 3, GI = 332748118; // If MTT don't const
void init_poly_env(int m, int g ,int gi) { mod = m, G = g, GI = gi; }
inline ll add(ll a, ll b) { a += b; return a >= mod ? a - mod : a; }
inline ll sub(ll a, ll b) { a -= b; return a < 0 ? a + mod : a; }
inline ll mul(ll a, ll b) { return a * b % mod; }
ll qpow(ll a, ll b) {
    ll res = 1; a %= mod;
    for (; b; b >>= 1, a = mul(a, a)) if (b & 1) res = mul(res, a);
    return res;
}
ll sqrt_mod(ll a) {
    if (a == 0) return 0;
    ll t = mod - 1, s = 0;
    while (!(t & 1)) t >>= 1, s++;
    ll n = 2;
    while (qpow(n, (mod - 1) >> 1) != moe - 1) n++;
    ll x = qpow(a, (t + 1) >> 1), y = qpow(a, t), c = qpow(n, t);
    for (int i = 1; i < s; i++) {
        ll tmp = qpow(y, 1LL << (s - i - 1));
        if (tmp != 1) {
            x = mul(x, qpow(c, 1LL << (i - 1)));
            y = mul(y, qpow(c, 1LL << i));
        }
    }
    return min(x, mod - x);
}
// ================= NTT CORE (OPTIMIZED) =================
void ntt(vector<ll> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    vector<ll> roots(n); roots[0] = 1;
    ll w_base = qpow(invert ? GI : G, (mod - 1) / n);
    for (int i = 1; i < n; i++) roots[i] = mul(roots[i-1], w_base);
    for (int len = 2; len <= n; len <<= 1) {
        int step = n / len;
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j];
                ll v = mul(a[i + j + len / 2], roots[j * step]);
                a[i + j] = add(u, v);
                a[i + j + len / 2] = sub(u, v);
            }
        }
    }
    if (invert) {
        ll n_inv = qpow(n, mod - 2);
        for (auto &x : a) x = mul(x, n_inv);
    }
    return ;
}
// ================= POLYNOMIAL OPS =================
vector<ll> poly_mul(vector<ll> a, vector<ll> b) {
    if (a.empty() || b.empty()) return {};
    int sz = a.size() + b.size() - 1, n = 1;
    while (n < sz) n <<= 1;
    a.resize(n, 0); b.resize(n, 0);
    ntt(a, 0), ntt(b, 0);
    for (int i = 0; i < n; i++) a[i] = mul(a[i], b[i]);
    ntt(a, 1);
    a.resize(sz);
    return a;
}
vector<ll> poly_inv(const vector<ll> &f, int deg) {
    assert(!f.empty() && f[0] != 0);
    vector<ll> g(deg, 0);
    g[0] = qpow(f[0], mod - 2);
    for (int cur = 1; cur < deg; cur <<= 1) {
        int n   = cur << 2;
        int tgt = cur << 1;
        vector<ll> tmp(n, 0), ng(n, 0);
        for (int i = 0; i < min((int)f.size(), tgt); i++) tmp[i] = f[i];
        for (int i = 0; i < cur; i++) ng[i] = g[i];
        ntt(tmp, 0); ntt(ng, 0);
        for (int i = 0; i < n; i++) ng[i] = mul(ng[i], sub(2, mul(tmp[i], ng[i])));
        ntt(ng, 1);
        for (int i = 0; i < min(tgt, deg); i++) g[i] = ng[i];
        for (int i = min(tgt, deg); i < deg; i++) g[i] = 0;
    }
    g.resize(deg);
    return g;
}
vector<ll> poly_deriv(const vector<ll> &f) {
    if (f.size() <= 1) return {};
    vector<ll> res(f.size() - 1);
    for (int i = 1; i < (int)f.size(); i++) res[i-1] = mul(f[i], i);
    return res;
}
vector<ll> poly_integ(const vector<ll> &f) {
    vector<ll> res(f.size() + 1, 0);
    for (int i = 0; i < (int)f.size(); i++)
        res[i + 1] = mul(f[i], qpow(i + 1, mod - 2));
    return res;
}
vector<ll> poly_ln(const vector<ll> &f, int deg) {
    assert(!f.empty() && f[0] == 1);
    auto df = poly_deriv(f);
    auto inv_f = poly_inv(f, deg);
    auto prod = poly_mul(df, inv_f);
    prod.resize(deg - 1);
    auto res = poly_integ(prod);
    res.resize(deg);
    return res;
}
vector<ll> poly_exp(const vector<ll> &f, int deg) {
    assert(f.empty() || f[0] == 0);
    vector<ll> g(deg, 0);
    g[0] = 1;
    for (int cur = 1; cur < deg; cur <<= 1) {
        int n = cur << 1;
        auto ln_g = poly_ln(g, n);
        vector<ll> h(n, 0);
        h[0] = 1;
        for (int i = 1; i < n; i++) {
            ll fi = (i < (int)f.size()) ? f[i] : 0;
            h[i] = sub(fi, ln_g[i]);
        }
        vector<ll> ng(n, 0);
        for (int i = 0; i < cur; i++) ng[i] = g[i];
        auto nh = poly_mul(ng, h);
        for (int i = 0; i < min(n, deg); i++) g[i] = nh[i];
        fill(g.begin() + min(n, deg), g.end(), 0);
    }
    g.resize(deg);
    return g;
}
vector<ll> poly_sqrt(const vector<ll> &f, int deg) {
    assert(!f.empty());
    ll c = sqrt_mod(f[0]);
    vector<ll> g(deg, 0);
    g[0] = c;
    ll inv2 = (mod + 1) / 2;
    for (int cur = 1; cur < deg; cur <<= 1) {
        int n = cur << 1;
        auto inv_g = poly_inv(g, n);
        vector<ll> tmp(n, 0);
        for (int i = 0; i < min((int)f.size(), n); i++) tmp[i] = f[i];
        auto fg = poly_mul(inv_g, tmp);
        for (int i = 0; i < min(n, deg); i++) {
            ll gi = (i < cur) ? g[i] : 0;
            ll fgi = (i < (int)fg.size()) ? fg[i] : 0;
            g[i] = mul(add(gi, fgi), inv2);
        }
        fill(g.begin() + min(n, deg), g.end(), 0);
    }
    g.resize(deg);
    return g;
}
pair<vector<ll>, vector<ll>> poly_divmod(const vector<ll> &f, const vector<ll> &g) {
    int n = f.size(), m = g.size();
    assert(m > 0 && g[m-1] != 0);
    if (n < m) return {{}, f};
    auto rf = f, rg = g;
    reverse(rf.begin(), rf.end());
    reverse(rg.begin(), rg.end());
    int qdeg = n - m + 1;
    rf.resize(qdeg, 0); rg.resize(qdeg, 0);
    auto rq = poly_mul(rf, poly_inv(rg, qdeg));
    rq.resize(qdeg);
    reverse(rq.begin(), rq.end());
    auto qg = poly_mul(rq, g);
    vector<ll> r(m - 1);
    for (int i = 0; i < m - 1; i++) {
        ll fi = (i < n) ? f[i] : 0;
        ll qi = (i < (int)qg.size()) ? qg[i] : 0;
        r[i] = sub(fi, qi);
    }
    return {rq, r};
}
// ================= TRIGONOMETRIC =================
ll get_i() { static ll I = -1; if (I==-1) I = qpow(G, (mod-1)/4); return I; }
vector<ll> poly_sin(const vector<ll> &f, int deg) {
    assert(f.empty() || f[0] == 0);
    ll I = get_i(), inv2i = mul((mod + 1) >> 1, qpow(I, mod - 2));
    vector<ll> if_(deg,0), nif_(deg,0);
    for (int i = 0; i < min(deg, (int)f.size()); i++) {
        if_[i] = mul(f[i], I); nif_[i] = sub(0, if_[i]);
    }
    auto e1 = poly_exp(if_, deg), e2 = poly_exp(nif_, deg);
    vector<ll> res(deg);
    for (int i = 0; i < deg; i++) res[i] = mul(sub(e1[i], e2[i]), inv2i);
    return res;
}
vector<ll> poly_cos(const vector<ll> &f, int deg) {
    assert(f.empty() || f[0] == 0);
    ll I = get_i(), inv2 = (mod + 1) >> 1;
    vector<ll> if_(deg,0), nif_(deg,0);
    for (int i = 0; i < min(deg,(int)f.size()); i++) {
        if_[i] = mul(f[i], I); nif_[i] = sub(0, if_[i]);
    }
    auto e1 = poly_exp(if_, deg), e2 = poly_exp(nif_, deg);
    vector<ll> res(deg);
    for (int i = 0; i < deg; i++) res[i] = mul(add(e1[i], e2[i]), inv2);
    return res;
}
vector<ll> poly_arcsin(const vector<ll> &f, int deg) {
    assert(f.empty() || f[0] == 0);
    auto f2 = poly_mul(f, f); f2.resize(deg, 0);
    vector<ll> t(deg, 0); t[0] = 1;
    for (int i = 0; i < deg; i++) t[i] = sub(t[i], f2[i]);
    auto sq = poly_sqrt(t, deg);
    auto integ = poly_mul(poly_deriv(f), poly_inv(sq, deg));
    integ.resize(deg - 1);
    auto res = poly_integ(integ); res.resize(deg);
    return res;
}
vector<ll> poly_arctan(const vector<ll> &f, int deg) {
    assert(f.empty() || f[0] == 0);
    auto f2 = poly_mul(f, f); f2.resize(deg, 0);
    vector<ll> t(deg, 0); t[0] = 1;
    for (int i = 0; i < deg; i++) t[i] = add(t[i], f2[i]);
    auto integ = poly_mul(poly_deriv(f), poly_inv(t, deg));
    integ.resize(deg - 1);
    auto res = poly_integ(integ); res.resize(deg);
    return res;
}
```

### 3. API 速查表

| 函数                      | 作用                  | 前置条件                 | 复杂度         |
| ------------------------- | --------------------- | ------------------------ | -------------- |
| `init_poly_env(mod,g,gi)` | 设定模数环境          | **必须最先调用**         | $O(1)$         |
| `poly_mul(a,b)`           | 多项式乘法            | 无                       | $O(n\log n)$   |
| `poly_inv(f,deg)`         | 求逆 $\bmod\ x^{deg}$ | $f(0)\neq 0$             | $O(n\log n)$   |
| `poly_ln(f,deg)`          | $\ln f(x)$            | $f(0)=1$                 | $O(n\log n)$   |
| `poly_exp(f,deg)`         | $\exp f(x)$           | $f(0)=0$                 | $O(n\log^2 n)$ |
| `poly_sqrt(f,deg)`        | $\sqrt{f(x)}$         | $f(0)$ 是二次剩余        | $O(n\log^2 n)$ |
| `poly_divmod(f,g)`        | 带余除法 $(q,r)$      | $g\neq 0$                | $O(n\log n)$   |
| `poly_sin(f,deg)`         | $\sin f(x)$           | $f(0)=0$, $4\mid(mod-1)$ | $O(n\log^2 n)$ |
| `poly_cos(f,deg)`         | $\cos f(x)$           | $f(0)=0$, $4\mid(mod-1)$ | $O(n\log^2 n)$ |
| `poly_arcsin(f,deg)`      | $\arcsin f(x)$        | $f(0)=0$                 | $O(n\log^2 n)$ |
| `poly_arctan(f,deg)`      | $\arctan f(x)$        | $f(0)=0$                 | $O(n\log^2 n)$ |
| `fft_conv(a,b)`           | 实数/整数卷积         | 无需 init                | $O(n\log n)$   |

### 4. 注意事项

1.  **`sqrt_mod` 通用性**: 内置 Tonelli-Shanks 算法，适用于所有 $p \equiv 1 \pmod 4$ 的 NTT 质数。若 $f(0)$ 非二次剩余会触发 `assert`。
2.  **三角函数前提**: $\sin/\cos$ 需要模数存在虚数单位 $i$，即 $4 \mid (mod-1)$。常用 NTT 质数均满足。
3.  **`__int128` 依赖**: `mul()` 使用 `__int128` 防溢出。MSVC 用户请替换为 `long double` 拆位乘法。
4.  **内存管理**: 牛顿迭代产生大量临时向量。$n > 2^{17}$ 时建议手动管理内存池或使用全局数组。
5.  **前置条件**: 除 `assert` 外不做运行时校验，非法输入导致结果错误属正常行为。

### 5. 常用 NTT 友好质数参考

| mod | G | GI | 最大长度 $2^m$ | 备注 |
|-----|---|----|----------------|------|
| 998244353 | 3 | 332748118 | $2^{23}$ | 最常用 |
| 1004535809 | 3 | 334845270 | $2^{21}$ | 备选 |
| 469762049 | 3 | 156587350 | $2^{21}$ | 三模 NTT 用 |
| 167772161 | 3 | 55924054 | $2^{25}$ | 大长度 |

## 高斯消元法

矩阵从 $1$ 开始。

```cpp
const int N = 110;
const double eps = 1e-7;
double a[N][N];
int solve(int n){
	for(int i = 1; i <= n; i++){
		int p = 0;
		for(int j = i; j <= n; j++) 
            if(fabs(a[j][i]) > fabs(a[p][i])) p = j;
		for(int j = 1; j <= n + 1; j++)
			swap(a[p][j], a[i][j]);
		double k = a[i][i];
		if(fabs(k) < eps) continue;
		for(int j = 1; j <= n + 1; j++) a[i][j] /= k;
		for(int j = 1; j <= n; j++){
			if(i == j) continue;
			double x = a[j][i];
			for(int k = 1; k <= n + 1; k++)
				a[j][k] = a[j][k] - a[i][k] * x;
		}
	}
	for(int i = 1; i <= n; i++)
		if(fabs(a[i][i]) < eps && fabs(a[i][n+1]) > eps) return -1;
	for(int i = 1; i <= n; i++)
		if(fabs(a[i][i]) < eps && fabs(a[i][n+1]) < eps) return 1;
	return 0;
}
```

返回 $-1$：无解；  
返回 $1$ ：无数解；  
返回 $0$ ：唯一解。

### 矩阵求逆

```cpp
const int N = 410, mod = 1e9 + 7;
int a[N][N * 2 + 1];
int qpow(int x, int y = mod - 2){
	int res = 1;
	while(y){
		if(y & 1) res = res * x % mod;
		x = x * x % mod, y >>= 1;
	}
	return res;
}
int solve(int n){
	for(int i = 1; i <= n; i++){
		int p = 0;
		for(int j = i; j <= n; j++){
			if(a[j][i] != 0){
				p = j;
                break;
            }
        }
        if(a[p][i] == 0) return -1;
		for(int j = 1; j <= n * 2; j++)
			swap(a[p][j], a[i][j]);
		int k = a[i][i];
		if(!k) continue;
		for(int j = 1; j <= n * 2; j++)
            a[i][j] = a[i][j] * qpow(k) % mod;
		for(int j = 1; j <= n; j++){
			if(i == j) continue;
			int x = a[j][i];
			for(int k = 1; k <= n * 2; k++)
				a[j][k] = (a[j][k] - a[i][k] * x % mod + mod) % mod;
		}
	}
	for(int i = 1; i <= n; i++)
		if(a[i][i] == 0) return -1;
	return 0;
}
```

## 线性基

```cpp
const int N = 60;
int p[N];
void insert(int x){
	for(int i = N; i >= 0; i--){
		if((x >> i) & 1){
			if(p[i] == 0) return p[i] = x, void();
			else x ^= p[i];
        }
    }
    return ;
}
int build(){
	int n = 0;
	for(int i = 0; i <= N; i++)
		for(int j = i + 1; j <= M; j++)
			if(p[j] & (1ll << i))
				p[j] ^= p[i];
	for(int i = 0; i <= M; i++)
		if(p[i]) p[n++] = p[i];
	return n; // 返回值为正交化线性基长度
}
```

- 求子集异或和最大值 
  **正交化线性基后**，所有数的异或值。
  
- 求子集异或和最小值 
  **正交化线性基后后**，第一个非零数。
  
- 判断 $x$ 是否能被表示 
  尝试插入 $x$，如果可以插入，那么不存在；否则存在。
  
- 求异或的 $k$ 小值 
  **正交化线性基后**，将 $k$ 转为二进制，异或对应位的线性基。
  
- 求 $x$ 在线性基中的排名  
  1. 设已经得到正交化的线性基（$p_0\sim p_{cnt-1}$）。
  2. 线性基能够得到的不相同的元素共 $2^{cnt}$ 个。
  3. 从 $p_0\sim p_{cnt}$ 遍历，如果 $x\ge p_i$ 且 $x\oplus p_i<x$，$x\gets x\oplus p_i$，$k\gets k\operatorname{or}2^i$。
  4. 答案是 $k+1$。
  ```cpp line-numbers
  int rk(int x,int len){
  	int ans = 0;
  	for(int i = 0; i < len; i++)
  		if(x >= p[i] && (x ^ p[i]) < x)
  			x ^= p[i], ans |= (1ll << i);
  	return res + 1;
  }
  ```
  
- 求 $x$ 在 $a_i$ 所有子集异或和排序后的排名（不同于上一个，这个要求不去重）  
  所有元素重复的次数相同。

## 矩阵树定理 (Matrix Tree Theorem)

**特性**: 用于计算无向图的生成树个数、有向图的外向/内向生成树（阿博雷斯cence）个数。核心是基尔霍夫（Kirchhoff）矩阵的行列式。

**用途**: 提供构建拉普拉斯矩阵及计算行列式的功能，支持无向图生成树和有向图生成树计数。

```cpp
#define int long long
const int N = 310, mod = 1e9 + 7;
int n, L[N][N];
void ins(int i, int j, int k){
    L[j][j] += k, L[i][j] -= k;
    return ;
}
int det(){  // 求拉普拉斯矩阵的行列式
    int ans = 1;
    for(int i = 2; i <= n; i++){
        int pos = i;
        for(int j = i; j <= n; j++) if(abs(L[j][i]) > abs(L[pos][i])) pos = j;
        if(L[pos][i] == 0) return 0;
        if(pos != i) ans = -ans;
        swap(L[pos], L[i]);
        for(int j = i + 1; j <= n; j++){
            if(L[j][i] > L[i][i]) swap(L[i], L[j]), ans = -ans;
            while(L[j][i]){
                int d = L[i][i] / L[j][i];
                for(int k = i; k <= n; k++) 
                    L[i][k] = (L[i][k] + mod - d  * L[j][k] % mod) % mod;
                swap(L[i], L[j]), ans = -ans;
            }
        }
    }
    for(int i = 2; i <= n; i++) ans = ans * L[i][i] % mod;
    return (ans + mod) % mod;
}
```

### 注意事项：

如果要统计所有生成树的边权和：
- 那么拉普拉斯的矩阵里面要填上对应的边权。

如果要统计内向有根树/外向有根树的数量：
- 要统计入度/出度，并删去根所在行列。

## Best 定理 (Best's Theorem)

**特性**: 计算有向欧拉图中欧拉回路的数量。  
**公式**: 
$$ \text{EC}(G) = t_r(G) \cdot \prod_{v \in V} (\deg^+(v) - 1)! $$
其中 $t_r(G)$ 是以任意节点 $r$ 为根的**内向**生成树个数。  
**注意**: 图必须是有向欧拉图（每个节点入度等于出度，且弱连通）。

**用途**: 结合矩阵树定理和阶乘，计算欧拉回路数。

```cpp
using ll = long long;
const ll mod = 1000003;
const int N = 3141595;
ll fact[N + 5];
ll qpow(ll x,ll y); // a^b % mod
ll inv(ll x);
ll det(vector<vector<ll> > a, int n){
    ll ans = 1;
    for(int i = 0; i < n; i++){
        int p = i;
        for(int j = i + 1; j < n; j++){
            if(a[j][i]){
                p = j;
                break;
            }
        }
        if(!a[p][i]) return 0;
        if(p != i){
            swap(a[p], a[i]);
            ans=(mod - ans) % mod;
        }
        ans = ans * a[i][i] % mod;
        ll iv=inv(a[i][i]);
        for(int j = i + 1; j < n; j++){
            if(!a[j][i]) continue;
            ll f = a[j][i] * iv % mod;
            for(int k = i; k < n; k++)
                a[j][k] = (a[j][k] - f * a[i][k] % MOD + MOD) % MOD;
        }
    }
    return ans;
}
ll BEST(int n){
    vector<vector<int> > e(n);
    vector<int> in(n),out(n);
    int m = 0;
    for(int i = 0; i < n; i++){
        int s;
        cin >> s;
        out[i] = s;
        m += s;
        while(s--){
            int v;
            cin >> v;
            --v;
            e[i].push_back(v);
            in[v]++;
        }
    }
    if(!m) return 1;
    for(int i = 0; i < n; i++)
        if(in[i] != out[i]) return 0;
    if(!out[0]) return 0;
    vector<int> id(n, -1), ver;
    for(int i = 0; i < n; i++){
        if(in[i] || out[i]){
            id[i] = ver.size();
            ver.push_back(i);
        }
    }
    int k = ver.size();
    vector<vector<ll> > L(k, vector<ll>(k));
    for(int u = 0; u < n; u++){
        if(id[u] < 0)continue;
        for(int v : e[u]){
            L[id[u]][id[u]]++;
            if(L[id[u]][id[u]] >= mod) L[id[u]][id[u]] -= mod;
            L[id[u]][id[v]] = (L[id[u]][id[v]] - 1 + mod) % mod;
        }
    }
    vector<vector<ll> > a(k-1, vector<ll>(k-1));
    int x = 0;
    for(int i = 0; i < k; i++){
        if(i == id[0]) continue;
        int y = 0;
        for(int j = 0; j < k; j++){
            if(j == id[0]) continue;
            a[x][y++] = L[i][j];
        }
        x++;
    }
    ll tr = det(a,k-1);
    ll ans = tr * out[0] % mod;
    for(int i = 0; i < n; i++)
        if(out[i]) ans = ans * fact[out[i] - 1] % mod;
    return ans;
}
```

**注意事项**:
1. 务必确保图是欧拉图（入度=出度）。
2. `solve` 中的 `root` 可以是任意节点，结果相同。
3. 如果题目要求“本质不同”的回路（旋转同构视为相同），请将结果除以边数 $m$（需计算 $m$ 的逆元）。

## LGV 引理 (Lindström–Gesselien–Viennot Lemma)

**该部分内容可以选择性忽略！**

**特性**: 计算不相交路径组的数量。适用于 DAG，特别是网格图。
**公式**: 
$$ \det(M) = \sum_{\pi \in S_n} \text{sgn}(\pi) \prod_{i=1}^n P(A_i \to B_{\pi(i)}) $$
若源点 $A_i$ 和汇点 $B_i$ 满足“任何非恒等排列的路径组必然相交”的几何条件（如网格中 $A_i, B_i$ 单调排列），则 $\det(M)$ 直接等于不相交路径组数。
**注意**: 
1. 需要计算任意 $A_i$ 到 $B_j$ 的路径数 $P(A_i \to B_j)$。
2. 路径数计算取决于图的结构（网格图用组合数，一般 DAG 用 DP）。
3. 最后求 $n \times n$ 行列式。

**用途**: 封装 LGV 引理，支持自定义路径计数函数。

```cpp
/**
 * LGV Lemma Template
 * Calculates number of non-intersecting path systems.
 * Depends on matrix_tree.cpp (for det)
 */
#include <bits/stdc++.h>
#include "matrix_tree.cpp"
using namespace std;
typedef long long ll;

const int MAXN = 505;
ll comb[MAXN][MAXN];
// Precompute combinations for Grid Graphs
void init_comb(int n, ll mod) {
    mod = mod;
    for (int i = 0; i <= n; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % mod;
        }
    }
}
// Path count in Grid from (x1, y1) to (x2, y2)
// Only Right (x+1) and Up (y+1) moves allowed
ll grid_path_count(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (dx < 0 || dy < 0) return 0;
    return comb[dx + dy][dx];
}

struct LGVSolver {
    int n; // Number of pairs
    vector<pair<int,int>> sources;
    vector<pair<int,int>> sinks;

    // Function pointer for path counting
    // ll (*path_func)(int, int, int, int); 
    LGVSolver(int _n) : n(_n) {}
    
    void set_sources(const vector<pair<int,int>>& A) {
        sources = A;
    }
    
    void set_sinks(const vector<pair<int,int>>& B) {
        sinks = B;
    }
    
    // Calculate determinant using custom path count function
    // For grid graphs, use grid_path_count
    ll solve(ll (*path_func)(int, int, int, int)) {
        vector<vector<ll>> M(n, vector<ll>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                auto [sx, sy] = sources[i];
                auto [tx, ty] = sinks[j];
                M[i][j] = path_func(sx, sy, tx, ty);
            }
        }
        return det(M, n);
    }
};
```

### API 速查表

| 函数               | 作用               | 前置条件               | 时间复杂度                    |
| ------------------ | ------------------ | ---------------------- | ----------------------------- |
| `init_comb`        | 预处理组合数       | $mod$ 设定             | $O(N^2)$                      |
| `grid_path_count`  | 网格两点路径数     | $x2 \ge x1, y2 \ge y1$ | $O(1)$                        |
| `LGVSolver::solve` | 计算不相交路径组数 | 源汇点已设置           | $O(n^3 + n^2 \cdot T_{path})$ |

**注意事项**:
1. LGV 引理要求路径是不相交的（Vertex-disjoint or Edge-disjoint depending on context, usually Vertex-disjoint in grids implies Edge-disjoint for simple paths）。
2. 必须保证源点和汇点的顺序使得只有恒等排列的路径组可能不相交（例如 $A_i$ 和 $B_i$ 都在对角线上，且坐标单调）。
3. 如果不是网格图，需自行实现 `path_func`，例如通过拓扑排序 DP 计算 DAG 中两点间路径数。


## 二次剩余

见“多项式”

## 牛顿迭代

如果 $G(F(x))\equiv 0\pmod {x^n}$，且 $F_0(x)\equiv F(x)\pmod{x^{\lceil n/2\rceil}}$，则：
$$
F(x)\equiv F_0(x)-\frac{G(F_0(x))}{G'(F_0(x))}\pmod{x^n}
$$

## Pollard-Rho

```cpp
bool miller_rabin(int n){
	if(n == 2) return 1;
	if(n < 2 || !(n & 1)) return 0;
	int m = n - 1, k = 0;
	while(!(m & 1)) k++, m >>= 1;
	for(int i = 0; i < Times; i++){
		int a = rd() % (n - 1) + 1;
		int x = qp(a, m, n);
		int y = 0;
		for(int j = 0; j < k; j++){
			y=(__int128)(x) * x % n;
			if(y == 1 && x != 1 && x != n - 1) return 0;
			x = y;
		}
		if(y != 1) return 0;
	}
	return 1;
}
int ans;
int cal(int x, int c, int n){ return ((__int128)(x) * x + c) % n; }
int pollard_rho(int n, int c){
	int i = 1, k = 2;
	int x=rand() % (n - 1) + 1, y = x;
	while(1){
		i++;
		x = ((__int128)(x) * x % n + c) % n;
		int d = gcd((y - x + n) % n, n);
		if(1 < d && d < n) return d;
		if(x == y) return n;
		if(i == k){
			y = x;
			k <<= 1;
		}
	}
}
map<int, int> E;
void find(int n, int c){
	if(n == 1) return;
	if(miller_rabin(n)){
        ++E[n];
		return;
	}
	int p = n, k = c;
	while(p >= n) p = pollard_rho(p, c--);
	find(p, k), find(n / p, k);
}
```

## 高数

### 单位根

定义：
$$
\omega_n^k=\cos\left(\frac{2\pi}nk\right)+i\sin\left(\frac{2\pi}nk\right)
$$
单位根反演：

$$
[n\mid k]=\frac1n\sum_{i=0}^{n-1}\omega_n^{ik}
$$

### 洛必达

洛必达法则：如果在 $\lim\limits_{x\to a}\frac{f(x)}{g(x)}$ 中，$f(a)=g(a)=0$。那么：
$$
\lim\limits_{x\to a}\frac{f(x)}{g(x)}=\lim\limits_{x\to a}\frac{f'(x)}{g'(x)}
$$

### 泰勒展开（特例）

$$
f(x)=\sum_{i=0}^{+\infty}\dfrac{f^{(i)}(0)x^i}{i!}
$$

可以得到 $e^{ix}=\cos x+i\sin x$，特例为 $e^{i\pi}+1=0$。

### 三角恒等变换

- $\cos^2\theta+\sin^2\theta=1$；
- 关于 $\cos$ 和 $\sin$：奇变偶不变，符号看象限。
- 和差角公式：
  - $\cos(x+y)=\cos x\cos y-\sin x\sin y$；
  - $\sin(x+y)=\cos x\sin y+\sin x\cos y$。
- 旋转坐标轴：
  - 将 $(x,y)$ 所在的坐标轴旋转了 $\theta$ 后，坐标会变成 $(x\cos\theta-y\sin\theta,x\sin\theta+y\cos\theta)$。

## 原根

```cpp
#define int long long
const int N = 1e6 + 10;
int n, d, cnt, ft[N], ans[N];
int qp(int x, int y){ // 这里的模数是 n
    int res = 1;
    while(y){
        if(y & 1) res = res * x % n;
        x = x * x % n, y >>= 1;
    }
    return res;
}
int ola(int n, int res = 0, int p = 2) {
	res = n;
	while(p * p <= n) {
		if(n % p == 0) {
			while(n % p == 0) n /= p;
			res = res / p * (p - 1);
		}
		++p;
	}
	if(n > 1) res = res / n * (n - 1);
	return res;
}
void getft(int n, int _n = 0, int p = 2) {
	_n = n;
	while(p * p <= n) {
		if(n % p == 0) {
			while(n % p == 0) n /= p;
			ft[++cnt] = _n / p;
		}
		++p;
	}
	if(n > 1) ft[++cnt] = _n / p;
}
bool chk(int n) {
	for(int i = 1; i <= cnt; i++)
		if(qp(n, ft[i]) == 1) return 0;
	return 1;
}

void work() {
	cin >> n;
	int phi = ola(n), t = 0;
	cnt = 0;
	if(n == 2){
		cout << "1\n1\n";
		return;
	}
	getft(phi);
	for(int i = 1; i <= 200; i++){
		if(gcd(i, n) == 1 && chk(i)) {
			t = i;
			break;
		}
    }
	int s = 0;
	if(t){
		for(int i = 1; i <= phi - 1; i++)
			if (gcd(i, phi) == 1) ans[++s] = qp(t, i);
		sort(ans + 1, ans + s + 1);
	}
	cout << s << '\n';
	for(int i = 1; i <= s; i++) 
        cout << ans[i] << ' ';
	cout << '\n';
}
```

使用方式：调用 work，输入 $n$，输出 $n$ 的所有原根，一般可能只用的上最小原根。

## 集合幂级数

代码中记 $N=2^{n}-1$ 。

### $\textsf{FMT}$

高维前缀和及其逆运算，正确性显然。

又称为 $\textsf{Zeta}$ 和 $\textsf{Mobius}$ 。

```C++
void FMT(int *a, int xs) {
	if (xs == 1) {
		rep(i, 0, n - 1)
			rep(j, 0, N - 1)
				if (j >> i & 1) a[j] = (a[j] + a[j ^ (1 << i)]) % M;
	} else {
		rep(i, 0, n - 1)
			rep(j, 0, N - 1)
				if (j >> i & 1) a[j] = (a[j] - a[j ^ (1 << i)] + M) % M;
	}
}
```

### $\textsf{FWT}$

设 $c(i,j)$ 是 $a_j$ 对 $A_i$ 的贡献系数：$A_i=\sum_{j=0}^{n-1}c(i,j)a_j$ 。

根据 FWT 的基本性质得到：$c(i,j)c(i,k)=c(i,j\oplus k)$ 。

设 $$g(l_1,l_2,h) $$ 为 $a[l,l_1+2^{h})\to A[l_2,l_2+2^{h})$ 的贡献系数计算过程：

考虑把最高位提出来：

$g(l_1,l_2,h)$ 等价于下列过程：

1. $g(l_1,l_2,h-1)c(0,0)$

2. $g(l_1,l_2+2^{h-1},h-1)c(0,1)$

3. $g(l_1+2^{h-1},l_2,h-1)c(1,0)$

4. $g(l_1+2^{h-1},l_2+2^{h-1},h-1)c(1,1)$

计算流程如下：

1. 划分 将长度为 $2^h$ 根据最高位划分成前后 $2^{h-1}$ 个数构成的两段。

2. 递归求解 分别对左右两边 FWT 

3. 合并阶段 $c(0,0)A'_0+c(0,1)A'_1\to A_0$ ；$c(1,0)A'_0+c(1,1)A'_1\to A_1$ 。

4. 终止条件，当 $h=0$ 时，返回原数即可。

给出一个递归实现！

```C++
#define mid (s + t >> 1)
inline void A(int &x, int y) { x += y; if (x >= M) x -= M; }
inline int V(int x, int y) { return 1ll * x * y % M; }
void FWT(int a[], const int c[2][2], int s = 0, int t = N, int len = (N + 1) / 2) {
	if (len) {
		FWT(a, c, s, mid, len >> 1), FWT(a, c, mid + 1, t, len >> 1);
		rep(i, s, t) a_[i] = a[i], a[i] = 0;
		rep(i, s, mid) rep(j, 0, 1) rep(k, 0, 1)
			A(a[i + j * len], V(c[j][k], a_[i + k * len]));
	}
}
```

这个 FWT 效率很不错的，而且直接传这个 $c$ 矩阵就可以使用，非常便捷！

```dylan
int cor[2][2][2] = {{{1, 0}, {1, 1}}, {{1, 0}, {M - 1, 1}}};
int cad[2][2][2] = {{{1, 1}, {0, 1}}, {{1, M - 1}, {0, 1}}};
int cxo[2][2][2] = {{{1, 1}, {1, M - 1}}, {{(M + 1) / 2, (M + 1) / 2}, {(M + 1) / 2, (M - 1) / 2}}};
```

Gcend 给了一堆正常 and 好用的递推：

```cpp
#define int long long
#define poly vector<int>
using namespace std;
const int mod = 998244353, inv2 = 499122177;
void OR(poly &f, int op){
    int n = f.size();
    for(int len = 2, k = 1; len <= n; len <<= 1, k <<= 1){
        for(int i = 0; i < n; i += len){
            for(int j = 0; j < k; j++){
                f[i + j + k] += f[i + j] * op;
                if(f[i + j + k] >= mod) f[i + j + k] -= mod;
                else if(f[i + j  +k] < 0) f[i + j + k] += mod;
            }
        }
    }
    return ;
}
void AND(poly &f, int op){
    int n = f.size();
    for(int len = 2, k = 1; len <= n; len <<= 1, k <<= 1){
        for(int i = 0; i < n; i += len){
            for(int j = 0; j < k; j++){
                f[i + j] += f[i + j + k] * op;
                if(f[i + j] >= mod) f[i + j] -= mod;
                if(f[i + j] < 0) f[i + j] += mod;
            }
        }
    }
    return ;
}
void XOR(poly &f, int op){
    int n = f.size();
    for(int len = 2, k = 1; len <= n; len <<= 1, k <<= 1){
        for(int i = 0; i< n; i += len){
            for(int j = 0; j < k; j++){
                f[i + j] += f[i + j + k];
                f[i + j + k] = f[i + j] - 2ll * f[i + j + k];
                f[i + j] = f[i + j] % mod * op % mod;
                f[i + j + k] = f[i + j + k] % mod * op % mod;
                if(f[i + j] >= mod) f[i + j] -= mod;
                if(f[i + j + k] < 0) f[i + j + k] += mod; 
            }
        }
    }
    return ;
}
poly operator | (poly a, poly b){
    int n = a.size();
    OR(a, 1), OR(b, 1);
    for(int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod;
    OR(a, -1); return a;
}
poly operator & (poly a, poly b){
    int n = a.size();
    AND(a, 1), AND(b, 1);
    for(int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod;
    AND(a, -1); return a;
}
poly operator ^ (poly a, poly b){
    int n = a.size();
    XOR(a, 1), XOR(b, 1);
    for(int i = 0; i< n; i++) a[i] = a[i] * b[i] % mod;
    XOR(a, inv2); return a;
}
```

这个板子重载了，可以直接用。

### 子集卷积

注意到 $(x,y)\to z$ 等价于 $x|y=z$ 且 $popc(x)+popc(y)=popc(z)$ 。

按所有 $popc$ 作 $\textsf{Zeta}$ ，按上述等式求点积之后 使用 $\textsf{Mobius}$ 即可。

```C++
rep(i, 0, n) FMT(a[i], 1), FMT(b[i], 1);
rep(w, 0, n)
	rep(i, 0, N - 1) {
		rep(j, 0, w)
			c[w][i] = (c[w][i] + 1ll * a[j][i] * b[w - j][i] % M) % M;
	}
rep(w, 0, n) FMT(c[w], M - 1);
```

### $\textsf{exp}$

它的泰勒展开是 $e^{F(x)}=\sum_{n\geq 0}\frac{F^n(x)}{n!}$ 。

#### $\textsf{组合意义}$

将 $[x^S]F(x)$ 系数视为划分出一个 $S$ 的子集的  $a$，则 $[x^S]e^{F(x)}$ 为 $S$ 的所有划分方案的 $\prod a$ 之和。

特别地 $[x^\emptyset]F(x)=0$ 。设 $S$ 的最大元为 $u$ 。不妨枚举 $u$ 所在的小集合。$[x^S]e^{F(x)}=\sum_{u\in T,T\subseteq S}[x^T]F(x)\times [x^{S-T}]e^{F(x)}$ 。

 $O(3^n)$ 的实现显然。

$O(n^22^n)$ 相当于子集卷积。从小到大枚举 $u$ 。

对 $popc(T)=z$ 且 $T$ 包含 $u$ 的集合 $T$ 分类作 Zeta 。

记 $popc(T)=x$ ，$popc(S-T)=y$ ，枚举 $(x,y)$ ， $S$， 点乘贡献到 $popc=x+y,S'=S∪\{u\}$ 。

乍一看感觉是 $O(n^32^n)$ ？实则不然，我们有不等式 $\sum_{u=0}^{n-1}2^u <2^n$ 。所以是 $O(n^22^n)$ 的复杂度，支持非素数模数。

```C#
rep(i, 0, (1ull << n) - 1) cin >> a[i], f[pc[i]][i] += a[i];
g[0][0] = 1;
rep(u, 1, n) {
	int K = (1ull << u - 1);
	rep(i, 1, u) FMT(f[i] + K, u - 1, 1);
	rep(i, 0, u - 1) FMT(g[i], u - 1, 1);
	rep(i, 1, u)
		rep(j, 0, u - i)
			rep(S, 0, (1 << u - 1) - 1) {
				g[i + j][S + K] = (g[i + j][S + K] + 1ull * f[i][S + K] * g[j][S]);
			}
	rep(i, 0, u - 1) FMT(g[i], u - 1, (ull)(-1));
	rep(i, 1, u) FMT(g[i] + K, u - 1, (ull)(-1));
}
```

### $\textsf{ln}$

#### 组合意义

如果说 exp 对应的问题是：已知连通图方案数，求所有图方案数。

那么 ln 对应的问题就是：已知所有图方案数，求联通图方案数。

$[x^S]G(x)=[x^S]F(x)-\sum_{T\subseteq S,u\subseteq T}[x^T]G(x)\times [x^{S-T}]F(x)$ 。

做法是容斥：所有图-不连通图。每次钦定最大元分给一个别的点集，与当前点集独立，这个 $O(3^n)$ 还是很好写。

$O(2^nn^2)$ 的做法也是一个子集卷积，我们初始令 $[x^S]G(x)=[x^S]F(x)$ ，从小到大枚举 $u$ ，令 $G$ 和 $F$ 做添加 $\{u\}$ 的子集卷积即可，处理完后令 $[x^S]G(x)\to [x^S]F(x)-[x^S]G(x)$ ？。

答案是：这个做法·是假的。因为 $ln$ 需要半在线，我们这么做不好界定 减法的时间，不妨先枚举 $i$ 再枚举 $u$ ，就可以动态更新 $G$ 了。

```C++
rep(u, 0, n - 1) {
	const int K = 1 << u;
	rep(k, 0, u) FMT(f[k], u, 1);
	rep(k, 1, n) rep(S, K, 2 * K - 1) g[k][S] = 0;
	rep(k, 1, n) {
		rep(S, 0, K - 1) {
			int sum = 0;
			rep(i, 1, k - 1)
				sum += g[i][S + K] * f[k - i][S];
			g[k][S + K] = sum;
		}
		FMT(g[k] + K, u, 2);
		rep(S, 0, K - 1) {
			g[k][S + K] = f[k][S + K] - g[k][S + K];
			ans[k][S + K] = g[k][S + K];
		}
		FMT(g[k] + K, u, 1);
	}
	rep(k, 0, u) FMT(f[k], u, 2);
}
```

# 图论

## tarjan 全家桶

```cpp
// ==================== SCC（有向图强连通分量） ====================
vector<int> dfnScc, lowScc, stkScc;
vector<bool> inStack;
vector<vector<int> > scc;
int sccCnt;
void tarjan_scc(int u) {
    dfnScc[u] = lowScc[u] = ++timer;
    stkScc.push_back(u);
    inStack[u] = 1;
    for (int v : gDir[u]) {
        if (!dfnScc[v]) {
            tarjan_scc(v);
            lowScc[u] = min(lowScc[u], lowScc[v]);
        }
        else if (inStack[v]) {          // 必须判在栈中，防止横叉边
            lowScc[u] = min(lowScc[u], dfnScc[v]);
        }
    }
    if (lowScc[u] == dfnScc[u]) {
        vector<int> comp;
        while (1) {
            int v = stkScc.back(); stkScc.pop_back();
            inStack[v] = false;
            comp.push_back(v);
            if (v == u) break;
        }
        scc.push_back(comp);
    }
}
void solve_scc() {
    dfnScc.assign(n + 1, 0);
    lowScc.assign(n + 1, 0);
    inStack.assign(n + 1, false);
    timer = 0;
    scc.clear();
    for (int i = 1; i <= n; ++i) {
        if (!dfnScc[i]) tarjan_scc(i);
    }
    sccCnt = scc.size();
}
// ==================== 点双连通分量 ====================
vector<int> dfnV, lowV, stkV;    // stkV 是边栈
vector<vector<int>> bcc;
void tarjan_vbcc(int u, int pe) {
    dfnV[u] = lowV[u] = ++timer;
    for (int eid : g[u]) {
        if (eid == pe) continue;
        int v = (edges[eid].u == u ? edges[eid].v : edges[eid].u);
        if (!dfnV[v]) {
            stkV.push_back(eid);          // 树边入栈
            tarjan_vbcc(v, eid);
            lowV[u] = min(lowV[u], lowV[v]);
            if (lowV[v] >= dfnV[u]) {
                vector<int> verts;
                while (true) {
                    int e = stkV.back(); stkV.pop_back();
                    verts.push_back(edges[e].u);
                    verts.push_back(edges[e].v);
                    if (e == eid) break;
                }
                sort(verts.begin(), verts.end());
                verts.erase(unique(verts.begin(), verts.end()), verts.end());
                bcc.push_back(verts);
            }
        } else if (dfn[v] < dfn[u]) {
            stkV.push_back(eid);          // 回边入栈
            lowV[u] = min(lowV[u], dfnV[v]);
        }
    }
}
void solve_vbcc() {
    dfnV.assign(n + 1, 0);
    lowV.assign(n + 1, 0);
    usedEdge.assign(edges.size(), false);
    timer = 0;
    bcc.clear();
    stkV.clear();
    for (int i = 1; i <= n; ++i) {
        if (!dfnV[i]) {
            if (g[i].empty()) bcc.push_back({i});
            else tarjan_vbcc(i, -1);
        }
    }
}
// ==================== 边双连通分量 ====================
vector<int> dfnE, lowE, compE;
vector<bool> isBridge;
int ebcCnt;
void tarjan_bridge(int u, int pe) {
    dfnE[u] = lowE[u] = ++timer;
    for (int eid : g[u]) {
        if (eid == pe) continue;
        int v = (edges[eid].u == u ? edges[eid].v : edges[eid].u);
        if (!dfnE[v]) {
            tarjan_bridge(v, eid);
            lowE[u] = min(lowE[u], lowE[v]);
            if (lowE[v] > dfnE[u]) isBridge[eid] = true;
        } else {
            lowE[u] = min(lowE[u], dfnE[v]);   // 不用判栈
        }
    }
}
void dfs_ebcc(int u, int cid) {
    compE[u] = cid;
    for (int eid : g[u]) {
        if (isBridge[eid]) continue;
        int v = (edges[eid].u == u ? edges[eid].v : edges[eid].u);
        if (compE[v] == -1) dfs_ebcc(v, cid);
    }
}
void solve_ebcc() {
    dfnE.assign(n + 1, 0);
    lowE.assign(n + 1, 0);
    isBridge.assign(edges.size(), false);
    timer = 0;

    for (int i = 1; i <= n; ++i) {
        if (!dfnE[i]) tarjan_bridge(i, -1);
    }
    compE.assign(n + 1, -1);
    ebcCnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (compE[i] == -1) dfs_ebcc(i, ebcCnt++);
    }
}
```

## SPFA-SLF-LLL

```cpp
int spfa_slf_lll(int S){
	deque<int> q;
	dis[S] = 0;
	int tmp;
	q.push_back(S);
	int sum = dis[S], num = 1;
	cnt[S]++;
	visited[S] = true; //入队即true。
	int flag = 0;         //标志，若为真，则表示存在负环。
	while(!q.empty()){
		tmp = q.front();
		while(dis[tmp] * num > sum){
			//lll优化
			q.pop_front();
			q.push_back(tmp);
			tmp = q.front();
		}
		q.pop_front();
		sum -= dis[tmp];
		num--;
		visited[tmp] = false; //出队则false。
		int v, w;
		int t = graph[tmp].size();//避免多次调用此函数。
        //松弛操作
        for(int i = 0; i< t; i++){
			v = graph[tmp][i].to;
			w = graph[tmp][i].w;
			if(dis[v] > dis[tmp] + w){
				dis[v] = dis[tmp] + w;//更新最短路径
				if(!visited[v]){
					//判断是否在队列中
					if(!q.empty() && dis[v] > dis[q.front()]){
						//和队头元素进行比较。
						q.push_back(v);//大于入队尾
					}
					else q.push_front(v); //小于入队头
					sum += dis[v];
					num++, cnt[v]++;
					if(cnt[v] > n){ flag = 1; return flag; }
					visited[v] = true;
				}
			}
        }
	}
	return flag;
}
```

## 最小树形图（朱刘算法）

```cpp
typedef long long ll;
const ll INF = numeric_limits<ll>::max() / 4;
struct Edge {
    int u, v;   // 起点 u -> 终点 v
    ll  w;      // 边权
};
/*
朱刘算法（Chu-Liu / Edmonds）
求有向图中以 root 为根的最小树形图（可以到达所有点）
@param n      顶点数，编号 [0, n)
@param root   根节点编号
@param edges  边集
@return       最小树形图的总权值；若不存在则返回 -1
时间复杂度 O(n * m)
*/
ll chuLiuEdmonds(int n, int root, vector<Edge> edges) {
    ll ans = 0;
    vector<int> pre(n), id(n), vis(n);
    vector<ll>  in(n);
    while (true) {
        // ① 为每个点选一条最小入边
        fill(in.begin(), in.end(), INF);
        for (const Edge& e : edges)
            if (e.u != e.v && e.w < in[e.v])
                in[e.v] = e.w, pre[e.v] = e.u;
        // 除根以外有孤立点，说明不存在树形图
        for (int i = 0; i < n; ++i)
            if (i != root && in[i] == INF) return -1;
        // ② 找环（每个点沿最小入边走，必然走到环或根）
        int cnt = 0;
        fill(id.begin(), id.end(), -1);
        fill(vis.begin(), vis.end(), -1);
        in[root] = 0;
        for (int i = 0; i < n; ++i) {
            ans += in[i];
            int v = i;
            while (vis[v] != i && id[v] == -1 && v != root)
                vis[v] = i, v = pre[v];
            if (v != root && id[v] == -1) {           // 发现一个新环
                for (int u = pre[v]; u != v; u = pre[u])
                    id[u] = cnt;
                id[v] = cnt++;
            }
        }
        if (cnt == 0) break;                          // 没有环：算法结束
        // ③ 缩点：环外的点各自成新点，重建所有边
        for (int i = 0; i < n; ++i)
            if (id[i] == -1) id[i] = cnt++;
        for (Edge& e : edges) {
            int u = e.u, v = e.v;
            e.u = id[u], e.v = id[v];
            if (id[u] != id[v]) e.w -= in[v];         // 环上入边的代价已计入答案
        }
        n = cnt;
        root = id[root];
    }
    return ans;
}
```

用法：`chuLiuEdmonds(n, root, edges)`，其中，$n$ 为总点数，$root$ 为根，$edges$ 为边集，用的是 $\text{0-based}$。

## 最小斯坦纳树

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int MAXN = 1010;        // 最大顶点数
const int MAXK = 10;          // 最大终端数（1<<MAXK 不宜过大）
// ---------- 邻接表：vector 数组 ----------
struct Edge {
    int to;
    ll  w;
};
vector<Edge> adj[MAXN];       // adj[u] 存 u 的所有出边
void addEdge(int u, int v, ll w) {
    adj[u].push_back({v, w});
}
// ---------- 斯坦纳树 ----------
int terminal[MAXK];           // 终端节点编号
ll  dp[1 << MAXK][MAXN];      // dp[mask][i]：以 i 为根覆盖终端集合 mask 的最小代价
/*
@param n  顶点数，编号 [0, n)
@param k  终端数，terminal[0..k-1]
@return   最小斯坦纳树的边权和；不可达返回 -1
*/
ll steinerTree(int n, int k) {
    int full = (1 << k) - 1;
    // 初始化
    for (int mask = 0; mask <= full; ++mask)
        for (int i = 0; i < n; ++i)
            dp[mask][i] = INF;
    for (int i = 0; i < k; ++i)
        dp[1 << i][terminal[i]] = 0;
    // 按 mask 从小到大枚举
    for (int mask = 1; mask <= full; ++mask) {
        // ① 子集合并
        for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
            int other = mask ^ sub;
            for (int i = 0; i < n; ++i) {
                if (dp[sub][i] != INF && dp[other][i] != INF) {
                    ll v = dp[sub][i] + dp[other][i];
                    if (v < dp[mask][i]) dp[mask][i] = v;
                }
            }
        }
        // ② Dijkstra 松弛：在图上扩展根节点
        priority_queue<pair<ll, int>,
                       vector<pair<ll, int>>,
                       greater<pair<ll, int>>> pq;
        for (int i = 0; i < n; ++i)
            if (dp[mask][i] != INF) pq.push({dp[mask][i], i});
        while (!pq.empty()) {
            auto pr = pq.top(); pq.pop();
            ll d = pr.first; int u = pr.second;
            if (d != dp[mask][u]) continue;

            for (const Edge& e : adj[u]) {
                int v = e.to;
                ll  w = e.w;
                if (dp[mask][v] > d + w) {
                    dp[mask][v] = d + w;
                    pq.push({dp[mask][v], v});
                }
            }
        }
    }
    // 取包含所有终端时的最小代价
    ll ans = INF;
    for (int i = 0; i < n; ++i)
        ans = min(ans, dp[full][i]);
    return ans == INF ? -1 : ans;
}
```

用法：`steinerTree(n, k)`，其中，$n$ 为总点数，$k$ 为要求联通的点数，$terminal$ 里面存的是所有“终端”，$\text{0-based}$，存储下标 $0\sim k-1$。需要提前加边。

加无向边 $(u,v,w)$：

```cpp
addEdge(u, v, w);
addEdge(v, u, w);
```

## 点分治

```cpp
const int N = 1e4 + 10;
int m, rt, cnt, tot, a[N], dis[N], fa[N], head[N], q[110], mxsz[N], sz[N];
bool vis[N], ans[110];
struct node{
	int nxt, to, w;
}e[N << 1];
void add(int x, int y, int z){
	e[++cnt].nxt = head[x];
	e[cnt].to = y, e[cnt].w = z;
	head[x] = cnt;
    return ;
}
void get_root(int u, int f, int siz){
	sz[u] = 1, mxsz[u] = 0;
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].to;
		if(v == f || vis[v]) continue;
		get_root(v, u, siz);
		sz[u] += sz[v], mxsz[u] = max(mxsz[u], sz[v]);
	}
	mxsz[u] = max(mxsz[u], siz - sz[u]);
	if(!rt || mxsz[u] < mxsz[rt]) rt = u;
	return ;
}
bool cmp(int x, int y){
	return dis[x] < dis[y];
}
void get_dis(int u, int f, int d, int root){
	a[++tot] = u, dis[u] = d, fa[u] = root;
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].to;
		if(v == f || vis[v]) continue;
		get_dis(v, u, d + e[i].w, root);
	}
	return ;
}
void calc(int u){
	tot = 0, a[++tot] = u, dis[u] = 0, fa[u] = u;
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].to;
		if(vis[v]) continue;
		get_dis(v, u, e[i].w, v);
	}
	sort(a + 1, a + tot + 1, cmp);
	for(int i = 1; i <= m; i++){
		int l = 1, r = tot;
		if(ans[i]) continue;
		while(l < r){
			if(dis[a[l]] + dis[a[r]] > q[i]) r--;
			else if(dis[a[l]] + dis[a[r]] < q[i]) l++;
			else if(fa[a[l]] == fa[a[r]]){
				if(dis[a[r]] == dis[a[r - 1]]) r--;
				else l++;
			}
			else {
				ans[i] = 1;
				break;
			}
		}	
	}
	return ;
}
void solve(int u){
	vis[u] = 1, calc(u);
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].to;
		if(vis[v]) continue;
		rt = 0, get_root(v, 0, sz[v]), solve(rt);
	}
	return ;
}
int main(){
	int n;
	cin >> n >> m;
	for(int i = 1, x, y, z; i < n; i++)
        cin >> x >> y >> z, add(x, y, z), add(y, x, z);
	for(int i = 1; i <= m; i++) cin >> q[i];
	get_root(1, 0, n), solve(rt);
	for(int i = 1; i <= m; i++){
		if(ans[i]) cout << "AYE\n";
		else cout << "NAY\n";
	}
	return 0;
}
```

给定一棵有 *n* 个点的树，询问树上距离为 *k* 的点对是否存在。

## 动态点分治（点分树）

```cpp
void calcsiz(int x, int f) {
    siz[x] = 1;
    maxx[x] = 0;
    for (int j = h[x]; j; j = nxt[j])
        if (p[j] != f && !vis[p[j]]) {
            calcsiz(p[j], x);
            siz[x] += siz[p[j]];
            maxx[x] = max(maxx[x], siz[p[j]]);
        }
    maxx[x] =
        max(maxx[x], sum - siz[x]);  // maxx[x] 表示以 x 为根时的最大子树大小
    if (maxx[x] < maxx[rt])
        rt = x;  // 这里不能写 <= ，保证在第二次 calcsiz 时 rt 不改变
}
void pre(int x) {
    vis[x] = true;  // 表示在之后的过程中不考虑 x 这个点
    for (int j = h[x]; j; j = nxt[j])
        if (!vis[p[j]]) {
            sum = siz[p[j]];
            rt = 0;
            maxx[rt] = inf;
            calcsiz(p[j], -1);
            calcsiz(rt, -1);  // 计算两次，第二次求出以 rt 为根时的各子树大小
            fa[rt] = x;
            pre(rt);  // 记录点分树上的父亲
        }
}
int main() {
    sum = n;
    rt = 0;
    maxx[rt] = inf;
    calcsiz(1, -1);
    calcsiz(rt, -1);
    pre(rt);
}
```

## Kruskal 重构树

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct edge {
    int x, y, w;
} e[N];
bool cmp(edge x, edge y) {
    return x.w < y.w;
}
int n, m, q, cnt, fa[N][25], faa[N], val[N], dep[N];
vector<int> v[N];
int find(int x) {
    if (x == faa[x])
        return x;

    return faa[x] = find(faa[x]);
}
void kruskal() {
    cnt = n;
    sort(e + 1, e + m + 1, cmp);
    for (int i = 1; i < 2 * n; i++)
        fa[i][0] = faa[i] = i;
    for (int i = 1; i <= m; i++) {
        int x = find(e[i].x), y = find(e[i].y);
        if (x == y) continue;
        fa[x][0] = fa[y][0] = faa[x] = faa[y] = ++cnt;
        val[cnt] = e[i].w;
        v[x].push_back(cnt), v[y].push_back(cnt);
        v[cnt].push_back(x), v[cnt].push_back(y);
    }
    return ;
}
void dfs(int x) {
    dep[x] = dep[fa[x][0]] + 1;
    for (auto i : v[x]) {
        if (i == fa[x][0]) continue;
        dfs(i);
    }
    return ;
}
void init() {
    for (int j = 1; (1 << j) < 2 * n; j++)
        for (int i = 1; i < 2 * n; i++)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
    return ;
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 20; i >= 0; i--)
        if (dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    if (x == y)
        return x;
    for (int i = 20; i >= 0; i--)
        if (fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
int main() {
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++)
        cin >> e[i].x >> e[i].y >> e[i].w;
    kruskal();
    for (int i = 1; i <= cnt; i++) {
        if (!dep[i]) {
            int f = find(i);
            dfs(f);
        }
    }
    init();
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (find(x) != find(y))
            cout << -1 << "\n";
        else
            cout << val[lca(x, y)] << "\n";
    }
    return 0;
}
```

最小瓶颈路的代码，倍增实现。

## 圆方树

```cpp
/*
    圆方树（Round-Square Tree）模板
    用途：处理无向图上与点双连通分量、割点相关的路径问题。
    编号约定：
    - 圆点（原图节点）：1 .. n
    - 方点（每个点双新建）：n+1 .. tot
    建树核心：
    Tarjan 求点双，每个点双新建一个方点，
    方点连接该点双内的所有圆点，得到一棵树（图不连通时为森林）。
    常用姿势：
    - 方点权值设为 1，圆点权值设为 0：
    路径上方点个数 = 路径上必经点数 - 1（两端都是圆点）。
    - 需要别的权值时，在 build() 后覆盖 val 再 preprocess()。
*/
class RoundSquareTree {
public:
    vector<long long> val;   // 节点权值：默认圆点 0，方点 1
    explicit RoundSquareTree(int n) : n(n) {
        maxNodes = 2 * n + 5;
        G = new vector<int>[n + 1];        // 原图
        T = new vector<int>[maxNodes];     // 圆方树
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        val.assign(maxNodes, 0);
        tot = n;
        idx = 0;
        LOG = 0;
    }
    ~RoundSquareTree() {
        delete[] G;
        delete[] T;
    }
    void addEdge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }
    // 构建圆方树（对每个连通块分别 Tarjan）
    void build() {
        for (int i = 1; i <= n; ++i)
            if (!dfn[i]) tarjan(i, 0);
        // 方点权值默认为 1
        for (int i = n + 1; i <= tot; ++i)
            val[i] = 1;
    }
    int nodeCount() const { return tot; }
private:
    int n, tot, idx, LOG, maxNodes;
    vector<int>* G;
    vector<int>* T;
    vector<int> dfn, low, stk;
    vector<int> depth, vis;
    vector<long long> prefix;
    vector<int> up;   // 扁平化倍增表：up[u * LOG + j]
    int upAt(int u, int j) const { return up[(long long)u * LOG + j]; }
    int& upAt(int u, int j) { return up[(long long)u * LOG + j]; }
    void tarjan(int u, int fa) {
        dfn[u] = low[u] = ++idx;
        stk.push_back(u);
        for (int v : G[u]) {
            if (v == fa) continue;
            if (!dfn[v]) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    ++tot;                        // 新建方点
                    int x;
                    do {
                        x = stk.back(); stk.pop_back();
                        T[tot].push_back(x);
                        T[x].push_back(tot);
                    } while (x != v);
                    // 割点 u 也属于该点双
                    T[tot].push_back(u);
                    T[u].push_back(tot);
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
};
```

用法：加边 `addEdge`，然后 `build`。

## 网络流全家桶

### 特性与注意

**用于：**
- 解决各类网络流问题，包括最大流、费用流、上下界网络流、最小割等。
- **支持输出具体方案**：每条边的实际流量、最小割的节点划分。
- 适用于竞赛编程（OI/ACM），所有图结构均采用**链式前向星**实现，避免 `vector` 建图带来的常数开销和内存碎片。

**注意：**
- 节点编号建议从 $1$ 开始。
- 所有容量和费用使用 `long long`，INF 设为 $10^{18}$。
- **链式前向星特性**：正向边索引为 $i$，反向边索引为 $i \oplus 1$。添加边时成对添加。
- 上下界网络流通过构建辅助图求解，方案提取需结合下界和残量流量。

---

### dinic_maxflow.cpp - Dinic 最大流算法

**用途：** 计算最大流，支持输出每条边流量方案和最小割集合。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 20005; // 根据实际边数调整，通常为 M*2
const long long INF = 1e18;

struct Edge {
    int to, next;
    long long cap, flow;
} e[MAXM];

int head[MAXN], tot;
int n, s, t;
int level[MAXN], cur[MAXN];

void init_dinic(int _n) {
    n = _n;
    memset(head, -1, sizeof(head));
    tot = 0;
}

// 返回正向边的索引
int add_edge(int u, int v, long long cap) {
    e[tot] = {v, head[u], cap, 0};
    head[u] = tot++;
    e[tot] = {u, head[v], 0, 0};
    head[v] = tot++;
    return tot - 2; // 返回正向边索引
}

bool bfs() {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i != -1; i = e[i].next) {
            if (e[i].cap - e[i].flow > 0 && level[e[i].to] == -1) {
                level[e[i].to] = level[u] + 1;
                q.push(e[i].to);
            }
        }
    }
    return level[t] != -1;
}

long long dfs(int u, long long f) {
    if (u == t || f == 0) return f;
    long long flow_sum = 0;
    for (int& i = cur[u]; i != -1; i = e[i].next) {
        if (level[e[i].to] == level[u] + 1 && e[i].cap - e[i].flow > 0) {
            long long d = dfs(e[i].to, min(f, e[i].cap - e[i].flow));
            if (d > 0) {
                e[i].flow += d;
                e[i ^ 1].flow -= d;
                flow_sum += d;
                f -= d;
                if (f == 0) break;
            }
        }
    }
    return flow_sum;
}

long long max_flow(int _s, int _t) {
    s = _s; t = _t;
    long long flow = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        flow += dfs(s, INF);
    }
    return flow;
}

// 获取最小割 S 集合
vector<int> get_min_cut_set() {
    vector<int> res;
    vector<bool> vis(n + 1, false);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        res.push_back(u);
        for (int i = head[u]; i != -1; i = e[i].next) {
            if (e[i].cap - e[i].flow > 0 && !vis[e[i].to]) {
                vis[e[i].to] = true;
                q.push(e[i].to);
            }
        }
    }
    return res;
}
```

#### API 速查表

| 函数名称              | 作用                    | 前置条件   | 时间复杂度 |
| --------------------- | ----------------------- | ---------- | ---------- |
| `init_dinic(n)`       | 初始化图                | 无         | $O(n)$     |
| `add_edge(u, v, cap)` | 添加边，返回正向边索引  | 无         | $O(1)$     |
| `max_flow(s, t)`      | 求最大流                | 图已构建   | $O(V^2E)$  |
| `get_min_cut_set()`   | 获取最小割 S 集合点标号 | 已求最大流 | $O(V+E)$   |

**注意事项：**
- 输出方案：遍历所有添加边时记录的索引 `idx`，`e[idx].flow` 即为该边流量。
- 最小割方案：`get_min_cut_set` 返回的点属于 S 集合，其余属于 T 集合。

---

### bounded_network_flow.cpp - 上下界网络流

**用途：** 处理有上下界的可行流、最大流、最小流。通过构建辅助图求解，并还原原图方案。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 40005; // 辅助图边数更多
const long long INF = 1e18;

struct Edge {
    int to, next;
    long long cap, flow;
} e[MAXM];

int head[MAXN], tot;
int n, s, t; // 原图源汇
int ss, tt;  // 超级源汇
long long demand[MAXN];

// 记录原图边的信息
struct OrigEdgeInfo {
    int u, v;
    long long lower, upper;
    int idx; // 正向边在 e 中的索引
};
vector<OrigEdgeInfo> orig_e;

void init_bounded(int _n, int _s, int _t) {
    n = _n; s = _s; t = _t;
    ss = n + 1; tt = n + 2;
    memset(head, -1, sizeof(head));
    tot = 0;
    memset(demand, 0, sizeof(demand));
    orig_e.clear();
}

int add_bounded_edge(int u, int v, long long lower, long long upper) {
    int idx = tot;
    e[tot] = {v, head[u], upper - lower, 0};
    head[u] = tot++;
    e[tot] = {u, head[v], 0, 0};
    head[v] = tot++;
    
    demand[u] -= lower;
    demand[v] += lower;
    
    orig_e.push_back({u, v, lower, upper, idx});
    return idx;
}

void add_aux_edge(int u, int v, long long cap) {
    e[tot] = {v, head[u], cap, 0};
    head[u] = tot++;
    e[tot] = {u, head[v], 0, 0};
    head[v] = tot++;
}

// 内部 Dinic 实现
int level[MAXN], cur[MAXN];
bool bfs_dinic(int S, int T) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[S] = 0;
    q.push(S);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i != -1; i = e[i].next) {
            if (e[i].cap - e[i].flow > 0 && level[e[i].to] == -1) {
                level[e[i].to] = level[u] + 1;
                q.push(e[i].to);
            }
        }
    }
    return level[T] != -1;
}

long long dfs_dinic(int u, int T, long long f) {
    if (u == T || f == 0) return f;
    long long flow_sum = 0;
    for (int& i = cur[u]; i != -1; i = e[i].next) {
        if (level[e[i].to] == level[u] + 1 && e[i].cap - e[i].flow > 0) {
            long long d = dfs_dinic(e[i].to, T, min(f, e[i].cap - e[i].flow));
            if (d > 0) {
                e[i].flow += d;
                e[i ^ 1].flow -= d;
                flow_sum += d;
                f -= d;
                if (f == 0) break;
            }
        }
    }
    return flow_sum;
}

long long dinic_max_flow(int S, int T) {
    long long flow = 0;
    while (bfs_dinic(S, T)) {
        memcpy(cur, head, sizeof(head));
        flow += dfs_dinic(S, T, INF);
    }
    return flow;
}

// 1. 无源汇可行流
pair<bool, vector<long long>> feasible_flow() {
    long long sum_pos_demand = 0;
    for (int i = 1; i <= n; i++) {
        if (demand[i] > 0) {
            add_aux_edge(ss, i, demand[i]);
            sum_pos_demand += demand[i];
        } else if (demand[i] < 0) {
            add_aux_edge(i, tt, -demand[i]);
        }
    }
    
    long long flow = dinic_max_flow(ss, tt);
    if (flow != sum_pos_demand) {
        return {false, {}};
    }
    
    vector<long long> flows;
    for (auto& e : orig_e) {
        flows.push_back(e.lower + e[e.idx].flow);
    }
    return {true, flows};
}

// 2. 有源汇最大流
pair<long long, vector<long long>> max_flow_with_bounds() {
    // 添加 t->s 无穷大边，不记录在 orig_e
    int idx_ts = tot;
    e[tot] = {s, head[t], INF, 0}; head[t] = tot++;
    e[tot] = {t, head[s], 0, 0}; head[s] = tot++;
    
    long long sum_pos_demand = 0;
    for (int i = 1; i <= n; i++) {
        if (demand[i] > 0) {
            add_aux_edge(ss, i, demand[i]);
            sum_pos_demand += demand[i];
        } else if (demand[i] < 0) {
            add_aux_edge(i, tt, -demand[i]);
        }
    }
    
    long long flow_feasible = dinic_max_flow(ss, tt);
    if (flow_feasible != sum_pos_demand) {
        return {-1, {}};
    }
    
    long long base_flow = e[idx_ts].flow;
    
    // 在残量网络上跑 s->t 最大流
    // 注意：此时 ss, tt 仍连接在图中，但通常不会影响 s->t 的增广，因为它们已经满流或平衡
    // 更严谨的做法是断开 ss, tt，但链式前向星难删边。
    // 由于 ss, tt 只有入边或出边且已饱和，它们不会提供新的增广路给 s->t
    long long additional_flow = dinic_max_flow(s, t);
    
    vector<long long> flows;
    for (auto& e : orig_e) {
        flows.push_back(e.lower + e[e.idx].flow);
    }
    
    return {base_flow + additional_flow, flows};
}

// 3. 有源汇最小流
pair<long long, vector<long long>> min_flow_with_bounds() {
    int idx_ts = tot;
    e[tot] = {s, head[t], INF, 0}; head[t] = tot++;
    e[tot] = {t, head[s], 0, 0}; head[s] = tot++;
    
    long long sum_pos_demand = 0;
    for (int i = 1; i <= n; i++) {
        if (demand[i] > 0) {
            add_aux_edge(ss, i, demand[i]);
            sum_pos_demand += demand[i];
        } else if (demand[i] < 0) {
            add_aux_edge(i, tt, -demand[i]);
        }
    }
    
    long long flow_feasible = dinic_max_flow(ss, tt);
    if (flow_feasible != sum_pos_demand) {
        return {-1, {}};
    }
    
    long long base_flow = e[idx_ts].flow;
    
    // 跑 t->s 最大流以退流
    long long reduce_flow = dinic_max_flow(t, s);
    
    vector<long long> flows;
    for (auto& e : orig_e) {
        flows.push_back(e.lower + e[e.idx].flow);
    }
    
    return {base_flow - reduce_flow, flows};
}
```

#### API 速查表

| 函数名称                       | 作用                 | 前置条件 | 时间复杂度 |
| ------------------------------ | -------------------- | -------- | ---------- |
| `init_bounded(n, s, t)`        | 初始化               | 无       | $O(n)$     |
| `add_bounded_edge(u, v, l, c)` | 添加上下界边         | 无       | $O(1)$     |
| `feasible_flow()`              | 求无源汇可行流及方案 | 图已构建 | $O(V^2E)$  |
| `max_flow_with_bounds()`       | 求有源汇最大流及方案 | 图已构建 | $O(V^2E)$  |
| `min_flow_with_bounds()`       | 求有源汇最小流及方案 | 图已构建 | $O(V^2E)$  |

**注意事项：**
- 方案输出：`flows[i]` 对应第 $i$ 条添加的原始边的实际流量。
- 辅助边（ss/tt 相关）和 t->s 边不计入原图方案。

---

### min_cost_max_flow.cpp - 最小费用最大流

**用途：** 求最小费用最大流，支持输出每条边流量方案。使用势函数优化 Dijkstra。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 20005;
const long long INF = 1e18;

struct Edge {
    int to, next;
    long long cap, cost, flow;
} e[MAXM];

int head[MAXN], tot;
int n, s, t;
long long dist[MAXN], potential[MAXN];
int pre_node[MAXN], pre_edge[MAXN];

void init_mcmf(int _n) {
    n = _n;
    memset(head, -1, sizeof(head));
    tot = 0;
    memset(potential, 0, sizeof(potential));
}

int add_edge_mcmf(int u, int v, long long cap, long long cost) {
    int idx = tot;
    e[tot] = {v, head[u], cap, cost, 0};
    head[u] = tot++;
    e[tot] = {u, head[v], 0, -cost, 0};
    head[v] = tot++;
    return idx;
}

bool dijkstra() {
    fill(dist, dist + n + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    
    dist[s] = 0;
    pq.push({0, s});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        
        for (int i = head[u]; i != -1; i = e[i].next) {
            Edge& ed = e[i];
            long long reduced_cost = ed.cost + potential[u] - potential[ed.to];
            if (ed.cap - ed.flow > 0 && dist[ed.to] > dist[u] + reduced_cost) {
                dist[ed.to] = dist[u] + reduced_cost;
                pre_node[ed.to] = u;
                pre_edge[ed.to] = i;
                pq.push({dist[ed.to], ed.to});
            }
        }
    }
    
    if (dist[t] == INF) return false;
    
    for (int i = 1; i <= n; i++) {
        if (dist[i] < INF) {
            potential[i] += dist[i];
        }
    }
    
    return true;
}

pair<long long, long long> min_cost_max_flow() {
    long long total_flow = 0, total_cost = 0;
    
    while (dijkstra()) {
        long long min_cap = INF;
        for (int v = t; v != s; v = pre_node[v]) {
            int i = pre_edge[v];
            min_cap = min(min_cap, e[i].cap - e[i].flow);
        }
        
        for (int v = t; v != s; v = pre_node[v]) {
            int i = pre_edge[v];
            e[i].flow += min_cap;
            e[i ^ 1].flow -= min_cap;
        }
        
        total_flow += min_cap;
        total_cost += min_cap * potential[t];
    }
    
    return {total_flow, total_cost};
}
```

#### API 速查表

| 函数名称                         | 作用             | 前置条件 | 时间复杂度      |
| -------------------------------- | ---------------- | -------- | --------------- |
| `init_mcmf(n)`                   | 初始化           | 无       | $O(n)$          |
| `add_edge_mcmf(u, v, cap, cost)` | 添加边，返回索引 | 无       | $O(1)$          |
| `min_cost_max_flow()`            | 求最小费用最大流 | 无负圈   | $O(F E \log V)$ |

**注意事项：**

- 方案输出：遍历记录的索引 `idx`，`e[idx].flow` 为流量。
- 若存在负权边，需先运行 Bellman-Ford 初始化 `potential`，或使用 SPFA 版本。

---

### negative_cycle_mcmf.cpp - 有负圈的费用流

**用途：** 处理含负圈的费用流。先消圈，再求最小费用流。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 20005;
const long long INF = 1e18;

struct NCMCFEdge {
    int to, next;
    long long cap, cost, flow;
} nc_e[MAXM];

int nc_head[MAXN], nc_tot;
int nc_n;

void init_ncmcf(int _n) {
    nc_n = _n;
    memset(nc_head, -1, sizeof(nc_head));
    nc_tot = 0;
}

int add_nc_edge(int u, int v, long long cap, long long cost) {
    int idx = nc_tot;
    nc_e[nc_tot] = {v, nc_head[u], cap, cost, 0};
    nc_head[u] = nc_tot++;
    nc_e[nc_tot] = {u, nc_head[v], 0, -cost, 0};
    nc_head[v] = nc_tot++;
    return idx;
}

void cancel_negative_cycles() {
    bool updated = true;
    while (updated) {
        updated = false;
        vector<long long> dist(nc_n + 1, INF);
        vector<int> pre_v(nc_n + 1, -1), pre_e(nc_n + 1, -1);
        vector<bool> in_q(nc_n + 1, false);
        vector<int> cnt(nc_n + 1, 0);
        queue<int> q;
        
        for (int i = 1; i <= nc_n; i++) {
            dist[i] = 0;
            q.push(i);
            in_q[i] = true;
        }
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            in_q[u] = false;
            
            for (int i = nc_head[u]; i != -1; i = nc_e[i].next) {
                NCMCFEdge& e = nc_e[i];
                if (e.cap - e.flow > 0 && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    pre_v[e.to] = u;
                    pre_e[e.to] = i;
                    
                    if (!in_q[e.to]) {
                        q.push(e.to);
                        in_q[e.to] = true;
                        cnt[e.to]++;
                        
                        if (cnt[e.to] > nc_n) {
                            updated = true;
                            long long min_cap = INF;
                            int v = e.to;
                            do {
                                min_cap = min(min_cap, nc_e[pre_e[v]].cap - nc_e[pre_e[v]].flow);
                                v = pre_v[v];
                            } while (v != e.to);
                            
                            v = e.to;
                            do {
                                nc_e[pre_e[v]].flow += min_cap;
                                nc_e[pre_e[v] ^ 1].flow -= min_cap;
                                v = pre_v[v];
                            } while (v != e.to);
                            
                            goto restart_spfa;
                        }
                    }
                }
            }
        }
        restart_spfa:;
    }
}

// 注意：消圈后，需将剩余容量转移到标准 MCMF 结构中求解
// 此处仅展示消圈逻辑，完整求解需结合 min_cost_max_flow.cpp
```

#### API 速查表

| 函数名称                       | 作用     | 前置条件 | 时间复杂度 |
| ------------------------------ | -------- | -------- | ---------- |
| `init_ncmcf(n)`                | 初始化   | 无       | $O(n)$     |
| `add_nc_edge(u, v, cap, cost)` | 添加边   | 无       | $O(1)$     |
| `cancel_negative_cycles()`     | 消除负圈 | 图已构建 | 不确定     |

**注意事项：**
- 消圈后，原图流量状态已更新。
- 后续需将残量网络复制到标准 MCMF 结构中继续求解。

---

### 其他注意事项

1. **链式前向星**：所有图均使用 `head` 和 `e` 数组，索引从 0 开始，正向边 $i$ 的反向边为 $i \oplus 1$。
2. **方案输出**：
   - **最大流/费用流**：记录 `add_edge` 返回的索引，求解后读取 `e[idx].flow`。
   - **最小割**：使用 `get_min_cut_set` 获取 S 集合。
   - **上下界**：实际流量 = `lower` + `e[idx].flow`。
3. **内存**：根据题目规模调整 `MAXN` 和 `MAXM`。`MAXM` 需包含反向边，通常为边数的 2-4 倍（上下界更多）。
4. **初始化**：每次新图务必调用 `init` 函数。

## LCA

### $O(n \log n) - O(1)$

```cpp
int n, m, R, dn, dfn[N], mi[19][N];
vector<int> e[N];
int get(int x, int y) {return dfn[x] < dfn[y] ? x : y;}
void dfs(int id, int f) {
    mi[0][dfn[id] = ++dn] = f;
    for(int it : e[id]) if(it != f) dfs(it, id); 
}
int lca(int u, int v) {
    if(u == v) return u;
    if((u = dfn[u]) > (v = dfn[v])) swap(u, v);
    int d = __lg(v - u++);
    return get(mi[d][u], mi[d][v - (1 << d) + 1]);
}
// 主函数部分：
dfs(Root, 0);
for(int i = 1; i <= __lg(n); i++)
    for(int j = 1; j + (1 << i) - 1 <= n; j++)
        mi[i][j] = get(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
```

### $O(n) - O(1)$

```cpp
void dfs1(int x){
	d[x] = f[x] = ++tot;
	for(int v : G[x]) {
		if(v == fat[x]) continue;
		fat[v] = x, dfs1(v);
		if(lb[f[v]] > lb[f[x]]) f[x] = f[v];
	}
	top[f[x]] = x;
}
void dfs2(int x){
	s[x] |= 1 << lb[f[x]];
	for(int v : G[x]){
		if(v ^ fat[x]){
			s[v] = s[x],
			dfs2(v);
        }
    }
    return ;
}
int lca(int x, int y){
	if(f[x] == f[y]) return d[x] < d[y] ? x : y;
	int p = hb[f[x] ^ f[y]];
	int h = lb[(s[x] & s[y]) >> p << p];
	int F = (f[x] >> h | 1) << h;
	if(f[x] ^ F){
		int m = hb[s[x] & ((1 << h) - 1)];
		m = (f[x] >> m | 1) << m;
		x = fat[top[m]];
	}
	if(f[y] ^ F){
		int m = hb[s[y] & ((1 << h) - 1)];
		m = (f[y] >> m | 1) << m;
		y = fat[top[m]];
	}
	return d[x] < d[y] ? x : y;
}
```

# 字符串

## $\textsf{ACAM}$

```C++
const int NR = 2e5 + 5;
namespace AC {
	struct Node {
		int son[26], ans, fail, idx;
		void init() {
			memset(son, 0, sizeof(son));
			ans = idx = 0;
		}
	} tr[NR << 5];
	int tot, ans[NR], idx;
	vector<int> g[NR << 5];  
	void init() {
		tot = idx = 0;
		tr[0].init();
	}
	void insert(char s[], int &idx) {
		int u = 0;
		for (int i = 1; s[i]; i++) {
			int &son = tr[u].son[s[i] - 'a'];
			if (!son) son = ++tot, tr[son].init();
			u = son;
		}
		if (!tr[u].idx) tr[u].idx = ++idx;
		idx = tr[u].idx;
	}
	void build() {
		queue<int> q;
		rep(i, 0, 25)
			if (tr[0].son[i]) {
				q.push(tr[0].son[i]);
				g[0].push_back(tr[0].son[i]);
			}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			rep(i, 0, 25) {
				if (tr[u].son[i]) {
					tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
					g[tr[tr[u].fail].son[i]].push_back(tr[u].son[i]);
					q.push(tr[u].son[i]);
				} else
					tr[u].son[i] = tr[tr[u].fail].son[i];
			}
		}
	}
	void qry(char t[]) {
		int u = 0;
		for (int i = 1; t[i]; i++) {
			u = tr[u].son[t[i] - 'a'];
			tr[u].ans++;
		}
	}
	void dfs(int u) {
		for (int v : g[u]) {
			dfs(v);
			tr[u].ans += tr[v].ans;
		}
		ans[tr[u].idx] = tr[u].ans;
	}
}
```

## $\textsf{SAM}$

```C++
int n, idt = 1, last = 1, ft[NR], sz[NR], len[NR], t[NR][26];
void extend(int c) {
    int p = last, cur = ++idt;
    len[cur] = len[p] + 1, last = cur, sz[cur] = 1;
    while (!t[p][c])
        t[p][c] = cur, p = ft[p];
    if (!p)
        return ft[cur] = 1, void();
    int q = t[p][c];
    if (len[p] + 1 == len[q])
        return ft[cur] = q, void();
    int q1 = ++idt;
    len[q1] = len[p] + 1, ft[q1] = ft[q], ft[q] = ft[cur] = q1;
    while (t[p][c] == q)
        t[p][c] = q1, p = ft[p];
    memcpy(t[q1], t[q], sizeof t[q1]);
}
ll dfs(int x) {
    ll res = 0;
    for (auto y : e[x]) {
        ret = max(ret, dfs(y));
        sz[x] += sz[y];
        if (sz[y] > 1)
            res = max(res, 1ll * sz[y] * len[y]);
    }
    return res;
}
```

## $\textsf{Z}$ 函数

```C++
void getz(string a,string b,int z[]){ // b 与 b 的每一个后缀的 LCP
	int l=0,r=0;
	int n=b.size();
	for(int i=0;i<n;i++) z[i]=0;
	while(z[0]<min((int)a.size(),n)&&a[z[0]]==b[z[0]]) z[0]++;
	for(int i=1;i<n;i++){
		int len=r-i+1;
		if(i<=r&&z[i-l]<len) z[i]=z[i-l];
		else{
			z[i]=max(0,len);
			while(i+z[i]<n&&a[z[i]]==b[i+z[i]]) z[i]++;
		}
		if(i+z[i]-1>r) l=i,r=i+z[i]-1;
	}
}
void getp(string a,string b,int p[]){ // 匹配，表示 b 与 a 的每一个后缀的 LCP 长度
	int l=0,r=0;
	int n=b.size();
	for(int i=0;i<n;i++) p[i]=0;
	while(p[0]<min((int)a.size(),n)&&a[p[0]]==b[p[0]]) p[0]++;
	for(int i=1;i<n;i++){
		int len=r-i+1;
		if(i<=r&&z[i-l]<len) p[i]=z[i-l];
		else{
			p[i]=max(0,len);
			while(i+p[i]<n&&a[p[i]]==b[i+p[i]]) p[i]++;
		}
		if(i+p[i]-1>r) l=i,r=i+p[i]-1;
	}
}
```

用法：
```cpp
getz(b,b,z);
getp(b,a,p);
```

## manacher

```C++
vector<int> d1(n);
for (int i = 0, l = 0, r = -1; i < n; i++) {
	int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
	while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
		k++;
	}
	d1[i] = k--;
	if (i + k > r) {
		l = i - k;
		r = i + k;
	}
}
vector<int> d2(n);
for (int i = 0, l = 0, r = -1; i < n; i++) {
	int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
	while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
		k++;
	}
	d2[i] = k--;
	if (i + k > r) {
		l = i - k - 1;
		r = i + k;
	}
}
```



## 回文自动机

```C++
using ll = long long;
const int mod = 1e9 + 7;
const int MAXN = 1e6 + 5;
int add(int x, int y) {
	x += y;
	return x >= mod ? x -= mod : x;
}
namespace pam {
	int sz, tot, last;
	int ch[MAXN][26], len[MAXN], fail[MAXN];
	int cnt[MAXN], dep[MAXN], dif[MAXN], slink[MAXN];
	char s[MAXN];
	int node(int l) {
		sz++;
		memset(ch[sz], 0, sizeof(ch[sz]));
		len[sz] = l;
		fail[sz] = 0;
		cnt[sz] = 0;
		dep[sz] = 0;
		return sz;
	}
	void clear() {
		sz = -1;
		last = 0;
		s[tot = 0] = '$';
		node(0);
		node(-1);
		fail[0] = 1;
	}
	int getfail(int x) {
		while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
		return x;
	}
	void insert(char c) {
		s[++tot] = c;
		int now = getfail(last);
		if (!ch[now][c - 'a']) {
			int x = node(len[now] + 2);
			fail[x] = ch[getfail(fail[now])][c - 'a'];
			dep[x] = dep[fail[x]] + 1;
			ch[now][c - 'a'] = x;
			dif[x] = len[x] - len[fail[x]];
			if (dif[x] == dif[fail[x]])
				slink[x] = slink[fail[x]];
			else
				slink[x] = fail[x];
		}
		last = ch[now][c - 'a'];
		cnt[last]++;
	}
}  // namespace pam
using pam::dif;
using pam::fail;
using pam::len;
using pam::slink;
int n, dp[MAXN], g[MAXN];
string s;
char t[MAXN];
int main() {
	pam::clear();
	cin >> s;
	n = s.size();
	s = " " + s;
	for (int i = 1, j = 0; i <= n; i++)
		t[++j] = s[i], t[++j] = s[n - i + 1];
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		pam::insert(t[i]);
		for (int x = pam::last; x > 1; x = slink[x]) {
			g[x] = dp[i - len[slink[x]] - dif[x]];
			if (dif[x] == dif[fail[x]]) g[x] = add(g[x], g[fail[x]]);
			if (i % 2 == 0) dp[i] = add(dp[i], g[x]);  // 在偶数位置更新 dp 数组
		}
	}
	cout << dp[n];
	return 0;
}
```

# 动态规划

## 决策单调性

### 分治算法

```cpp
int w(int l,int r); // 计算 w(l,r)
void check(int j,int i){
	if(w(j,i)<dp[i]) dp[i]=w(j,i),opt[i]=j; // 更新 dp 值和最优决策点
}
void calc(int l,int r,int opl,int opr){
	int mid=(l+r)>>1;
	for(int i=opl;i<=min(opr,mid);i++) cheke(i,mid); // 求 opt(mid)
	if(l<mid) calc(l,mid-1,opl,opt[mid]);
	if(mid<r) calc(mid+1,r,opt[mid],opr);
}
```

### 简化 LARSCH

```cpp
int w(int l, int r); // 计算 w(l,r)
void check(int j, int i){
	if(w(j, i) < dp[i]) dp[i] = w(j, i), opt[i] = j; // 更新 dp 值和最优决策点
}
void calc(int l, int r){
	int mid = (l + r + 1) >> 1;
	for(int i = opt[l]; i <= opt[r]; i++) check(i, mid);
	if(mid < r) calc(l, mid);
	for(int i = l + 1; i <= mid; i++) check(i, r);
	if(l < mid) calc(mid, r);
    return ;
}
```

使用方式：

```cpp
check(1, n), check(1, 1), calc(1, n);
```

## Slope Trick

**特性（用于）**：维护一维凸分段线性函数 $f(x)$ 的最小值、最小点区间，以及常见的保持凸性的函数变换。适合处理带有绝对值、单侧惩罚、平移、区间转移最小值的一维凸优化问题。

### 适用范围

本模板适用于满足以下条件的函数：

- $f(x)$ 是一维凸分段线性函数，即斜率随 $x$ 单调不减。

该文件是核心模板，维护一个凸分段线性函数：

$$
f(x)=\text{min\_f}
+\sum_{p\in L}\max(0,p-x)
+\sum_{q\in R}\max(0,x-q)
$$

其中 $L$ 保存左侧断点，$R$ 保存右侧断点，并维护不变式：

$$
\max L \le \min R
$$

最小值为 `min_f`，最小点区间为 $[\max L,\min R]$；若某一侧为空，则对应方向无界。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll ST_INF = (1LL << 62);
struct SlopeTrick {
    ll min_f = 0;
    ll off_l = 0, off_r = 0;
    multiset<ll> L, R;
    SlopeTrick() = default;
    void clear() {
        L.clear(); R.clear();
        min_f = off_l = off_r = 0;
    }
    bool empty() const {
        return L.empty() && R.empty();
    }
    size_t size() const {
        return L.size() + R.size();
    }
    void add_const(ll c) {
        min_f += c;
    }
    void add_x_minus_a(ll a) {
        if (!L.empty()) {
            auto it = prev(L.end());
            ll l = *it + off_l;
            if (l > a) {
                min_f += l - a;
                R.insert(l - off_r);
                L.erase(it);
                L.insert(a - off_l);
                return;
            }
        }
        R.insert(a - off_r);
    }
    void add_a_minus_x(ll a) {
        if (!R.empty()) {
            auto it = R.begin();
            ll r = *it + off_r;
            if (r < a) {
                min_f += a - r;
                L.insert(r - off_l);
                R.erase(it);
                R.insert(a - off_r);
                return;
            }
        }
        L.insert(a - off_l);
    }
    void add_abs(ll a) {
        add_x_minus_a(a); add_a_minus_x(a);
    }
    void shift_all(ll d) {
        off_l += d; off_r += d;
    }
    void shift_min_window(ll a, ll b) {
        off_l += a; off_r += b;
    }
    void prefix_min_le() {
        R.clear(); off_r = 0;
    }
    void suffix_min_ge() {
        L.clear(); off_l = 0;
    }
    ll min_value() const {
        return min_f;
    }
    pair<ll, ll> argmin() const {
        ll l = L.empty() ? -ST_INF : (*prev(L.end()) + off_l);
        ll r = R.empty() ? ST_INF : (*R.begin() + off_r);
        return {l, r};
    }
    struct ArgMinExact {
        bool left_unbounded = false;
        bool right_unbounded = false;
        ll l = 0, r = 0;
    };
    ArgMinExact argmin_exact() const {
        ArgMinExact res;
        if (L.empty()) {
            res.left_unbounded = true;
            res.l = -ST_INF;
        }
        else
            res.l = *prev(L.end()) + off_l;
        if (R.empty()) {
            res.right_unbounded = true;
            res.r = ST_INF;
        }
        else
            res.r = *R.begin() + off_r;
        return res;
    }
};
```

### API 速查表

| 函数                    | 作用                                 |                  前置条件 |  时间复杂度 |
| ----------------------- | ------------------------------------ | ------------------------: | ----------: |
| `SlopeTrick()`          | 构造函数，初始函数为 $f(x)=0$        |                        无 |      $O(1)$ |
| `clear()`               | 重置为空函数 $f(x)=0$                |                        无 |      $O(N)$ |
| `empty()`               | 判断当前函数是否没有任何断点         |                        无 |      $O(1)$ |
| `size()`                | 返回当前断点总数                     |                        无 |      $O(1)$ |
| `add_const(c)`          | $f(x)\gets f(x)+c$                   |        `min_f + c` 不溢出 |      $O(1)$ |
| `add_x_minus_a(a)`      | $f(x)\gets f(x)+\max(0,x-a)$         |          坐标与偏移不溢出 | $O(\log N)$ |
| `add_a_minus_x(a)`      | $f(x)\gets f(x)+\max(0,a-x)$         |          坐标与偏移不溢出 | $O(\log N)$ |
| `add_abs(a)`            | $f(x)\gets f(x)+|x-a|$               |          坐标与偏移不溢出 | $O(\log N)$ |
| `shift_all(d)`          | $f(x)\gets f(x-d)$                   |                偏移不溢出 |      $O(1)$ |
| `shift_min_window(a,b)` | $f(x)\gets \min_{y\in[x-b,x-a]}f(y)$ |      $a\le b$，偏移不溢出 |      $O(1)$ |
| `prefix_min_le()`       | $f(x)\gets \min_{y\le x}f(y)$        |          允许删除右侧断点 |    $O(|R|)$ |
| `suffix_min_ge()`       | $f(x)\gets \min_{y\ge x}f(y)$        |          允许删除左侧断点 |    $O(|L|)$ |
| `min_value()`           | 返回当前最小值                       |                        无 |      $O(1)$ |
| `argmin()`              | 返回最小点区间，无界端点用哨兵值     | `ST_INF` 不与真实端点冲突 |      $O(1)$ |
| `argmin_exact()`        | 返回最小点区间，并用布尔值标记无界   |                        无 |      $O(1)$ |

---

### 其他与注意事项

- 本模板的核心不变式是：
  $$
  \max L\le \min R
  $$
  其中 $L$、$R$ 指实际坐标，即加上 `off_l`、`off_r` 后的坐标。

- `add_x_minus_a(a)` 与 `add_a_minus_x(a)` 使用的恒等式为：
  $$
  (l-x)_+ + (x-a)_+
  =
  (l-a)+(a-x)_+ + (x-l)_+,\quad l>a
  $$
  以及：
  $$
  (a-x)_+ + (x-r)_+
  =
  (a-r)+(r-x)_+ + (x-a)_+,\quad r<a
  $$
  其中 $(t)_+=\max(0,t)$。

- `shift_min_window(a,b)` 的语义是：
  $$
  g(x)=\min_{y\in[x-b,x-a]} f(y)
  $$
  因此如果 DP 转移是：
  $$
  dp_i(x)=cost_i(x)+\min_{y:\ x-y\in[a,b]}dp_{i-1}(y)
  $$
  那么应该先对旧函数调用：
  ```cpp
  st.shift_min_window(a, b);
  ```
  再加入当前代价。

- `prefix_min_le()` 是：
  $$
  f(x)\gets \min_{y\le x}f(y)
  $$
  常用于非递减约束：
  $$
  x_{i-1}\le x_i
  $$

- `suffix_min_ge()` 是：
  $$
  f(x)\gets \min_{y\ge x}f(y)
  $$
  常用于非递增约束：
  $$
  x_{i-1}\ge x_i
  $$

- 本模板没有显式使用 `vector`，而是使用 `multiset` 维护断点。若追求更小常数，可改成双 `priority_queue` 实现，但标准库 `priority_queue` 底层通常依赖 `vector`。

- 如果答案可能超过 `long long`，建议：
  - 将 `min_f` 改成 `__int128`；
  - 或者在每次 `min_f += ...` 前判断溢出；
  - 或者确认题目数据保证答案在 `long long` 内。

- `ST_INF` 只是表示无穷远的哨兵值。若真实最优区间端点可能达到 `ST_INF`，请使用 `argmin_exact()` 并根据 `left_unbounded`、`right_unbounded` 判断。

# 数据结构

## 多维偏序

```C++
#define mid (s + t >> 1)
void Par2(int n, Node x) {
	sort(x + 1, x + n + 1, cmpX);
	rep(i, 1, n) {
		if (x[i].op == 2) res += BIT::qry(x[i].b - 1);
		else BIT::upd(x[i].b);
	}
}
void Par3(int s, int t) {
	if (s ^ t) {
		Par3(s, mid), Par3(mid + 1, t);
		sort(A + s, A + mid + 1, cmpY);
		sort(A + mid + 1, A + t + 1, cmpY);
		rep(i, mid + 1, t) {
			while (s <= mid && A[s].b <= A[i].b) BIT::upd(A[s].c, A[s].val);
			A[i].res += BIT::qry(A[i].c);
		}
	}
}
bitset<NR> A[NR];
void ParK(int n, int k, Node r[]) {
	rep(d, 1, k) {
		bitset<NR> pre;
		rep(i, 1, n) swap(r[i].x[1], r[i].x[d]);
		sort(r + 1, r + n + 1, cmp);
		rep(i, 1, n) {
			A[r[i].id] &= pre;
			pre.set(r[i].id);
		}
		rep(i, 1, n) swap(r[i].x[1], r[i].x[d]);
	}
	rep(i, 1, n) ans[i] = A[i].count();
}
```

## $\textsf{K-D Tree}$

```C++
void maintain(int x) {
    L[x] = R[x] = s[x].x,D[x] = U[x] = s[x].y;
    if (lc[x])
        L[x] = min(L[x], L[lc[x]]), R[x] = max(R[x], R[lc[x]]),
		D[x] = min(D[x], D[lc[x]]), U[x] = max(U[x], U[lc[x]]);
    if (rc[x])
        L[x] = min(L[x], L[rc[x]]), R[x] = max(R[x], R[rc[x]]),
		D[x] = min(D[x], D[rc[x]]), U[x] = max(U[x], U[rc[x]]);
}
int build(int l, int r) {
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    double av1 = 0, av2 = 0, va1 = 0, va2 = 0;  // average variance
    rep (i, l, r) av1 += s[i].x, av2 += s[i].y;
    av1 /= (r - l + 1),av2 /= (r - l + 1);
    rep (i, l, r)
        va1 += (av1 - s[i].x) * (av1 - s[i].x),va2 += (av2 - s[i].y) * (av2 - s[i].y);
    if (va1 > va2) 
		nth_element(s + l, s + mid, s + r + 1, cmp1);
    else 
		nth_element(s + l, s + mid, s + r + 1, cmp2);
    lc[mid] = build(l, mid - 1);
    rc[mid] = build(mid + 1, r);
    maintain(mid);
    return mid;
}
void query(int l, int r, int x) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    long long t = sq(s[mid].x - s[x].x) + sq(s[mid].y - s[x].y);

    if (t > q.top()) q.pop(), q.push(t);

    long long distl = dist(x, lc[mid]), distr = dist(x, rc[mid]);
	
    if (distl > q.top() && distr > q.top()) {
        if (distl > distr) {
            query(l, mid - 1, x);
            if (distr > q.top()) 
				query(mid + 1, r, x);
        } else {
            query(mid + 1, r, x);
            if (distl > q.top()) 
				query(l, mid - 1, x);
        }
    } else {
        if (distl > q.top()) 
			query(l, mid - 1, x);
        if (distr > q.top()) 
			query(mid + 1, r, x);
    }
}
```

## 平衡树

```C++
struct FHQTreap {
    int tot, root;
    int newNode(int v) {
        ++tot;
        t[tot].lc = t[tot].rc = 0;
        t[tot].val = v;
        t[tot].cnt = t[tot].siz = 1;
        t[tot].pri = rand();
        return tot;
    }
    void pushup(int p) {
        t[p].siz = t[t[p].lc].siz + t[t[p].rc].siz + t[p].cnt;
    }
    void split(int p, int key, int &a, int &b) {
        if (!p) 
            return a = b = 0, void();
        if (t[p].val <= key) {
            a = p;
            split(t[p].rc, key, t[p].rc, b);
            pushup(a);
        } else {
            b = p;
            split(t[p].lc, key, a, t[p].lc);
            pushup(b);
        }
    }
    int merge(int a, int b) {
        if (!a || !b) return a | b;
        if (t[a].pri < t[b].pri) {
            t[a].rc = merge(t[a].rc, b);
            return pushup(a), a;
        } else {
            t[b].lc = merge(a, t[b].lc);
            return pushup(b), b;
        }
    }
    void insert(int v) {
        int a, b, mid, c;
        split(root, v - 1, a, b);
        split(b, v, mid, c);
        if (mid) {
            t[mid].cnt++;
            pushup(mid);
        } else 
            mid = newNode(v);
        root = merge(merge(a, mid), c);
    }
    void erase(int v, int a = 0, int b = 0, int mid = 0, int c = 0) {
        split(root, v - 1, a, b);
        split(b, v, mid, c);
        if (mid) {
            t[mid].cnt--;
            if (t[mid].cnt == 0) 
                mid = 0;
            else 
                pushup(mid);
        }
        root = merge(merge(a, mid), c);
    }
    int kth(int k, int p = root) {
        while (p) {
            int leftSize = t[t[p].lc].siz;
            if (k <= leftSize) 
                p = t[p].lc;
            else if (k <= leftSize + t[p].cnt) 
                return t[p].val;
            else 
                k -= leftSize + t[p].cnt , p = t[p].rc;
        }
        return -1;  
    }
    int countLEQ(int v, int p = root, int res = 0) {
        while (p) {
            if (t[p].val <= v) 
                res += t[t[p].lc].siz + t[p].cnt , p = t[p].rc;
            else 
                p = t[p].lc;
        }
        return res;
    }
};
```

## 珂朵莉树

```C++
#define int long long
const int p=1e9 + 7, N = 1e5 + 10;
struct node{
	int l, r;
	mutable int v;
	node(int x, int y = -1,int z = 0){
		l = x, r = y, v = z;
	}
	bool operator < (const node &a) const {
		return l < a.l;
	}
};
set<node> odt;
auto split(int pos){
	auto it = odt.lower_bound(node(pos));
	if(it != odt.end() && it -> l == pos) return it;
	it--;
	int l = it -> l, r = it -> r, v = it -> v;
	odt.erase(it), odt.insert(node(l, pos - 1, v));
	return odt.insert(node(pos, r, v)).first;
}
void assign(int l, int r, int v){
	auto itr = split(r + 1), itl = split(l);
	odt.erase(itl, itr), odt.insert(node(l, r, v));
	return ;
}
void add(int l, int r, int v){
	auto itr = split(r + 1), itl = split(l);
	for(auto it = itl; it != itr; it++) it -> v += v;
	return ;
}
int kth(int l, int r, int k){
	vector<pair<int, int> > v;
	auto itr = split(r + 1), itl = split(l);
	for(auto it = itl; it != itr; it++) v.push_back({it -> v, (it -> r) - (it -> l) + 1});
	sort(v.begin(), v.end());
	for(auto it = v.begin(); it != v.end(); it++){
		k -= it -> second;
		if(k <= 0) return it -> first;
	}
	return -1;
}
int a[N];
signed main(){
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i], odt.insert(node(i, i, a[i]));
	/*
    assign(l, r, k);
    add(l, r, k);
    kth(l, r, k);
    */
    return 0;
}
```

## 李超树

```C++
struct func {
	int k;
	ll b;
	func() : k(0), b(-inf) {}
	func(int _k, ll _b) : k(_k), b(_b) {}
	ll f(ll x) { return k * x + b; }
};
struct Li_Tree {
	int cnt, rt[N];
	struct tree {
		func v;
		int ls, rs;
		tree() : v(), ls(0), rs(0) {}
		ll f(ll x) { return v.f(x); }
	} t[N * 43];
    
	#define ls(x) t[x].ls
	#define rs(x) t[x].rs
	#define d ((l + r) >> 1)
    
	void up(int &c, int p, ll l, ll r, func v) {
		c = ++cnt;
		t[c] = t[p];
		if (l == r) {
			if (v.f(l) > t[c].f(l)) swap(v, t[c].v);
			return;
		}
		if (v.f(d) > t[c].f(d)) swap(t[c].v, v);
		if (v.f(l) > t[c].f(l)) up(ls(c), ls(p), l, d, v);
		if (v.f(r) > t[c].f(r)) up(rs(c), rs(p), d + 1, r, v);
	}

	ll qy(int c, ll l, ll r, ll x) {
		if (!c) return -inf;
		if (l == r) return t[c].f(x);
		if (x <= d) return max(t[c].f(x), qy(ls(c), l, d, x));
		return max(t[c].f(x), qy(rs(c), d + 1, r, x));
	}
} T1, T2;
```

## $\textsf{Segment Tree Beats}$

```C++
const int N = 5e5 + 5, SZ = N << 2, INF = 1e9 + 7;
int n, m, a[N];
struct data {
	int mx, mx2, mn, mn2, cmx, cmn, tmx, tmn;
	ll sum, tad;
} t[SZ];
void pushup(int u) {
	const int lu = u << 1, ru = u << 1 | 1;
	t[u].sum = t[lu].sum + t[ru].sum;
	if (t[lu].mx == t[ru].mx) {
		t[u].mx = t[lu].mx, t[u].cmx = t[lu].cmx + t[ru].cmx;
		t[u].mx2 = max(t[lu].mx2, t[ru].mx2);
	} else if (t[lu].mx > t[ru].mx) {
		t[u].mx = t[lu].mx, t[u].cmx = t[lu].cmx;
		t[u].mx2 = max(t[lu].mx2, t[ru].mx);
	} else {
		t[u].mx = t[ru].mx, t[u].cmx = t[ru].cmx;
		t[u].mx2 = max(t[lu].mx, t[ru].mx2);
	}
	if (t[lu].mn == t[ru].mn) {
		t[u].mn = t[lu].mn, t[u].cmn = t[lu].cmn + t[ru].cmn;
		t[u].mn2 = min(t[lu].mn2, t[ru].mn2);
	} else if (t[lu].mn < t[ru].mn) {
		t[u].mn = t[lu].mn, t[u].cmn = t[lu].cmn;
		t[u].mn2 = min(t[lu].mn2, t[ru].mn);
	} else {
		t[u].mn = t[ru].mn, t[u].cmn = t[ru].cmn;
		t[u].mn2 = min(t[lu].mn, t[ru].mn2);
	}
}
void push_add(int u, int l, int r, ll v) {
	t[u].sum += (r - l + 1ll) * v;
	t[u].mx += v, t[u].mn += v;
	if (t[u].mx2 != -INF) t[u].mx2 += v;
	if (t[u].mn2 != INF) t[u].mn2 += v;
	if (t[u].tmx != -INF) t[u].tmx += v;
	if (t[u].tmn != INF) t[u].tmn += v;
	t[u].tad += v;
}
void push_min(int u, int tg) {
	if (t[u].mx <= tg) return;
	t[u].sum += (tg * 1ll - t[u].mx) * t[u].cmx;
	if (t[u].mn2 == t[u].mx) t[u].mn2 = tg;
	if (t[u].mn == t[u].mx) t[u].mn = tg;
	if (t[u].tmx > tg) t[u].tmx = tg;
	t[u].mx = tg, t[u].tmn = tg;
}
void push_max(int u, int tg) {
	if (t[u].mn > tg) return;
	t[u].sum += (tg * 1ll - t[u].mn) * t[u].cmn;
	if (t[u].mx2 == t[u].mn) t[u].mx2 = tg;
	if (t[u].mx == t[u].mn) t[u].mx = tg;
	if (t[u].tmn < tg) t[u].tmn = tg;
	t[u].mn = tg, t[u].tmx = tg;
}
void pushdown(int u, int l, int r) {
	const int lu = u << 1, ru = u << 1 | 1, mid = (l + r) >> 1;
	if (t[u].tad)
		push_add(lu, l, mid, t[u].tad), push_add(ru, mid + 1, r, t[u].tad);
	if (t[u].tmx != -INF) push_max(lu, t[u].tmx), push_max(ru, t[u].tmx);
	if (t[u].tmn != INF) push_min(lu, t[u].tmn), push_min(ru, t[u].tmn);
	t[u].tad = 0, t[u].tmx = -INF, t[u].tmn = INF;
}
void build(int u = 1, int l = 1, int r = n) {
	t[u].tmn = INF, t[u].tmx = -INF;
	if (l == r) {
		t[u].sum = t[u].mx = t[u].mn = a[l];
		t[u].mx2 = -INF, t[u].mn2 = INF;
		t[u].cmx = t[u].cmn = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
	pushup(u);
}
void add(int L, int R, int v, int u = 1, int l = 1, int r = n) {
	if (R < l || r < L) return;
	if (L <= l && r <= R) return push_add(u, l, r, v);
	int mid = (l + r) >> 1;
	pushdown(u, l, r);
	add(L, R, v, u << 1, l, mid), add(L, R, v, u << 1 | 1, mid + 1, r);
	pushup(u);
}
void tomin(int L, int R, int v, int u = 1, int l = 1, int r = n) {
	if (R < l || r < L || t[u].mx <= v) return;
	if (L <= l && r <= R && t[u].mx2 < v) return push_min(u, v);
	int mid = (l + r) >> 1;
	pushdown(u, l, r);
	tomin(L, R, v, u << 1, l, mid), tomin(L, R, v, u << 1 | 1, mid + 1, r);
	pushup(u);
}
void tomax(int L, int R, int v, int u = 1, int l = 1, int r = n) {
	if (R < l || r < L || t[u].mn >= v) return;
	if (L <= l && r <= R && t[u].mn2 > v) return push_max(u, v);
	int mid = (l + r) >> 1;
	pushdown(u, l, r);
	tomax(L, R, v, u << 1, l, mid), tomax(L, R, v, u << 1 | 1, mid + 1, r);
	pushup(u);
}
ll qsum(int L, int R, int u = 1, int l = 1, int r = n) {
	if (R < l || r < L) return 0;
	if (L <= l && r <= R) return t[u].sum;
	int mid = (l + r) >> 1;
	pushdown(u, l, r);
	return qsum(L, R, u << 1, l, mid) + qsum(L, R, u << 1 | 1, mid + 1, r);
}
ll qmax(int L, int R, int u = 1, int l = 1, int r = n) {
	if (R < l || r < L) return -INF;
	if (L <= l && r <= R) return t[u].mx;
	int mid = (l + r) >> 1;
	pushdown(u, l, r);
	return max(qmax(L, R, u << 1, l, mid), qmax(L, R, u << 1 | 1, mid + 1, r));
}
ll qmin(int L, int R, int u = 1, int l = 1, int r = n) {
	if (R < l || r < L) return INF;
	if (L <= l && r <= R) return t[u].mn;
	int mid = (l + r) >> 1;
	pushdown(u, l, r);
	return min(qmin(L, R, u << 1, l, mid), qmin(L, R, u << 1 | 1, mid + 1, r));
}
```

## 单侧递归

```cpp
#define int long long
const int N = 1e5 + 10, inf = -1e18;
int n, q, a[N];
int mx[N << 2], tr[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid ((l + r) >> 1)
int calc(int l, int r, int p, int v){
    if(mx[p] <= v) return (r - l + 1) * v;
    if(l == r) return mx[p];
    if(mx[ls] = v) return (mid - l + 1) * v + calc(mid + 1, r, rs, v);
    return tr[p] - tr[ls] + calc(l, mid, ls, v);
}
inline void push_up(int l, int r, int p){
    mx[p] = max(mx[ls], mx[rs]);
    tr[p] = tr[ls] + calc(mid + 1, r, rs, mx[ls]);
    return ;
}
void build(int l, int r, int p){
    if(l==r) return mx[p] = tr[p] = a[l], void();
    build(l, mid, ls), build(mid + 1, r, rs), push_up(l, r, p);
}
void update(int l, int r, int p, int pos, int v){
    if(l == r) return mx[p] = tr[p] = v, void();
    if(pos <= mid) update(l, mid, ls, pos, v);
    else update(mid + 1, r, rs, pos, v);
    push_up(l, r, p);
}
int query(int l, int r, int p, int ql, int qr, int &now){
    if(qr < l || r < ql) return 0;
    if(ql <= l && r <= qr){
        int ans = calc(l, r, p, now);
        return now = max(now, mx[p]), ans;
    }
    int ans = 0;
    if(ql <= mid) ans += query(l, mid, ls, ql, qr, now);
    if(qr > mid) ans += query(mid + 1, r, rs, ql, qr, now);
    return ans;
}
int main() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1, n, 1);
    while(q--){
        int op, x, y, now;
        cin >> op >> x >> y;
        if(op == 1) now = -a[x], cout << query(1, n, 1, x, y, now) << "\n";
        else update(1, n, 1, x, y), a[x] = y;
    }
    return 0;
}
```

## 猫树

以 CF1100F：求区间线性基为例题。

### 离线 Cat / 猫树分治

```cpp
const int M = 21, N = 5e5 + 5, len = M;
struct LineSet{
	int p[M + 1];
	LineSet(){ memset(p, 0, sizeof p); }
	void insert(int x){
		for(int i = M; i >= 0; i--)
			if(x >> i){
				if(p[i] == 0) return p[i] = x, void();
				else x ^= p[i];
			}
	}
	void clear(){
		memset(p, 0, sizeof p);
	}
	int query(){
		int ans = 0;
		for(int i = M; i >= 0; i--)
			ans = max(ans, ans ^ p[i]);
		return ans;
	}
	void print(){
		for(int i = 1; i < len; i++)
			cout << p[i] << ' ';
		cout <<'\n';
	}
};
LineSet Union(LineSet a, LineSet b){
	LineSet c = a;
	for(int i = 0; i <= len; i++) c.insert(b.p[i]);
	return c;
}
LineSet make(int x){
	LineSet p;
	p.insert(x);
	return p;
}
int n, a[N << 1], digit[N << 3], id[N << 1], tn;
LineSet pre[N], pos[N], ans[N];
vector<pair<int, pair<int, int> > > qu[N << 2];
void init(int n = N * 8 - 5){
	digit[1] = 1;
	for(int i = 2; i <= n; i++)
		digit[i] = digit[i / 2] + 1;
}
void make(int u = 1, int l = 1, int r = n){
	if(l == r) return id[l] = u, void();
	int mid=(l + r) >> 1;
	make(u << 1, l, mid), make(u << 1 | 1, mid + 1, r);
}
#define LCA(x,y) (x >> digit[x ^ y])
LineSet p, q;
void build(int u = 1, int l = 1, int r = n){
	int mid = (l + r) >> 1;
	if(l != r)
		build(u << 1, l, mid),
		build(u << 1 | 1, mid + 1, r);
	if(mid > tn) return ;
	p.clear(), q.clear();
	for(int i = mid; i >= l; i--){
		p.insert(a[i]);
		pre[i] = p;
	}
	for(int i = mid; i <= min(r, tn); i++){
		q.insert(a[i]);
		pos[i] = q;
	}
	for(auto Q : qu[u]){
		int id = Q.first, L = Q.second.first, R = Q.second.second;
		ans[id] = Union(pre[L], pos[R]);
	}
}
#define mp(x,y,z) make_pair(x,make_pair(y,z))
signed main(){
	init();
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	tn = n;
	n = pow(2, ceil(log2(n)));
	make();
	int q;
	cin >> q;
	for(int i = 1; i <= q; i++){
		int l, r;
		cin >> l >> r;
		qu[LCA(id[l], id[r])].push_back(mp(i, l, r));
	}
	build();
	for(int i = 1; i <= q; i++)
		cout << ans[i].query() << '\n';
	return 0;
}
```

### 在线 Cat / 猫树

```cpp
#define int long long
const int M = 61, N = 5e5 + 5;
struct LineSet{
	int p[M + 1], len = M;
	LineSet(){ memset(p, 0, sizeof p); }
	void insert(int x){
		for(int i = M; i >= 0; i--)
			if(x >> i){
				if(p[i] == 0) return p[i] = x, void();
				else x ^= p[i];
			}
	}
	int query(){
		int ans = 0;
		for(int i = M; i >= 0; i--)
			ans = max(ans, ans ^ p[i]);
		return ans;
	}
	int build(){
		int n = 0;
		for(int i = 0; i <= M; i++)
			for(int j = i + 1;j <= M; j++)
				if(p[j] & (1ll << i))
					p[j] ^= p[i];
		for(int i = 0; i <= M; i++)
			if(p[i]) p[n++] = p[i];
		len = n;
		return n;
	}
	void print(){
		for(int i = 1; i < len; i++)
			cout << p[i] << ' ';
		cout <<'\n';
	}
};
LineSet Union(LineSet a, LineSet b){
	LineSet c = a;
	for(int i = 0; i < b.len; i++) c.insert(b.p[i]);
	return c;
}
LineSet make(int x){
	LineSet p;
	p.insert(x);
	return p;
}
int n, a[N];
struct CatTree{
	int digit[N], mi[N * 4], id[N * 4];
	#define LCA(x, y) (x >> digit[x ^ y])
	CatTree(int n = N - 5){
		digit[1] = 1;
		for(int i = 2; i <= n; i++)
			digit[i] = digit[i / 2] + 1;
	}
	vector<LineSet> pre[N * 4], pos[N * 4];
	void build(int u = 1, int l = 1, int r = n){
		int mid = (l + r)>>1;
		mi[u] = mid;
		if(l == r){
			id[l] = u;
			pre[u].push_back(make(a[l])),
			pos[u].push_back(make(a[r]));
			return ;
		}
		LineSet p, q;
		for(int i = mid; i >= l; i--){
			p.insert(a[i]);
			pre[u].push_back(p);
		}
		for(int i = mid; i <= r; i++){
			q.insert(a[i]);
			pos[u].push_back(q);
		}
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}
	LineSet query(int l,int r){
		int u=LCA(id[l], id[r]);
		return Union(pre[u][mi[u] - l], pos[u][r - mi[u]]);
	}
}seg;
signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	n=pow(2, ceil(log2(n)));
	seg.build();
	int q;
	cin >> q;
	while(q--){
		int l, r;
		cin >> l >> r;
		LineSet p = seg.query(l, r);
		cout<<seg.query(l, r).query()<<'\n';
	}
	return 0;
}
```

## LCT-连通性

```C++
struct Splay {
	int ch[NR][2], fa[NR], tag[NR];
	void clear(int x) {
		ch[x][0] = ch[x][1] = fa[x] = tag[x] = 0;
	}
	int getch(int x) {
		return ch[fa[x]][1] == x;
	}
	int isroot(int x) {
		return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
	}
	void pushdown(int x) {
		if (tag[x]) {
			if (ch[x][0]) {
				swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
				tag[ch[x][0]] ^= 1;
			}
			if (ch[x][1]) {
				swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
				tag[ch[x][1]] ^= 1;
			}
			tag[x] = 0;
		}
	}
	void update(int x) {
		if (!isroot(x)) update(fa[x]);
		pushdown(x);
	}
	void rotate(int x) {
		int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
		fa[x] = z;
		if (!isroot(y)) ch[z][chy] = x;
		ch[y][chx] = ch[x][chx ^ 1];
		fa[ch[x][chx ^ 1]] = y;
		ch[x][chx ^ 1] = y;
		fa[y] = x;
	}
	void splay(int x) {
		update(x);
		for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
			if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
	}
	void access(int x) {
		for (int f = 0; x; f = x, x = fa[x]) {
			splay(x);
			ch[x][1] = f;
		}
	}
	void makeroot(int x) {
		access(x);
		splay(x);
		swap(ch[x][0], ch[x][1]);
		tag[x] ^= 1;
	}
	int find(int x) {
		access(x);
		splay(x);
		while (ch[x][0]) x = ch[x][0];
		splay(x);
		return x;
	}
} st;
```

## 整体二分

```C++
struct Query {
	int i, l, r, k;
};
Query s[NR], t1[NR], t2[NR];
int n, m, cnt, pos, p[NR], ans[NR];
pair<int, int> a[NR];
void binary(int l, int r, int ql, int qr) {
	if (l > r) return;
	if (ql == qr) {
		rep(i, l, r) ans[s[i].i] = ql;
		return;
	}
	int cnt1 = 0, cnt2 = 0, mid = (ql + qr) >> 1;
	while (pos <= n - 1 && a[pos + 1].first <= mid)
		BIT::add(a[pos + 1].second, 1), ++pos;
	while (pos >= 1 && a[pos].first > mid)
		BIT::add(a[pos].second, -1), --pos;

	rep(i, l, r) {
		int now = BIT::sum(s[i].r) - BIT::sum(s[i].l - 1);
		if (s[i].k <= now)
			t1[++cnt1] = s[i];
		else
			t2[++cnt2] = s[i];
	}
	rep(i, 1, cnt1) s[l + i - 1] = t1[i];
	rep(i, 1, cnt2) s[l + cnt1 + i - 1] = t2[i];
	binary(l, l + cnt1 - 1, ql, mid);
	binary(l + cnt1, r, mid + 1, qr);
}
```

## 线段树分裂/合并

```C++
void merge(int a, int b, int &p, int s, int t) {
	if (!a || !b) return p = a + b, void();
	if (s == t) return T[p = a] += T[b], void();
	merge(L[a], L[b], L[a], s, mid), merge(R[a], R[b], R[a], mid + 1, t);
	pushup(p = a);
}

void split(int &a, int &b, int l, int r, int s, int t) {
	if (!a) return;
	if (l <= s && t <= r) return b = a, a = 0, void();
	b = ++idx;
	if (l <= mid) split(L[a], L[b], l, r, s, mid);
	if (r > mid) split(R[a], R[b], l, r, mid + 1, t);
	pushup(a);
	pushup(b);
}

void modify(int pos, int s, int t, int &p, int v) {
	if (!p) p = ++idx;
	if (s == t) {
		return T[p] += v, void();
	}
	if (pos <= mid) modify(pos, s, mid, L[p], v);
	else modify(pos, mid + 1, t, R[p], v);
	pushup(p);
}

void qry(int l, int r, int s, int t, int p) {
	if (!p) return;
	if (l <= s && t <= r) return res += T[p], void();
	if (l <= mid) qry(l, r, s, mid, L[p]);
	if (r > mid) qry(l, r, mid + 1, t, R[p]);
}

void kth(int s, int t, int p, int k) {
	if (!p) return;
	if (s == t) return ans = s, void();
	if (T[L[p]] < k) ans = mid, kth(mid + 1, t, R[p], k - T[L[p]]);
	else kth(s, mid, L[p], k);
}
```

## 树套树（线段树套平衡树）

```C++
struct Node {
    int s[2], p, v;
    int size;
    void init(int _v, int _p) {
        v = _v, p = _p;
        size = 1;
    }
} tr[NR];
int L[NR], R[NR], T[NR], idx, w[NR];
void pushup(int x) {
	tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}
void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}
void splay(int& root, int x, int k) {
    while(tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if(z != k)
            if((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if(k == 0) root = x;
}
void insert(int& root, int v) {
    int u = root, p = 0;
    while(u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++ idx;
    if(p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(root, u, 0);
}
int get_kth(int root, int v) {
    int u = root, res = 0;
    while(u) {
        if(tr[u].v < v) res += tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    return res;
}
void update(int& root, int x, int y) {
    int u = root;
    while(u) {
        if(tr[u].v == x) break;
        if(tr[u].v < x) u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    splay(root, u, 0);
    int l = tr[u].s[0], r = tr[u].s[1];
    while(tr[l].s[1]) l = tr[l].s[1];
    while(tr[r].s[0]) r = tr[r].s[0];
    splay(root, l, 0), splay(root, r, l);
    tr[r].s[0] = 0;
    pushup(r), pushup(l);
    insert(root, y) ;
}
void build(int u, int l, int r) {
    L[u] = l, R[u] = r;
    insert(T[u], -INF);
    insert(T[u], INF);
    for(int i = l; i <= r; i ++ ) insert(T[u], w[i]);
    if(l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}
int query(int u, int a, int b, int x) {
    if(L[u] >= a && R[u] <= b) return get_kth(T[u], x) - 1;
    int mid = L[u] + R[u] >> 1, res = 0;
    if(a <= mid) res += query(u << 1, a, b, x);
    if(b > mid) res += query(u << 1 | 1, a, b, x);
    return res;
}
void change(int u, int p, int x) {
    update(T[u], w[p], x);
    if(L[u] == R[u]) return;
    int mid = L[u] + R[u] >> 1;
    if(p <= mid) change(u << 1, p, x);
    else change(u << 1 | 1, p, x);
}
int get_pre(int root, int v) {
    int u = root, res = -INF;
    while(u) {
        if(tr[u].v < v) res = max(res, tr[u].v), u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    return res;
}
int get_suf(int root, int v) {
    int u = root, res = INF;
    while(u) {
        if(tr[u].v > v) res = min(res, tr[u].v), u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    return res;
}
int query_pre(int u, int a, int b, int x) {
    if(L[u] >= a && R[u] <= b) return get_pre(T[u], x);
    int mid = L[u] + R[u] >> 1, res = -INF;
    if(a <= mid) res = max(res, query_pre(u << 1, a, b, x));
    if(b > mid) res = max(res, query_pre(u << 1 | 1, a, b, x));
    return res;
}
int query_suf(int u, int a, int b, int x) {
    if(L[u] >= a && R[u] <= b) return get_suf(T[u], x);
    int mid = L[u] + R[u] >> 1, res = INF;
    if(a <= mid) res = min(res, query_suf(u << 1, a, b, x));
    if(b > mid) res = min(res, query_suf(u << 1 | 1, a, b, x));
    return res;
}
```

## 树剖

取自 NOI2021 - 庆典

```C++
void DfsInit(int u) {
	sz[u] = 1;
	for (int v : g[u]) {
		dep[v] = dep[u] + 1;
		Dad[v] = u;
		DfsInit(v);
		sz[u] += sz[v];
		if (sz[v] > sz[hvy[u]]) hvy[u] = v;
	}
}
int ltp[NR];
void Dfs2(int u, int tp) {
	ltp[u] = tp;
	dfn[u] = ++dfc;
	if (hvy[u]) Dfs2(hvy[u], tp);
	for (int v : g[u])
		if (v != hvy[u]) Dfs2(v, v);
}
int T[NR << 2], B[NR << 2], Sum[NR];
#define mid ((s + t) >> 1)
void pushup(int p) {
	T[p] = T[p << 1] + T[p << 1 | 1];
}
void psd(int p, int s, int t) {
	T[p << 1] = Sum[mid] - Sum[s - 1];
	T[p << 1 | 1] = Sum[t] - Sum[mid];
	B[p << 1] = B[p << 1 | 1] = 1;
	B[p] = 0;
}
void qsd(int p, int s, int t) {
	B[p << 1] = B[p << 1 | 1] = B[p];
	T[p << 1] = T[p << 1 | 1] = 0;
	B[p] = 0;
}
void upd(int l, int r, int s = 1, int t = sc, int p = 1) {
	if (l <= s && t <= r) {
		T[p] = Sum[t] - Sum[s - 1];
		if (s != t) qsd(p, s, t);
		B[p] = 1;
		return;
	}
	if (B[p] == -1) qsd(p, s, t);
	else if (B[p] == 1) psd(p, s, t);
	if (l <= mid) upd(l, r, s, mid, p << 1);
	if (mid < r) upd(l, r, mid + 1, t, p << 1 | 1);
	pushup(p);
}
int qry(int l, int r, int s = 1, int t = sc, int p = 1) {
	if (s > r || t < l) return 0;
	if (l <= s && t <= r) return T[p];
	if (B[p] == -1) qsd(p, s, t);
	else if (B[p] == 1) psd(p, s, t);
	return qry(l, r, s, mid, p << 1) + qry(l, r, mid + 1, t, p << 1 | 1);
}
#define Max(a, b) ((dep[a] > dep[b]) ? a : b)
int LCA(int a, int b) {
	while (ltp[a] != ltp[b]) {
		if (dep[ltp[a]] < dep[ltp[b]]) swap(a, b);
		a = Dad[ltp[a]];
	}
	return ((dep[a] < dep[b]) ? a : b);
}
int qans(int x, int y = 0) {
	int ans = 0;
	while (dep[Dad[ltp[x]]] > dep[y]) {
		ans += qry(dfn[ltp[x]], dfn[x]);
		x = Dad[ltp[x]];
	}
	if (y != Dad[ltp[x]])
		ans += qry(dfn[y] + 1, dfn[x]);
	else
		ans += qry(dfn[ltp[x]], dfn[x]);
	return ans;
}
```

## 树上 k 级祖先 / 长链剖分

```cpp
void dfs(int x,int fat){
	mxdep[x]=dep[x]=dep[fat]+1;
	fa[x][0]=fat;
	for(int i=1;i<=20;i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int v:G[x])
		if(v!=fat){
			dfs(v,x);
			if(mxdep[v]>mxdep[x]) son[x]=v,mxdep[x]=mxdep[v];
		}
}
void DFS(int x,int p){
	top[x]=p;
	if(x==p){
		for(int i=0,t=x;i<=mxdep[x]-dep[x];i++)
			U[x].push_back(t),t=fa[t][0];
		for(int i=0,t=x;i<=mxdep[x]-dep[x];i++)
			D[x].push_back(t),t=son[t];
	}
	if(son[x]) DFS(son[x],p);
	for(int v:G[x]) if(v!=son[x]) DFS(v,v);
}
int ask(int x,int k){
	if(!k) return x;
	int cnt=LOG[k];
	x=fa[x][cnt];
	k-=(1<<cnt)+dep[x]-dep[top[x]],x=top[x];
	return k>=0?U[x][k]:D[x][-k];
}
```


# 计算几何

## 平面直角坐标系

平面直角坐标系就是笛卡尔坐标系，这一部分会在人教版七年级数学中系统地学习。

在这篇文章中，我们会经常用到坐标表示，包括下面的向量。同时，我们的点和向量都是通过**坐标**来保存的。

## 向量及其运算

### 向量

向量是既有大小又有方向的量，可以用一个带有箭头的线段表示。

如果一个向量的起点是点 $A$，终点是点 $B$，那么这个向量可以被表示为 $\overrightarrow{AB}$，或者用一个小写英文字母表示为 $\vec{a}$ 或 $\mathbf{a}$（教科书上加粗时也是斜体）。

向量具有平移不变性，对于任意一个向量，都可以把它的起点平移到原点。因此我们可以在坐标系中用一对有序实数对来表示向量，也就是这个向量起点为原点时终点的坐标 $(x,y)$。

### 向量的模

模就是模长，向量的模就是向量的长度。表示为 $|\vec{a}|$，对于 $\vec{a}=(x,y),\left|\vec{a}\right|=\sqrt{x^2+y^2}$。

### 相反向量

如果两个向量大小相等，方向相反，那么这两个向量互为相反向量，$\vec{a}$ 的相反向量表示为 $-\vec{a}$，$\left|\vec{a}\right|=\left|-\vec{a}\right|$。对于 $\vec{a}=(x,y),-\vec{a}=(-x,-y)$。

### 垂直向量

如果两个向量所在的直线互相垂直，那么这两个向量互称垂直向量，表示为 $\vec{a}\bot\vec{b}$。

### 共线向量

如果两个向量所在的直线互相平行，那么这两个向量互为共线向量，表示为 $\vec{a}\|\vec{b}$。因为两向量平行，所以平移其中一个向量，总能和另一个向量共线。

### 向量的加减

前面提到了向量具有平移不变性，那么 $\vec{a}+\vec{b}$ 就相当于把向量 $\vec{a},\vec{b}$ 首尾相接（假设 $\vec{a}$ 的首接在 $\vec{b}$ 的尾），此时 $\vec{a}$ 的尾指向 $\vec{b}$ 的首就是相加后的向量。对于 $\vec{a}=(x_1,y_1),\vec{b}=(x_2,y_2)$，$\vec{a}+\vec{b}=(x_1+x_2,y_1+y_2)$。

![](http://www.wjyyy.top/wp-content/uploads/2018/12/201812201906.png)

向量的减法实际上是一个向量加上另一个向量的相反向量，也就是 $\vec{a}-\vec{b}=\vec{a}+\left(-\vec{b}\right)$，可以先把 $\vec{b}$ 向量变成 $-\vec{b}$，然后再进行加法计算。$\vec{a}-\vec{b}=(x_1-x_2,y_1-y_2)$。

![](http://www.wjyyy.top/wp-content/uploads/2018/12/201812201912.png)

向量的加减法具有交换律。

### 零向量

零向量的模长为 $0$ ，方向任意，它与任何一个向量都**共线**，但在高中数学中不认为它与任何一个向量都垂直。坐标为 $(0,0)$。

### 向量的数乘

向量的数乘实际上是对向量进行放缩。数乘的形式是 $\lambda\vec{a}$，其中常数 $\lambda\in\mathbb{R}$ 是对向量放缩的程度，可正可负可为零。数乘不改变向量的方向，因此 $\vec{a}\|\lambda\vec{a}$。对于 $\vec{a}=(x,y),\lambda\vec{a}=(\lambda x,\lambda y)$。

### 向量的数量积

向量的数量积，也叫点积、内积，几何意义为一个向量在另一个向量上的投影再乘上第二个向量的模长。$\vec{a}$ 与 $\vec{b}$ 的数量积表示为 $\vec{a}\cdot\vec{b}$，是一个实数。计算式为 $\vec{a}\cdot\vec{b}=\left|\vec{a}\right|\left|\vec{b}\right|\cos\theta(\theta=\left<\vec{a},\vec{b}\right>)$（$\theta$ 表示 $\vec{a},\vec{b}$ 的夹角）。引入坐标后，通过三角恒等变换的推导，对于 $\vec{a}=(x_1,y_1),\vec{b}=(x_2,y_2)$，$\vec{a}\cdot\vec{b}=x_1x_2+y_1y_2$。

* 如果两个向量同向（共线），那么它们的数量积为他们的模长之积。
* 如果两个向量夹角 $<90^\circ$，那么它们的数量积为正。
* 如果两个向量夹角 $=90^\circ$，那么他们的数量积为 $0$，因为 $\cos 90^\circ=0$。
* 如果两个向量夹角 $>90^\circ$，那么它们的数量积为负。
* 如果两个向量反向（共线），那么它们的数量积为他们的模长之积的相反数。

由向量的数量积可以判断它们的夹角和投影。向量的数量积具有交换律。

### 向量的外积

向量的外积，也叫叉积，几何意义是两向量由平行四边形法则围成的面积。外积是一个向量，垂直于原来两个向量所在的平面。对于 $\vec{a}=(x_1,y_1),\vec{b}=(x_2,y_2)$，$\vec{a}\times\vec{b}$ 的方向就要用右手从$\vec{a}$沿着不大于平角的方向旋转，大拇指的方向就是外积的方向。如果外积方向朝外，那么值为正，否则值为负。计算式为 $\vec{a}\times\vec{b}=|\vec{a}||\vec{b}|\sin\theta=x_1y_2-x_2y_1$。因为有谁转向谁的区别，所以外积没有交换律。

$\vec a\times \vec b$ 的正负也可以理解为，把 $\vec a$ 逆时针方向转到 $\vec b$ 的方向，夹角为 $\theta$。当 $0\le\theta<\pi$ 时值为正；当 $\pi\le\theta<2\pi$ 时值为负。

* 如果 $\vec{a}\|\vec{b}$，那么由 $\sin 0^\circ=\sin 180^\circ=0,\vec{a}\times\vec{b}=\vec{0}$，得到的数字结果也是$0$。
* 如果 $\vec{b}$ 的终点在 $\vec{a}$ 的左侧（假设已经共起点），那么 $\vec{a}\times \vec{b}>0$，$\vec{a}$ **握向** $\vec{b}$转过的角逆时针不超过 $180^\circ$，结果为正。
* 如果 $\vec{b}$ 的终点在 $\vec{a}$ 的右侧，那么 $\vec{a}\times \vec{b}<0$，$\vec{a}$ **握向** $\vec{b}$ 转过的角逆时针超过了 $180^\circ$，或者说顺时针不超过 $180^\circ$，大拇指朝内，结果为负。

由向量外积可以判断两向量的**旋转关系**，同时可以方便地求出**点到直线的距离**。分别会用于下面的凸包和旋转卡壳。

一般情况下我们储存点就会把它放在向量中，用向量 $\overrightarrow{OA}$ 来表示 $A$ 这个点。因此下文的 $A\times B$ 就表示向量 $\overrightarrow{OA}$ 与向量 $\overrightarrow{OB}$ 的叉积。

#### 线段交点

**upd on 2019.3.12**

根据面积我们可以求出两线段交点。

我们对于两个线段 $AB,CD$，可以通过面积和相似来求出交点 $O$ 的坐标。因为 $A$ 的坐标已知，实际上是通过求出 $\overrightarrow{AO}$ 来确定 $O$ 的坐标。

我们根据上面的叉积公式求面积，得到 $S_{\triangle ACD}=\frac{\overrightarrow{AD}\times\overrightarrow{AC}}2,S_{\triangle BCD}=\frac{\overrightarrow{BC}\times \overrightarrow{BD}}2$。

再作垂线 $AE\bot CD,BF\bot CD$，$S_{\triangle ACD}=\frac {|CD|\times |AE|}2,S_{\triangle BCD}=\frac {|CD|\times |BF|}2$。则 $\frac{|AE|}{|BF|}=\frac{S_{\triangle ACD}}{S_{\triangle BCD}}$。

此时 $\triangle AEO\backsim\triangle BFO$，得到 $\frac{|AE|}{|BF|}=\frac{|AO|}{|BO|}$。

![](http://www.wjyyy.top/wp-content/uploads/2019/03/201903121600.png)

又因为 $\overrightarrow{AO}=\frac{|AO|}{|AB|}\cdot \overrightarrow{AB}=\frac{|AO|}{|AO|+|BO|}\cdot \overrightarrow{AB}$，令原点为 $O'$，则 $\overrightarrow{O'O}=\overrightarrow{O'A}+\overrightarrow{AO}$，$\overrightarrow{O'O}$ 的坐标即为 $O$ 的坐标。

### 向量旋转

**upd on 2019.3.1**

这个知识点虽然在这篇文章里没有应用，但是是计算几何的基本操作技巧。

设 $\vec a=(x,y)$ ，倾角为 $\theta$ ，长度为 $l=\sqrt{x^2+y^2}$。则 $x=l\cos \theta,y=l\sin\theta$。令其顺时针旋转 $\alpha$ 度角，得到向量 $\vec b=(l\cos(\theta+\alpha),l\sin(\theta+\alpha))$。

![](http://www.wjyyy.top/wp-content/uploads/2019/03/201903010907.png)

由三角恒等变换得，
$$
\vec{b}=(l(\cos\theta\cos\alpha-\sin\theta\sin\alpha),l(\sin\theta\cos\alpha+\cos\theta\sin\alpha))
$$
化简，~~去括号~~
$$
\vec b=(l\cos\theta\cos\alpha-l\sin\theta\sin\alpha,l\sin\theta\cos\alpha+l\cos\theta\sin\alpha)
$$
把上面的 $x,y$ 代回来得
$$
\vec b=(x\cos\alpha-y\sin\alpha,y\cos\alpha+x\sin\alpha)
$$
即使不知道三角恒等变换，这个式子也很容易记下来。

## 三角剖分求面积

三角剖分可以用来求任意多边形的面积。

我们只需要知道一个多边形的各个连续顶点分别在哪里即可。

上面提到了向量的叉积是表示的是有向面积，方向用正负表示，此时正负就派上用场了。

我们如果把相邻**每两个顶点与原点构成的向量的叉积**的数值的一半依次累加起来，就能得到多边形的面积。如下图：红色面积表示负的，蓝色面积表示正的。

$$S_{ABCDEF}=\frac{\overrightarrow{OA}\times \overrightarrow{OB}+\overrightarrow{OB}\times \overrightarrow{OC}+\dots +\overrightarrow{OF}\times \overrightarrow{OA}}2$$

首先计算 $\overrightarrow{OA}\times \overrightarrow{OB}$，得到负的面积 $-S_{\triangle OAB}$，在图上表示为红色部分；然后计算 $S_{\triangle OBC}$，此时在图上表示为**抵消** $-S_{\triangle OBP}$，**并额外加上正的** $S_{\triangle PBC}$。

![三角剖分1](http://www.wjyyy.top/wp-content/uploads/2019/02/201902140847.png)

然后依次进行下去

![三角剖分2](http://www.wjyyy.top/wp-content/uploads/2019/02/201902140906.png)

可以看出，多边形外部出现过的红色总会被消掉，因为多边形是闭合的。当出现了一条相对原点向右的边时，则之后必然会出现一条相对原点向左的边来封闭这个多边形。

如果原点在多边形内部就更好理解了。多边形凹的部分会被”拐回来的部分“给减掉，剩下的部分都可以直接相加。

最终对于 $n$ 边形 $A_1A_2\dots A_n$，面积计算公式就是 $S=x_ny_1-y_nx_1+\sum_{i=1}^{n-1}(x_iy_{i+1}-y_ix_{i+1})$。

当用向量存点时，计算可以用相邻向量叉积之和，$S=A_n\times A_1+\sum_{i=1}^{n-1}A_i\times A_{i+1}$。

## 凸包

### 定义

**凸包**就是求一个周长最小的，并且能包围所有给定点的多边形。当多边形表面存在凹陷时，根据三角不等式 $\left\{\begin{matrix}a+b>c\\ b+c>a\\ a+c>b\end{matrix}\right.$，一定没有直接把最短那条边连起来优。

![img](http://www.wjyyy.top/wp-content/uploads/2018/06/QQ截图20180623222031.png)

### 性质

如果按逆时针方向看，凸包上每两条相邻的边都是向左拐的。比如说，与边 $\vec{a}_i$ 顺时针方向相邻的是边 $\vec{a}_{i+1}$，那么对于任意 $i\in[1,n)$（ $n$ 为凸包上点的个数）有 $\vec{a}_i\times \vec{a}_{i+1}>0,\vec{a}_n\times \vec{a}_1>0$。因为用右手从 $\vec{a}_i$ 的方向顺小于平角的一边握向 $\vec{a}_{i+1}$，大拇指总会指向外边。

### 求法

首先把所有点以横坐标为第一关键字，纵坐标为第二关键字排序。

显然排序后最小的元素和最大的元素一定在凸包上。而且因为是凸多边形，我们如果从一个点出发逆时针走，轨迹总是 “左拐” 的，一旦出现右拐，就说明这一段不在凸包上。因此我们可以用一个单调栈来维护上下凸壳。

因为从左向右看，上下凸壳所旋转的方向不同，为了让单调栈起作用，我们首先**升序枚举**求出下凸壳，然后**降序**求出上凸壳。

求凸壳时，一旦发现即将进栈的点（$P$）和栈顶的两个点（$S_1,S_2$，其中 $S_1$ 为栈顶 ）行进的方向向右旋转，即叉积小于 $0$：$\overrightarrow{S_2S_1}\times \overrightarrow{S_1P}<0$，则弹出栈顶，回到上一步，继续检测，直到 $\overrightarrow{S_2S_1}\times \overrightarrow{S_1P}\ge 0$ 或者栈内仅剩一个元素为止。

通常情况下不需要保留位于凸包边上的点，因此上面一段中 $\overrightarrow{S_2S_1}\times \overrightarrow{S_1P}<0$ 这个条件中的 “$<$” 可以视情况改为 $\le$，同时后面一个条件应改为 $>$。

最后不要忘了把最小的元素与栈顶进行比较，以保证最后一段也是凸壳。

时间复杂度 $O(n\log n)$。

### 代码

```cpp
std::sort(p+1,p+1+n);
stk[++tp]=1;
for(int i=2;i<=n;++i)
{
    while(tp>1&&(p[stk[tp]]-p[stk[tp-1]])*(p[i]-p[stk[tp]])<=0)
        used[stk[tp--]]=0;
    used[i]=1;
    stk[++tp]=i;
}
int qaq=tp;
for(int i=n-1;i>0;--i)
    if(!used[i])
    {
        while(tp>qaq&&(p[stk[tp]]-p[stk[tp-1]])*(p[i]-p[stk[tp]])<=0)
            used[stk[tp--]]=0;
        used[i]=1;
        stk[++tp]=i;
    }
for(int i=1;i<=tp;++i)
    h[i]=p[stk[i]];
```

最后$h$数组中存的就是凸包了。（下标$1$和$tp$存的是同一个点）

## 旋转卡壳

跟我一起读

$$
\text{xu}\acute{\text a}\text n\ \text{zhu}\check{\text a}\text n\ \text{k}\check{\text a}\ \text{k}\acute{\text e}
$$

$$
\huge\text{ 旋\ 转\ 卡\ 壳}
$$

~~我也不知道该怎么读。~~这个词一共有$2^4=16$种读法。

### 前言

**Warning：前言部分仅供引入，严禁参考。**

刚学旋转卡壳时，是看到了一句话：“同时旋转两条平行线直到其中一条和多边形的一条边重合”。那不就是旋转到夹角较小的那一条边上去吗？

![img](http://www.wjyyy.top/wp-content/uploads/2018/12/201812192119.png)

$\angle 1<\angle 2$，那么我们把平行线逆时针旋转过 $\angle 1$ 的大小，就可以和多边形的一边重合了。

于是就出现了这样的代码：

```cpp
/***vct结构体内部***/
friend db operator ^(vct a,vct b)//求夹角
{
    db tmp=a.x*b.x+a.y*b.y;
    tmp/=a.dis();
    tmp/=b.dis();
    return fabs(acos(tmp));
}

/***主函数中***/
while(t2<tp)
{
    db d1=t^(h[t1+1]-h[t1]);//夹角1
    db d2=t_^(h[t2+1]-h[t2]);//夹角2
    if(d1<d2)
    {
        ++t1;
        t.rot(d1);
        t_.rot(d1);
    }
    else
    {
        ++t2;
        t.rot(d2);
        t_.rot(d2);
    }
    db tmp=(h[t1]-h[t2]).dis();
    ans=ans>tmp?ans:tmp;
}
```

然而这样会产生较大的精度误差，显然不是计算几何想要的。

### 凸多边形的切线

如果一条直线与凸多边形有交点，并且整个凸多边形都在这条直线的一侧，那么这条直线就是该凸多边形的一条切线。

### 对踵点

如果过凸多边形上两点作一对平行线，使得整个多边形都在这两条线之间，那么这两个点被称为一对对踵点。

### 凸多边形的直径

即凸多边形上任意两个点之间距离的最大值。直径一定会**在对踵点中产生**，如果两个点不是对踵点，那么两个点中一定可以让一个点向另一个点的对踵点方向移动使得距离更大。并且点与点之间的距离可以体现为线与线之间的距离，在非对踵点之间构造平行线，一定没有在对踵点构造平行线优，这一点可以通过平移看出。

### 旋转卡壳

这是一张比较标致的动图，生动地体现了旋转卡壳的过程，NOIWC2017中的《膜你抄》中也用了这张图。

![](http://www.wjyyy.top/wp-content/uploads/2018/12/917714-20160520110032529-8641355.gif)

![](http://www.wjyyy.top/wp-content/uploads/2018/12/201812202025.png)

为了减小误差~~（上面那个傻乎乎的方法误差就比较大~~，并方便计算，我们求出每一条边的对踵点。通过上面的图可以看出，边的对踵点同时是这两个点的对踵点，因此并没有遗漏。

同时，通过边来求，可以很好地运用叉积的计算，减小了误差。

![img](http://www.wjyyy.top/wp-content/uploads/2018/12/201812192155.png)

对于最下面这条边来说，对于上面四个顶点，他们分别与这条边构成了四个**同底不同高**的三角形，而三角形面积可以用叉积算出来，三角形的面积此时也就反映了点到直线的距离了。由于面积是单峰的，那么对单独一条边的对踵点，我们可以用三分来求，对于所有边，我们可以用two-pointer来 $O(n)$ 求出。因为随着边在逆时针枚举，它的对踵点$T$也在逆时针移动。

> ### 补充：对于三角形面积
>
> ![img](http://www.wjyyy.top/wp-content/uploads/2018/12/201812192201.png)
>
> 因为
> $$\left\{\begin{matrix}\vec{AB}\times\vec{AC}&=&|AB||AC|\sin\theta,\\ S_{\triangle ABC}&=&\frac 12 |AB||AC|\sin \theta,\\ S_{\triangle ABC}&=&\frac 12 |BC|h, \end{matrix}\right.\theta=\angle BAC$$
> 三式联立得 $h=\frac{\vec{AB}\times\vec{AC}}{|BC|}$。

因此可以用旋转卡壳来求凸多边形直径。

### 步骤

首先求出凸包，目的是把所有点按逆时针排序。然后枚举逆时针边，定义 $T$ 为当前的对踵点，若 $T$ 逆时针变动能增大到当前边的距离则改变 $T$，直到继续改变会导致距离减小为止。每次求出边（设为 $AB$）的对踵点 $T_i$ 后，分别用 $|AT_i|,|BT_i|$ 来更新答案，即凸多边形的直径。

时间复杂度 $O(n)$。

### 代码

```cpp
db dis(vct a,vct b,vct x)//求出x到ab的距离
{
    return fabs((a-x)*(b-x)/(a-b).dis());
}
int t=1;
db ans=0.0;
for(int i=1;i<tp;++i)
{
    while(dis(h[i],h[i+1],h[t])<=dis(h[i],h[i+1],h[t+1]))
        t=t%(tp-1)+1;
    ans=std::max(ans,std::max((h[i]-h[t]).dis(),(h[i+1]-h[t]).dis()));//这里的dis是向量的模长
}
```

## 半平面交

### 定义

#### 半平面

一条直线和直线的一侧。半平面是一个点集，因此是一条直线和直线的一侧构成的点集。当包含直线时，称为闭半平面；当不包含直线时，称为开半平面。

解析式一般为 $Ax+By+C\ge 0$。

在计算几何中用向量表示，整个题统一以向量的左侧或右侧为半平面。

![半平面](http://www.wjyyy.top/wp-content/uploads/2019/02/201902132142.png)

#### 半平面交

半平面交是指多个半平面的交集。因为半平面是点集，所以点集的交集仍然是点集。在平面直角坐标系围成一个区域。

这就很像普通的线性规划问题了，得到的半平面交就是线性规划中的可行域。一般情况下半平面交是有限的，经常考察面积等问题的解决。

它可以理解为向量集中每一个向量的右侧的交，或者是下面方程组的解。

$$\left\{\begin{matrix}A_1x+B_1y+C\ge 0\\ A_2x+B_2y+C\ge 0\\ \cdots\end{matrix}\right.$$

#### 多边形的核

如果一个点集中的点与多边形上任意一点的连线与多边形没有其他交点，那么这个点集被称为多边形的核。

把多边形的每条边看成是首尾相连的向量，那么这些向量在多边形内部方向的半平面交就是多边形的核。

### 解法 - S&I算法

#### 极角排序

~~以前一直不会极角排序太丢人了甚至不会写Graham求凸包~~

C语言有一个库函数叫做`atan2(double y,double x)`，可以返回 $\theta\in [-\pi,\pi]$（网上很多地方说左边是开的，不过对排序没有影响），$\theta =\arctan \frac{y}{x}$。

直接以向量为自变量，调用这个函数，以返回值为关键字排序，得到新的边（向量）集。

排序时，如果遇到共线向量（且方向相同），则取靠近可行域的一个。比如两个向量的极角相同，而我们要的是向量的左侧半平面，那么我们只需要保留左侧的向量。判断方法是取其中一个向量的起点或终点与另一个比较，检查是在左边还是在右边。

#### 维护单调队列

因为半平面交是一个凸多边形，所以需要维护一个凸壳。因为后来加入的只可能会影响最开始加入的或最后加入的边（此时凸壳连通），只需要删除队首和队尾的元素，所以需要用单调队列。

我们遍历排好序了的向量，并维护另一个交点数组。当单队中元素超过2个时，他们之间就会产生交点。

对于当前向量，如果上一个交点在这条向量表示的半平面交的**异侧**，那么上一条边就没有意义了。

![单调队列](http://www.wjyyy.top/wp-content/uploads/2019/02/201902140707.png)

如上图，假设取向量左侧半平面。极角排序后，遍历顺序应该是 $\vec a\to\vec b\to\vec c$。当 $\vec a$ 和 $\vec b$ 入队时，在交点数组里会产生一个点 $D$（交点数组保存队列中相同下标的向量与前一向量的交点）。

接下来枚举到 $\vec c$ 时，发现 $D$ 在 $\vec c$ 的右侧。而因为**产生** $D$ **的向量的极角一定比** $\vec c$ **要小**，所以产生 $D$ 的向量（指 $\vec b$）就对半平面交没有影响了。

还有一种可能的情况是快结束的时候，新加入的向量会从队首开始造成影响。

![队首影响](http://www.wjyyy.top/wp-content/uploads/2019/03/201903021609.png)

仍然假设取向量左侧半平面。加入向量 $\vec f$ 之后，第一个交点 $G$ 就在 $\vec f$ 的右侧，我们把上面的判断标准逆过来看，就知道此时应该删除向量 $\vec a$，也即**队首**的向量。

最后用队首的向量排除一下队尾多余的向量。因为队首的向量会被后面的约束，而队尾的向量不会。此时它们围成了一个环，因此队首的向量就可以约束队尾的向量。

#### 得到半平面交

如果半平面交是一个凸 $n$ 边形，最后在交点数组里会得到 $n$ 个点。我们再把它们首尾相连，就是一个统一方向（顺或逆时针）的 $n$ 多边形。

此时就可以用三角剖分求面积了。（求面积是最基础的考法）

偶尔会出现半平面交不存在或面积为0的情况，注意考虑边界。

时间复杂度 $O(n\log n)$。

> #### 注意事项
> 
> **upd on 2019.3.1**
>
> 昨天晚上 @[WG6101N](https://www.luogu.org/space/show?uid=70545) 同学跟我说两个循环写反了会挂得很惨…稍微研究了一下原因。
>
> 当出现一个可以把队列里的点全部弹出去的向量（即所有队列里的点都在该向量的右侧），则我们**必须**先处理队尾，再处理队首。因此在循环中，我们先枚举`--r;`的部分，再枚举`++l;`的部分，才不会错。原因如下。
>
> ![](http://www.wjyyy.top/wp-content/uploads/2019/03/201903010824.png)
>
> 一般情况下，我们在队列 (队列顺序为 $\left\{\vec{u},\vec{v}\right\}$) 后面加一条边（向量 $\vec w$），会产生一个交点 $N$ ，缩小 $\vec{v}$ 后面的范围。
>
> ![](http://www.wjyyy.top/wp-content/uploads/2019/03/201903010837.png)
>
> 但是毕竟每次操作都是一般的，因此可能会有把 $M$ 点“挤出去”的情况。
>
> ![](http://www.wjyyy.top/wp-content/uploads/2019/03/201903010829.png)
>
> 如果此时出现了向量 $\vec a$ ，使得 $M$ 在 $\vec a$ 的右侧，那么 $M$ 就要出队了。此时如果从队首枚举`++l`，显然是扩大了范围。实际上 $M$ 点是由 $\vec u$ 和 $\vec v$ 共同构成的，因此需要考虑影响到现有进程的是 $\vec u$ 还是 $\vec v$。而因为我们在极角排序后，向量是逆时针顺序，所以 $\vec v$ 的影响要更大一些。
>
> 就如上图，如果 $M$ 确认在 $\vec a$ 的右侧，那么此时 $\vec v$ 的影响一定不会对半平面交的答案作出任何贡献。
>
> 而我们排除队首的原因是**当前向量的限制比队首向量要大**，这个条件的前提是队列里有不止两个线段（向量），不然就会出现上面的情况。
>
> 所以一定要先排除队尾再排除队首。

### 代码

比较部分

```cpp
friend bool operator <(seg x,seg y)
{
    db t1=atan2((x.b-x.a).y,(x.b-x.a).x);
    db t2=atan2((y.b-y.a).y,(y.b-y.a).x);//求极角
    if(fabs(t1-t2)>eps)//如果极角不等
        return t1<t2;
    return (y.a-x.a)*(y.b-x.a)>eps;//判断向量x在y的哪边，令最靠左的排在最左边
}
```

增量部分

```cpp
//pnt its(seg a,seg b)表示求线段a,b的交点
//s[]是极角排序后的向量
//q[]是向量队列
//t[i]是s[i-1]与s[i]的交点
//【码风】队列的范围是(l,r]
//求的是向量左侧的半平面
int l=0,r=0;
for(int i=1;i<=n;++i)
    if((s[i]==s[i-1])==false)
    {
    	//务必先检查队尾再检查队首
        while(r-l>1&&(s[i].b-t[r])*(s[i].a-t[r])>eps)//如果上一个交点在向量右侧则弹出队尾
            --r;
        while(r-l>1&&(s[i].b-t[l+2])*(s[i].a-t[l+2])>eps)//如果第一个交点在向量右侧则弹出队首
            ++l;
        q[++r]=s[i];
        if(r-l>1)
            t[r]=its(q[r],q[r-1]);//求新交点
    }
while(r-l>1&&(q[l+1].b-t[r])*(q[l+1].a-t[r])>eps)//注意删除多余元素
    --r;
t[r+1]=its(q[l+1],q[r]);//再求出新的交点
++r;
//这里不能在t里面++r需要注意一下……
```

## Graham

```cpp
using db=double;
const db eps=1e-9;
const int N=1e5+5;
int n;
struct point{
	db x,y;
	point operator-(point &a){return {x-a.x,y-a.y};}
}start;
int st[N],tp;
db operator*(point a,point b){return a.x*b.y-b.x*a.y;}
db sq(db x){return x*x;}
db dis2(point a,point b){return sq(a.x-b.x)+sq(a.y-b.y);}
bool more_left(point a,point b,point c){
	db s=(b-a)*(c-a);
	return (s<0||(s==0&&dis2(b,a)>=dis2(c,a)));
}
bool cmp(point p1,point p2){
	db s=(p1-start)*(p2-start);
	return (s<0||(s==0&&dis2(p1,start)>=dis2(p2,start)));
}
vector<point>convex_hull(vector<point>a){
    int n=a.size();
    int fr=0;
    for(int i=0;i<n;i++)
		if(a[i].x<a[fr].x||(a[i].x==a[fr].x&&a[i].y<a[fr].y))
            fr=i;
	swap(a[0],a[fr]);
    start=a[0];
	sort(a.begin()+1,a.end(),cmp);
	a.push_back(a[0]);
	st[1]=0,st[2]=1;tp=2;
	for(int i=2;i<=n;i++){
		while(tp>1&&more_left(a[st[tp-1]],a[i],a[st[tp]]))tp--;
		st[++tp]=i;
	}
    vector<point>t;
    for(int i=1;i<=tp;i++)t.push_back(a[st[i]]);
    return t;
}
int main(){
	cin>>n;
    vector<point>a(n);
	for(int i=0;i<n;i++)cin>>a[i].x>>a[i].y;
    a=convex_hull(a);
	db ans=0;
	for(int i=0;i+1<a.size();i++)ans+=sqrt(dis2(a[i],a[i+1]));
	printf("%.2lf",ans);
	return 0;
}
```

## 感谢

- 感谢@[Dew](https://www.luogu.org/space/show?uid=63727)的审稿。
- 感谢kfdong给出的计算几何学习建议。
- 感谢管理员的认真审核~~（不管是否通过）过了~~。
- 感谢@[WG6101N](https://www.luogu.org/space/show?uid=70545)指出了**注意事项**。
- 感谢 wjyyy 的[计算几何初步](https://www.luogu.me/article/1pv0nw0s)

# 其他模板

## 高精度

```cpp
struct BigInteger {
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;
    bool sign;

    BigInteger(long long num = 0) { *this = num; }
    BigInteger(const string& str) { *this = str; }

    BigInteger operator = (long long num) {
        s.clear();
        sign = (num < 0);
        if (num < 0) num = -num;
        do {
            s.push_back(num % BASE);
            num /= BASE;
        } while (num > 0);
        return *this;
    }

    BigInteger operator = (const string& str) {
        s.clear();
        string numStr = str;
        sign = false;
        if (numStr[0] == '-') {
            sign = true;
            numStr = numStr.substr(1);
        }

        int x, len = (numStr.length() - 1) / WIDTH + 1;
        for (int i = 0; i < len; i++) {
            int end = numStr.length() - i * WIDTH;
            int start = max(0, end - WIDTH);
            sscanf(numStr.substr(start, end - start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return *this;
    }

    void normalize() {
        while (s.size() > 1 && s.back() == 0) s.pop_back();
        if (s.size() == 1 && s[0] == 0) sign = false;
    }

    bool operator < (const BigInteger& b) const {
        if (sign != b.sign) return sign;
        if (s.size() != b.s.size())
            return sign ? s.size() > b.s.size() : s.size() < b.s.size();
        for (int i = s.size() - 1; i >= 0; i--)
            if (s[i] != b.s[i])
                return sign ? s[i] > b.s[i] : s[i] < b.s[i];
        return false;
    }

    bool operator > (const BigInteger& b) const { return b < *this; }
    bool operator <= (const BigInteger& b) const { return !(b < *this); }
    bool operator >= (const BigInteger& b) const { return !(*this < b); }
    bool operator != (const BigInteger& b) const { return b < *this || *this < b; }
    bool operator == (const BigInteger& b) const { return !(b < *this) && !(*this < b); }

    BigInteger operator + (const BigInteger& b) const {
        if (sign == b.sign) {
            BigInteger c;
            c.sign = sign;
            c.s.clear();
            for (int i = 0, g = 0; ; i++) {
                if (g == 0 && i >= s.size() && i >= b.s.size()) break;
                int x = g;
                if (i < s.size()) x += s[i];
                if (i < b.s.size()) x += b.s[i];
                c.s.push_back(x % BASE);
                g = x / BASE;
            }
            return c;
        } else {
            if (sign) {
                BigInteger tmp = *this;
                tmp.sign = false;
                return b - tmp;
            } else {
                BigInteger tmp = b;
                tmp.sign = false;
                return *this - tmp;
            }
        }
    }

    BigInteger operator - (const BigInteger& b) const {
        if (sign != b.sign) {
            BigInteger tmp = b;
            tmp.sign = !b.sign;
            return *this + tmp;
        }

        if (*this == b) return BigInteger(0);

        BigInteger c;
        if ((!sign && *this > b) || (sign && *this < b)) {
            c = *this;
            for (int i = 0, g = 0; i < c.s.size() || i < b.s.size(); i++) {
                int x = c.s[i] - g;
                if (i < b.s.size()) x -= b.s[i];
                if (x < 0) {
                    g = 1;
                    x += BASE;
                } else {
                    g = 0;
                }
                if (i < c.s.size()) c.s[i] = x;
                else c.s.push_back(x);
            }
            c.normalize();
            c.sign = sign;
        } else {
            c = b - *this;
            c.sign = !sign;
        }
        return c;
    }

    BigInteger operator * (const BigInteger& b) const {
        BigInteger c;
        c.sign = (sign != b.sign);
        c.s.resize(s.size() + b.s.size(), 0);

        for (int i = 0; i < s.size(); i++) {
            long long g = 0;
            for (int j = 0; j < b.s.size() || g > 0; j++) {
                long long x = c.s[i + j] + g;
                if (j < b.s.size()) x += (long long)s[i] * b.s[j];
                c.s[i + j] = x % BASE;
                g = x / BASE;
            }
        }
        c.normalize();
        return c;
    }

    BigInteger operator / (const BigInteger& b) const {
        if (b == BigInteger(0)) throw "Division by zero";

        BigInteger c, current;
        c.sign = (sign != b.sign);
        c.s.resize(s.size(), 0);

        for (int i = s.size() - 1; i >= 0; i--) {
            current = current * BASE + s[i];

            int l = 0, r = BASE - 1, ans = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (b.abs() * mid <= current.abs()) {
                    ans = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            c.s[i] = ans;
            current = current - b.abs() * ans;
        }
        c.normalize();
        return c;
    }

    BigInteger operator / (int b) const {
        if (b == 0) throw "Division by zero";

        BigInteger c;
        c.sign = (sign != (b < 0));
        c.s.resize(s.size(), 0);

        if(b < 0) b = -b;
        long long r = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            r = r * BASE + s[i];
            c.s[i] = r / b;
            r %= b;
        }
        c.normalize();
        return c;
    }

    BigInteger abs() const {
        BigInteger result = *this;
        result.sign = false;
        return result;
    }

    BigInteger operator += (const BigInteger& b) { *this = *this + b; return *this; }
    BigInteger operator ++ (int) { BigInteger tmp = *this; *this = *this + 1; return tmp; }
    BigInteger operator ++ () { *this = *this + 1; return *this; }
    BigInteger operator -= (const BigInteger& b) { *this = *this - b; return *this; }
    BigInteger operator -- (int) { BigInteger tmp = *this; *this = *this - 1; return tmp; }
    BigInteger operator -- () { *this = *this - 1; return *this; }
    BigInteger operator *= (const BigInteger& b) { *this = *this * b; return *this; }
    BigInteger operator /= (const BigInteger& b) { *this = *this / b; return *this; }

    friend ostream& operator << (ostream& out, const BigInteger& x) {
        if (x.sign && !(x.s.size() == 1 && x.s[0] == 0)) out << '-';
        out << x.s.back();
        for (int i = x.s.size() - 2; i >= 0; i--) {
            char buf[20];
            sprintf(buf, "%08d", x.s[i]);
            out << buf;
        }
        return out;
    }

    friend istream& operator >> (istream& in, BigInteger& x) {
        string s;
        if (!(in >> s)) return in;
        x = s;
        return in;
    }
};
```

## pbds

### 平衡树

头文件：

```cpp
#include <ext/pb_ds/assoc_container.hpp>  // 因为 tree 定义在这里 所以需要包含这个头文件
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
__gnu_pbds::tree<Key, Mapped, Cmp_Fn = std::less<Key>, Tag = rb_tree_tag,
                 Node_Update = null_tree_node_update,
                 Allocator = std::allocator<char>>
```

构造方式：

```cpp
__gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type,
                 std::less<std::pair<int, int>>, __gnu_pbds::rb_tree_tag,
                 __gnu_pbds::tree_order_statistics_node_update>
    trr;
```

成员函数：
- `insert(x)`：向树中插入一个元素 x，返回 std::pair<point_iterator, bool>，其中第一个元素代表插入位置的迭代器，第二个元素代表是否插入成功．
- `erase(x)`：从树中删除一个元素/迭代器 x．如果 x 是迭代器，则返回指向 x 下一个的迭代器（如果 x 是 end() 则返回 end()）；如果 x 是 Key，则返回是否删除成功（如果不存在则删除失败）．
- `order_of_key(x)`：返回严格小于 x 的元素个数（以 `Cmp_Fn` 作为比较逻辑），即从 0 开始的排名．
- `find_by_order(x)`：返回 `Cmp_Fn` 比较的排名所对应元素的迭代器．
- `lower_bound(x)`：返回第一个不小于 x 的元素所对应的迭代器（以 `Cmp_Fn` 作为比较逻辑）．
- `upper_bound(x)`：返回第一个严格大于 x 的元素所对应的迭代器（以 `Cmp_Fn` 作为比较逻辑）．
- `join(x)`：将 x 树并入当前树，x 树被清空（必须确保两树的 比较函数 和 元素类型 相同）．
- `split(x,b)`：以 `Cmp_Fn` 比较，小于等于 x 的属于当前树，其余的属于 b 树．
- `empty()`：返回是否为空．
- `size()`：返回大小．

### 哈希表

头文件：

```cpp
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
```

构造方式：

```cpp
__gnu_pbds::gp_hash_table <T1, T2> H1;
// 防止被卡
#include <ctime>
#include <ext/pb_ds/assoc_container.hpp>
const int RANDOM = time(NULL);
struct MyHash {int operator() (int x) const {return x ^ RANDOM;}};
__gnu_pbds::gp_hash_table <int, int, MyHash> Table;
// 自定义
#include <vector>
#include <string>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
template <class T1, class T2> 
struct std::tr1::hash <std::pair <T1, T2> > {
    size_t operator() (std::pair <T1, T2> x) const {
        std::tr1::hash <T1> H1; std::tr1::hash <T2> H2;
        return H1(x.first) ^ H2(x.second); // 你自定义的 hash 函数。
    }
};
```

## fast-GCD

```cpp
int gcd(int a,int b){
    if(!a||!b)return a|b;
    int shift=__builtin_ctzll(a|b);
    a>>=__builtin_ctzll(a);
    do{
        b>>=__builtin_ctzll(b);
        if(a>b)swap(a,b);
        b-=a;
    }while(b);
    return a<<shift;
}
```

## 快速读写

```cpp
int read(){
	int x=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x;
}
void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
```

### 超级快速读写

```cpp
namespace IO{
    int len=0;
    char ibuf[(1<<20)+1],*iS,*iT,out[(1<<26)+1];
    #define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
    #define reg register
    inline int read(){
        reg char ch=gh();
        reg int x=0;
        reg char t=0;
        while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
        while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
        return t?-x:x;
    }
    inline void putc(char ch){
        out[len++]=ch;
    }
    template<class T>
    inline void write(T x){
        if(x<0)putc('-'),x=-x;
        if(x>9)write(x/10);
        out[len++]=x%10+48;
    }
    inline void flush(){
        fwrite(out,1,len,stdout);
        len=0;
    }
}
using IO::read;
using IO::write;
using IO::flush;
using IO::putc;
```

## 巴雷特模乘

```cpp
class barrett {
 	private:
  	int64_t I;
  	int32_t M;
	public:
  		barrett(uint32_t p) : 
    I(((__int128)1 << 64) / p), M(p) {assert(p && p <= (int)1e9 + 9);}
  	uint32_t operator ()(uint64_t x) {
    	return x - ((__int128(x) * I) >> 64) * M;
  	}
};
```

使用方法：
1. 初始化：`barrett mod(1000000007);`。模数最高 $10^9+9$，可调参。
2. 使用：`y = mod(x)` 即可。

# 香椿时代

这里空间太小了，放不下，所以删了。