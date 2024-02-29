
#include "Context.hpp"

namespace expression_solver {
// Initialize DefaultContext
Context Context::DefaultContext = Context();

// Add all operations to the DefaultContext
void InitializeDefaultContext() {
  using namespace operations;
  auto &dc = Context::getDefaultContext();

  // Operations
  dc.addOperation(std::make_shared<AddOperation>(nullptr, nullptr));
  dc.addOperation(std::make_shared<SubtractOperation>(nullptr, nullptr));
  dc.addOperation(std::make_shared<MultiplyOperation>(nullptr, nullptr));
  dc.addOperation(std::make_shared<DivideOperation>(nullptr, nullptr));
  dc.addOperation(std::make_shared<PowerOperation>(nullptr, nullptr));
  dc.addOperation(std::make_shared<ModuloOperation>(nullptr, nullptr));
  //dc.addOperation(std::make_shared<NegateOperation>(nullptr));
  dc.addOperation(std::make_shared<Atan2Operation>(nullptr, nullptr));
  dc.addOperation(std::make_shared<SinOperation>(nullptr));
  dc.addOperation(std::make_shared<CosOperation>(nullptr));
  dc.addOperation(std::make_shared<TanOperation>(nullptr));
  dc.addOperation(std::make_shared<AsinOperation>(nullptr));
  dc.addOperation(std::make_shared<AcosOperation>(nullptr));
  dc.addOperation(std::make_shared<AtanOperation>(nullptr));
  dc.addOperation(std::make_shared<LogOperation>(nullptr));
  dc.addOperation(std::make_shared<SqrtOperation>(nullptr));
  dc.addOperation(std::make_shared<AbsOperation>(nullptr));
  dc.addOperation(std::make_shared<ExpOperation>(nullptr));
  dc.addOperation(std::make_shared<CeilOperation>(nullptr));
  dc.addOperation(std::make_shared<FloorOperation>(nullptr));
  dc.addOperation(std::make_shared<RoundOperation>(nullptr));
  dc.addOperation(std::make_shared<TruncOperation>(nullptr));
  dc.addOperation(std::make_shared<MaxOperation>(nullptr, nullptr));
  dc.addOperation(std::make_shared<MinOperation>(nullptr, nullptr));
  dc.addOperation(std::make_shared<HypotOperation>(nullptr, nullptr));
  dc.addOperation(std::make_shared<LogicalAndOperation>(nullptr, nullptr));
  dc.addOperation(std::make_shared<LogicalOrOperation>(nullptr, nullptr));
  dc.addOperation(std::make_shared<LogicalNotOperation>(nullptr));
  dc.addOperation(std::make_shared<LogicalEqualOperation>(nullptr, nullptr));

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
  dc.setVariable("EPSILON", std::numeric_limits<double>::epsilon());}

// A função InitializeDefaultContext é chamada uma vez para inicializar
// DefaultContext
struct DefaultContextInitializer {
  DefaultContextInitializer() { InitializeDefaultContext(); }
} defaultContextInitializerInstance;

} // namespace expression_solver