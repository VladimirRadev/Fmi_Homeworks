#pragma once
#include <string>
#include <vector>

#include "TestCase.hpp"

/// TestSuite is a collection of many Test Cases
/// A Test Suite has a name so we can know which problem it's from
class TestSuite {

private:
    std::string name;
    TestCase* testCases = nullptr;
    int count;
    int capacity;

public:
    /// Constructor we'll need for initializing the TestSuite
    TestSuite();
    TestSuite(std::string name);
    TestSuite(const TestSuite& rhs);
    TestSuite& operator=(const TestSuite& rhs);

    ~TestSuite();
    /// Add a new test case to the collection of cases
    void add(const TestCase&);

    /// Retrieve the test cases, which are passing
    std::vector<TestCase> filterPassing() const;

    /// Retrieve the test cases, which are failing
    std::vector<TestCase> filterFailing() const;

    /// Retrieve the test cases, which have the specified error type
    std::vector<TestCase> filterByErrorType(ErrorType) const;

    /// Remove all test cases with the given error type
    void removeByErrorType(ErrorType);

    /// Retrieve the name of the TestSuite
    std::string getName() const;

    /// Change the name of the TestSuite
    void setName(const std::string&);

    int getCount()const;

    const TestCase* getTestCases()const;

    void printTestCases()const;
};
