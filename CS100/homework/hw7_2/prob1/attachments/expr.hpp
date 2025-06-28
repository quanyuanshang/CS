#ifndef EXPR_HPP
#define EXPR_HPP

#include <memory>
#include <string>
#include <iomanip>
#include <sstream>
#include <utility>
class ExprNode
{
public:
  // FIXME: Make any of these functions virtual, or pure virtual, if necessary.
  ExprNode() = default;

  virtual double evaluate(double x) const = 0;

  virtual double derivative(double x) const = 0;

  virtual std::string toString() const = 0;

  ~ExprNode() = default;
};

class Expr
{
  std::shared_ptr<ExprNode> mNode;

  Expr(std::shared_ptr<ExprNode> ptr) : mNode{std::move(ptr)} {}

public:
  Expr(double value) : mNode{std::make_shared<Constant>(value)} {}
  auto toString() const { return mNode->toString(); }
  auto evaluate(double x) const { return mNode->evaluate(x); }
  auto derivative(double x) const { return mNode->derivative(x); }

  // TODO: Add member functions if necessary.

  static const Expr x;
  /*friend Expr operator-(const Expr &);
  friend Expr operator+(const Expr &);
  friend Expr operator+(const Expr &, const Expr &);
  friend Expr operator-(const Expr &, const Expr &);
  friend Expr operator*(const Expr &, const Expr &);
  friend Expr operator/(const Expr &, const Expr &);*/

  // TODO: Add friend declarations if necessary.
};

class Variable : public ExprNode
{
public:
  double evaluate(double x) const override { return x; }
  double derivative(double ) const override { return 1; }
  std::string toString() const override { return "x"; }

  // TODO: evaluate, derivative and toString ...
};

const Expr Expr::x{std::make_shared<Variable>()};

class Constant : public ExprNode
{
  double mValue;

public:
  explicit Constant(double value) : mValue{value} {}
  double evaluate(double ) const override { return mValue; }
  double derivative(double ) const override { return 0; }
  std::string toString() const override
  {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << mValue;
    return oss.str();
  }

  // TODO: evaluate, derivative and toString ...
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
  double evaluate(double x)const override{
    double value = mOperand.evaluate(x);
    return mOpKind == UnaryOpKind::UOK_Minus ? -value : value;
  }
  double derivative(double x) const override{
    double derivative=mOperand.derivative(x);
    return mOpKind == UnaryOpKind::UOK_Minus ? -derivative : derivative;
  }

  // TODO: evaluate, derivative and toString ...
};

class BinaryOperator : public ExprNode
{
protected:
  Expr mLeft;
  Expr mRight;

public:
  BinaryOperator(Expr left, Expr right)
      : mLeft{std::move(left)}, mRight{std::move(right)} {}
};

class PlusOp : public BinaryOperator
{
public:
  using BinaryOperator::BinaryOperator;
  

  // TODO: evaluate, derivative and toString ...
};

class MinusOp : public BinaryOperator
{
public:
  using BinaryOperator::BinaryOperator;

  // TODO: evaluate, derivative and toString ...
};

class MultiplyOp : public BinaryOperator
{
public:
  using BinaryOperator::BinaryOperator;

  // TODO: evaluate, derivative and toString ...
};

class DivideOp : public BinaryOperator
{
public:
  using BinaryOperator::BinaryOperator;

  // TODO: evaluate, derivative and toString ...
};

// TODO: Add functions if necessary.


#endif // EXPR_HPP