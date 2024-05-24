#pragma once
#include "IStatistics.h"

class Mean : public IStatistics {
public:
	Mean() : m_mean{ 0 }, m_sum{ 0 },count{ 0 } {}
	void update( double next ) override;
	double eval() override { return m_mean; }
	const char* name() const override { return "mean"; }

private:
	double m_mean;
	double m_sum;
	size_t count;
};