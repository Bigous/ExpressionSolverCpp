#pragma once

#include "Expression.hpp"
#include <memory>
#include <string_view>
#include <functional>

namespace expression_solver {
namespace operations {

using OperandsList = std::vector<ExpressionPtr>;

class Operation : public Expression {
public:
  virtual ~Operation() = default;
  virtual constexpr std::string_view identifier() const = 0;
  virtual constexpr int precedence() const = 0;
  virtual constexpr int operandsCount() const = 0;
  virtual void setOperands(const OperandsList &operands) = 0;
  virtual void addOperand(const ExpressionPtr &operand) = 0;
  virtual const OperandsList &getOperands() const = 0;
  virtual std::shared_ptr<Operation> clone() const = 0;
};

using OperationPtr = std::shared_ptr<Operation>;


template<const char* Identifier, int Precedence, int Operands, double (*OperationFunction)(const OperandsList &)>
class TemplateOperation : public Operation {
public:
  constexpr std::string_view identifier() const override { return Identifier; }
  constexpr int precedence() const override { return Precedence; }
  double evaluate() const override { return OperationFunction(operands); }
  constexpr int operandsCount() const override { return Operands; }
  void setOperands(const OperandsList &operands) override { this->operands = operands; }
  void addOperand(const ExpressionPtr &operand) override { operands.push_back(std::move(operand)); }
  const OperandsList &getOperands() const override { return operands; }
  OperationPtr clone() const override {
    auto cloned = std::make_shared<TemplateOperation<Identifier, Precedence, Operands, OperationFunction>>();
    return cloned;
  }
  double evaluate(const OperandsList &operands) const { 
    //if(operands.size() != Operands) throw std::runtime_error("Invalid number of operands");
    return OperationFunction(operands);
  }
private:
  OperandsList operands;
};

} // namespace operations
} // namespace expression_solver
