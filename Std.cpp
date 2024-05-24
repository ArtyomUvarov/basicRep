#include"Std.h"

double Std::eval() {
	size_t size = m_vols.size();
	double m_step_sum = 0;

	for ( size_t i = 0; i < size; ++i )
		m_step_sum += pow( m_vols[i] - mean, 2 );

	if ( size > 0 )
	  m_std = sqrt( m_step_sum / double(size) );

	return m_std;

}