#include <iostream>
#include <string>
#include "MyHashMap.h" // Your hashmap header here

using namespace std;
// Longest Substring Without Repeating Characters
int lengthOfLongestSubstring(const string& s) {
    HashMap<char, int> lastIndex;  // store last index of each char
    int start = 0, maxLen = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        int prevIndex = -1;
        if (lastIndex.get(s[i], prevIndex)) {
            // if char seen before, move start forward if needed
            if (prevIndex >= start)
                start = prevIndex + 1;
        }
        lastIndex.put(s[i], i);
        maxLen = max(maxLen, i - start + 1);
    }
    return maxLen;
}

int lengthOfLongestSubstring(const string& s) {
    HashMap<char, int> lastIndex;
    int start = 0, maxLen = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        int prevIndex = -1;
        if (lastIndex.get(s[i], prevIndex) && prevIndex >= start) {
            start = prevIndex + 1;
        }
        lastIndex.put(s[i], i);
        maxLen = max(maxLen, i - start + 1);
    }
    return maxLen;
}


pair<int, int> twoSum(const vector<int>& nums, int target) {
    HashMap<int, int> numIndex; // key: num, value: index

    for (int i = 0; i < (int)nums.size(); i++) {
        int complement = target - nums[i];
        int compIndex;
        if (numIndex.get(complement, compIndex)) {
            return {compIndex, i};
        }
        numIndex.put(nums[i], i);
    }
    return {-1, -1}; // no solution
}

#include <algorithm>
// Assumes HashMap header is included

vector<vector<string>> groupAnagrams(const vector<string>& strs) {
    HashMap<string, vector<string>> groups;
    for (auto& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        vector<string> group;
        groups.get(key, group);
        group.push_back(s);
        groups.put(key, group);
    }
      vector<vector<string>> result;
    auto all = groups.getTable(); // vector<pair<string, vector<string>>>
    for (const auto& entry : all) {
        result.push_back(entry.second);
    }
    return result;//You may convert this to vector<vector<string>> if needed
}

int longestConsecutive(const vector<int>& nums) {
    HashMap<int, bool> map;
    for (int num : nums) map.put(num, true);

    int longest = 0;
    for (int num : nums) {
        bool exists;
        if (map.get(num - 1, exists) && exists) continue;

        int length = 1, current = num;
        while (map.get(current + 1, exists) && exists) {
            current++; length++;
        }
        longest = max(longest, length);
    }
    return longest;
}

string minWindow(const string& s, const string& t) {
    HashMap<char, int> need, window;
    for (char c : t) need.increment(c);
    int required = need.getSize();

    int left = 0, right = 0, valid = 0, start = 0, minLen = INT_MAX;
    while (right < (int)s.size()) {
        char c = s[right++];
        int needCount = 0;
        if (need.get(c, needCount)) {
            window.increment(c);
            int wCount;
            window.get(c, wCount);
            if (wCount == needCount) valid++;
        }
        while (valid == required) {
            if (right - left < minLen) {
                minLen = right - left;
                start = left;
            }
            char d = s[left++];
            int nCount = 0;
            if (need.get(d, nCount)) {
                int wCount;
                window.get(d, wCount);
                if (wCount == nCount) valid--;
                window.put(d, wCount - 1);
            }
        }
    }
    return minLen == INT_MAX ? "" : s.substr(start, minLen);
}


#include <queue>

vector<int> topKFrequent(const vector<int>& nums, int k) {
    HashMap<int, int> freq;

    // Count frequencies using custom hashmap
    for (int num : nums) {
        freq.increment(num);
    }

    // Extract all entries (num, count)
    vector<pair<int, int>> freqEntries = freq.getTable();

    // Sort entries by descending frequency
    sort(freqEntries.begin(), freqEntries.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Collect top k keys
    vector<int> result;
    for (int i = 0; i < k && i < (int)freqEntries.size(); ++i) {
        result.push_back(freqEntries[i].first);
    }

    return result;
}
int main() {
    string s = "abcabcbb";
    cout << "Longest substring without repeating characters length: "
         << lengthOfLongestSubstring(s) << endl;
    return 0;
}
