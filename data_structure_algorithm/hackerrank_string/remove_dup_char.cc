/*
https://www.hackerrank.com/challenges/reduced-string/problem

*/
#include "/Users/SteveAndrewWong/stdc++.h"
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl;

using namespace std;

// recursive call !!!
bool process(string &s) {
  for (int i = 0; i + 1 < (int)s.size(); ++i) {
    if (s[i] == s[i + 1]) {
      // s.erase(s.begin() + i); // pos
      // s.erase(s.begin() + i);
      s.erase(s.begin() + i, s.begin() + i + 2); // start pos, end pos      
      return true;
    }
  }
  return false;
}

void stack(string s){
  string v; // same as stack
  for (int i = 0; i < (int)s.size(); ++i) {
      if (!v.empty() && v.back() == s[i]) {
          v.pop_back();
      } else {
          v += (s[i]);
      }
  }
}

int main() {
  string s;
  // cin >> s;
  getline(cin, s);
  string dup = s;
  while (process(dup));

  if (s.empty()) s = "Empty String";
  cout << s << endl;
  return 0;
}