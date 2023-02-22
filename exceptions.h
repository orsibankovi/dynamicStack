#include <exception>

class UnderFlowException : public std::exception
{
public:
	const char *what() const throw() { return "Nincsen egyetlen elem sem!"; }
};
