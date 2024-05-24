#pragma once
#include "IStatistics.h"

class Max : public IStatistics {
public:
	Max() : m_max{ std::numeric_limits<double>::min() } {}
	void update( double next ) override;
	double eval() override { return m_max; }
	const char* name() const override { return "max"; }

private:
	double m_max;
};