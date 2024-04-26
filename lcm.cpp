#include <bits/stdc++.h>

using namespace std;

int findLcm(int first, int second) {
  int answer = 1;
  int a = first, b = second;
  for (int i = 2; i <= 11; i++) {
    if (a % i == 0 && b % i == 0) {
      a /= i;
      b /= i;

      answer *= i;
    }
  }

  return answer * a * b;
}

int getTarget(vector<int> basis, vector<int> powers) {
  int answer = 1;
  for (auto element : basis) {
    answer *= pow(element, powers[element]);
  }

  return answer;
}

int findAll(int a, int b, int aPow, int bPow, int nowA, int nowB, int target) {
  if (nowA > aPow || nowB > bPow) return 0;
  int result = pow(a, nowA) + pow(b, nowB);
  if (((int)(pow(a, nowA) * pow(b, nowB)) % a == 0 ||
       (int)(pow(a, nowA) * pow(b, nowB)) % b == 0) &&
      pow(a, nowA) * pow(b, nowB) != target)
    result = 0;
  return result + findAll(a, b, aPow, bPow, nowA + 1, nowB, target) +
         findAll(a, b, aPow, bPow, nowA, nowB + 1, target);
}

int findForSix(vector<int> basis, vector<int> powers, int target) {
  int result = 0;
  for (auto element : basis) {
    if (element == target) break;
    for (int i = 1; i <= powers[element]; i++) {
      result += pow(element, i) + target;
    }
  }

  return result;
}

int findAnotherPow(vector<int> basis, vector<int> powers, int target, int a) {
  int answer = 0;
  for (auto b : basis) {
    for (int i = 1; i <= powers[b]; i++) {
      int result = findLcm(a, pow(b, i));

      if (result == target) answer += a + pow(b, i);
    }
  }

  return answer;
}

int findMixSix(vector<int> basis, vector<int> powers, int target) {
  static vector<bool> history(20000, false);
  static int answer = 0;

  if (basis.size() < 2) return 0;

  int result = 1;

  for (int i = 0; i < basis.size(); i++) {
    result *= basis[i];
  }

  // init condition
  if (result == target) {
    history.clear();
    answer = 0;
  } else if (history[result] == false) {
    history[result] = true;

    answer += findAnotherPow(basis, powers, target, result);

    answer += result + target;
  }

  int skip = 0;

  while (skip != basis.size()) {
    vector<int> sub;
    for (int i = 0; i < basis.size(); i++) {
      if (i == skip) continue;

      sub.push_back(basis[i]);
    }
    findMixSix(sub, powers, target);

    skip++;
  }

  return answer;
}

void calculate(int &answer, vector<int> basis, vector<int> powers, int target) {
  for (int i = 0; i < basis.size() - 1; i++) {
    for (int j = i + 1; j < basis.size(); j++) {
      answer += findAll(basis[i], basis[j], powers[basis[i]], powers[basis[j]],
                        1, 1, target);
    }
  }

  answer += findForSix(basis, powers, target);

  answer += findMixSix(basis, powers, target);
}

int main() {
  short int cases;
  cin >> cases;
  const short totalCases = cases;
  while (cases--) {
    int answer = 0;

    vector<int> powers(10000, 0);
    vector<int> basis;

    short int c;
    cin >> c;

    for (int i = 0; i < c; i++) {
      int temp;
      int pow;
      cin >> temp;
      cin >> pow;

      basis.push_back(temp);
      powers[temp] = pow;
    }

    // start process

    int target = getTarget(basis, powers);
    // front and end
    answer += 1 + target + target + target;

    calculate(answer, basis, powers, target);

    printf("Case %d: %d\n", totalCases - cases, answer);
  }
}