// https://ideone.com/Tkters

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;

int MAX = 1000000;

int a[300000];

struct wavelet {
    int lo, hi;
    wavelet *c[2];
    vi b;
    
    wavelet(int *from, int *to, int x, int y) {
        lo = x, hi = y;
        if (lo == hi || from >= to) return;
        int mid = (lo+hi)/2;
        auto f = [mid](int x) { return x <= mid; };
        b.pb(0); for (auto it = from; it != to; it++) b.pb(b.back()+f(*it));
        auto pivot = stable_partition(from,to,f);
        c[0] = new wavelet(from,pivot,lo,mid);
        c[1] = new wavelet(pivot,to,mid+1,hi);
    }
    
    int kth(int l, int r, int k) { // kth number in [l,r]
        if (l > r) return 0;
        if (lo == hi) return lo;
        int inLeft = b[r]-b[l-1];
        int lb = b[l-1], rb = b[r];
        if (k <= inLeft) return c[0]->kth(lb+1,rb,k);
        return c[1]->kth(l-lb,r-rb,k-inLeft);
    }
    
    int LTE(int l, int r, int k) { // less than or equal to k
		if(l > r || k < lo) return 0;
		if(hi <= k) return r-l+1;
		int lb = b[l-1], rb = b[r];
		return c[0]->LTE(lb+1, rb, k)+c[1]->LTE(l-lb, r-rb, k);
	}
 
	int count(int l, int r, int k) { // equal to k
		if(l > r || k < lo || k > hi) return 0;
		if(lo == hi) return r - l + 1;
		int lb = b[l-1], rb = b[r], mid = (lo+hi)/2;
		if(k <= mid) return c[0]->count(lb+1, rb, k);
		return c[1]->count(l-lb, r-rb, k);
	}
};

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	int i,n,k,j,q,l,r;
	cin >> n;
	F0R(i,n) cin >> a[i+1];
	wavelet T(a+1, a+n+1, 1, MAX);
	cin >> q;
	while (q--){
		int x;
		cin >> x >> l >> r >> k;
		if(x == 0){
			//kth smallest
			cout << "Kth smallest: ";
			cout << T.kth(l, r, k) << endl;
		}
		if(x == 1){
			//less than or equal to K
			cout << "LTE: ";
			cout << T.LTE(l, r, k) << endl;
		}
		if(x == 2){
			//count occurence of K in [l, r]
			cout << "Occurence of K: ";
			cout << T.count(l, r, k) << endl;
		}
	}
	return 0;
}

// read!
// ll vs. int!
