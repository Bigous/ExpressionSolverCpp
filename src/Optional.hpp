#pragma once

namespace expression_solver {
template <typename T> class Optional {
  T m_value;
  bool hasValue;

public:
  Optional() : hasValue(false) {}
  Optional(T value) : m_value(value), hasValue(true) {}
  bool has_value() const { return hasValue; }
  T &value() const { return m_value; }
};
} // namespace expression_solver