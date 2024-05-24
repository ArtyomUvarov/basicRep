
#include "Min.h"
#include "Max.h"
#include "Mean.h"
#include "Std.h"

int main() {

	const size_t statistics_count = 4;
	IStatistics * statistics[statistics_count] = { new Min(), new Max(), new Mean(), new Std() };
	double val = 0;
	while (std::cin >> val) {
		for ( size_t i = 0; i < statistics_count; ++i ) {
			statistics[i]->update(val);
		}
	}
	if ( statistics_count > 1 )
	static_cast<Std *>( statistics[statistics_count-1] )->SetMean( statistics[statistics_count - 2]->eval() );
	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}