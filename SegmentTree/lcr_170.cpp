#include <iostream>
#include <vector>

using namespace std;

class SegmentTree
{
public:
    SegmentTree(int size) : n(size)
    {
        tree.resize(4 * n, 0);
    }

    void update(int index)
    {
        update(1, 0, n - 1, index);
    }

    int query(int l, int r)
    {
        if (l > r)
        {
            return 0;
        }
        return query(1, 0, n - 1, l, r);
    }

private:
    vector<int> tree;
    int         n;

    void update(int node, int l, int r, int index)
    {
        if (l == r)
        {
            tree[node]++;
            return;
        }

        int mid = (l + r) / 2;
        if (index <= mid)
        {
            update(2 * node, l, mid, index);
        }
        else
        {
            update(2 * node + 1, mid + 1, r, index);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int query(int node, int l, int r, int ql, int qr)
    {
        if (ql > r || qr < l)
        {
            return 0;
        }
        if (ql <= l && qr >= r)
        {
            return tree[node];
        }

        int mid = (l + r) / 2;
        return query(2 * node, l, mid, ql, qr) + query(2 * node + 1, mid + 1, r, ql, qr);
    };
};

int main()
{
    int n;
    cin >> n;
    vector<int> A(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> A[i];
        // 0-based
        A[i]--;
    }

    vector<long long> inversion_count(n, 0);
    SegmentTree       st(n);

    for (int i = 0; i < n; ++i)
    {
        // 0-based
        // (A[i], n-1]
        // [A[i]+1, n-1]
        int inversions_with_Ai = st.query(A[i] + 1, n - 1);
        // update
        inversion_count[i] = (i > 0 ? inversion_count[i - 1] : 0) + inversions_with_Ai;
        st.update(A[i]);
    }

    for (int i = 0; i < n; ++i)
    {
        cout << inversion_count[i] << endl;
    }

    return 0;
}