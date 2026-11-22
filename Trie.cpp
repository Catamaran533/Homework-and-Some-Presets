#include "Trie.h"
#include <algorithm>
#include <utility>

Trie* Trie::copy() const {
    Trie* ans = new Trie();
    ans->curr_endings = curr_endings;
    ans->subtree_endings = subtree_endings;
    for (auto [key, trie] : m) {
        ans->m[key] = trie->copy();
    }
    return ans;
}

int Trie::size() const {
    return subtree_endings;
}

Trie::~Trie() {
    for (auto& [a, b] : m) {
        delete b;
    }
}

Trie::Trie() {}

Trie::Trie(const Trie& other) {
    curr_endings = other.curr_endings;
    subtree_endings = other.subtree_endings;
    for (const auto& [key, child] : other.m) {
        m[key] = child->copy();
    }
}

Trie& Trie::operator=(const Trie& other) {
    if (this == &other) {
        return *this;
    }
    Trie t(other);
    std::swap(m, t.m);
    std::swap(curr_endings, t.curr_endings);
    std::swap(subtree_endings, t.subtree_endings);
    return *this;
}

void Trie::insert(std::string& s, int idx) {
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

int Trie::count(std::string& s, int idx) {
    if (idx == s.size()) {
        return curr_endings;
    }
    if (m.find(s[idx]) == m.end()) {
        return 0;
    }
    return m[s[idx]]->count(s, idx + 1);
}

void Trie::erase(std::string& s, int idx) {
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

void Trie::add_all_words_to_vector(std::string& word, std::vector<std::string>& words) const {
    for (int i = 0; i < curr_endings; i++) {
        words.push_back(word);
    }
    for (auto [a, b] : m) {
        word += a;
        b->add_all_words_to_vector(word, words);
        word.pop_back();
    }
}

void Trie::add_unique_words_to_vector(std::string& word, std::vector<std::string>& words) const {
    for (int i = 0; i < std::min(1, curr_endings); i++) {
        words.push_back(word);
    }
    for (auto [a, b] : m) {
        word += a;
        b->add_unique_words_to_vector(word, words);
        word.pop_back();
    }
}

void Trie::insert(std::string s) {
    insert(s, 0);
}

int Trie::count(std::string s) {
    return count(s, 0);
}

bool Trie::contains(std::string s) {
    return count(s, 0) != 0;
}

bool Trie::erase(std::string s) {
    if (contains(s)) {
        erase(s, 0);
        return true;
    }
    return false;
}

bool Trie::unique_insert(std::string s) {
    if (count(s, 0) == 0) {
        insert(s, 0);
        return true;
    }
    return false;
}

std::vector<std::string> Trie::get_all_words() const {
    std::string word;
    std::vector<std::string> words;
    add_all_words_to_vector(word, words);
    return words;
}

std::vector<std::string> Trie::get_unique_words() const {
    std::string word;
    std::vector<std::string> words;
    add_unique_words_to_vector(word, words);
    return words;
}

std::ostream& operator<<(std::ostream& os, const Trie& t) {
    std::vector<std::string> words = t.get_all_words();
    if (words.size() == 0) {
        return os;
    }
    for (int i = 0; i < words.size() - 1; i++) {
        os << words[i] << ' ';
    }
    os << words.back();
    return os;
}