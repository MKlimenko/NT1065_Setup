#include "NT1065_Setup.hpp"

#include <iostream>
#include <vector>

int main(){
	NT1065_Params p;
	p.FormBuffer();

	NT1065_SPI_Setup s;
	s.p.LoadParams("C:\\lib2.hex");
	s.Setup();
	s.Read_Partition();

	return 0;
}
