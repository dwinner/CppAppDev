#include <iostream>
#include <iterator>
#include <map>
#include <algorithm>

using namespace std;

string filter_ws(const string &s)
{
    const char *ws {" \r\n\t"};
    const auto a (s.find_first_not_of(ws));
    const auto b (s.find_last_not_of(ws));
    if (a == string::npos) {
        return {};
    }
    return s.substr(a, b);
}

multimap<size_t, string> get_sentence_stats(const string &content)
{

    multimap<size_t, string> ret;

    const auto end_it (end(content));
    auto it1 (begin(content));         // start at beginning of string
    auto it2 (find(it1, end_it, '.')); // Start at first '.' dot character

    while (it1 != end_it && distance(it1, it2) > 0) {

        string s {filter_ws({it1, it2})};

        if (s.length() > 0) {
            const auto words (count(begin(s), end(s), ' ') + 1);
            ret.emplace(make_pair(words, move(s)));
        }

        it1 = next(it2, 1);
        it2 = find(it1, end_it, '.');
    }

    return ret;
}

int main()
{
    cin.unsetf(ios::skipws);
    string content {istream_iterator<char>{cin}, {}};

    for (const auto & [word_count, sentence]
            : get_sentence_stats(content)) {
        cout << word_count << " words: " << sentence << ".\n";
    }
}

