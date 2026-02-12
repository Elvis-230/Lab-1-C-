#include <vector>
#include <iostream>
#include <string>
#include <functional>

using namespace std;

// Simple DOCTEST-like test framework
class TestFramework {
public:
    static TestFramework& instance() {
        static TestFramework tf;
        return tf;
    }
    
    void addTest(const string& name, function<void()> test) {
        tests.push_back({name, test});
    }
    
    int runAll() {
        int passed = 0;
        int failed = 0;
        cout << "Running DOCTEST unit tests...\n" << endl;
        
        for (const auto& test : tests) {
            try {
                test.func();
                cout << "✓ " << test.name << endl;
                passed++;
            } catch (const exception& e) {
                cout << "✗ " << test.name << " - " << e.what() << endl;
                failed++;
            }
        }
        
        cout << "\n" << "=" << string(50, "=") << endl;
        cout << "Tests passed: " << passed << endl;
        cout << "Tests failed: " << failed << endl;
        cout << "=" << string(50, "=") << "\n" << endl;
        
        return failed == 0 ? 0 : 1;
    }
    
private:
    struct Test {
        string name;
        function<void()> func;
    };
    vector<Test> tests;
};

class TestChecker {
private:
    bool passed;
    string expression;
    
public:
    TestChecker(bool cond, const string& expr) : passed(cond), expression(expr) {
        if (!cond) {
            throw runtime_error("CHECK failed: " + expr);
        }
    }
};

#define TEST_CASE(name) \
    void test_##__LINE__(); \
    namespace { \
        struct RegisterTest##__LINE__ { \
            RegisterTest##__LINE__() { \
                TestFramework::instance().addTest(name, test_##__LINE__); \
            } \
        }; \
        static RegisterTest##__LINE__ register_test##__LINE__; \
    } \
    void test_##__LINE__()

#define CHECK(condition) TestChecker((condition), #condition)

bool prefixNonNegative(const vector<int>& a) {
    int sum = 0;
    for (int x : a) {
        sum += x;
        if (sum < 0) return false;
    }
    return true;
}

bool prefixNonPositive(const vector<int>& a) {
    int sum = 0;
    for (int x : a) {
        sum += x;
        if (sum > 0) return false;
    }
    return true;
}

// Unit Tests for prefixNonNegative
TEST_CASE("prefixNonNegative: valid array") {
    vector<int> arr = {1, -1, 1, -1};
    CHECK(prefixNonNegative(arr) == true);
}

TEST_CASE("prefixNonNegative: invalid array") {
    vector<int> arr = {1, -1, -1, 1};
    CHECK(prefixNonNegative(arr) == false);
}

TEST_CASE("prefixNonNegative: empty array") {
    vector<int> arr = {};
    CHECK(prefixNonNegative(arr) == true);
}

TEST_CASE("prefixNonNegative: single positive") {
    vector<int> arr = {1};
    CHECK(prefixNonNegative(arr) == true);
}

TEST_CASE("prefixNonNegative: single negative") {
    vector<int> arr = {-1};
    CHECK(prefixNonNegative(arr) == false);
}

// Unit Tests for prefixNonPositive
TEST_CASE("prefixNonPositive: valid array") {
    vector<int> arr = {-1, 1, -1};
    CHECK(prefixNonPositive(arr) == true);
}

TEST_CASE("prefixNonPositive: invalid array") {
    vector<int> arr = {1, -1, 1, -1};
    CHECK(prefixNonPositive(arr) == false);
}

TEST_CASE("prefixNonPositive: empty array") {
    vector<int> arr = {};
    CHECK(prefixNonPositive(arr) == true);
}

TEST_CASE("prefixNonPositive: single positive") {
    vector<int> arr = {1};
    CHECK(prefixNonPositive(arr) == false);
}

TEST_CASE("prefixNonPositive: single negative") {
    vector<int> arr = {-1};
    CHECK(prefixNonPositive(arr) == true);
}

int main() {
    return TestFramework::instance().runAll();
}
