//논리식을 논리곱 정규형으로 표현했을 때 각 절에 두 개의 변수만이 존재하는 경우에 대해 참인 결과를 내보낸다.
const int vars = 10001;

vector<vector<int> > adj(vars*2);
vector<int> sccId(vars*2,-1);
vector<int> visited(vars*2,-1);
stack<int> st;
int scccnt, vcnt;

int scc(int here){
	int ret = visited[here] = vcnt++;
	st.push(here);
	for(int i=0;i<adj[here].size();i++){
		int there = adj[here][i];
		if(visited[there] == -1)
			ret = min(ret, scc(there));
		else if(sccId[there] == -1)
			ret = min(ret, visited[there]);
	}
	if(ret == visited[here]){
		while(true){
			int t = st.top();
			st.pop();
			sccId[t] = scccnt;
			if(t == here) break;
		}
		++scccnt;
	}
	return ret;
}

int opp(int n) { return n%2 ? n-1 : n+1; }

int main(){
	int N,M;
	scanf("%d %d",&N,&M);
	for(int i=0;i<M;i++){
		int A,B;
		scanf("%d %d",&A,&B);
		A = (A>0 ? A*2 : -A*2+1);
		B = (B>0 ? B*2 : -B*2+1);
		adj[opp(A)].pb(B);
		adj[opp(B)].pb(A);
	}
	for(int i=2;i<2*(N+1);i++)
		if(visited[i] == -1) scc(i);
	for(int i=2;i<2*(N+1);i+=2)
		if(sccId[i] == sccId[i+1]){
			printf("0\n");
			return 0;
		}
	printf("1\n");

	// // SCC번호의 역순으로 각 정점을 정렬하면 위상 정렬 순서가 된다.
	vector<int> value(vars*2, -1);
	vector<pii> order;
	for(int i=2;i<2*(N+1);i++)
		order.pb(mp(-sccId[i],i));
	sort(order.begin(), order.end());

	for(int i=0;i<2*N;i++){
		int vertex = order[i].second;
		int variable = vertex/2, isTrue = vertex%2 == 0;
		if(value[variable] != -1) continue;
		// not A가 먼저 나왔을 경우 A는 참
		// A가 not A보다 먼저 나왔을 경우 A는 거짓
		value[variable] = !isTrue;
	}
	
	for(int i=1;i<=N;i++){
		printf("%d ",value[i]);
		return 0;
	}
	printf("\n");
}