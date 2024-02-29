#include <queue>
#include <stack>
#include <string_view>

#include "ExpressionSolver.hpp"
#include "Operation.hpp"

namespace expression_solver {
using OperationPtr = operations::OperationPtr;

struct Token {

  std::string_view value;

  // Token(std::string_view source) { value = source; }

  Token(const Token &other) { value = other.value; }

  Token(Token &&other) : value(std::move(other.value)) {}
  Token(const std::string &source, size_t start, size_t end)
      : value(source.data() + start, end - start) {}
  Token() = default;

  Token &operator=(const Token &other) {
    value = other.value;
    return *this;
  }

  Token &operator=(Token &&other) {
    value = std::move(other.value);
    return *this;
  }

  bool operator==(const Token &other) const { return value == other.value; }

  bool operator!=(const Token &other) const { return value != other.value; }

  bool isOperation(const Context &context, OperationPtr &op) const {
    auto optOp = context.getOperation(std::string(value));
    if (optOp.has_value()) {
      op = optOp.value();
      return true;
    }
    return false;
  }

  bool isVariable(const Context &context, double &Value) const {
    auto optVal = context.getVariable(std::string(value));
    if (optVal.has_value()) {
      Value = optVal.value();
      return true;
    }
    return false;
  }

  bool isPlaceholder(const Context &context, PlaceHolderPtr &Value) const {
    auto optVal = context.getPlaceholder(std::string(value));
    if (optVal.has_value()) {
      Value = optVal.value();
      return true;
    }
    return false;
  }

  bool isConst(double &Value) const {
    try {
      Value = std::stod(std::string(value));
      return true;
    } catch (std::invalid_argument &e) {
      return false;
    }
  }
};

std::vector<Token> tokenize(const std::string &expression,
                            const Context &context) {
  std::vector<Token> tokens;

  for (int i = 0; i < expression.size(); i++) {
    char c = expression[i];

    // Skip whitespace
    if (c == ' ') { // finish token
      continue;
    }

    // Check for parentheses
    if (c == '(' || c == ')') {
      tokens.emplace_back(Token(expression, i, i + 1));
      continue;
    }

    int j = i;

    // Check for numbers and constants
    if (std::isdigit(c) || c == '.') {
      while (j < expression.size() &&
             (std::isdigit(expression[j]) || expression[j] == '.')) {
        j++;
      }
      tokens.emplace_back(Token(expression, i, j));
      i = j - 1;
      continue;
    }

    // Check for variables and placeholders
    if (std::isalpha(c) || c == '_') {
      while (j < expression.size() &&
             (std::isalnum(expression[j]) || c == '_' || c == '.')) {
        j++;
      }
      tokens.emplace_back(Token(expression, i, j));
      i = j - 1;
      continue;
    }

    // Check for operations
    bool cont = false;
    auto possible_ops = context.getOperationsStartingWith(c);
    for (auto op : possible_ops) {
      std::string id(op->identifier());
      if (expression.substr(i, id.size()) == id) {
        tokens.emplace_back(Token(expression, i, i + id.size()));
        i += static_cast<int>(id.size()) - 1;
        cont = true;
        break;
      }
    }
    if (cont)
      continue;

    throw std::invalid_argument("Invalid character in expression");
  }

  return tokens;
}

ExpressionPtr build_tree(std::queue<Token> &postfixTokens,
                         const Context &context) {
  std::stack<ExpressionPtr> expressions;
  double value;
  OperationPtr op;
  PlaceHolderPtr placeholder;

  while (!postfixTokens.empty()) {
    auto &token = postfixTokens.front();
    if (token.isConst(value)) {
      expressions.push(std::make_shared<ConstExpression>(value));
    } else if (token.isOperation(context, op)) {
      auto newOp = op->clone();
      int operandsCount = newOp->operandsCount();
      for(int i = 0; i < operandsCount; i++) {
        newOp->addOperand(expressions.top());
        expressions.pop();
      }
      expressions.push(newOp);
    } else if (token.isVariable(context, value)) {
      expressions.push(std::make_shared<ConstExpression>(value));
    } else if (token.isPlaceholder(context, placeholder)) {
      expressions.push(placeholder);
    }
    // else if (token.value == "-") {
    //   if (expressions.empty() || expressions.top()->getSymbol() == "(") {
    //     // Unary negation
    //     auto operand = std::make_shared<ConstExpression>(0);
    //     expressions.push(operand);
    //     expressions.push(std::make_shared<BinaryMinusExpression>());
    //   } else {
    //     // Binary subtraction
    //     expressions.push(std::make_shared<BinaryMinusExpression>());
    //   }
    // }
    else {
      throw std::invalid_argument("Invalid token in postfix expression");
    }
    postfixTokens.pop();
  }

  return expressions.top();
}

ExpressionPtr parse(std::vector<Token> &tokens, const Context &context) {
  std::stack<Token> operators;
  std::queue<Token> postfixTokens;

  OperationPtr curr_op;

  for (auto &token : tokens) {
    if (token.value == "(") {
      operators.emplace(token);
      continue;
    }
    if (token.value == ")") {
      while (operators.top().value != "(") {
        postfixTokens.emplace(operators.top());
        operators.pop();
      }
      operators.pop();
      continue;
    }
    if (token.isOperation(context, curr_op)) {
      while (!operators.empty()) {
        auto topOp = operators.top();
        auto op = context.getOperation(std::string(topOp.value));
        if (!op.has_value())
          break;
        if (op.value()->precedence() < curr_op->precedence())
          break;
        postfixTokens.emplace(topOp);
        operators.pop();
      }
      operators.emplace(token);
      continue;
    }
    postfixTokens.push(token);
  }

  while (!operators.empty()) {
    postfixTokens.emplace(operators.top());
    operators.pop();
  }

  return build_tree(postfixTokens, context);
}

ExpressionPtr optimize(ExpressionPtr expression, const Context &context,
                       int recursionDepth = 0) {
  using namespace operations;
  if (recursionDepth >= 20) {
    return expression;
  }

  auto constExp = std::dynamic_pointer_cast<ConstExpression>(expression);
  if (constExp) {
    return expression;
  }

  auto op = std::dynamic_pointer_cast<Operation>(expression);
  if (op) {
    auto operands = op->getOperands();
    bool allConst = true;
    for (auto &operand : operands) {
      operand = optimize(operand, context, recursionDepth + 1);
      if (!std::dynamic_pointer_cast<ConstExpression>(operand)) {
        allConst = false;
      }
    }
    op->setOperands(operands);
    if (allConst) {
      return std::make_shared<ConstExpression>(op->evaluate());
    }
    return expression;
  }

  return expression;
}

ExpressionPtr ExpressionSolver::compile(const std::string &expression) const {
  auto tokens = tokenize(expression, context);
  auto parsed = parse(tokens, context);
  return optimize(parsed, context);
}

} // namespace expression_solver