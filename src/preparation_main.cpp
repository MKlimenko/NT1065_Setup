#include "NT1065_Params.hpp"

#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
	try {
		if (argc != 3 && argc != 4)
			throw std::runtime_error("Usage: NT1065_Settings_Preparation.exe \t\t\"NT1065_Settings.hex\" \t\"NT1065_Settings_processed.bin\" \t\"-text(optional)\"\n");

		std::string input = argv[1];
		std::string output = argv[2];
		bool save_as_text = false;

		if (argc == 3)
			save_as_text = false;
		else
			save_as_text = true;

		NT1065_Params p;
		p.LoadParams(input);
	
		auto vec_of_params = p.GetBuffer();
		
		if (save_as_text) {
			std::ofstream file(output.c_str());
			if (!file.is_open())
				throw "Unable to open output file";
			file << std::hex << "{ ";
			for (auto &el : vec_of_params)
				file << "0x" << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << static_cast<std::int32_t>(el) << ", ";
			file << " };";
		}
		else {
			std::ofstream file(output.c_str(), std::ios::binary);
			if (!file.is_open())
				throw "Unable to open output file";
			file.write(reinterpret_cast<char*>(vec_of_params.data()), vec_of_params.size() * sizeof(vec_of_params[0]));
		}
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown exception has occured\n";
	}
	return 0;
}