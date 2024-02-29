#pragma once

#include <string>
#include <memory>

namespace expression_solver {
  class Expression {
  public:
    virtual ~Expression() = default;
    virtual double evaluate() const = 0;
  };

  typedef std::shared_ptr<Expression> ExpressionPtr;

  class ConstExpression : public Expression {
  private:
    double value;

  public:
    explicit ConstExpression(double value) : value(value) {}
    ~ConstExpression() override = default;

    double evaluate() const override {
      return value;
    }
  };

  class IdentifiedExpression : public Expression { 
  private:
    std::string identifier;
    public:
      explicit IdentifiedExpression(std::string identifier) : identifier(identifier) {}
      std::string_view getIdentifier() const {
        return identifier;
      }
  };

  class PlaceHolder : public IdentifiedExpression {
    double value;
  public:
    explicit PlaceHolder(std::string identifier, double value) : IdentifiedExpression(identifier) {}
    double evaluate() const override {
      return value;
    }
    void setValue(double value) {
      this->value = value;
    }
  };

  typedef std::shared_ptr<PlaceHolder> PlaceHolderPtr;

}