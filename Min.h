#pragma once
#include "IStatistics.h"

class Min : public IStatistics {
public:
	Min() : m_min{ std::numeric_limits<double>::max() } {}
	void update( double next ) override;
	double eval() override { return m_min;}
	const char* name() const override { return "min";}

private:
	double m_min;
};