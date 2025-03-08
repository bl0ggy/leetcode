#pragma once

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "listnode.h"
#include "treenode.h"

using namespace std;

const string Reset = "\e[0m";
const string Error = "\e[31m";
const string Success = "\e[32m";
const string Warning = "\e[33m";

// Lets us check if a template type Test is a container of type Ref
// e.g. with template<typename Value> ...
//      is_specialization<Value, vector>::value will be true if Value is an std::vector of any type
template <typename Test, template <typename...> class Ref> struct is_specialization : std::false_type {};
template <template <typename...> class Ref, typename... Args> struct is_specialization<Ref<Args...>, Ref> : std::true_type {};

// ++++++++++++++++++++++++++++++++ //
// Definition of toString functions //
// ++++++++++++++++++++++++++++++++ //
// Basic types
inline string toString(bool b) {
    return b ? "true" : "false";
}
inline string toString(unsigned long long i) {
    return to_string(i);
}
inline string toString(long long i) {
    return to_string(i);
}
inline string toString(unsigned long i) {
    return to_string(i);
}
inline string toString(long i) {
    return to_string(i);
}
inline string toString(unsigned int i) {
    return to_string(i);
}
inline string toString(int i) {
    return to_string(i);
}
inline string toString(double i) {
    return to_string(i);
}
inline string toString(char c) {
    return string{c};
}
inline string toString(string s) {
    return "\"" + s + "\"";
}
// Forward declarations
template <typename First, typename Second> inline string toString(pair<First, Second> obj);
template <typename Value, size_t Size> inline string toString(array<Value, Size> obj, int level = 0);
template <typename Value> inline string toString(vector<Value> obj, int level = 0);
template <typename Value> inline string toString(list<Value> obj, int level = 0);
template <typename Value> inline string toString(deque<Value> obj, int level = 0);
template <typename Value, typename Compare> inline string toString(set<Value, Compare> obj);
template <typename Value> inline string toString(unordered_set<Value> obj);
template <typename Key, typename Value> inline string toString(map<Key, Value> obj);
template <typename Key, typename Value> inline string toString(unordered_map<Key, Value> obj);
template <typename Value> inline string toString(stack<Value> obj);
// Implementations
template <typename First, typename Second> inline string toString(pair<First, Second> obj) {
    stringstream ss;
    ss << "[" << toString(obj.first) << "," << toString(obj.second) << "]";
    return ss.str();
}
template <typename Value, size_t Size> inline string toString(array<Value, Size> obj, int level) {
    stringstream ss;
    ss << "[";
    for (auto it = obj.begin(); it != obj.end(); it++) {
        if (it != obj.begin()) {
            ss << "," << (level == 0 ? "\n" : " ");
        }
        if constexpr (is_specialization<Value, vector>::value) {
            ss << toString(*it, level + 1);
        } else {
            ss << toString(*it);
        }
    }
    ss << "]";
    return ss.str();
}
template <typename Value> inline string toString(vector<Value> obj, int level) {
    stringstream ss;
    ss << "[";
    for (auto it = obj.begin(); it != obj.end(); it++) {
        if (it != obj.begin()) {
            ss << "," << (level == 0 ? "\n" : " ");
        }
        if constexpr (is_specialization<Value, vector>::value) {
            ss << toString(*it, level + 1);
        } else {
            ss << toString(*it);
        }
    }
    ss << "]";
    return ss.str();
}
template <typename Value> inline string toString(list<Value> obj, int level) {
    stringstream ss;
    ss << "[";
    for (auto it = obj.begin(); it != obj.end(); it++) {
        if (it != obj.begin()) {
            ss << "," << (level == 0 ? "\n" : " ");
        }
        if constexpr (is_specialization<Value, vector>::value) {
            ss << toString(*it, level + 1);
        } else {
            ss << toString(*it);
        }
    }
    ss << "]";
    return ss.str();
}
template <typename Value> inline string toString(deque<Value> obj, int level) {
    stringstream ss;
    ss << "[";
    for (auto it = obj.begin(); it != obj.end(); it++) {
        if (it != obj.begin()) {
            ss << ", ";
        }
        if constexpr (is_specialization<Value, vector>::value) {
            ss << toString(*it, level + 1);
        } else {
            ss << toString(*it);
        }
    }
    ss << "]";
    return ss.str();
}
template <typename Value, typename Compare> inline string toString(set<Value, Compare> obj) {
    stringstream ss;
    ss << "[";
    for (auto it = obj.begin(); it != obj.end(); it++) {
        if (it != obj.begin()) {
            ss << ", ";
        }
        ss << toString(*it);
    }
    ss << "]";
    return ss.str();
}
template <typename Value> inline string toString(unordered_set<Value> obj) {
    stringstream ss;
    ss << "[";
    for (auto it = obj.begin(); it != obj.end(); it++) {
        if (it != obj.begin()) {
            ss << ", ";
        }
        ss << toString(*it);
    }
    ss << "]";
    return ss.str();
}
template <typename Key, typename Value> inline string toString(map<Key, Value> obj) {
    stringstream ss;
    ss << "[";
    for (auto it = obj.begin(); it != obj.end(); it++) {
        if (it != obj.begin()) {
            ss << "\n";
        }
        ss << toString(*it);
    }
    ss << "]";
    return ss.str();
}
template <typename Key, typename Value> inline string toString(unordered_map<Key, Value> obj) {
    stringstream ss;
    ss << "[";
    for (auto it = obj.begin(); it != obj.end(); it++) {
        if (it != obj.begin()) {
            ss << "\n";
        }
        ss << toString(*it);
    }
    ss << "]";
    return ss.str();
}
template <typename Value> inline string toString(stack<Value> obj) {
    stringstream ss;
    ss << "[";
    while (obj.size()) {
        ss << obj.top();
        obj.pop();
        if (obj.Size() > 0) {
            ss << "," << endl;
        }
    }
    ss << "]";
    return ss.str();
}

// +++++++++++++++++++++++++++++ //
// Definition of Testing classes //
// +++++++++++++++++++++++++++++ //
// Limitation: Impssible to add the variadic at the first position
template <typename Output, typename... Input> class TestCase {
  public:
    Output expectedOutput;
    tuple<Input...> inputs;
    Output returnedOutput;

    TestCase(Output expectedOutput, Input... inputs) : expectedOutput(expectedOutput), inputs(std::make_tuple(inputs...)), returnedOutput() {
    }

    tuple<Input...> getInputs() {
        return inputs;
    }
};

template <typename Output, typename... Inputs> class TestSuite {
  public:
    using TC = TestCase<Output, Inputs...>;
    using OutputType = Output;
    vector<TC> testCases;
    string outputName;
    array<string, sizeof...(Inputs)> inputNames;

    template <typename OutputName, typename... InputNames> TestSuite(OutputName outputName, InputNames &&...inputNames) {
        this->outputName = outputName;
        auto lambda = [this]<std::size_t... I>(std::index_sequence<I...>, auto &&...args) { ((this->inputNames[I] = std::forward<InputNames>(args)), ...); };
        lambda(std::make_index_sequence<sizeof...(Inputs)>{}, std::forward<InputNames>(inputNames)...);
    }

    void addTestCases(vector<TC> testCases) {
        this->testCases = testCases;
    }

    void print() {
        for (int i = 0; i < testCases.size(); i++) {
            print(testCases[i]);
        }
    }
    void print(size_t i) {
        assert(i < testCases.size());
        print(testCases[i]);
    }
    void print(TC &testCase) {
        printInputs(testCase.inputs);
        cout << "Expected output " << outputName << ": " << toString(testCase.expectedOutput) << endl;
    }

  private:
    template <typename TupleT, std::size_t... Is> void printInputsImp(const TupleT &tp, std::index_sequence<Is...>) {
        auto printElem = [this](size_t i, const auto &x) { cout << "Input " << toString(inputNames[i]) << ": " << toString(x) << endl; };
        (printElem(Is, std::get<Is>(tp)), ...);
    }

    template <typename TupleT, std::size_t TupSize = std::tuple_size_v<TupleT>> void printInputs(const TupleT &tp) {
        printInputsImp(tp, std::make_index_sequence<TupSize>{});
    }
};

class Solution;

class Main {
  public:
    template <typename Solution = Solution, typename Func, typename TestSuiteType> //
    int runTests(Func testFunction, TestSuiteType &testSuite, const function<bool(typename TestSuiteType::TC &testCase)> &validationFunction = nullptr) {
        preRun();

        if (testSuite.testCases.size() == 0) {
            cout << Error << "No tests found" << endl;
            exit(1);
        }
        for (auto &testCase : testSuite.testCases) {
            testSuite.print(testCase);
            Solution solution;
            applyTestCase(&solution, testFunction, testCase, testCase.getInputs());
            bool validation;
            if (validationFunction != nullptr) {
                validation = validationFunction(testCase);
            } else {
                if constexpr (std::is_pointer<typename TestSuiteType::OutputType>::value) {
                    validation = *(testCase.returnedOutput) == *(testCase.expectedOutput);
                } else {
                    validation = testCase.returnedOutput == testCase.expectedOutput;
                }
            }
            if (validation) {
                cout << Success << "  => Pass\n";
            } else {
                fails++;
                cout << Error << "  => Failed : returned ";
                cout << toString(testCase.returnedOutput);
                cout << "\n";
            }
            cout << Reset << "\n";
        }

        postRun();
        return fails;
    }

  protected:
    template <typename Solution, typename Func, typename TestCaseType, typename... Inputs> void applyTestCase(Solution *solution, Func testFunction, TestCaseType &testCase, tuple<Inputs...> inputs) {
        apply([&](auto &&...args) { runTestsInternal(solution, testFunction, testCase, args...); }, inputs);
    }
    template <typename Solution, typename Func, typename TestCaseType, typename... Inputs> void runTestsInternal(Solution *solution, Func testFunction, TestCaseType &testCase, Inputs &&...inputs) {
        testCase.returnedOutput = (solution->*testFunction)(inputs...);
    }

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
        if (fails == 0) {
            cout << Success << "Total fails: " << fails << endl;
        } else {
            cout << Error << "Total fails: " << fails << endl;
        }
        cout << Reset;
    }
};
