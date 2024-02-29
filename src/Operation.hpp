#pragma once

#include "Expression.hpp"
#include <memory>      // Add missing include directive for <memory>
#include <string_view> // Add missing include directive for <string_view>

namespace expression_solver {
namespace operations {

class Operation : public Expression {
public:
  virtual ~Operation() = default;
  virtual constexpr std::string_view identifier() const = 0;
  virtual constexpr int precedence() const = 0;
};

typedef std::shared_ptr<Operation> OperationPtr;

class BinaryOperation : public Operation {
public:
  BinaryOperation(ExpressionPtr left, ExpressionPtr right)
      : left(std::move(left)), right(std::move(right)) {}
  virtual ~BinaryOperation() = default;

  virtual constexpr std::string_view identifier() const = 0;

  virtual ExpressionPtr create(ExpressionPtr left,
                               ExpressionPtr right) const = 0;

  void setLeft(ExpressionPtr left) { this->left = std::move(left); }
  void setRight(ExpressionPtr right) { this->right = std::move(right); }

  ExpressionPtr getLeft() const { return left; }
  ExpressionPtr getRight() const { return right; }

protected:
  ExpressionPtr left;
  ExpressionPtr right;
};

class AddOperation : public BinaryOperation {
public:
  AddOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}
  double evaluate() const override {
    return left->evaluate() + right->evaluate();
  }

  constexpr std::string_view identifier() const override { return "+"; }

  constexpr int precedence() const override { return 1; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<AddOperation>(std::move(left), std::move(right));
  }
};

class SubtractOperation : public BinaryOperation {
public:
  SubtractOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}
  double evaluate() const override {
    return left->evaluate() - right->evaluate();
  }

  constexpr std::string_view identifier() const override { return "-"; }

  constexpr int precedence() const override { return 1; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<SubtractOperation>(std::move(left),
                                               std::move(right));
  }
};

class MultiplyOperation : public BinaryOperation {
public:
  MultiplyOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}

  double evaluate() const override {
    return left->evaluate() * right->evaluate();
  }

  constexpr std::string_view identifier() const override { return "*"; }

  constexpr int precedence() const override { return 2; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<MultiplyOperation>(std::move(left),
                                               std::move(right));
  }
};

class DivideOperation : public BinaryOperation {
public:
  DivideOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}

  double evaluate() const override {
    return left->evaluate() / right->evaluate();
  }

  constexpr std::string_view identifier() const override { return "/"; }

  constexpr int precedence() const override { return 2; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<DivideOperation>(std::move(left), std::move(right));
  }
};

class PowerOperation : public BinaryOperation {
public:
  PowerOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}

  double evaluate() const override {
    return std::pow(left->evaluate(), right->evaluate());
  }

  constexpr std::string_view identifier() const override { return "^"; }

  constexpr int precedence() const override { return 3; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<PowerOperation>(std::move(left), std::move(right));
  }
};

class ModuloOperation : public BinaryOperation {
public:
  ModuloOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}

  double evaluate() const override {
    return std::fmod(left->evaluate(), right->evaluate());
  }

  constexpr std::string_view identifier() const override { return "%"; }

  constexpr int precedence() const override { return 2; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<ModuloOperation>(std::move(left), std::move(right));
  }
};

class UnaryOperation : public Operation {
protected:
  ExpressionPtr operand;
public:
  UnaryOperation(ExpressionPtr operand) : operand(std::move(operand)) {}
  virtual ~UnaryOperation() = default;

  virtual constexpr std::string_view identifier() const = 0;

  virtual double evaluate() const = 0;

  virtual ExpressionPtr create(ExpressionPtr operand) const = 0;

  void setOperand(ExpressionPtr operand) { this->operand = std::move(operand); }
  ExpressionPtr getOperand() const { return operand; }
};

class NegateOperation : public UnaryOperation {
public:
  NegateOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return -(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "-"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<NegateOperation>(std::move(operand));
  }
};

class SinOperation : public UnaryOperation {
public:
  SinOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::sin(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "sin"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<SinOperation>(std::move(operand));
  }
};

class CosOperation : public UnaryOperation {
public:
  CosOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::cos(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "cos"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<CosOperation>(std::move(operand));
  }
};

class TanOperation : public UnaryOperation {
public:
  TanOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::tan(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "tan"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<TanOperation>(std::move(operand));
  }
};

class AsinOperation : public UnaryOperation {
public:
  AsinOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::asin(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "asin"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<AsinOperation>(std::move(operand));
  }
};

class AcosOperation : public UnaryOperation {
public:
  AcosOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::acos(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "acos"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<AcosOperation>(std::move(operand));
  }
};

class AtanOperation : public UnaryOperation {
public:
  AtanOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::atan(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "atan"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<AtanOperation>(std::move(operand));
  }
};

class LogOperation : public UnaryOperation {
public:
  LogOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::log(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "log"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<LogOperation>(std::move(operand));
  }
};

class SqrtOperation : public UnaryOperation {
public:
  SqrtOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::sqrt(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "sqrt"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<SqrtOperation>(std::move(operand));
  }
};

class AbsOperation : public UnaryOperation {
public:
  AbsOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::abs(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "abs"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<AbsOperation>(std::move(operand));
  }
};

class ExpOperation : public UnaryOperation {
public:
  ExpOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::exp(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "exp"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<ExpOperation>(std::move(operand));
  }
};

class CeilOperation : public UnaryOperation {
public:
  CeilOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::ceil(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "ceil"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<CeilOperation>(std::move(operand));
  }
};

class FloorOperation : public UnaryOperation {
public:
  FloorOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::floor(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "floor"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<FloorOperation>(std::move(operand));
  }
};

class RoundOperation : public UnaryOperation {
public:
  RoundOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::round(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "round"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<RoundOperation>(std::move(operand));
  }
};

class TruncOperation : public UnaryOperation {
public:
  TruncOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return std::trunc(operand->evaluate()); }

  constexpr std::string_view identifier() const override { return "trunc"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<TruncOperation>(std::move(operand));
  }
};

class MinOperation : public BinaryOperation {
public:
  MinOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}

  double evaluate() const override {
    return std::min(left->evaluate(), right->evaluate());
  }

  constexpr std::string_view identifier() const override { return "min"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<MinOperation>(std::move(left), std::move(right));
  }
};

class MaxOperation : public BinaryOperation {
public:
  MaxOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}

  double evaluate() const override {
    return std::max(left->evaluate(), right->evaluate());
  }

  constexpr std::string_view identifier() const override { return "max"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<MaxOperation>(std::move(left), std::move(right));
  }
};

class Atan2Operation : public BinaryOperation {
public:
  Atan2Operation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}

  double evaluate() const override {
    return std::atan2(left->evaluate(), right->evaluate());
  }

  constexpr std::string_view identifier() const override { return "atan2"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<Atan2Operation>(std::move(left), std::move(right));
  }
};

class HypotOperation : public BinaryOperation {
public:
  HypotOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}

  double evaluate() const override {
    return std::hypot(left->evaluate(), right->evaluate());
  }

  constexpr std::string_view identifier() const override { return "hypot"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<HypotOperation>(std::move(left), std::move(right));
  }
};

class LogicalAndOperation : public BinaryOperation {
public:
  LogicalAndOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}

  double evaluate() const override {
    return left->evaluate() && right->evaluate();
  }

  constexpr std::string_view identifier() const override { return "&&"; }

  constexpr int precedence() const override { return 0; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<LogicalAndOperation>(std::move(left), std::move(right));
  }
};

class LogicalOrOperation : public BinaryOperation {
public:
  LogicalOrOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}

  double evaluate() const override {
    return left->evaluate() || right->evaluate();
  }

  constexpr std::string_view identifier() const override { return "||"; }

  constexpr int precedence() const override { return 0; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<LogicalOrOperation>(std::move(left), std::move(right));
  }
};

class LogicalNotOperation : public UnaryOperation {
public:
  LogicalNotOperation(ExpressionPtr operand) : UnaryOperation(std::move(operand)) {}

  double evaluate() const override { return !operand->evaluate(); }

  constexpr std::string_view identifier() const override { return "!"; }

  constexpr int precedence() const override { return 4; }

  ExpressionPtr create(ExpressionPtr operand) const override {
    return std::make_shared<LogicalNotOperation>(std::move(operand));
  }
};

class LogicalEqualOperation : public BinaryOperation {
public:
  LogicalEqualOperation(ExpressionPtr left, ExpressionPtr right)
      : BinaryOperation(std::move(left), std::move(right)) {}

  double evaluate() const override {
    return left->evaluate() == right->evaluate();
  }

  constexpr std::string_view identifier() const override { return "=="; }

  constexpr int precedence() const override { return 0; }

  ExpressionPtr create(ExpressionPtr left, ExpressionPtr right) const override {
    return std::make_shared<LogicalEqualOperation>(std::move(left), std::move(right));
  }
};

} // namespace operations
} // namespace expression_solver
