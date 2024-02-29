#include "Context.hpp"

namespace expression_solver {
// Initialize DefaultContext
Context Context::DefaultContext = Context();

constexpr char addId[] = "+";
constexpr auto add = [](const operations::OperandsList &operands) {
  return operands[1]->evaluate() + operands[0]->evaluate();
};

constexpr char subtractId[] = "-";
constexpr auto subtract = [](const operations::OperandsList &operands) {
  return operands[1]->evaluate() - operands[0]->evaluate();
};

constexpr char multiplyId[] = "*";
constexpr auto multiply = [](const operations::OperandsList &operands) {
  return operands[1]->evaluate() * operands[0]->evaluate();
};

constexpr char divideId[] = "/";
constexpr auto divide = [](const operations::OperandsList &operands) {
  return operands[1]->evaluate() / operands[0]->evaluate();
};

constexpr char powerId[] = "^";
constexpr auto power = [](const operations::OperandsList &operands) {
  return std::pow(operands[1]->evaluate(), operands[0]->evaluate());
};

constexpr char moduloId[] = "%";
constexpr auto modulo = [](const operations::OperandsList &operands) {
  return std::fmod(operands[1]->evaluate(), operands[0]->evaluate());
};

constexpr char negateId[] = "-";
constexpr auto negate = [](const operations::OperandsList &operands) {
  return -operands[0]->evaluate();
};

constexpr char atan2Id[] = "atan2";
constexpr auto atan2 = [](const operations::OperandsList &operands) {
  return std::atan2(operands[1]->evaluate(), operands[0]->evaluate());
};

constexpr char sinId[] = "sin";
constexpr auto sin = [](const operations::OperandsList &operands) {
  return std::sin(operands[0]->evaluate());
};

constexpr char cosId[] = "cos";
constexpr auto cos = [](const operations::OperandsList &operands) {
  return std::cos(operands[0]->evaluate());
};

constexpr char tanId[] = "tan";
constexpr auto tan = [](const operations::OperandsList &operands) {
  return std::tan(operands[0]->evaluate());
};

constexpr char asinId[] = "asin";
constexpr auto asin = [](const operations::OperandsList &operands) {
  return std::asin(operands[0]->evaluate());
};

constexpr char acosId[] = "acos";
constexpr auto acos = [](const operations::OperandsList &operands) {
  return std::acos(operands[0]->evaluate());
};

constexpr char atanId[] = "atan";
constexpr auto atan = [](const operations::OperandsList &operands) {
  return std::atan(operands[0]->evaluate());
};

constexpr char logId[] = "log";
constexpr auto log = [](const operations::OperandsList &operands) {
  return std::log(operands[0]->evaluate());
};

constexpr char sqrtId[] = "sqrt";
constexpr auto sqrt = [](const operations::OperandsList &operands) {
  return std::sqrt(operands[0]->evaluate());
};

constexpr char absId[] = "abs";
constexpr auto abs = [](const operations::OperandsList &operands) {
  return std::abs(operands[0]->evaluate());
};

constexpr char expId[] = "exp";
constexpr auto exp = [](const operations::OperandsList &operands) {
  return std::exp(operands[0]->evaluate());
};

constexpr char ceilId[] = "ceil";
constexpr auto ceil = [](const operations::OperandsList &operands) {
  return std::ceil(operands[0]->evaluate());
};

constexpr char floorId[] = "floor";
constexpr auto floor = [](const operations::OperandsList &operands) {
  return std::floor(operands[0]->evaluate());
};

constexpr char roundId[] = "round";
constexpr auto round = [](const operations::OperandsList &operands) {
  return std::round(operands[0]->evaluate());
};

constexpr char truncId[] = "trunc";
constexpr auto trunc = [](const operations::OperandsList &operands) {
  return std::trunc(operands[0]->evaluate());
};

constexpr char maxId[] = "max";
constexpr auto max = [](const operations::OperandsList &operands) {
  return std::max(operands[1]->evaluate(), operands[0]->evaluate());
};

constexpr char minId[] = "min";
constexpr auto min = [](const operations::OperandsList &operands) {
  return std::min(operands[1]->evaluate(), operands[0]->evaluate());
};

constexpr char hypotId[] = "hypot";
constexpr auto hypot = [](const operations::OperandsList &operands) {
  return std::hypot(operands[1]->evaluate(), operands[0]->evaluate());
};

constexpr char logicalAndId[] = "&&";
constexpr auto logicalAnd = [](const operations::OperandsList &operands) {
  auto x = operands[1]->evaluate();
  if (x == 0)
    return 0.0;
  return operands[0]->evaluate() == 0.0 ? 0.0 : 1.0;
};

constexpr char logicalOrId[] = "||";
constexpr auto logicalOr = [](const operations::OperandsList &operands) {
  auto x = operands[1]->evaluate();
  if (x != 0)
    return 1.0;
  return operands[0]->evaluate() != 0.0 ? 1.0 : 0.0;
};

constexpr char logicalNotId[] = "!";
constexpr auto logicalNot = [](const operations::OperandsList &operands) {
  return operands[0]->evaluate() == 0 ? 1.0 : 0.0;
};

// Add all operations to the DefaultContext
void InitializeDefaultContext() {
  using namespace operations;
  auto &dc = Context::getDefaultContext();

  // Operations
  dc.addOperation(std::make_shared<TemplateOperation<addId, 1, 2, add>>());
  dc.addOperation(
      std::make_shared<TemplateOperation<subtractId, 1, 2, subtract>>());
  dc.addOperation(
      std::make_shared<TemplateOperation<multiplyId, 2, 2, multiply>>());
  dc.addOperation(
      std::make_shared<TemplateOperation<divideId, 2, 2, divide>>());
  dc.addOperation(std::make_shared<TemplateOperation<powerId, 3, 2, power>>());
  dc.addOperation(
      std::make_shared<TemplateOperation<moduloId, 2, 2, modulo>>());
  // dc.addOperation(std::make_shared<TemplateOperation<negateId, 0, 1,
  // negate>>());
  dc.addOperation(std::make_shared<TemplateOperation<atan2Id, 4, 2, atan2>>());
  dc.addOperation(std::make_shared<TemplateOperation<sinId, 4, 1, sin>>());
  dc.addOperation(std::make_shared<TemplateOperation<cosId, 4, 1, cos>>());
  dc.addOperation(std::make_shared<TemplateOperation<tanId, 4, 1, tan>>());
  dc.addOperation(std::make_shared<TemplateOperation<asinId, 4, 1, asin>>());
  dc.addOperation(std::make_shared<TemplateOperation<acosId, 4, 1, acos>>());
  dc.addOperation(std::make_shared<TemplateOperation<atanId, 4, 1, atan>>());
  dc.addOperation(std::make_shared<TemplateOperation<logId, 4, 1, log>>());
  dc.addOperation(std::make_shared<TemplateOperation<sqrtId, 4, 1, sqrt>>());
  dc.addOperation(std::make_shared<TemplateOperation<absId, 4, 1, abs>>());
  dc.addOperation(std::make_shared<TemplateOperation<expId, 4, 1, exp>>());
  dc.addOperation(std::make_shared<TemplateOperation<ceilId, 4, 1, ceil>>());
  dc.addOperation(std::make_shared<TemplateOperation<floorId, 4, 1, floor>>());
  dc.addOperation(std::make_shared<TemplateOperation<roundId, 4, 1, round>>());
  dc.addOperation(std::make_shared<TemplateOperation<truncId, 4, 1, trunc>>());
  dc.addOperation(std::make_shared<TemplateOperation<maxId, 4, 2, max>>());
  dc.addOperation(std::make_shared<TemplateOperation<minId, 4, 2, min>>());
  dc.addOperation(std::make_shared<TemplateOperation<hypotId, 4, 2, hypot>>());
  dc.addOperation(
      std::make_shared<TemplateOperation<logicalAndId, -1, 2, logicalAnd>>());
  dc.addOperation(
      std::make_shared<TemplateOperation<logicalOrId, -1, 2, logicalOr>>());
  dc.addOperation(
      std::make_shared<TemplateOperation<logicalNotId, -1, 1, logicalNot>>());

  // Variables
  dc.setVariable("PI", 3.14159265358979323846);
  dc.setVariable("E", 2.71828182845904523536);
  dc.setVariable("PHI", 1.61803398874989484820);
  dc.setVariable("GAMMA", 0.57721566490153286060);
  dc.setVariable("DEG", 180.0 / 3.14159265358979323846);
  dc.setVariable("RAD", 3.14159265358979323846 / 180.0);
  dc.setVariable("INF", std::numeric_limits<double>::infinity());
  dc.setVariable("NAN", std::numeric_limits<double>::quiet_NaN());
  dc.setVariable("TRUE", 1);
  dc.setVariable("FALSE", 0);
  dc.setVariable("NULL", 0);
  dc.setVariable("EPSILON", std::numeric_limits<double>::epsilon());
}

// A função InitializeDefaultContext é chamada uma vez para inicializar
// DefaultContext
struct DefaultContextInitializer {
  DefaultContextInitializer() { InitializeDefaultContext(); }
} defaultContextInitializerInstance;

} // namespace expression_solver