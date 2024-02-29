#include "../src/ExpressionSolver.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace expression_solver;
using namespace expression_solver::operations;

int runConstTests(const std::vector<std::tuple<std::string, double> > &tests, const expression_solver::ExpressionSolver &solver);

int main() {
  expression_solver::ExpressionSolver solver;
  std::vector<std::tuple<std::string, double> > constTests = {
      {"1+1", 2},
      {"1-1", 0},
      {"1*1", 1},
      {"1/1", 1},
      {"1+2*3", 7},
      {"(1+2)*3", 9},
      {"(1+2)*(3+4)", 21},
      {"(1+2)*(3+4)/2", 10.5},
      {"(1+2)*(3+4)/2-1", 9.5},
      {"(1+2)*(3+4)/2-1*2", 8.5},
      {"(1+2)*(3+4)/2-1*2/2", 9.5},
      {"(1+2)*(3+4)/2-1*2/2+1", 10.5},
      {"(1+2)*(3+4)/2-1*2/2+1*2", 11.5},
      {"(1+2)*(3+4)/2-1*2/2+1*2/2", 10.5},
      {"(1+2)*(3+4)/2-1*2/2+1*2/2-1", 9.5},
      {"(1+2)*(3+4)/2-1*2/2+1*2/2-1*2", 8.5},
      {"(1+2)*(3+4)/2-1*2/2+1*2/2-1*2/2", 9.5},
      {"(1+2)*(3+4)/2-1*2/2+1*2/2-1*2/2+1", 10.5},
      {"(1+2)*(3+4)/2-1*2/2+1*2/2-1*2/2+1*2", 11.5},
      {"(1+2)*(3+4)/2-1*2/2+1*2/2-1*2/2+1*2/2", 10.5},
      {"((1+2)*(3+4)/2-1*2/2+1)*2/2-1*2/2+1*2/2", 10.5},
      {"((1+2)*((3+4)/2-1)*2/2+1)*2/(2-1*2/2+1*2)/2", 2.8333333333333333333333333333333},
      {"PI * DEG", 180.0},
      {"PI * PI", 9.8696044010893586188344909998762},
      {"PI * PI / PI^2", 1.0},
      {"PI * INF", std::numeric_limits<double>::infinity()},
      {"PI * TRUE", 3.14159265358979323846},
      {"PI * FALSE", 0},
      {"PI * NULL", 0},
      {"PI * EPSILON", 3.14159265358979323846 * std::numeric_limits<double>::epsilon()},
      {"E * E", 7.3890560989306495721715710580548},
      {"E * INF", std::numeric_limits<double>::infinity()},
      {"E * TRUE", 2.71828182845904523536},
      {"E * FALSE", 0},
      {"E * NULL", 0},
      {"E * EPSILON", 2.71828182845904523536 * std::numeric_limits<double>::epsilon()},
      {"log(2)", 0.69314718055994530941723212145818},
      {"log(E)", 1},
      {"log(1)", 0},
      {"log(0)", -std::numeric_limits<double>::infinity()},
      {"log(INF)", std::numeric_limits<double>::infinity()},
      {"log(0.5)", -0.69314718055994530941723212145818},
      {"log(10) / log(2)", 3.3219280948873626},
      {"3 max 5", 5},
      {"3 min 5", 3},
      {"75 % 3", 0},
      {"75 % 4", 3},
      {"75 % 5", 0},
      {"75 % 6", 3},
      {"75 % 7", 5},
      {"75 % 8", 3},
      {"75 % 9", 3},
      {"75 % 10", 5},
      {"75 % 11", 9},
      {"sin(0)", 0},
      {"sin(PI/2)", 1},
      {"sin(PI)", 0},
      {"sin(3*PI/2)", -1},
      {"sin(2*PI)", 0},
      {"cos(0)", 1},
      {"cos(PI/2)", 0},
      {"cos(PI)", -1},
      {"cos(3*PI/2)", 0},
      {"cos(2*PI)", 1},
      {"tan(0)", 0},
      {"tan(PI/4)", 1},
      {"tan(PI/2)", std::numeric_limits<double>::infinity()},
      {"tan(3*PI/4)", -1},
      {"tan(PI)", 0},
      {"tan(5*PI/4)", 1},
      {"tan(3*PI/2)", std::numeric_limits<double>::infinity()},
      {"tan(7*PI/4)", -1},
      {"tan(2*PI)", 0},
      {"atan(0)", 0},
      {"atan(1)", std::atan(1)},
      {"atan(INF)", std::atan(std::numeric_limits<double>::infinity())},
  };
  int passed = runConstTests(constTests, solver);

  return passed == constTests.size() ? 0 : 1;
}

int runConstTests(const std::vector<std::tuple<std::string, double> > &constTests, const expression_solver::ExpressionSolver &solver)
{
  int passed = 0;
  for (const auto &[expression, expected] : constTests)
  {
    auto exp = solver.compile(expression);
    if(std::dynamic_pointer_cast<expression_solver::ConstExpression>(exp) == nullptr)
    {
      std::cout << "Optimization Test failed: " << expression << " = " << expected << " (expected a ConstExpression)" << std::endl;
    }
    double result = solver.solve(exp);
    
    // Allow for small differences in floating point numbers
    if (std::abs(result - expected) < 1e-10)
    {
      std::cout << "Test passed: " << expression << " = " << expected << std::endl;
      passed++;
    }
    else
    {
      std::cout << "Test failed: " << expression << " = " << result << " (expected " << expected << ")" << std::endl;
    }
  }
  return passed;
}