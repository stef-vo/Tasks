
// version 5.0
#include <boost/filesystem.hpp>
#include <thread>
#include <chrono>
//#include <vector>
//#include <algorithm>
//#include <cstdio>
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <cctype>

using namespace std::chrono;

// Counts the number of files with extensions from vector ext_vector
// in directory dir including subdirectories 
unsigned HowManyFiles(const std::string dir, const std::vector<std::string> ext_vector,
					  std::vector <std::string> & file_names)
{    
    unsigned files_counter = 0;
	for (unsigned i = 0; i < ext_vector.size(); i++)
	{
		std::string ext(ext_vector[i]);
		boost::filesystem::recursive_directory_iterator current(dir);  
		boost::filesystem::recursive_directory_iterator end;
		for (; current != end; current++)
			if (boost::filesystem::is_regular_file(current->status()) && ext.compare((*current).path().extension().string()) == 0)
			{
				files_counter++;
				file_names.push_back((*current).path().string());
			}
	}
	return files_counter;
}

/* Checks if str is blank. */
bool isBlank(const std::string str)
{
	int n = str.length();
	for (int i = 0; i < n; ++i)
		if (!isspace(str[i]))
			return false;
	return true;
}

/* Counts blank lines in file_str.*/
unsigned CountBlankLines(const std::string file_str)
{
    unsigned blank_lines = 0;
	std::ifstream file;
	file.open(file_str, std::ifstream::in);
	std::string line;
	while(getline(file, line))
	{
		if (isBlank(line))
			blank_lines++;
	}
	file.close();
	return blank_lines;
}

/* Counts lines in comments. */
unsigned CountCommentLines(const std::string file_str)
{
    unsigned comments = 0;
	std::ifstream file;
	file.open(file_str, std::ifstream::in);
	std::string line;
	bool in_multi_line_comment = false;
	while(getline(file, line))
	{
		if (!in_multi_line_comment && line.find("/*") != std::string::npos)
        in_multi_line_comment = true;

		if (in_multi_line_comment || line.find("//") != std::string::npos)
        comments++;

		if (in_multi_line_comment && line.find("*/") != std::string::npos)
        in_multi_line_comment = false;
	}
	file.close();
	return comments;
}

/* Counts all the lines in file_str. */
unsigned CountAllLines(const std::string file_str)
{
    unsigned lines = 0;
	std::ifstream file;
	file.open(file_str, std::ifstream::in);
	std::string line;
	while(getline(file, line))
	{
		lines++;
	}
	file.close();
	return lines;
}

/* Counts code lines in file_str. */
unsigned CountCodeLines(const std::string file_str)
{
    return CountAllLines(file_str) - CountCommentLines(file_str) - CountBlankLines(file_str);
}

/* Gets information on file_str. */
void GetFileInfo(const std::string file_str, unsigned& all_lines, unsigned& code_lines,
					 unsigned& blank_lines, unsigned& comment_lines)
{
    all_lines = CountAllLines(file_str);
	code_lines = CountCodeLines(file_str);
	blank_lines = CountBlankLines(file_str);
	comment_lines = CountCommentLines(file_str);
}

int main()
{   
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	std::vector<std::string> ext_vector;
	std::vector<std::string>::iterator it;
	ext_vector.push_back(".c");
	ext_vector.push_back(".cpp");
	ext_vector.push_back(".h");
	ext_vector.push_back(".hpp");

	std::cout << "Extensions:\n";
	for (it = ext_vector.begin(); it<ext_vector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << "\n\n";

    std::cout << "Files with these extensions found: ";
	std::string dir("E:\\Root");
	std::vector <std::string> file_names;
	int n = HowManyFiles(dir, ext_vector, file_names);
	std::cout << n;
	std::cout << "\n\n";

	std::cout << "Files found: \n";
	for (int i = 0; i < n; ++i)
		std::cout << file_names[i] << "\n";
	std::cout << "\n\n";



	std::string file_name("E:\\Root\\file.cpp");
	
	std::cout << "The number of blank lines in " << file_name << " is: ";
	std::cout << CountBlankLines(file_name);
	std::cout << "\n\n";

	std::cout << "The number of comment lines in " << file_name << " is: ";
	std::cout << CountCommentLines(file_name);
	std::cout << "\n\n";

	std::cout << "Total number of lines in " << file_name << " is: ";
	std::cout << CountAllLines(file_name);
	std::cout << "\n\n";


	std::cout << "Code lines in " << file_name << " are: ";
	std::cout << CountCodeLines(file_name);
	std::cout << "\n\n";

	//static const int num_threads = 3;
	//unsigned num_cycles = n % num_threads;

	unsigned all_lines;
	unsigned code_lines;
	unsigned blank_lines;
	unsigned comment_lines;

	unsigned total_lines = 0;
	unsigned total_code_lines = 0;
	unsigned total_blank_lines = 0;
	unsigned total_comment_lines = 0;

	for (int i = 0; i < 5; i++)
	{
		std::thread *tt = new std::thread[3];
		for (int j = 0; j < 3; j++)
		{
			all_lines = CountAllLines(file_names[3 * i + j]);
			code_lines = CountCodeLines(file_names[3 * i + j]);
			blank_lines = CountBlankLines(file_names[3 * i + j]);
			comment_lines = CountCommentLines(file_names[3 * i + j]);
			
			total_lines += all_lines;
			total_code_lines += code_lines;
			total_blank_lines += blank_lines;
			total_comment_lines += comment_lines;
			
			tt[j] = std::thread(GetFileInfo, std::ref(file_names[3 * i + j]),
				std::ref(all_lines), std::ref(code_lines),
				std::ref(blank_lines), std::ref(comment_lines));
		}

		tt[0].join();
		tt[1].join();
		tt[2].join();
		delete[] tt;

	}

	std::ofstream output_file;
	output_file.open("E:\\info.txt");
	if (output_file.is_open())
	{
		output_file << "Total files: " << n << "\n";
		output_file << "Total lines: " << total_lines << "\n";
		output_file << "Total code lines: " << total_code_lines << "\n";
		output_file << "Total blank lines: " << total_blank_lines << "\n";
		output_file << "Total comment lines: " << total_comment_lines << "\n";
		output_file.close();
	}
	


	

	



	high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();

    std::cout << duration << " milliseconds\n\n";


	return 0;
}

