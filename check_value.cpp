#include <iostream>
#include "random_value.h"
#include "high_scores.h"

int main() {
	const string high_scores_filename = "high_scores.txt";
	string user_name = AskMe();
	const int target_value = random();
	int current_value = 0;
	int    attempts_count = 1;
	bool not_win = true;

	cout << "Enter your guess:" << std::endl;

	do {
		cin >> current_value;

		if (current_value < target_value) {
			cout << "less than " << current_value << endl;
			attempts_count++;
		}
		else if (current_value > target_value) {
			cout << "greater than " << current_value << endl;
			attempts_count++;
		}
		else {
			cout << "you win!" <<" attemps = "<< attempts_count << endl;
			WriteInTable( high_scores_filename, user_name, attempts_count );
			ReadResults( high_scores_filename );
			break;
		}

	} while(true);

	return 0;
}