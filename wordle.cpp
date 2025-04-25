#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helper(std::string& in, std::string& floating, std::set<std::string>& output, const std::set<std::string>& dict, int index);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
  std::set<std::string> output;
  std::string tempIn = in;
  std::string tempFloat = floating;
  helper(tempIn, tempFloat, output, dict, 0);
  
  return output;
}


void helper(std::string& in, std::string& floating, std::set<std::string>& output, const std::set<std::string>& dict, int index){
  if(index == in.size()){
    if(floating.empty() && (dict.find(in) != dict.end())){ // made a real word and no remaining floating letters
      output.insert(in);
    }
    return;
  }

  if(in[index] != '-'){ // space already filled
    helper(in, floating, output, dict, index+1);
    return;
  }

  for(char c = 'a'; c <= 'z'; ++c) {
    char original = in[index];
    in[index] = c;
    size_t pos = floating.find(c);

    if(pos != std::string::npos) {
      std::string newFloating = floating;
      newFloating.erase(pos, 1);
      helper(in, newFloating, output, dict, index + 1);
    } else {
      // Count how many dashes are left
      int remainingDashes = 0;
      for(int i = index + 1; i < static_cast<int>(in.size()); i++) {
        if(in[i] == '-') remainingDashes++;
      }

      if(static_cast<int>(floating.size()) <= remainingDashes) {
        helper(in, floating, output, dict, index + 1);
      }
    }
    
    in[index] = original;
  }
}