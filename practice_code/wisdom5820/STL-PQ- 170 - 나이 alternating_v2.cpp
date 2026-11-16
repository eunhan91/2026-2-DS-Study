
/*
- 170번 코드 문제점 
    : 전역 변수 G에 따라 비교 기준이 바뀌지만, 기존 힙은 새로운 기준으로 재구성되지 않아 힙 구조와 비교 기준이 불일치할 수 있음
- 원래 코드 의도 
    : 남은 원소 개수가 짝수일 때 최솟값, 홀수일 때 최댓값을 꺼내는 것
- 해결방법 
    : multiset을 사용하면 정렬된 상태를 유지하므로 begin()으로 최솟값, prev(end())로 최댓값을 꺼낼 수 있음
*/

/* == set vs multiset == 
차이 : 중복 원소를 허용하는지 여부

- set : 중복 원소 허용 X
- multiset : 중복 원소 허용 O

priority_queue는 중복 원소를 허용하므로, 이 코드에서는 원래 동작을 유지하려면 multiset이 더 적합하다
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int data[] = {
        45, 23, 11, 6, 27, 71, 9,
        30, 62, 99, 63, 34, 90, 32
    };

    // multiset은 원소들을 정렬된 상태로 관리하므로
    // 최솟값과 최댓값을 모두 효율적으로 선택할 수 있음
    multiset<int> Room(data, data+12);

    int G = Room.size();
    
    while(!Room.empty()) {
        if (G % 2 == 0) {
            auto it = Room.begin();
            cout << *it << "\n";
            Room.erase(it);
        }
        else {
            auto it = prev(Room.end());
            cout << *it << "\n";
            Room.erase(it);
        }

        G--;
    }

}