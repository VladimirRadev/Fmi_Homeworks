#include <cstring>
#include <iostream>

#include "Error.hpp"
#include "TestCase.hpp"
#include "TestSuite.hpp"

using namespace std;
int main()
{
	int kur = 0,s=0;
	Error errNone = Error::newNone();
	Error builFailde = Error::newBuildFailed("New build failed");
	Error errNone1 = Error::newNone();
	Error warnign = Error::newWarning("Warning!");
	Error Doublewarnign = Error::newWarning("Double Warning!");
	Error failed = Error::newFailedAssertion("failed assertion!");
	TestCase testCase("passing test",errNone);
	TestCase testCase1("warning", warnign);
	TestCase testCase2("build failed", builFailde);
	TestCase testCase3("warn", Doublewarnign);
	TestSuite testSuite("kur");
	TestSuite suite(testSuite);
	cout<<testSuite.getName() << endl;
	//testSuite.add(testCase);
	testSuite.add(testCase1);
	//testSuite.add(testCase2);
	testSuite.add(testCase3);
	cout << testSuite.filterPassing().size() << endl;
	cout << testSuite.filterFailing().size() << endl;
	std::vector<TestCase>testsWithWarningType;
	testsWithWarningType = testSuite.filterByErrorType(ErrorType::FailedAssertion);
	for (int i = 0; i < testsWithWarningType.size(); i++)
	{
		cout<<testsWithWarningType[i].getErrorMessage() << endl;
	}
	testSuite.removeByErrorType(ErrorType::Warning);
	testSuite.printTestCases();
	testSuite.add(testCase1);
	testSuite.printTestCases();
	testSuite.removeByErrorType(ErrorType::Warning);
	testSuite.removeByErrorType(ErrorType::Warning);
	testSuite.removeByErrorType(ErrorType::Warning);
	if (testCase.getErrorType()==ErrorType::Warning)
	{
		cout << testCase.getName() << endl;
		return 0;
	}
	else
	{
		cout << testCase.getErrorMessage() << endl;
		return 0;
	}
	

	if (failed.getType()==ErrorType::BuildFailed)
	{
		
		std::cout << failed.getMessage() << endl;
	}
	if (builFailde.getType() == ErrorType::BuildFailed)
	{
		cout << " build failde" << endl;
	}
	if (builFailde.hasMessage())
	{
		cout << builFailde.getMessage() << endl;
	}
	cout << boolalpha << errNone1.hasMessage() << endl;
}