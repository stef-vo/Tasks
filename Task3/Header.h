#ifndef _HEADER_H_
#define _HEADER_H_
#include <boost/filesystem.hpp>
#include <thread>
#include <chrono>

unsigned HowManyFiles(const std::string dir, const std::vector<std::string> ext_vector,
					  std::vector <std::string> & file_names);

bool isBlank(const std::string str);

unsigned CountBlankLines(const std::string file_str);

unsigned CountCommentLines(const std::string file_str);

unsigned CountAllLines(const std::string file_str);

unsigned CountCodeLines(const std::string file_str);

void GetFileInfo(const std::string file_str, unsigned& all_lines, unsigned& code_lines,
					 unsigned& blank_lines, unsigned& comment_lines);
#endif