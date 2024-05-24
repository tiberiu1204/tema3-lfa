#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::ifstream in("input");
std::unordered_map<
    std::string,
    std::unordered_map<
        std::string,
        std::unordered_map<char,
                           std::pair<std::string, std::vector<std::string>>>>>
    pda; // in order: string(current_state), string(stack_symbol),
         // char(input_char), pair<string(next_state),
         // vector(replacement_symbols)>
std::stack<std::string> s;

int main() {
  int n;
  in >> n;
  for (int i = 0; i < n; i++) {
    std::string input;
    in >> std::ws;
    std::getline(in, input);
    std::stringstream ss(input);
    std::string state, stack_symbol, next_state;
    char input_char;
    ss >> state >> stack_symbol >> input_char >> next_state;
    std::string replacement_symbol;
    std::vector<std::string> replacement_symbols;
    while (ss >> replacement_symbol) {
      replacement_symbols.push_back(replacement_symbol);
    }
    pda[state][stack_symbol][input_char] = {next_state, replacement_symbols};
  }
  int m;
  in >> m;
  std::unordered_set<std::string> final_states;
  for (int i = 0; i < m; i++) {
    std::string fs;
    in >> fs;
    final_states.insert(fs);
  }
  std::string initial_state, initial_symbol;
  in >> initial_state >> initial_symbol;
  s.push(initial_symbol);
  std::string word;
  in >> word;
  if (word.empty()) {
    if (final_states.find(initial_state) != final_states.end()) {
      std::cout << "Cuvant acceptat!\n";
    } else {
      std::cout << "Cuvant respins!\n";
    }
    return 0;
  }
  size_t index = 0;
  std::string current_state = initial_state;
  while (!s.empty()) {
    std::string stack_sym = s.top();
    s.pop();
    char input_char = index < word.size() ? word[index] : '-';
    std::pair<std::string, std::vector<std::string>> &trans =
        pda[current_state][stack_sym][input_char];
    if (trans.first.empty()) {
      break;
    }
    for (int i = trans.second.size() - 1; i >= 0; i--) {
      s.push(trans.second[i]);
    }
    current_state = trans.first;
    index++;
  }
  if (final_states.find(current_state) != final_states.end()) {
    std::cout << "Cuvant acceptat!\n";
  } else {
    std::cout << "Cuvant respins!\n";
  }
}
