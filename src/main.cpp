#include "HashTableEF.h"
#include <iostream>
#include <fstream>

enum WordToTranslation {
  ENGLISHTOFRENCH, // 0 = false
  FRENCHTOENGLISH // 1 = true
};

HashTableTS load_dictionary(int mode) {
  HashTableTS mapped_dictionary;

  std::ifstream dictionary("dictionary.txt");
  std::string pair;
  while (getline(dictionary, pair)) {
    std::string s1 = pair.substr(0, pair.find(','));
    std::string s2 = pair.substr(pair.find(',') + 1, pair.length());

    StringPair new_pair;
    if (mode == ENGLISHTOFRENCH) {
      new_pair.word = s1;
      new_pair.translation = s2;
    } else {
      new_pair.word = s2;
      new_pair.translation = s1;
    }

    mapped_dictionary.insert(new_pair);
  }

  return mapped_dictionary;
}

int main(int argc, char *argv[])
{
  std::cout << "Welcome to the Enligsh-French Translator" << std::endl;
  
  std::string input = "MM";
  while (input != "quit") {
    std::cout << "=================== Main Menu ===================" << std::endl;
    std::cout << "To translate from English to French, type 'EtoF'" << std::endl;
    std::cout << "To translate from French to English, type 'FtoE'" << std::endl;
    std::cout << "To practice your translations, type 'practice'" << std::endl;
    std::cout << "To quit, type 'quit'" << std::endl;
    std::cout << "You can return to the main menu by typing 'MM'" << std::endl;

    std::cin >> input;

    if (input == "EtoF" || input == "FtoE") {
      int mode;
      if (input == "EtoF")
        mode = ENGLISHTOFRENCH;
      else
        mode = FRENCHTOENGLISH;

      HashTableTS dictionary = load_dictionary(mode);

      while (input != "MM") {
        std::cout << "Enter a word to translate: " << std::endl;

        std::cin >> input;
        std::string translation = dictionary.get_translation(input);
        if (translation == "MM")
          std::cout << "Returning to main menu..." << std::endl;
        else if (translation.empty())
          std::cout << "Sorry, I don't have the translation for that word" << std::endl;
        else
          std::cout << "The translation for '" << input << "' is '" << translation << "'" << std::endl;
      }

    }
    else if (input == "practice") {

    }
    else if (input == "MM") {
      continue;
    }
    else if (input != "quit") {
      std::cout << "Invalid selection" << std::endl;
    }
  }

  std::cout << "Quitting..." << std::endl;

  return 0;
}