#include "Mean.h"

void Mean::update( double next ) {
	if ( count == 0 ) {
		m_sum = next;
		m_mean = m_sum;
	}
	else {
		m_sum += next;
		m_mean = m_sum / double( count + 1 );
	}
	count++;
}