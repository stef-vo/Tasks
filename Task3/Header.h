#pragma once

#include <boost/filesystem.hpp>
#include <thread>
#include <queue>
#include <mutex>

/* Creates queue of files Tasks with extensions ext_vector in directory dir. */
void CreateQueue(std::string dir, std::vector<std::string> ext_vector,
					  std::queue <std::string> & Tasks, unsigned & total_files);

/* Checks if str is blank. */
bool IsBlank(const std::string & str);

/* Counts lines in file. */
void CountLines(std::fstream & file, unsigned & lines, unsigned & code_lines,
	unsigned & blank_lines, unsigned & comment_lines);


/* Gets files from the queue. */
void GetResult(std::queue <std::string> & Tasks, unsigned & total_lines,
	unsigned & total_code_lines, unsigned & total_blank_lines,
	unsigned & total_comment_lines);


// Prints files info
void PrintResult(unsigned & total_files, unsigned & total_lines, unsigned & total_code_lines,
	unsigned & total_blank_lines, unsigned & total_comment_lines);


