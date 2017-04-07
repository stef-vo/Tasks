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

	std::cout << "The task is to print info about all the files\n";
	std::cout << "with the extensions ";
	for (it = ext_vector.begin(); it<ext_vector.end(); it++)
		std::cout << ' ' << *it;
	//std::cout << "\n";

	std::string dir("E:\\Boost\\boost_1_52_0\\boost\\asio"); // path to the root directory may be changed as you wish
	std::queue <std::string> file_names; // vector of file names with given extensions
	std::cout << "\n" << "in directory " << dir << "\n\n";
	std::cout << "Wait a little!" << "\n\n";
	unsigned num_files;
	CreateQueue(dir, ext_vector, file_names, num_files);
	
	unsigned total_lines;
	unsigned total_code_lines;
	unsigned total_blank_lines;
	unsigned total_comment_lines;

	GetResult(file_names, total_lines, total_code_lines, total_blank_lines, total_comment_lines);

	PrintResult(num_files, total_lines, total_code_lines, total_blank_lines, total_comment_lines);
	
	unsigned num_threads = std::thread::hardware_concurrency();

		std::thread *tt = new std::thread[num_threads];
		for (unsigned j = 0; j < num_threads; ++j)
		{
			tt[j] = std::thread(GetResult, std::ref(file_names), std::ref(total_lines),
				std::ref(total_code_lines), std::ref(total_blank_lines),
				std::ref(total_comment_lines));
		}

		for (unsigned j = 0; j < num_threads; ++j)
			tt[j].join();
		
		delete[] tt;
	
	std::cout << "\nIt took the program ";
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
	std::cout << duration << " milliseconds to run with " << num_threads << " threads";
	std::cout << "\n\n";

	return 0;
}