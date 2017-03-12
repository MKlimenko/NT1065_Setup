#include "NT1065_Setup.hpp"

#include <iostream>
#include <vector>

void main() {
	NT1065_Params p;

	p.FormBuffer();
	// Extract the generated buffer from the class member
	auto result_pre = p.GetBuffer();

	// Extract the selected buffer and try to parse it
	p.SetBuffer(result_pre);
	auto result_post = p.GetBuffer();
	if (result_pre == result_post)
		std::cout << "Success!\n";
	else {
		std::cerr << "Error! Difference in the:\n";
		for (std::size_t i = 0; i < result_pre.size(); ++i) {
			if (result_pre[i] != result_post[i]) {
				std::cout << i << "-th element. Expected: " << static_cast<std::int32_t>(result_pre[i]) <<
					".\tReceived: " << static_cast<std::int32_t>(result_post[i]) << std::endl;
			}
		}
	}

	p.SaveParams("G:\\Lib.hex");
	p.LoadParams("G:\\Lib.hex");
}