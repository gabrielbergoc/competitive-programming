/*
Created by Gabriel Bergoc on 17/09/2021.
*/
#include <iostream>
#include <string>
#include <fstream>

void printAnagrams(std::string str, std::string aux, bool* chosen);

int main() {
    
    std::string input, aux;
    std::cin >> input;
    
    bool* chosen = (bool*) calloc(input.size(), sizeof(bool));
    for (int i = 0; i < input.size(); i++) {
        chosen[i] = false;
    }
    
    printAnagrams(input, aux, chosen);
    
    return 0;
}

void printAnagrams(std::string str, std::string aux, bool* chosen) {
    
    // recursion base; print if all letters are chosen
    if (aux.size() == str.size()) {
        std::ofstream file;
        file.open("anagrams.txt", std::ios_base::app);
        file << aux << std::endl;
        file.close();
    } else {
        
        // loop through string to choose different letters
        for (int i = 0; i < str.size(); i++) {
            
            // if letter was already chosen, skip
            if (chosen[i]) continue;
            
            // choose letter
            aux.push_back(str[i]);
            chosen[i] = true;
            
            // call recursion for next position
            printAnagrams(str, aux, chosen);
            
            // pop back letter to fill position with another letter
            aux.pop_back();
            chosen[i] = false;
            
        }
    }
}