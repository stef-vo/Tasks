#include "Header.h"

using namespace std::chrono;

int main()
{   
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	// Create vector of extensions
	std::vector<std::string> ext_vector;
	std::vector<std::string>::iterator it;
	ext_vector.push_back(".c");
	ext_vector.push_back(".cpp");
	ext_vector.push_back(".h");
	ext_vector.push_back(".hpp");

	std::string dir("E:\\Boost\\boost_1_52_0"); // path to the root directory may be changed if you like
	std::cout << "Looking for files with extensions";
	for (it = ext_vector.begin(); it<ext_vector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " in directory " << dir << "." << "\n\n";

	std::vector <std::string> file_names; // vector of file names with given extensions
	std::cout << "Files in " << dir << " with these extensions found: ";
	int total_num_files = CountFiles(dir, ext_vector, file_names);
	std::cout << total_num_files;
	std::cout << "\n\n";

	//std::string file_name("E:\\Root\\file.cpp"); // display info about one file
	
	int blank_lines;
	int comment_lines;
	int code_lines;
	int all_lines;
		
	const int num_threads = 4; // number of threads (may be changed as you wish)
	int num_cycles = total_num_files % num_threads; // so we have num_threads threads in every cycle

	// announce and initialize variables for all the files in root directory
	int total_lines = 0;
	int total_code_lines = 0;
	int total_blank_lines = 0;
	int total_comment_lines = 0;

	// creating threads
	for (int i = 0; i < num_cycles; ++i)
	{
		std::thread *tt = new std::thread[num_threads];
		for (int j = 0; j < num_threads; ++j)
		{
			tt[j] = std::thread(CountLines, file_names[num_threads * i + j],
				std::ref(blank_lines), std::ref(comment_lines), 
				std::ref(code_lines), std::ref(all_lines));

			total_lines += all_lines;
			total_code_lines += code_lines;
			total_blank_lines += blank_lines;
			total_comment_lines += comment_lines;
		}

		for (int j = 0; j < num_threads; ++j)
			tt[j].join();
		
		delete[] tt;
	}

	// still (total_num_files - num_cycles * num_threads) files left
	for (int j = num_cycles * num_threads; j < total_num_files; j++)
	{
		CountLines(file_names[j], blank_lines, comment_lines, code_lines, all_lines);
		
		total_lines += all_lines;
		total_code_lines += code_lines;
		total_blank_lines += blank_lines;
		total_comment_lines += comment_lines;
	}
			
	// display output
	std::cout << "Display information on root directory " << dir << "\n\n";
	std::cout << "Total files:           " << total_num_files << "\n";
	std::cout << "Total blank lines:    " << total_blank_lines << "\n";
	std::cout << "Total comment lines:  " << total_comment_lines << "\n";
	std::cout << "Total code lines:    " << total_code_lines << "\n";
	std::cout << "Total lines:         " << total_lines << "\n\n";
		
	std::cout << "It took ";
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
	std::cout << duration << " milliseconds to run this program with " << num_threads << " threads";
	std::cout << "\n\n";

	// output to the file E:\\info.txt; you can change file path if you like
	std::ofstream output_file;
	output_file.open("E:\\info.txt");
	if (output_file.is_open())
	{
		output_file << "Root directory " << dir << "\n\n";
		output_file << "Total files:           " << total_num_files << "\n";
		output_file << "Total blank lines:    " << total_blank_lines << "\n";
		output_file << "Total comment lines:  " << total_comment_lines << "\n";
		output_file << "Total code lines:    " << total_code_lines << "\n";
		output_file << "Total lines:         " << total_lines << "\n\n";
		output_file << "It took " << duration / 1000 <<
			" seconds to run this program with " << num_threads << " threads"; 
		output_file.close();
	}
	else
	{
		std::cout << "Impossible to open output file.";
		return 1;
	}
	
	// it's all folks
	return 0;
}

