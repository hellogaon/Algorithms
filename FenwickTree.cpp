#include <cstdio>
#include <vector>

using namespace std;

struct Fenwicktree {
  vector<int> tree;
  Fenwicktree(int n) : tree(n+1) {}
  //맨 오른쪽에 있는 1인 비트를 지우는 연산
  int sum(int pos){
    ++pos;
    int ret = 0;
    while(pos > 0){
      ret += tree[pos];
      pos &= (pos-1);
    }
    return ret;
  }
  //맨 오른쪽애 있는 1인 비트를 스스로에게 더해 주는 연산
  void add(int pos, int val){
    ++pos;
    while(pos < tree.size()){
      tree[pos] += val;
      pos += (pos & -pos);
    }
  }
};

int main(){
  int N,M,K;
  scanf("%d %d %d",&N,&M,&K);
  vector<int> v(N+1);
  Fenwicktree tree(N+1);
  for(int i=1;i<=N;i++){
    scanf("%d",&v[i]);
    tree.add(i,v[i]);
  }
  for(int i=0;i<M+K;i++){
    int A,B,C;
    scanf("%d %d %d",&A,&B,&C);
    if(A==1) tree.add(B,C-v[B]), v[B]=C;
    else printf("%d\n",tree.sum(C)-tree.sum(B-1));
  }
}
