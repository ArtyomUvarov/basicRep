#include "Max.h"

void Max::update( double next ) {	
	if ( next > m_max )
		m_max = next;
}