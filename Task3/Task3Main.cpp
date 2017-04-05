///
/// To test the code 
/// make sure that you have E:\\Root as a root directory
/// and there is a file "file.cpp" in the root directory or one of it's subdirectories.
/// The info will be saved in info.txt on disk E:
///

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

	std::cout << "Find files with extensions:\n";
	for (it = ext_vector.begin(); it<ext_vector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << "\n\n";

    std::string dir("E:\\Root"); // path to the root directory may be changed as you wish
	std::vector <std::string> file_names; // vector of file names with given extensions
	std::cout << "Files in " << dir << " with these extensions found: ";
	int n = HowManyFiles(dir, ext_vector, file_names);
	std::cout << n; // n is a total number of files found
	std::cout << "\n\n";

	std::cout << "Files found: \n";
	for (int i = 0; i < n; ++i)
		std::cout << file_names[i] << "\n";
	std::cout << "\n";
	
	std::string file_name("E:\\Root\\file.cpp"); // display info about one file
	
	std::cout << "The number of blank lines in " << file_name << " is:     ";
	std::cout << CountBlankLines(file_name);
	std::cout << "\n";

	std::cout << "The number of comment lines in " << file_name << " is:   ";
	std::cout << CountCommentLines(file_name);
	std::cout << "\n";

	std::cout << "Total number of lines in " << file_name << " is:        ";
	std::cout << CountAllLines(file_name);
	std::cout << "\n";

	std::cout << "The number of code lines in " << file_name << " is:     ";
	std::cout << CountCodeLines(file_name);
	std::cout << "\n\n";

	const int num_threads = 4; // number of threads (may be changed as you wish)
	int num_cycles = n % num_threads; // so we have num_threads threads in every cycle

	// announce variables for one file
	unsigned all_lines;
	unsigned code_lines;
	unsigned blank_lines;
	unsigned comment_lines;

	// announce and initialize variables for all the files in root directory
	unsigned total_lines = 0;
	unsigned total_code_lines = 0;
	unsigned total_blank_lines = 0;
	unsigned total_comment_lines = 0;

	// creating threads
	for (int i = 0; i < num_cycles; ++i)
	{
		std::thread *tt = new std::thread[num_threads];
		for (int j = 0; j < num_threads; ++j)
		{
			all_lines = CountAllLines(file_names[num_threads * i + j]);
			code_lines = CountCodeLines(file_names[num_threads * i + j]);
			blank_lines = CountBlankLines(file_names[num_threads * i + j]);
			comment_lines = CountCommentLines(file_names[num_threads * i + j]);
			
			total_lines += all_lines;
			total_code_lines += code_lines;
			total_blank_lines += blank_lines;
			total_comment_lines += comment_lines;
			
			tt[j] = std::thread(GetFileInfo, std::ref(file_names[num_threads * i + j]),
				std::ref(all_lines), std::ref(code_lines),
				std::ref(blank_lines), std::ref(comment_lines));
		}

		for (int j = 0; j < num_threads; ++j)
			tt[j].join();
		
		delete[] tt;
	}

	// still (n - num_cycles * num_threads) files left
	for (int j = num_cycles * num_threads; j < n; j++)
	{
		all_lines = CountAllLines(file_names[j]);
		code_lines = CountCodeLines(file_names[j]);
		blank_lines = CountBlankLines(file_names[j]);
		comment_lines = CountCommentLines(file_names[j]);
			
		total_lines += all_lines;
		total_code_lines += code_lines;
		total_blank_lines += blank_lines;
		total_comment_lines += comment_lines;
	}

	// display output
	std::cout << "Display information on root directory" << "\n\n";
	std::cout << "Total files:          " << n << "\n";
	std::cout << "Total lines:         " << total_lines << "\n";
	std::cout << "Total code lines:    " << total_code_lines << "\n";
	std::cout << "Total blank lines:    " << total_blank_lines << "\n";
	std::cout << "Total comment lines: " << total_comment_lines << "\n\n";
	
	// output to the file E:\\info.txt; you can change file path as you wish
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
	
	std::cout << "It took ";
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
	std::cout << duration << " milliseconds to run this program with " << num_threads << " threads";
	std::cout << "\n\n";
	
	// it's all folks
	return 0;
}

