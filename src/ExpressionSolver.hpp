#pragma once

#include <string_view>

#include "Context.hpp"
#include "Expression.hpp"

namespace expression_solver {

class ExpressionSolver {
  Context context;

public:
  ExpressionSolver(const Context &context = Context::getDefaultContext()) : context(context) {}

  ExpressionPtr compile(const std::string &expression) const;

  double solve(const std::string &expression) const {
    return solve(compile(expression));
  }

  double solve(const Expression &expression) const {
    return expression.evaluate();
  }

  double solve(ExpressionPtr expression) const {
    return expression->evaluate();
  }
};

} // namespace expression_solver
