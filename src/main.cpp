#include "NT1065_Params.hpp"

#include <iostream>
#include <vector>

namespace {
	std::string filename = "..\\..\\..\\src\\Lib.hex";
}

void main() {
	NT1065_Params p;

	p.LoadParams(filename);
	p.s.Channel_Settings[1].Ch_LSB = NT1065_Params::Channel_LSB::LSB;
	p.SaveParams(filename);
}