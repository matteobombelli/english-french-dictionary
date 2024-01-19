#include <string>

class StringPair {
    public:
    std::string word;
    std::string translation;

    // Default Constructor
    StringPair() { }

    StringPair(std::string w, std::string t) {
        word = w;
        translation = t;
    }

    bool operator == (const StringPair &rhs)
    {
        if (word == rhs.word && translation == rhs.translation)
            return true;
        return false;
    }
}; // Pair of word and translation strings