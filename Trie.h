#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Trie {
private:
    map<char, Trie*> m;
    int curr_endings = 0;
    int subtree_endings = 0;
    Trie* copy() const {
        Trie* ans = new Trie();
        ans->curr_endings = curr_endings;
        ans->subtree_endings = subtree_endings;
        for (auto [key, trie] : m) {
            ans->m[key] = trie->copy();
        }
        return ans;
    }
public:
    int size() const {
        return subtree_endings;
    }
    ~Trie() {
        for (auto& [a, b] : m) {
            delete b;
        }
    }
    Trie() {};
    Trie(const Trie& other) {
        curr_endings = other.curr_endings;
        subtree_endings = other.subtree_endings;
        for (const auto& [key, child] : other.m) {
            m[key] = child->copy();
        }
    }
    Trie& operator = (const Trie& other) {
        if (this == &other) {
            return *this;
        }
        Trie t(other);
        swap(m, t.m);
        swap(curr_endings, t.curr_endings);
        swap(subtree_endings, t.subtree_endings);
        return *this;
    }
private:
    void insert(string& s, int idx) {
        subtree_endings += 1;
        if (idx == s.size()) {
            curr_endings += 1;
            return;
        }
        if (m.find(s[idx]) == m.end()) {
            m[s[idx]] = new Trie();
        }
        m[s[idx]]->insert(s, idx + 1);
    }
    int count(string& s, int idx) {
        if (idx == s.size()) {
            return curr_endings;
        }
        if (m.find(s[idx]) == m.end()) {
            return 0;
        }
        return m[s[idx]]->count(s, idx + 1);
    }

    void erase(string &s, int idx) {
        subtree_endings -= 1;
        if (idx == s.size()) {
            curr_endings -= 1;
            return;
        }
        m[s[idx]]->erase(s, idx + 1);
        if (m[s[idx]]->size() == 0) {
            delete m[s[idx]];
            m.erase(s[idx]);
        }
    }

    void add_all_words_to_vector(string& word, vector<string>& words) const {
        for (int i = 0; i < curr_endings; i++) {
            words.push_back(word);
        }
        for (auto [a, b] : m) {
            word += a;
            b->add_all_words_to_vector(word, words);
            word.pop_back();
        }
    }

    void add_unique_words_to_vector(string& word, vector<string>& words) const {
        for (int i = 0; i < min(1, curr_endings); i++) {
            words.push_back(word);
        }
        for (auto [a, b] : m) {
            word += a;
            b->add_unique_words_to_vector(word, words);
            word.pop_back();
        }
    }

public:
    void insert(string s) {
        insert(s, 0);
    }
    int count(string s) {
        return count(s, 0);
    }
    bool contains(string s) {
        return count(s, 0) != 0;           ;
    }
    bool erase(string s) {
        if (contains(s)) {
            erase(s, 0);
            return true;
        }
        return false;
    }

    bool unique_insert(string s) {
        if (count(s, 0) == 0) {
            insert(s, 0);
            return true;
        }
        return false;
    }

    vector<string> get_all_words() const {
        string word;
        vector<string> words;
        add_all_words_to_vector(word, words);
        return words;
    }

    vector<string> get_unique_words() const {
        string word;
        vector<string> words;
        add_unique_words_to_vector(word, words);
        return words;
    }
};

ostream& operator << (ostream& os, const Trie& t) {
    vector<string> words = t.get_all_words();
    if (words.size() == 0) {
        return os;
    }
    for (int i = 0; i < words.size() - 1; i++) {
        os << words[i] << ' ';
    }
    os << words.back();
    return os;
}