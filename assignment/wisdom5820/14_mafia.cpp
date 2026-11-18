/*
   1. 사용한 AI: ChatGPT
   2. 과제에서 활용한 부분: DFS로 전체 부하 수 계산
   3. 어떤 도움이 필요했는지: 간접 부하까지 포함해 세는 방법을 질문함
   4. AI를 통해 추가·개선한 부분: 직속 부하마다 본인 1명과 DFS가 반환한 부하 수를 더하는 방법을 참고함
*/

#include <bits/stdc++.h>
using namespace std;

struct Member {
    string name; // 이름
    int total;   // 전체 부하 수
    int depth;   // 깊이
};


struct Compare {
    bool operator()(const Member& a, const Member& b) const {
        if (a.total != b.total)
            return a.total < b.total; // 1. 전체 부하 수가 많은 사람 우선 
        if (a.depth != b.depth)
            return a.depth > b.depth; // 2. 깊이가 작은 사람 우선
        return a.name > b.name;       // 3. 이름의 사전순 우선
    }
};

map<string, vector<string>> children; // 상사 - 직속 부하 목록
priority_queue<Member, vector<Member>, Compare> pq;

// 전체 부하 수 계산 
int dfs(const string& name, int depth) {
    int total = 0; // 현재 직원의 전체 부하 수 

    for (const string& child : children[name])  // 자식 노드 순회하면서 
        total += 1 + dfs(child, depth + 1); // 직속 부하 1명 + 해당 부하가 거느린 전체 부하 수

    pq.push({name, total, depth});
    return total;
}

int main() {
    int n;
    cin >> n;

    set<string> hasBoss; // 상사가 존재하냐 

    // 입력
    for (int i = 0; i < n - 1; ++i) {
        string person, boss;
        cin >> person >> boss;
        children[boss].push_back(person);
        hasBoss.insert(person);
    }

    // 루트 찾기 
    string root;
    for (const auto& entry : children) {
        if (hasBoss.count(entry.first) == 0) { // 상사가 존재하지 않는다 => 루트
            root = entry.first;
            break;
        }
    }

    dfs(root, 0);

    while (!pq.empty()) {
        cout << pq.top().name << '\n'; // 우선순위가 높은 거부터 출력
        pq.pop();
    }
}