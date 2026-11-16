#include <bits/stdc++.h>
using namespace std;

int G; // 초기값 : 0
// 전역변수는 자동으로 0으로 초기화됨

// private compare function
struct mycomp {
    bool operator()(const int& left, const int& right) {
        if (G % 2 == 0)
            return left > right;
        else
            return left < right;
    }
};

int main() {
    int thedata[] = { 45, 23, 11, 6, 27, 71, 9, 30, 62, 99, 63, 34, 90, 32 };

    priority_queue<int, vector<int>, mycomp> Room(thedata, thedata+12) ;
    // pq 생성 시점에는 G = 0
    // 따라서 left > right가 적용됨
    // => 최소 힙

    G = Room.size() ;
    while (!Room.empty()) {
        cout << " 끝까지 뽑아내기 " << setw(4) << Room.top() << endl;
        Room.pop(); // pop() 내부에서 비교함수 호출 -> 비교 기준과 실제 힙 구조가 일치하지 않는 문제
        G--; // G가 변경되어도 기존 힙이 새로운 기준으로 재정렬 되지 않음
    }

    cout << "\n 모두 뽑아낸 뒤의 pq size =  " << Room.size() << endl;
}

