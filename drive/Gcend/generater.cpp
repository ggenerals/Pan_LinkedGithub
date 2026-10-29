#include <bits/stdc++.h>
using namespace std;

const int N = 100000;
mt19937_64 rng;
int dcnt[N + 1], firstPos[N + 1];

int rnd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

void init() {
    for (int i = 1; i <= N; ++i)
        for (int j = i; j <= N; j += i)
            ++dcnt[j];

    fill(firstPos, firstPos + N + 1, N + 1);
    for (int i = 1; i <= N; ++i)
        firstPos[dcnt[i]] = min(firstPos[dcnt[i]], i);
}

struct Limit {
    int n, m, k, t;
    bool sameK;
};

// 字段依次为 n 上限、m 上限、k 上限、T、是否要求 k 相同。
Limit lim[11] = {
    {},
    {5,      5,      5,      100000, false}, // Sub 1
    {18,     18,     18,     100000, false}, // Sub 2
    {100000, 2,      2,      100000, true }, // Sub 3
    {200,    200,    200,    100000, false}, // Sub 4
    {200,    100000, 200,    100000, false}, // Sub 5
    {1000,   1000,   1000,   100000, false}, // Sub 6
    {1000,   100000, 1000,   100000, false}, // Sub 7
    {100000, 100000, 100000, 10,     false}, // Sub 8
    {100000, 100000, 100000, 100000, true }, // Sub 9
    {100000, 100000, 100000, 100000, false}  // Sub 10
};

int chooseN(int maxN, int mode) {
    int n;
    if (mode == 0) {
        int a[] = {
            1, 2, maxN, max(1, maxN - 1),
            max(1, maxN / 2)
        };
        n = a[rnd(0, 4)];
    } else if (mode == 1) {
        n = rnd(1, min(maxN, 30));
    } else if (mode == 3) {
        n = rnd(max(1, maxN - min(100, maxN - 1)), maxN);
    } else if (mode == 4) {
        int z = rnd(1, 4);
        if (z == 1)
            n = rnd(1, min(maxN, 20));
        else if (z <= 3)
            n = rnd(max(1, maxN - min(100, maxN - 1)), maxN);
        else
            n = rnd(1, maxN);
    } else {
        n = rnd(1, maxN);
    }
    return max(2, min(n, maxN));
}

int chooseM(int maxM, int mode) {
    if (mode == 0) return rnd(2, min(maxM, 3));
    if (mode == 3) return maxM;
    if (mode == 4 && rnd(1, 2) == 1) return maxM;
    return rnd(2, maxM);
}

// 对固定 n，返回一个不可能实现的 k；若没有则返回 -1。
int getInvalidK(int n, int maxK) {
    vector<int> v;
    for (int k = 1; k <= maxK; ++k)
        if (firstPos[k] >= n)
            v.push_back(k);

    if (v.empty()) return -1;
    return v[rnd(0, (int)v.size() - 1)];
}

struct Query {
    int n, m, k;
};

Query makeValid(const Limit &L, int mode) {
    int n = chooseN(L.n, mode);
    int m = chooseM(L.m, mode);
    int g = rnd(1, n - 1);
    return {n, m, dcnt[g]};
}

Query makeInvalid(const Limit &L, int mode) {
    int m = chooseM(L.m, mode);
    while (true) {
        int n = chooseN(L.n, mode);
        int k = getInvalidK(n, L.k);
        if (k != -1)
            return {n, m, k};
    }
}

int testCount(int sub) {
    return lim[sub].t;
}

void writeFile(int sub, int fileId, const vector<Query> &q) {
    string name = "sub" + to_string(sub) + "_" +
                  to_string(fileId) + ".in";

    ofstream fout(name);
    fout << q.size() << '\n';
    for (auto x : q)
        fout << x.n << ' ' << x.m << ' ' << x.k << '\n';
}

void genNormalFile(int sub, int fileId, uint64_t seed) {
    rng.seed(seed);
    const Limit &L = lim[sub];
    int T = testCount(sub);
    int mode = fileId - 1;

    vector<Query> q;
    q.reserve(T);

    // 大部分询问有解，至少放入一个无解询问。
    // 其他询问中约 0.5% 为无解情况。
    q.push_back(makeValid(L, mode));

    if (T >= 2)
        q.push_back(makeInvalid(L, mode));

    for (int i = 2; i < T; ++i) {
        if (rnd(1, 1000) <= 5)
            q.push_back(makeInvalid(L, mode));
        else
            q.push_back(makeValid(L, mode));
    }

    writeFile(sub, fileId, q);
}

void genSameKFile(int sub, int fileId, uint64_t seed) {
    rng.seed(seed);
    const Limit &L = lim[sub];
    int T = testCount(sub);

    vector<Query> q;
    q.reserve(T);

    // Sub 3：k <= 2 且同文件的 k 相同。
    // 固定 k=2，n=2 时无解，n>=3 时有解。
    if (sub == 3) {
        for (int i = 0; i < T; ++i) {
            bool invalid =
                (i == 1 || (i >= 2 && rnd(1, 1000) <= 5));

            int n = invalid ? 2 : rnd(3, L.n);
            q.push_back({n, 2, 2});
        }
        writeFile(sub, fileId, q);
        return;
    }

    // Sub 9：先取一个实际存在的因子个数 k。
    // firstPos[k] 是最小的、因子个数为 k 的正整数。
    int g = rnd(2, min(1000, L.n - 1));
    int k = dcnt[g];
    int first = firstPos[k];

    for (int i = 0; i < T; ++i) {
        bool invalid =
            (i == 1 || (i >= 2 && rnd(1, 1000) <= 5));

        int n, m;

        if (invalid)
            n = rnd(2, first);
        else
            n = rnd(first + 1, L.n);

        if (fileId == 1)
            m = rnd(2, 10);
        else if (fileId == 2)
            m = L.m;
        else if (fileId == 3)
            m = rnd(max(2, L.m - 100), L.m);
        else if (fileId == 4)
            m = rnd(2, min(L.m, 100));
        else
            m = rnd(2, L.m);

        q.push_back({n, m, k});
    }

    writeFile(sub, fileId, q);
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    uint64_t seed =
        chrono::steady_clock::now().time_since_epoch().count();

    if (argc >= 2)
        seed = stoull(argv[1]);

    init();

    for (int sub = 1; sub <= 10; ++sub) {
        for (int fileId = 1; fileId <= 5; ++fileId) {
            uint64_t curSeed =
                seed + 1000003ULL * sub + 9176ULL * fileId;

            if (lim[sub].sameK)
                genSameKFile(sub, fileId, curSeed);
            else
                genNormalFile(sub, fileId, curSeed);
        }
    }

    cerr << "Generated 50 files. "
         << "T=100000 except Sub 8 (T=10).\n";

    return 0;
}