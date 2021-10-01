#include"TestSuite.hpp"


TestSuite::TestSuite() :name(""), count(0), capacity(2)
{
	this->testCases = new TestCase[capacity];
}
TestSuite::TestSuite(std::string name) : count(0), capacity(2)
{
	this->name = name;
	this->testCases = new TestCase[capacity];
}
TestSuite::TestSuite(const TestSuite& rhs)
{
	this->name = rhs.name;
	delete[]this->testCases;
	this->testCases = new TestCase[rhs.getCount()];
	for (int i = 0; i < rhs.getCount(); i++)
	{
		this->testCases[i] = rhs.getTestCases()[i];
	}
	this->count = rhs.getCount();
	this->capacity = rhs.getCount();
}
TestSuite& TestSuite::operator=(const TestSuite& rhs)
{
	if (this != &rhs)
	{
		this->name = rhs.name;
		delete[]this->testCases;
		this->testCases = new TestCase[rhs.getCount()];
		for (int i = 0; i < rhs.getCount(); i++)
		{
			this->testCases[i] = rhs.getTestCases()[i];
		}
		this->count = rhs.getCount();
		this->capacity = rhs.getCount();
	}
	return *this;
}
TestSuite::~TestSuite()
{
	delete[]this->testCases;
}
void TestSuite::add(const TestCase& testCase)
{
	if (count + 1 > capacity)
	{
		capacity *= 2;
		TestCase* newTestCases = new TestCase[capacity];
		for (int i = 0; i < count; i++)
		{
			newTestCases[i] = this->testCases[i];
		}
		newTestCases[count] = testCase;
		++count;
		delete[]testCases;
		testCases = newTestCases;
		return;
	}
	else
	{
		testCases[count] = testCase;
		++count;
	}
}

std::vector<TestCase> TestSuite::filterPassing() const
{
	std::vector<TestCase>result;
	for (int i = 0; i < this->count; i++)
	{
		if (this->testCases[i].isPassing())
		{
			result.push_back(this->testCases[i]);
		}
	}
	return result;
}
std::vector<TestCase> TestSuite::filterFailing() const
{
	std::vector<TestCase>result;
	for (int i = 0; i < this->count; i++)
	{
		if (!this->testCases[i].isPassing())
		{
			result.push_back(this->testCases[i]);
		}
	}
	return result;
}

std::vector<TestCase> TestSuite::filterByErrorType(ErrorType toCheck) const
{
	std::vector<TestCase>result;
	for (int i = 0; i < this->count; i++)
	{
		if (this->testCases[i].getErrorType() == toCheck)
		{
			result.push_back(this->testCases[i]);
		}
	}
	return result;
}

void TestSuite::removeByErrorType(ErrorType toRemove)
{
	std::vector<int>indexesLeftAfterDelete;
	for (int i = 0; i < this->count; i++)
	{
		if (this->testCases[i].getErrorType() != toRemove)
		{
			indexesLeftAfterDelete.push_back(i);
		}
	}
	int newCount = indexesLeftAfterDelete.size();
	if (newCount < this->count && newCount != 0)
	{
		int indexOfNewTestCases = 0;
		TestCase* newTestCases = new TestCase[newCount];
		for (int i = 0; i < newCount; i++)
		{
			for (int j = 0; j < this->count; j++)
			{
				if (indexesLeftAfterDelete[i] == j)
				{
					newTestCases[indexOfNewTestCases++] = this->testCases[j];
					break;
				}
				continue;
			}
		}
		delete[]this->testCases;
		this->testCases = newTestCases;
		this->count = newCount;
		this->capacity = newCount;
		return;

	}
	else if (newCount == 0)
	{

		TestCase* newTestCases = new TestCase[1];
		delete[]this->testCases;
		this->testCases = newTestCases;
		this->count = 0;
		this->capacity = 1;
		return;
	}
	else
	{
		return;
	}
}
std::string TestSuite::getName() const
{
	return this->name;
}
void TestSuite::setName(const std::string& name)
{
	this->name = name;
}
int TestSuite::getCount()const
{
	return this->count;
}
const TestCase* TestSuite::getTestCases()const
{
	return this->testCases;
}
void TestSuite::printTestCases()const
{
	std::cout << std::endl;
	std::cout << "TestCases in suite: " << this->getName() << std::endl;
	for (int i = 0; i < this->count; i++)
	{
		std::cout << this->testCases[i].getName() << std::endl;
	}
	std::cout << std::endl;
}