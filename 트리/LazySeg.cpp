struct SegTree{
  int n;
  vector<ll> sum;
  vector<ll> lazy;
  SegTree(vector<ll>& a){
    n = a.size();
    sum.resize(4 * n);
    lazy.resize(4 * n);
    init(a,1,0,n-1);
  }
  ll init(vector<ll>& a, int node, int nl, int nr){
    if(nl == nr) return sum[node] = a[nl];
    int mid = (nl+nr)/2;
    return sum[node] = init(a,node*2,nl,mid) + init(a,node*2+1,mid+1,nr);
  }
  ll query(int l, int r, int node, int nl, int nr){
    update_lazy(nl,nr,node);
    if(r < nl || nr < l) return 0;
    if(l <= nl && nr <= r) return sum[node];
    int mid = (nl+nr)/2;
    return query(l,r,node*2,nl,mid) + query(l,r,node*2+1,mid+1,nr);
  }
  void update_lazy(int l, int r, int node){
    if(lazy[node] != 0){
      sum[node] += (r-l+1)*lazy[node];
      if(l != r){
        lazy[node*2] += lazy[node];
        lazy[node*2+1] += lazy[node];
      }
      lazy[node] = 0;
    }
  }
  void update_range(int l, int r, ll diff, int node, int nl, int nr){
    update_lazy(nl,nr,node);
    if(r < nl || nr < l) return;
    if(l <= nl && nr <= r){
      sum[node] += (nr-nl+1)*diff;
      if(nl != nr){
        lazy[node*2] += diff;
        lazy[node*2+1] += diff;
      }
      return;
    }
    int mid = (nl+nr)/2;
    update_range(l,r,diff,node*2,nl,mid);
    update_range(l,r,diff,node*2+1,mid+1,nr);
    sum[node] = sum[node*2] + sum[node*2+1];
  }
};
