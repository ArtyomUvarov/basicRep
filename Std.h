#pragma once
#include "IStatistics.h"

class Std : public IStatistics {
public:
	Std() : m_vols(), m_std{ 0 }, mean{ 0 } {}
	void update( double next ) override { m_vols.push_back(next); }
	double eval() override;
	const char * name() const override { return "std"; }
  void SetMean( double me ){ mean = me;}

private:
	std::vector<double> m_vols;
	double m_std;
	double mean;
};