#include <cassert>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<string> removeSubfolders(vector<string> &folders) {
        sort(folders.begin(), folders.end());
        vector<size_t> indicesToRemove;
        for (size_t root = 0; root < folders.size(); root++) {
            if (find(indicesToRemove.begin(), indicesToRemove.end(), root) != indicesToRemove.end()) {
                continue;
            }
            for (size_t tested = root + 1; tested < folders.size(); tested++) {
                if (find(indicesToRemove.begin(), indicesToRemove.end(), root) != indicesToRemove.end()) {
                    continue;
                }
                if (folders[tested].find(folders[root] + "/") == 0) {
                    indicesToRemove.push_back(tested);
                }
            }
        }

        auto it = indicesToRemove.rbegin();
        while (it != indicesToRemove.rend()) {
            folders.erase(folders.begin() + *it);
            it++;
        }
        return folders;
    }
};

int main() {
    vector<string> input = {"/a", "/a/b", "/a/b/c", "/b", "/b/c"};
    vector<string> expected = {"/a", "/b"};

    auto start = chrono::system_clock::now();

    Solution solution;
    vector<string> result = solution.removeSubfolders(input);
    assert(result.size() == expected.size());
    for (int i = 0; i < result.size(); i++) {
        assert(result[i] == expected[i]);
    }

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << elapsed.count() << '\n';

    return 0;
}
