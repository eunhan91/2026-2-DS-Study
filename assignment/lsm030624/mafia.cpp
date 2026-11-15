/*
1. 사용한 AI (model 까지) :
    Chat GPT 6 Astra

2. 과제에서 활용한 부분 :
    함수 구현에 있어서 활용을 하였습니다.

3. 어떤 도움이 필요했는지 :
    보스를 찾는 것과 mafia 아래의 총 부하 수, boss 까지의 거리를 구하는 함수를 구분하였고, 위 값들을 바탕으로 sort를 하여 따로 vector<string> order에 저장하고자 하였습니다.

4. AI 제시 코드에서 추가, 개선한 부분 :
    기존에는 vector<string> order와 map<string, vector<string>> mafia_relation만 활용하였지만 map<string, string> person_boss를 통해서 int distance_to_boss를 구하는 것이 더 낫다는 제시를 받았습니다.
    void output()의 sort() 함수의 구현에 있어서 아직 람다 함수 구현이 어려워서 도움을 받았습니다.
*/

#include <bits/stdc++.h>
using namespace std;

struct mafia{
    vector<mafia*> people;
    string name = "";
};

void input(int& N, vector<string>& order, map<string, vector<string>>& mafia_relation, map<string, string>& person_boss){
    cin >> N;
    for (int i = 1; i < N; i++){
        string person, boss;
        cin >> person >> boss;
        mafia_relation[boss].push_back(person);
        person_boss[person] = boss;
        order.push_back(person);
    }
} // end of input()

string find_boss(const map<string, vector<string>>& mafia_relation) {
    set<string> subordinates;

    for (const auto& [boss, people] : mafia_relation) {
        for (const string& person : people) {
            subordinates.insert(person);
        }
    }
    for (const auto& [boss, people] : mafia_relation) {
        if (subordinates.count(boss) == 0) {
            return boss;
        }
    }
    exit(0); // 보스를 찾지 못한 경우
} // end of find_boss()

// person 아래에 있는 모든 부하 수 (자기 자신 제외)
int number_of_people(const string& person, const map<string, vector<string>>& mafia_relation) {
    auto it = mafia_relation.find(person);

    // 직속 부하가 없는 경우
    if (it == mafia_relation.end()) {
        return 0;
    }

    int count = 0;
    for (const string& subordinate : it->second) {
        count += 1 + number_of_people(subordinate, mafia_relation);
    }
    return count;
} // end of number_of_people()

// person에서 최상위 보스까지의 거리
int distance_to_boss(const string& person, const map<string, string>& person_boss) {
    int distance = 0;
    string current = person;

    auto it = person_boss.find(current);
    while (it != person_boss.end()) {
        current = it->second;
        ++distance;
        it = person_boss.find(current);
    }
    return distance;
} // end of distance_to_boss()

void output(const string& boss, vector<string>& order, const map<string, vector<string>>& mafia_relation, const map<string, string>& person_boss){

    cout << boss << '\n';

    sort(order.begin(), order.end(),[&](const string& a, const string& b) {
         int countA = number_of_people(a, mafia_relation);
         int countB = number_of_people(b, mafia_relation);

         if (countA != countB) {
             return countA > countB; // 부하가 많을수록 먼저
         }

         int distanceA = distance_to_boss(a, person_boss);
         int distanceB = distance_to_boss(b, person_boss);

         if (distanceA != distanceB) {
             return distanceA < distanceB; // 보스와 가까울수록 먼저
         }
         return a < b; // 같으면 이름 사전순
     });

    for (const string& person : order) {
        cout << person << '\n';
    }
} // end of output()

int main() {
    int N;
    vector<string> order;
    map<string, vector<string>> mafia_relation; // 보스와 직속 부하를 저장
    map<string, string> person_boss; // 부하 -> 직속 보스

    input(N, order, mafia_relation, person_boss);

    string boss = find_boss(mafia_relation);

    output(boss, order, mafia_relation, person_boss);
} // end of main()
