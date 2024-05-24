#pragma once
#include <iostream>
#include <limits>
#include <vector>

class IStatistics {
public:
	virtual ~IStatistics() {}
	virtual void update( double next ) = 0;
	virtual double eval() = 0;
	virtual const char* name() const = 0;
};