#ifndef _NT1065_SETUP_HPP_
#define _NT1065_SETUP_HPP_

#include "NT1065_Params.hpp"
#include "armhal.h"

///<summary>Class for performing the SPI flashing on the MC127.01 board</summary>
class NT1065_SPI_Setup {
public:
	///<summary>Setup status</summary>
	enum class NT1065_Status {
		Ok,
		PLL_Lock_Ok,
		Wrong_ID,
		PLL_Error,
		LPF_Error,
		Unknown_Error
	};

private:
	const ARMHAL_SPI_CHIP_SELECT NT1065_device = ARMHAL_SPI_DEVICE_2;
	const std::uint32_t Clock_frequency = 80000000;
	const std::uint32_t SPI_frequency = 10000000;
	const std::uint32_t SPI_bits = 16;
	const ARMHAL_SPI_MODE SPI_mode = ARMHAL_SPI_MODE_0;

		///<summary>Send data to the NT1065. Some unknown legacy code runs here</summary>
	///<param name='buf'>Partition to send</param>
	NT1065_Status Send_Partition(const std::uint8_t *buf) {
		// std::vector constructor would be more preferable, but STL by DS-5 doesn't support C++11
		std::uint32_t first_pack[] = { 2, 3, 41, 45, 42, 46, 43, 47, };
		for (auto i = 0; i < sizeof(first_pack) / sizeof(first_pack[0]); ++i)
			WriteRegistry(first_pack[i], buf[first_pack[i]]);

		// Execute PLL tuning
		WriteRegistry(43, buf[43] | 0x1);
		WriteRegistry(47, buf[47] | 0x1);

		while(1){
			auto pll_exec = ReadRegistry(43) & 0x1;
			auto pll_b_exec = ReadRegistry(47) & 0x1;
			pll_exec |= (pll_b_exec << 1);
			if(pll_exec == 0)
				break;
		}

		std::uint32_t filter_pack[] = { 14, 21, 28, 35, 4, };
		for (auto i = 0; i < sizeof(filter_pack) / sizeof(filter_pack[0]); ++i)
			WriteRegistry(filter_pack[i], buf[filter_pack[i]]);

		while(1){
			auto lpf_exec = ReadRegistry(4) & 0x1;
			if(lpf_exec == 0)
				break;
		}

		std::uint32_t second_pack[] = { 12, 11, 16, 23, 30, 37, 15, 22, 29, 36, 19, 26, 33, 40, 13, 20, 27, 34, };
		for (auto i = 0; i < sizeof(second_pack) / sizeof(second_pack[0]); ++i)
			WriteRegistry(second_pack[i], buf[second_pack[i]]);

		// Wait for PLL to be set up
		std::uint16_t pll_status = ReadRegistry(44) << 8;
		pll_status |= ReadRegistry(48);

		if ((pll_status & 0x0101) == 0x0101){
			std::uint8_t LPF_status = ReadRegistry(4);
			if ((LPF_status & 0x3) != 0x2)
				return NT1065_Status::LPF_Error;
			return NT1065_Status::PLL_Lock_Ok;
		}

		return NT1065_Status::PLL_Error;
	}

	///<summary>Write single NT1065 registry</summary>
	///<param name='reg_num'>Number of registry</param>
	///<param name='reg_data'>Data to send</param>
	template <typename T>
	void WriteRegistry(T reg_num, std::uint8_t reg_data) {
		std::uint32_t data = reg_num & 0x7F;
		data <<= 8;
		data |= reg_data;

		ARMHAL_SPI_Send(NT1065_device, data);
	}

	///<summary>Read single NT1065 registry</summary>
	///<param name='reg'>Number of registry</param>
	template <typename T>
	std::uint8_t ReadRegistry(T reg) {
		reg |= 0x80;
		reg <<= 8;

		std::uint16_t res = ARMHAL_SPI_Receive(NT1065_device, reg);
		res &= 0xFF;
		return static_cast<std::uint8_t>(res);
	}

public:
	///<summary>Object of NT1065_Params with values</summary>
	NT1065_Params p;

	NT1065_SPI_Setup(){
		ARMHAL_SPI_Settings settings = {Clock_frequency, SPI_frequency, SPI_bits, SPI_mode};
		ARMHAL_SPI_Init(&settings);
	}

	///<summary>Main setup function</summary>
	///<returns>Setup status</returns>
	NT1065_Status Setup() {
		auto NT1065_ID = (ReadRegistry(0) << 8) | ReadRegistry(1);
		auto true_ID = 0x214A;
		if (NT1065_ID == true_ID) {
			std::printf("NT1065_ID ok\n");
			auto result = Send_Partition(p.GetBufferPtr());
			auto NT1065_ID = (ReadRegistry(0) << 8) | ReadRegistry(1);
			NT1065_ID = (ReadRegistry(0) << 8) | ReadRegistry(1);
			if (result == NT1065_Status::PLL_Lock_Ok) {
				std::printf("NT1065_PLL_Lock ok\n");
				return NT1065_Status::Ok;
			}
			else
				return result;
		}
		else
			return NT1065_Status::Wrong_ID;
	}
	
	///<summary>Receive data from the NT1065</summary>
	void Read_Partition() {
		std::uint8_t buffer[49];
		for (auto i = 0; i < 49; ++i)
			buffer[i] = ReadRegistry(i);
		p.SetBuffer(buffer, 49);
	}

};

#endif // !_NT1065_SETUP_HPP_
