
#include <bits/stdc++.h>
using namespace std;

// 1. struct 비교 함수 (기본 public)
struct StructComp {
    bool operator()(const int& a, const int& b) const {
        return a > b; // 최소 힙
    }
};

// 2. class 비교 함수 (기본 private)
class ClassComp {
public:
    bool operator()(const int& a, const int& b) const {
        return a < b; // 최대 힙
    }
};

// 3. struct 내부에서 비교하기
struct structPerson {
    int age;
    int height;

    structPerson(int a, int h) : age(a), height(h) {}

    bool operator<(const structPerson& other) const {
        return age < other.age; 
    }
};

// 4. class 내부에서 비교하기
class classPerson {
public:
    int age;
    int height;

    classPerson(int a, int h) : age(a), height(h) {}

    bool operator<(const classPerson& other) const {
        return age < other.age;
    }
};

int main() {
    priority_queue<int, vector<int>, StructComp> PQ1;
    priority_queue<int, vector<int>, ClassComp> PQ2;

    priority_queue<structPerson> PQ3;
    priority_queue<classPerson> PQ4;

    // pass...
}
