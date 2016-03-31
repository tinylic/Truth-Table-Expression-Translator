//============================================================================
// Name        : Mini_project.cpp
// Author      : Li Chen
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ExpressionToChart.h"
#include "ChartToExpression.h"
#include "simple_test.h"
using namespace std;
using namespace SimpleTest;
string expr_to_truthtable(int n, const string& expr) {
	ExpressionToChart ETC;
	return ETC.solve(n, expr);
}

string truthtable_to_expr(const string& truth_table) {
	ChartToExpression CTE;
	return CTE.solve(truth_table);
}
int test_main() {
	ExpressionToChart ETC;
	ChartToExpression CTE;
	//correctness testing
	//testing expression to chart

	//check sample
	CHECK_EQUAL(ETC.solve(3, "~A | B & C"), "11010101");

	//check unit input
	CHECK_EQUAL(ETC.solve(1, "A"), "10");
	CHECK_EQUAL(ETC.solve(2, "A"), "1010");

	//check complex input
	CHECK_EQUAL(ETC.solve(4, "A & ~B ^ C & D"), "1101001000100010");
	//CHECK_EQUAL(ETC.solve(6, "~A | B | C & D | ~E & F"), "1101001000100010");
	//testing chart to expression
	//check all 0
	CHECK_EQUAL(CTE.solve("0000"), "0");
	//check all 1
	CHECK_EQUAL(CTE.solve("11"), "1");
	//check sample
	CHECK_EQUAL(CTE.solve("11010101"), "~A | B & C");
	//check complex input
	CHECK_EQUAL(CTE.solve(	"1111110111011101111111111111111111111101110111011111110111011101"),
							"~A | ~E & F | B | C & D");
	//cross testing
	CHECK_EQUAL(ETC.solve(4, CTE.solve("1101001000100010")), "1101001000100010");
	CHECK_EQUAL(ETC.solve(6, CTE.solve(	"1111110111011101111111111111111111111101110111011111110111011101")),
										"1111110111011101111111111111111111111101110111011111110111011101");
	//robustness testing

	//testing expression to chart

	//check empty input
	CHECK_THROW(ETC.solve(1, "   "), EmptyStringError);

	//check invalid characters
	CHECK_THROW(ETC.solve(2, "A + B"), InvalidCharError);

	//check invalid variables
	CHECK_THROW(ETC.solve(2, "A | C"), InvalidVariableError);

	//check syntax error
	CHECK_THROW(ETC.solve(2, "A | ^ B"), SyntaxError);
	CHECK_THROW(ETC.solve(1, "AA"), SyntaxError);
	CHECK_THROW(ETC.solve(2, "A(A | B)"), SyntaxError);

	//check bracket mismatching
	CHECK_THROW(ETC.solve(2, "A ^ B)"), BracketMismatchingError);

	//testing chart to expression

	//check empty input
	CHECK_THROW(CTE.solve(""), EmptyStringError);

	//check invalid input numbers
	CHECK_THROW(CTE.solve("1234"), InvalidCharError);

	//check invalid truthtable length
	CHECK_THROW(CTE.solve("101"), InvalidLengthError);

	return 0;
}
int tester() {
	try {
		int result = test_main();
		CHECK_EQUAL(result, 0);
	} catch (CriticalError) {
		std::cerr << "Critical error occurred. Testing aborted.\n";
	} catch (...) {
		exceptionError();
	}
	switch (errorCnt) {
	case 0:
		std::cout << " **** no errors detected\n";
		return exitSuccess;
	case 1:
		std::cerr << " **** 1 error detected\n";
		break;
	default:
		std::cerr << " **** " << errorCnt << " errors detected\n";
		break;
	}
}
int main() {

	string expr;
	string truth_table;
	int n;
	if (tester() == exitSuccess)
		cout << "Test Finished" << endl;
	//getline(cin, truth_table);
	scanf("%d\n", &n);
	getline(cin, expr);
	cout << expr_to_truthtable(n, expr);
	//cout << truthtable_to_expr(truth_table);
	//ETC.solve();
	//cout << CTE.solve();
	//cout << "Hello\n";
	return 0;
}
