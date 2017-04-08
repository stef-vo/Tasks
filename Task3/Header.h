#pragma once

#include <boost/filesystem.hpp>
#include <thread>
#include <queue>
#include <mutex>

void CreateQueue(std::string dir, std::vector<std::string> ext_vector,
				std::queue <std::string> & Tasks, unsigned & total_files);

bool IsBlank(const std::string & str);

void CountLines(std::fstream & file, unsigned & lines, unsigned & code_lines,
				unsigned & blank_lines, unsigned & comment_lines);

void GetResult(std::queue <std::string> & Tasks, unsigned & total_lines,
				unsigned & total_code_lines, unsigned & total_blank_lines,
				unsigned & total_comment_lines);

void PrintResult(const unsigned & total_files, const unsigned & total_lines,
				 const unsigned & total_code_lines, const unsigned & total_blank_lines,
				 const unsigned & total_comment_lines, long long duration, unsigned num_threads);


