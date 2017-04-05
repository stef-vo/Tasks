#pragma once

#include <boost/filesystem.hpp>
#include <thread>
#include <chrono>

// Counts files 
int CountFiles(std::string dir, std::vector<std::string> ext_vector, std::vector <std::string> & file_names);

/* Checks if str is blank. */
bool IsBlank(const std::string str);

/* Counts lines in file_str. */
void CountLines(std::string file_str, int & blank_lines, int & comment_lines, int & code_lines, int & all_lines);