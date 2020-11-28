#include"pch.h"
#include <iostream>

template<class T>
class Formula
{
public:
	virtual ~Formula() = default;

	std::ostream& print(std::ostream& out = std::cout) const
	{
		return doPrint(out);
	}

	T value() const
	{
		return doValue();
	}

	friend std::ostream& operator<<(std::ostream& out, const Formula& n)
	{
		return n.print(out);
	}

	Formula* clone() const
	{
		return doClone();
	}

	static Formula* parseRPN(std::ostream& in = std::cin);
private:
	virtual std::ostream& doPrint(std::ostream& out) const = 0;
	virtual T doValue() const = 0;
	virtual Formula* doClone() const = 0;
};

template<class T>
class Constant : public Formula<T>
{
public:
	Constant(const T& _literal) :
		m_literal{ _literal }
	{}
private:
	T m_literal;

	std::ostream& doPrint(std::ostream& out) const override
	{
		return out << m_literal;
	}

	T doValue() const override
	{
		return m_literal;
	}

	Constant* doClone() const override
	{
		return new Constant(*this);
	}
};

template<class T>
class Operation : public Formula<T>
{
private:
	char op;
	Formula<T>* left;
	Formula<T>* right;
	Operation* doClone() const override
	{
		return new Operation(*this);
	}

	void copy(const Operation& other)
	{
		op = other.op;
		left = other.left->clone();
		right = other.right->clone();
	}

	void del()
	{
		delete left;
		delete right;
	}

	virtual std::ostream& doPrint(std::ostream& out) const override
	{
		out << "( ";
		left->print(out);
		out << " " << op << " ";
		right->print(out);
		out << " )";
	}

	T doValue() const
	{
		T leftValue = left->value();
		T rightValue = right->value();
		switch (op)
		{
		case '+':
			return leftValue + rightValue;
		case '-':
			return leftValue - rightValue;
		case '*':
			return leftValue * rightValue;
		case '/':
			//TODO handle division by 0
			return leftValue / rightValue;
		default:
			//TODO handle error
			return 0;
		}
	}
public:
	Operation(char _op, const Formula<T>& _left, const Formula<T>& _right) :
		op(_op), left(_left.clone()), right(_right.clone()) {}

	Operation(const Operation& other)
	{
		copy(other);
	}
	Operation& operator=(const Operation& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
	~Operation()
	{
		del();
	}
};

template< class T>
Operation<T> operator+(const Formula<T>& lhs, const Formula<T>& rhs)
{
	return Operation<T>('+', lhs, rhs);
}
template< class T>
Operation<T> operator-(const Formula<T>& lhs, const Formula<T>& rhs)
{
	return Operation<T>('-', lhs, rhs);
}
template< class T>
Operation<T> operator*(const Formula<T>& lhs, const Formula<T>& rhs)
{
	return Operation<T>('*', lhs, rhs);
}
template< class T>
Operation<T> operator/(const Formula<T>& lhs, const Formula<T>& rhs)
{
	return Operation<T>('/', lhs, rhs);
}
template<class T>
Formula<T>* Formula<T>::parseRPN(std::istream& in)
{
	// TODO
}

int main()
{
	Constant<int> one(1);
	Constant<int> two(2);

	Operation<int> plus('+', one, two);
	return 0;
}
