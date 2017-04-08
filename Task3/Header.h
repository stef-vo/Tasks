#pragma once

#include <boost/filesystem.hpp>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>

void CreateQueue(std::string dir, std::vector<std::string> ext_vector,
				std::queue <std::string> & tasks, unsigned & total_files);

bool IsBlank(const std::string & str);

void CountLines(std::fstream & file, unsigned & lines, unsigned & code_lines,
				unsigned & blank_lines, unsigned & comment_lines);

void GetResult(std::queue <std::string> & tasks, std::atomic<unsigned> & total_lines,
				std::atomic<unsigned> & total_code_lines, std::atomic<unsigned> & total_blank_lines,
				std::atomic<unsigned> & total_comment_lines);

void PrintResult(const unsigned & total_files, const std::atomic<unsigned> & total_lines,
				 const std::atomic<unsigned> & total_code_lines, const std::atomic<unsigned> & total_blank_lines,
				 const std::atomic<unsigned> & total_comment_lines, long long duration, unsigned num_threads);


