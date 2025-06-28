#ifndef EXPR_HPP
#define EXPR_HPP

#include <memory>
#include <string>
#include <sstream>
#include <utility>
  #include <iomanip>
class ExprNode
{
public:
  // Done: Make any of these functions virtual, or pure virtual, if necessary.
  ExprNode() = default;

  virtual double evaluate(double x) const = 0;

  virtual double derivative(double x) const = 0;

  virtual std::string toString() const = 0;

  virtual ~ExprNode() = default;
};

class Expr
{
  std::shared_ptr<ExprNode> mNode;

  Expr(std::shared_ptr<ExprNode> ptr) : mNode{std::move(ptr)} {}

public:
  Expr(double value);

  // DONE: Add member functions if necessary.

  static const Expr x;

  auto toString() const { return mNode->toString(); }
  auto evaluate(double x) const { return mNode->evaluate(x); }
  auto derivative(double x) const { return mNode->derivative(x); }

  // DONE: Add friend declarations if necessary.
  friend Expr operator-(const Expr &);
  friend Expr operator+(const Expr &);
  friend Expr operator-(const Expr &, const Expr &);
  friend Expr operator+(const Expr &, const Expr &);
  friend Expr operator*(const Expr &, const Expr &);
  friend Expr operator/(const Expr &, const Expr &);
};

class Variable : public ExprNode
{
public:
  // DONE: evaluate, derivative and toString ...
  double evaluate(double x) const override { return x; };
  double derivative(double) const override { return 1; };
  std::string toString() const override { return "x"; };
};

const Expr Expr::x{std::make_shared<Variable>()};

class Constant : public ExprNode
{
  double mValue;

public:
  explicit Constant(double value) : mValue{value} {}

  // DONE: evaluate, derivative and toString ...

  double evaluate(double) const override { return mValue; };
  double derivative(double) const override { return 0; };
  std::string toString() const override
  {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << mValue;
    return oss.str();
  };
};

Expr::Expr(double value) : mNode{std::make_shared<Constant>(value)} {}

enum class UnaryOpKind
{
  UOK_Plus,
  UOK_Minus
};

class UnaryOperator : public ExprNode
{
  UnaryOpKind mOpKind;
  Expr mOperand;

public:
  UnaryOperator(UnaryOpKind op, Expr operand) : mOpKind{op}, mOperand{std::move(operand)} {}

  double evaluate(double x) const override
  {
    double value = mOperand.evaluate(x);
    return mOpKind == UnaryOpKind::UOK_Minus ? -value : value;
  };
  double derivative(double x) const override
  {
    double value = mOperand.derivative(x);
    return mOpKind == UnaryOpKind::UOK_Minus ? -value : value;
  };
  std::string toString() const override
  {
    return mOpKind == UnaryOpKind::UOK_Minus ? "-(" + mOperand.toString() + ")" : mOperand.toString();
  };
};

class BinaryOperator : public ExprNode
{
protected:
  Expr mLeft;
  Expr mRight;

public:
  BinaryOperator(Expr left, Expr right)
      : mLeft{std::move(left)}, mRight{std::move(right)} {} // 默认构造函数够用
};

class PlusOp : public BinaryOperator
{
public:
  using BinaryOperator::BinaryOperator;

  // DONE: evaluate, derivative and toString ...
  double evaluate(double x) const override
  {
    return mLeft.evaluate(x) + mRight.evaluate(x);
  }
  double derivative(double x) const override
  {
    return mLeft.derivative(x) + mRight.derivative(x);
  }
  std::string toString() const override
  {
    return "(" + mLeft.toString() + ") + (" + mRight.toString() + ")";
  }
};

class MinusOp : public BinaryOperator
{
public:
  using BinaryOperator::BinaryOperator;

  // DONE: evaluate, derivative and toString ...
  double evaluate(double x) const override
  {
    return mLeft.evaluate(x) - mRight.evaluate(x);
  }
  double derivative(double x) const override
  {
    return mLeft.derivative(x) - mRight.derivative(x);
  }
  std::string toString() const override
  {
    return "(" + mLeft.toString() + ") - (" + mRight.toString() + ")";
  }
};

class MultiplyOp : public BinaryOperator
{
public:
  using BinaryOperator::BinaryOperator;

  // DONE: evaluate, derivative and toString ...
  double evaluate(double x) const override
  {
    return mLeft.evaluate(x) * mRight.evaluate(x);
  }
  double derivative(double x) const override
  {
    return mLeft.derivative(x) * mRight.evaluate(x) + mLeft.evaluate(x) * mRight.derivative(x);
  }
  std::string toString() const override
  {
    return "(" + mLeft.toString() + ") * (" + mRight.toString() + ")";
  }
};

class DivideOp : public BinaryOperator
{
public:
  using BinaryOperator::BinaryOperator;

  // TODO: evaluate, derivative and toString ...
  double evaluate(double x) const override
  {
    return mLeft.evaluate(x) / mRight.evaluate(x);
  }
  double derivative(double x) const override
  {

    return (mLeft.derivative(x) * mRight.evaluate(x) - mLeft.evaluate(x) * mRight.derivative(x)) / (mRight.evaluate(x) * mRight.evaluate(x));
  }
  std::string toString() const override
  {
    return "(" + mLeft.toString() + ") / (" + mRight.toString() + ")";
  }
};
/*Expr operator-(const Expr &operand)
{
  return {std::make_shared<UnaryOperator>(UnaryOpKind::UOK_Minus, operand)};
};
Expr operator-(const Expr &lhs, const Expr &rhs)
{
  return {std::make_shared<MinusOp>(lhs, rhs)};
}
Expr operator+(const Expr &lhs, const Expr &rhs)
{
  return {std::make_shared<PlusOp>(lhs, rhs)};
};
Expr operator+(const Expr &operand)
{
  return {std::make_shared<UnaryOperator>(UnaryOpKind::UOK_Plus, operand)};
};
Expr operator*(const Expr &lhs, const Expr &rhs)
{
  return {std::make_shared<MultiplyOp>(lhs, rhs)};
};
Expr operator/(const Expr &lhs, const Expr &rhs)
{
  return {std::make_shared<DivideOp>(lhs, rhs)};
};
// TODO: Add functions if necessary.

#endif // EXPR_HPP