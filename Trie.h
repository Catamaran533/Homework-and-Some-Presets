#pragma once
#include <map>
#include <ostream>
#include <string>
#include <vector>

class Trie {
private:
    std::map<char, Trie*> m;
    int curr_endings = 0;
    int subtree_endings = 0;

    Trie* copy() const;

public:
    int size() const;
    ~Trie();
    Trie();
    Trie(const Trie& other);
    Trie& operator=(const Trie& other);

private:
    void insert(std::string& s, int idx);
    int count(std::string& s, int idx);
    void erase(std::string& s, int idx);
    void add_all_words_to_vector(std::string& word, std::vector<std::string>& words) const;
    void add_unique_words_to_vector(std::string& word, std::vector<std::string>& words) const;

public:
    void insert(std::string s);
    int count(std::string s);
    bool contains(std::string s);
    bool erase(std::string s);
    bool unique_insert(std::string s);
    std::vector<std::string> get_all_words() const;
    std::vector<std::string> get_unique_words() const;
};

std::ostream& operator<<(std::ostream& os, const Trie& t);