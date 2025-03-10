#include "common.h"

class Solution {
  public:
    long long countOfSubstrings(string word, int k) {
        return count(word, k) - count(word, k + 1);
    }
    long long count(string word, int k) {
        array<bool, 26> isVowel{
            true, false, false, false, true, false, false, false, true, false, false, false, false, false, true, false, false, false, false, false, true, false, false, false, false, false,
        };
        int length = word.length();
        int consonants = 0;
        long long substringsCount = 0;
        unordered_map<char, int> vowels;
        int left = 0, right = 0;
        while (right < length) {
            char nextLetter = word[right];

            if (isVowel[nextLetter - 'a']) {
                vowels[nextLetter]++;
            } else {
                consonants++;
            }

            while (allVowels(vowels) && consonants >= k) {
                substringsCount += length - right;
                char prevLetter = word[left];
                if (isVowel[prevLetter - 'a']) {
                    vowels[prevLetter]--;
                } else {
                    consonants--;
                }
                left++;
            }

            right++;
        }

        return substringsCount;
    }
    bool allVowels(unordered_map<char, int> &vowels) {
        return vowels['a'] > 0 && vowels['e'] > 0 && vowels['i'] > 0 && vowels['o'] > 0 && vowels['u'] > 0;
    }
};

int main() {
    TestSuite<long long, string, int> testSuite("Substrings count", "word", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            0,
            "aeioqq",
            1,
        },
        {
            1,
            "aeiou",
            0,
        },
        {
            3,
            "ieaouqqieaouqq",
            1,
        },
        // Submission test cases
        {
            1,
            "aeouih",
            0,
        },
        {
            4,
            "aoaiuefi",
            1,
        },
        {
            6,
            "eeuiaoiucu",
            0,
        },
        {
            1,
            "buoeia",
            0,
        },
        // My test cases
        {
            2,
            "aeouihaeiou",
            0,
        },
    });

    Main main;
    main.runTests(&Solution::countOfSubstrings, testSuite);
}
