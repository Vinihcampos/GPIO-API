#include <iostream>
#include <fstream> // std::fstream
#include <string>  // std::string
#include <sstream> // std::stringstream
#include <vector>  // std::vector
#include <utility> // std::pair
#include <thread>  // std::this_thread::sleep_for
#include <chrono>  // std::chrono::seconds
#include <iomanip> // std::setprecision

// Struct to save informations about cpu
struct CpuInfo{
	std::string cpu;
	double active;
	double total;

	CpuInfo(std::string _cpu) : cpu{_cpu}, active{0}, total{0}{}
};

int check_cpu_usage(int sleep_time){

	// Defining path file
	std::string path = "/proc/stat";
	std::string input, cpu;
	double usage;
	std::ifstream cpu_status_file;
	std::stringstream ss;

	cpu_status_file.open(path, std::ifstream::in);
	cpu = ""; usage = 0;

	// Reading /proc/stat file 
	getline(cpu_status_file, input);
	ss << input;
	ss >> cpu;
	
	// Storing prev use of each cpu
	CpuInfo prev_cpu_usage = CpuInfo("Total");
	for(int i = 0; i < 4; ++i){
		ss >> usage;
		if(i < 3) prev_cpu_usage.active += usage;
		else prev_cpu_usage.total = prev_cpu_usage.active + usage;
	}
	ss.str(std::string());
	ss.clear();
	cpu_status_file.close();

	// Sleeping
	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));

	cpu_status_file.open(path, std::ifstream::in);
	cpu = ""; usage = 0;

	// Reading /proc/stat file again
	getline(cpu_status_file, input);
	ss << input;
	ss >> cpu;
	
	// Storing curr use of each cpu
	CpuInfo curr_cpu_usage = CpuInfo("Total");
	for(int i = 0; i < 4; ++i){
		ss >> usage;
		if(i < 3) curr_cpu_usage.active += usage;
		else curr_cpu_usage.total = curr_cpu_usage.active + usage;
	}
	ss.str(std::string());
	ss.clear();
	cpu_status_file.close();

	return 100 * (curr_cpu_usage.active - prev_cpu_usage.active) / (curr_cpu_usage.total - prev_cpu_usage.total);

}

int main(int argn, char * argv[]){
	
	int sleep_time = 1000;

	// Setting interval time in milliseconds to get cpu info
	if(argn > 1){
		sleep_time = atoi(argv[1]);
	}

	while(true){
		std::cout << check_cpu_usage(sleep_time) << std::endl;
	}

	return 0;
}