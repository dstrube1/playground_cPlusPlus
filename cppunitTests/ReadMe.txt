Starting from here:
https://freedesktop.org/wiki/Software/cppunit/

and this:
https://en.wikipedia.org/wiki/CppUnit

which both have some broken links; but 1.13.2 seems like a good place to start.

Before diving into the official examples, let's try 
1- the accepted answer here:
https://stackoverflow.com/questions/13210248/cppunit-creating-a-simple-test

2- this from duckduckgo's AI answer:
===
/*
CppUnit is a unit testing framework for C++ that allows developers to write and run tests for their code. An example of a simple test case in CppUnit involves creating a class that inherits from TestFixture, setting up test data in the setUp() method, and using assertions like CPPUNIT_ASSERT to verify expected outcomes in test methods.
 comp.nus.edu.sg University of North Carolina at Chapel Hill

Overview of CppUnit
CppUnit is a unit testing framework for C++ that is similar to JUnit for Java. It allows developers to write and run tests for their code, ensuring that individual components work as expected. The framework supports automatic test execution and provides a structured way to organize tests.

Basic Structure of a CppUnit Test
Test Case Class
To create a test case, you need to define a class that inherits from CppUnit::TestFixture. This class will contain your test methods.
*/
class MyTest : public CppUnit::TestFixture {
public:
    void setUp() {
        // Code to set up test environment
    }

    void tearDown() {
        // Code to clean up after tests
    }

    void testExample() {
        CPPUNIT_ASSERT(1 + 1 == 2); // Example assertion
    }
};
/*
Test Suite
A test suite is a collection of test cases. You can create a suite to run multiple tests together.
*/
CppUnit::TestSuite suite;
suite.addTest(new CppUnit::TestCaller<MyTest>("testExample", &MyTest::testExample));
/*
Running Tests
To execute the tests, you typically use a TestRunner. This will run all the tests in the suite and report the results.
*/
int main() {
    CppUnit::TestRunner runner;
    runner.addTest(&suite);
    runner.run();
    return 0;
}

/*
Example of a Complete Test
Here’s a complete example that includes a simple test case for a hypothetical Calculator class.
*/

class CalculatorTest : public CppUnit::TestFixture {
public:
    void setUp() {
        // Initialize calculator object
    }

    void tearDown() {
        // Clean up
    }

    void testAddition() {
        CPPUNIT_ASSERT(calculator.add(2, 3) == 5);
    }

    void testSubtraction() {
        CPPUNIT_ASSERT(calculator.subtract(5, 3) == 2);
    }
};

// Main function to run tests
int main() {
    CppUnit::TestSuite suite;
    suite.addTest(new CppUnit::TestCaller<CalculatorTest>("testAddition", &CalculatorTest::testAddition));
    suite.addTest(new CppUnit::TestCaller<CalculatorTest>("testSubtraction", &CalculatorTest::testSubtraction));

    CppUnit::TestRunner runner;
    runner.addTest(&suite);
    runner.run();
    return 0;
}

/*
This example demonstrates how to set up a basic testing environment using CppUnit, define test cases, and run them.
*/

===END AI

3-
https://cppunit.sourceforge.net/doc/cvs/cppunit_cookbook.html

4- 
https://www.codeguru.com/cplusplus/unit-testing-with-cppunit/

