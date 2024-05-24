#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>

std::ifstream in("input");

std::unordered_map<char, std::unordered_set<char>>
    unit_prod_map; // key = terminal, value = set of non terminals
std::unordered_map<char, std::set<std::pair<char, char>>>
    prod_map; // key = non terminal, value = pair of non terminals
std::unordered_set<char> non_terminals;
std::unordered_set<char> terminals;

int main() {
  int n;
  in >> n;
  char start_sym;
  for (int i = 0; i < n; i++) {
    int type;
    in >> type;
    char s;
    in >> s;
    if (i == 0)
      start_sym = s;
    non_terminals.insert(s);
    if (type == 1) {
      char terminal;
      in >> terminal;
      terminals.insert(terminal);
      unit_prod_map[terminal].insert(s);
    } else {
      char s1, s2;
      in >> s1 >> s2;
      prod_map[s].insert({s1, s2});
    }
  }
  std::string w;
  in >> w;
  if (w.empty()) {
    if (unit_prod_map['-'].find(start_sym) != unit_prod_map[start_sym].end()) {
      std::cout << "Cuvantul apartine limbajului generat de gramatica data!\n";
    } else {
      std::cout
          << "Cuvantul nu apartine limbajului generat de gramatica data! \n";
    }
    return 0;
  }
  n = w.size();
  std::unordered_set<char> dp[n + 1][n + 1];
  for (int i = 1; i <= n; i++) {
    char c = w[i - 1];
    dp[i][i] = unit_prod_map[c];
  }
  for (int l = 2; l <= n; l++) {
    for (int i = 1; i <= n - l + 1; i++) {
      int j = i + l - 1;
      for (int k = i; k <= j - 1; k++) {
        for (const auto &prod : prod_map) {
          char left_hand_side = prod.first;
          for (const auto &right_hand_side : prod.second) {
            if (dp[i][k].find(right_hand_side.first) != dp[i][k].end() &&
                dp[k + 1][j].find(right_hand_side.second) !=
                    dp[k + 1][j].end()) {
              dp[i][j].insert(left_hand_side);
            }
          }
        }
      }
    }
  }
  if (dp[1][n].find(start_sym) != dp[1][n].end()) {
    std::cout << "Cuvantul apartine limbajului generat de gramatica data!\n";
  } else {
    std::cout
        << "Cuvantul nu apartine limbajului generat de gramatica data! \n";
  }
}
