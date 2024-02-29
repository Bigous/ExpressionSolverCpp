#pragma once
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <set>

#include "Operation.hpp"

namespace expression_solver {
class Context {
  static Context DefaultContext;

  std::unordered_map<std::string, double> variables;
  std::unordered_map<std::string, operations::OperationPtr> operations;
  std::unordered_map<std::string, PlaceHolderPtr> placeholders;
  std::unordered_map<char, std::vector<operations::OperationPtr>> operationFirstChar;

public:
  Context() = default;

  Context(const Context &other)
      : variables(other.variables), operations(other.operations),
        placeholders(other.placeholders), operationFirstChar(other.operationFirstChar) {}

  Context &operator=(const Context &other) {
    if (this != &other) {
      variables = other.variables;
      operations = other.operations;
      placeholders = other.placeholders;
      operationFirstChar = other.operationFirstChar;
    }
    return *this;
  }

  Context &operator=(Context &&other) noexcept {
    if (this != &other) {
      variables = std::move(other.variables);
      operations = std::move(other.operations);
      placeholders = std::move(other.placeholders);
      operationFirstChar = std::move(other.operationFirstChar);
    }
    return *this;
  }

  virtual ~Context() = default;

  static Context &getDefaultContext() { return DefaultContext; }

  virtual std::optional<double> getVariable(const std::string &name) const {
    auto it = variables.find(name);
    if (it == variables.end()) {
      return std::nullopt;
    }
    return it->second;
  }

  virtual void setVariable(std::string name, double value) {
    variables[name] = value;
  }

  virtual void removeVariable(const std::string &name) {
    variables.erase(name);
  }

  virtual void clearVariables() { variables.clear(); }

  virtual bool hasVariable(const std::string &name) const {
    return variables.find(name) != variables.end();
  }

  virtual void addOperation(operations::OperationPtr operation) {
    for (char c : operation->identifier()) {
      if(operationFirstChar.find(c) == operationFirstChar.end()) {
        operationFirstChar[c] = { operation };
      } else {
        operationFirstChar[c].emplace_back(operation);
      }
    }
    operations[operation->identifier().data()] = std::move(operation);
  }

  virtual const std::vector<operations::OperationPtr> &getOperationsStartingWith(char c) const {
    static std::vector<operations::OperationPtr> empty;
    auto it = operationFirstChar.find(c);
    if (it == operationFirstChar.end()) {
      return empty;
    }
    return it->second;
  }

  virtual void removeOperation(const std::string &identifier) {
    operations.erase(identifier);
  }

  virtual std::optional<operations::OperationPtr>
  getOperation(const std::string &identifier) const {
    auto it = operations.find(identifier);
    if (it == operations.end()) {
      return std::nullopt;
    }
    return it->second;
  }

  virtual bool hasOperation(const std::string &identifier) const {
    return operations.find(identifier) != operations.end();
  }

  virtual void addPlaceholder(PlaceHolderPtr placeholder) {
    placeholders[std::string(placeholder->getIdentifier())] =
        std::move(placeholder);
  }

  virtual void removePlaceholder(const std::string &identifier) {
    placeholders.erase(identifier);
  }

  virtual std::optional<PlaceHolderPtr>
  getPlaceholder(const std::string &identifier) const {
    auto it = placeholders.find(identifier);
    if (it == placeholders.end()) {
      return std::nullopt;
    }
    return it->second;
  }
};
} // namespace expression_solver