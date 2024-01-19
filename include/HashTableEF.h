#include <vector>
#include <math.h>

#include "StringPair.h"

class HashTableTS {
private:

    int SIZE = 2;
    int USED = 0;
    int MAX_LOAD = 2;
    std::vector< std::vector<StringPair> > arr;

    int get_hash(std::string s){
        // djb2 hash function
        unsigned long hash = 5381;
        char c;
        for(int i=0; i<s.size(); i++){
            c=s[i++];
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }

        return hash % SIZE;
    }
    

    void expand_table() {
        SIZE *= 2;
        USED = 0;
        std::vector< std::vector<StringPair> > oldarr(arr);
        arr.clear();
        arr.resize(SIZE);

        for (int i = 0; i < (int)oldarr.size(); i++) {
            for (int j = 0; j < (int)oldarr[i].size(); j++) {
                StringPair val = oldarr[i][j];
                int key = get_hash(val.word);
                arr[key].push_back(val);
                ++USED;
            }
        }
    }

public:

    HashTableTS() {
        arr.resize(SIZE);
    }


    ~HashTableTS() { }
    
    // Inserts a StringPair using word as the mapping
    bool insert(StringPair val) {
        int key = get_hash(val.word);
        for (int i = 0; i < (int)arr[key].size(); i++) {
            if (arr[key][i] == val) {
                return false; // Value found
            }
        }

        arr[key].push_back(val);
        ++USED;

        // Check and handle rehashing here
        if (USED > MAX_LOAD * SIZE) {
            expand_table();
        }

        return true; // Value not found
    }
    

    bool remove(StringPair val) {
        int key = get_hash(val.word);
        for (int i = 0; i < (int)arr[key].size(); i++) {
            if (arr[key][i] == val) {
                arr[key][i] = arr[key].back();
                arr[key].pop_back();

                --USED;
                return true; // Value found
            }
        }

        return false; // Value not found
    }


    std::string get_translation(std::string word) {
        int key = get_hash(word);
        for (int i = 0; i < (int)arr[key].size(); i++) {
            if (arr[key][i].word == word)
                return arr[key][i].translation; // found
        }

        return ""; // not found
    }
    

}; // Hash Table for string pairs, seperate chaining using vectors with load <= 2