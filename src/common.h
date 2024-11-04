#pragma once

#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

inline string print(string s) {
    stringstream ss;
    ss << s;
    string str = ss.str();
    if (str.length() > 80) {
        str = str.substr(0, 80) + "...";
    }
    return str;
}

inline string print(long long i) {
    stringstream ss;
    ss << i;
    string str = ss.str();
    if (str.length() > 80) {
        str = str.substr(0, 80) + "...";
    }
    return str;
}

inline string print(vector<int> vec) {
    stringstream ss;
    ss << "{";
    for (auto it = vec.begin(); it != vec.end(); it++) {
        ss << *it;
        if (it + 1 != vec.end()) {
            ss << ", ";
        }
    }
    ss << "}";
    string str = ss.str();
    if (str.length() > 80) {
        str = str.substr(0, 80) + "...";
    }
    return str;
}

inline string print(vector<string> vec) {
    stringstream ss;
    ss << "{";
    for (auto it = vec.begin(); it != vec.end(); it++) {
        ss << *it;
        if (it + 1 != vec.end()) {
            ss << ", ";
        }
    }
    ss << "}";
    string str = ss.str();
    if (str.length() > 80) {
        str = str.substr(0, 80) + "...";
    }
    return str;
}

inline string print(vector<vector<int>> grid) {
    stringstream ss;
    ss << "{";
    for (auto it = grid.begin(); it != grid.end(); it++) {
        ss << "{";
        for (auto it2 = it->begin(); it2 != it->end(); it2++) {
            ss << *it2;
            if (it2 + 1 != it->end()) {
                ss << ", ";
            }
        }
        ss << "}";
        if (it + 1 != grid.end()) {
            ss << ", ";
        }
    }
    ss << "}";
    string str = ss.str();
    if (str.length() > 80) {
        str = str.substr(0, 80) + "...";
    }
    return str;
}

inline string print(vector<pair<int, int>> v) {
    stringstream ss;
    ss << "{";
    for (auto p = v.begin(); p != v.end(); p++) {
        ss << "{" << p->first << ", " << p->second << "}";
        if (p + 1 != v.end()) {
            ss << ", ";
        }
    }
    string str = ss.str();
    if (str.length() > 80) {
        str = str.substr(0, 80) + "...";
    }
    return str;
}

template <typename Type> struct InputOutputType {
    string name;
    Type value;

    operator Type &() {
        return value;
    };

    Type operator=(Type val) {
        value = val;
        return val;
    }

    bool operator==(InputOutputType<Type> &other) {
        return value == other.value;
    }
};

template <typename...> class TestCase;

template <typename Input, typename Output> class TestCase<Input, Output> {
  public:
    // string inputName = InputName;
    InputOutputType<Input> input;
    InputOutputType<Output> expectedOutput;
    InputOutputType<Output> returnedOutput;

    inline void printFlattened() {
        cout << input.name << ": ";
        cout << print(input);
        cout << endl;
        cout << "Expected " << expectedOutput.name << ": ";
        cout << print(expectedOutput);
        cout << endl;
    }
};

template <typename Input1, typename Input2, typename Output> class TestCase<Input1, Input2, Output> {
  public:
    // string inputName = InputName;
    InputOutputType<Input1> input1;
    InputOutputType<Input2> input2;
    InputOutputType<Output> expectedOutput;
    InputOutputType<Output> returnedOutput;

    // inline void printFlattened();
    inline void printFlattened() {
        cout << input1.name << ": ";
        cout << print(input1);
        cout << endl;
        cout << input2.name << ": ";
        cout << print(input2);
        cout << endl;
        cout << "Expected " << expectedOutput.name << ": ";
        cout << print(expectedOutput);
        cout << endl;
    }
};

template <typename Input1, typename Input2, typename Input3, typename Output> class TestCase<Input1, Input2, Input3, Output> {
  public:
    // string inputName = InputName;
    InputOutputType<Input1> input1;
    InputOutputType<Input2> input2;
    InputOutputType<Input2> input3;
    InputOutputType<Output> expectedOutput;
    InputOutputType<Output> returnedOutput;

    // inline void printFlattened();
    inline void printFlattened() {
        cout << input1.name << ": ";
        cout << print(input1);
        cout << endl;
        cout << input2.name << ": ";
        cout << print(input2);
        cout << endl;
        cout << input3.name << ": ";
        cout << print(input3);
        cout << endl;
        cout << "Expected " << expectedOutput.name << ": ";
        cout << print(expectedOutput);
        cout << endl;
    }
};

class Main {
  public:
    template <typename TestCaseType, typename CallbackType> int runTests(vector<TestCaseType> &testCases, const CallbackType solutionCallback) {
        preRun();

        for (auto &test : testCases) {
            test.printFlattened();
            test.returnedOutput = solutionCallback(test);
            if (test.returnedOutput == test.expectedOutput) {
                cout << "\e[32;m  => Pass\n";
            } else {
                fails++;
                cout << "\e[31;m  => Failed : returned ";
                cout << print(test.returnedOutput);
                cout << "\n";
            }
            cout << "\e[0;m\n";
        }

        postRun();
        return fails;
    }

  protected:
    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    int fails;

    void preRun() {
        start = chrono::system_clock::now();
        fails = 0;
    }

    void postRun() {
        end = chrono::system_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - this->start);
        cout << "\nElapsed: " << elapsed.count() << "ms\n";
        cout << "Total fails: " << fails << endl;
    }
};
