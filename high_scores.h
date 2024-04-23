#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// Ask about name
string AskMe();

// Write new high score to the records table
int WriteInTable( string high_scores_filename, 
                   string user_name, 
                   int    attempts_count);
// Read the high score file and print all results
int ReadResults( string high_scores_filename );
