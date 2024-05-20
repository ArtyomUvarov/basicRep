#include <iostream>
#include <limits>
#include <vector>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
	virtual void CalculateEval(double mean){}; // ¬ычисл€ет статистическую характеристику (нужен не дл€ всех наследников)
	        int GetCount(){ return count; } // „исло обращений к методу update()
					void AddCount(){ count++; } 
private:
	int count = 0;
};


class Min : public IStatistics {
public:
	Min() : m_min{ std::numeric_limits<double>::min() } {}

	void update(double next) override {	
		if  ( GetCount() == 0 )
			m_min = next;
		else if ( next < m_min ) 
			m_min = next;
		AddCount();
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};


class Max : public IStatistics {
public:
	Max() : m_max{ std::numeric_limits<double>::max() } {}

	void update(double next) override {
		if ( GetCount() == 0 )
			m_max = next;
		else if ( next > m_max )
			m_max = next;
		AddCount();
	}

	double eval() const override {
		return m_max;
	}

	const char* name() const override {
		return "max";
	}

private:
	double m_max;
};


class Mean : public IStatistics {
public:
	Mean() : m_mean{ 0 }, m_sum{ 0 } {}

	void update(double next) override {
		int count = GetCount();
		if ( count == 0 ) { 
			m_sum = next;
			m_mean = m_sum;
		}
		else {
			m_sum += next;
			m_mean = m_sum / double( count + 1 );
		}
		AddCount();
	}

	double eval() const override {
		return m_mean;
	}

	const char* name() const override {
		return "mean";
	}

private:
	double m_mean;
	double m_sum;
};

class Std : public IStatistics {
public:
	Std() : m_vols(), m_std{ 0 } {}

	void update(double next) override {
		m_vols.push_back( next );
	}

	double eval() const override {	
		return m_std;
	}

	const char* name() const override {
		return "std";
	}
	void CalculateEval( double mean ) override { 
		size_t size = m_vols.size();
		double m_step_sum = 0;
	  for ( size_t i = 0; i < size; ++i ) 
		  m_step_sum += pow( m_vols[i] - mean, 2 );
		m_std = sqrt( m_step_sum / double(size) );
		
	}

private:
	std::vector<double> m_vols;
	double m_std;
};

int main() {

	const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
  statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};
	double val = 0;
	while (std::cin >> val) {
		for ( size_t i = 0; i < statistics_count; ++i ) {
			statistics[i]->update(val);
		}
	}
	if ( statistics_count > 1 )
	statistics[statistics_count-1]->CalculateEval( statistics[statistics_count - 2]->eval() );
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