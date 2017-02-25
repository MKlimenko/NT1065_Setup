#ifndef _NT_1065_SETUP_HPP_
#define _NT_1065_SETUP_HPP_

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

class NT1065_Params {
public:
	NT1065_Params() {
		std::fill(registers, registers + sizeof(registers) / sizeof(registers[0]), 0);
	}

#pragma region enums
	enum class NT_Mode {
		standby = 0,
		PLL_A,
		PLL_B,
		active,
	};

	enum class NT_TCXO {
		MHz_10 = 0,
		MHz_24_84,
	};

	enum class NT_LO_Source {
		PLL_A_Only = 0,
		PLL_A_B,
	};

	enum class NT_LPF_Autocalibration_Status {
		error = 0,
		success,
	};

	enum class NT_LPF_Autocalibration_Execute {
		finished = 0,
		start
	};

	enum class NT_Channel_Status_Monitor {
		channel_1 = 0,
		channel_2,
		channel_3,
		channel_4,
	};

	enum class NT_Temp_Mode {
		single = 0,
		continuous,
	};

	enum class NT_Temp_Execute {
		finished = 0,
		start,
	};

	enum class NT_LPF_ACS_AOK {
		forbidden = 0,
		permitted
	};

	enum class NT_PLL_LI_AOK {
		forbidden = 0,
		permitted
	};

	enum class NT_PLL_VCO_AOK {
		forbidden = 0,
		permitted
	};

	enum class NT_RF_AGC_AOK {
		forbidden = 0,
		permitted
	};

	enum class NT_StdBy_AOK {
		forbidden = 0,
		permitted
	};

	enum class NT_AOK {
		fail = 0,
		valid
	};

	enum class NT_RF_AGC {
		input_ok = 0,
		input_lower,
		input_higher,
		impossible_AGC_damaged,
	};

	enum class NT_CLK_Source {
		PLL_A = 0,
		PLL_B
	};

	enum class NT_CLK_TP {
		CMOS = 0,
		LVDS
	};

	enum class NT_CLK_CC {
		V_0_23 = 0,
		V_0_34,
		V_0_45,
		V_0_56,
	};

	enum class NT_CLK_OL {
		level_1_8 = 0,
		level_2_4,
		level_2_7,
		level_external,
	};

	enum class NT_Channel_LSB {
		USB = 0,
		LSB,
	};

	enum class NT_Channel_EN {
		disabled = 0,
		enabled
	};

	enum class NT_IFA_Amp_LVL {
		mV_200 = 0,
		mV_400
	};

	enum class NT_IFA_ResLoad {
		not_mounted = 0,
		mounted
	};

	enum class NT_RF_AGC_Mode {
		manual = 0,
		AGC
	};

	enum class NT_IFA_AGC_Mode {
		manual = 0,
		AGC
	};

	enum class NT_IFA_OP {
		level_1_55 = 0,
		level_1_75,
		level_1_90,
		level_2_00
	};

	enum class NT_IFA_OT {
		analog = 0,
		sg_mg
	};

	enum class NT_RF_AGC_UB {
		minus_47_dBm = 0,
		minus_45_dBm,
		minus_43_dBm,
		minus_42_dBm,
		minus_41_dBm,
		minus_40_dBm,
	};

	enum class NT_RF_AGC_LB {
		minus_49_dBm = 3,
		minus_46_dBm,
		minus_45_dBm,
		minus_43_dBm,
		minus_42_dBm,
	};

	enum class NT_IFA_Manual_Gain {
		minus_0_5_dB = 0,
		plus_10_5_dB = 3,
		plus_22_7_dB = 7,
		plus_31_5_dB = 10,
		plus_41_dB = 14,
		plus_50_7_dB = 17,
		plus_61_dB = 21,
		plus_63_dB = 23,
	};

	enum class NT_IFA_Gain {
		minus_0_35_dB = 7,
		minus_0_3_dB,
		minus_0_1_dB,
		plus_0_3_dB,
		plus_0_9_dB,
		plus_1_7_dB,
		plus_2_4_dB,
		plus_3_0_dB,
		plus_3_4_dB,
		plus_3_8_dB,
		plus_4_1_dB,
		plus_4_4_dB,
		plus_4_55_dB,
		plus_4_7_dB,
		plus_4_8_dB,
		plus_4_9_dB,
		plus_5_0_dB,
		plus_5_05_dB,
		plus_5_1_dB,
	};

	enum class NT_IFA_ADC_Clk {
		asyncronous = 1,
		rising_edge,
		falling_edge
	};

	enum class NT_IFA_ADC_OL {
		V_1_8 = 0,
		V_2_4,
		V_2_7,
		V_external
	};

	enum class NT_PLL_Band {
		L2_L3_L5 = 0,
		L1
	};

	enum class NT_PLL_Enable {
		disabled = 0,
		enabled
	};

	enum class NT_PLL_EXE {
		finished = 0,
		start
	};

	enum class NT_Vco_CV {
		valid = 0,
		upper_exceeded,
		lower_exceeded
	};

	enum class NT_PLL_Lock {
		not_locked = 0,
		locked
	};
#pragma endregion enums

	struct NT_System_Info {
		std::uint32_t ID_h = 0x42;
		std::uint32_t ID_l = 0x9;
		std::uint32_t Release = 0x2;
	} System_Info;

	struct NT_General_settings {
		NT_Mode Mode = NT_Mode::active;
		NT_TCXO TCXO = NT_TCXO::MHz_10;
		NT_LO_Source LO_Source = NT_LO_Source::PLL_A_B;
		NT_LPF_Autocalibration_Status LPF_ACS_S = NT_LPF_Autocalibration_Status::success;
		NT_LPF_Autocalibration_Execute LPF_EXE = NT_LPF_Autocalibration_Execute::start;
		NT_Channel_Status_Monitor Ch_StNumSel = NT_Channel_Status_Monitor::channel_1;
		NT_Temp_Mode TS_MD = NT_Temp_Mode::single;
		NT_Temp_Execute TS_EXE = NT_Temp_Execute::finished;

		NT_LPF_ACS_AOK LPF_ACS_AOK = NT_LPF_ACS_AOK::permitted;
		NT_PLL_LI_AOK PLL_LI_AOK = NT_PLL_LI_AOK::permitted;
		NT_PLL_VCO_AOK PLL_VCO_AOK = NT_PLL_VCO_AOK::permitted;
		NT_RF_AGC_AOK RF_AGC_AOK = NT_RF_AGC_AOK::forbidden;
		NT_StdBy_AOK StdBy_AOK = NT_StdBy_AOK::permitted;
		NT_AOK AOK = NT_AOK::valid;

		double TS_code = 0;

		NT_RF_AGC RF_AGC_Down = NT_RF_AGC::input_ok;
		NT_RF_AGC RF_AGC_Up = NT_RF_AGC::input_ok;
		double RF_GainSt = 0;

		std::uint8_t IFA_GainSt = 0;
	} General_settings;

	struct NT_Clock_Settings {
		std::uint8_t CDIV_R = 8;
		NT_CLK_Source CLK_Source = NT_CLK_Source::PLL_A;
		NT_CLK_TP CLK_TP = NT_CLK_TP::LVDS;
		NT_CLK_CC CLK_CC = NT_CLK_CC::V_0_45;
		NT_CLK_OL CLK_OL = NT_CLK_OL::level_1_8;

	} Clock_settings;

	struct NT_Channel_Settings {
		NT_Channel_LSB Ch_LSB = NT_Channel_LSB::LSB;
		NT_Channel_EN Ch_EN = NT_Channel_EN::enabled;
		double LPF_code = 15.12;

		NT_IFA_Amp_LVL IFA_AmpLvl = NT_IFA_Amp_LVL::mV_200;
		NT_IFA_ResLoad IFA_ResLoad = NT_IFA_ResLoad::mounted;
		NT_RF_AGC_Mode RF_AGC_MD = NT_RF_AGC_Mode::manual;
		NT_IFA_AGC_Mode IFA_AGC_MD = NT_IFA_AGC_Mode::AGC;
		NT_IFA_OP IFA_OP = NT_IFA_OP::level_1_75;
		NT_IFA_OT IFA_OT = NT_IFA_OT::analog;
		NT_RF_AGC_UB RF_AGC_UB = NT_RF_AGC_UB::minus_42_dBm;
		NT_RF_AGC_LB RF_AGC_LB = NT_RF_AGC_LB::minus_46_dBm;

		double RF_Gain = 11.0;
		NT_IFA_Manual_Gain IFA_ManGC = NT_IFA_Manual_Gain::minus_0_5_dB;
		NT_IFA_Gain IFA_Gain = NT_IFA_Gain::plus_0_3_dB;
		NT_IFA_ADC_Clk IFA_ADC_Clk = NT_IFA_ADC_Clk::rising_edge;
		NT_IFA_ADC_OL IFA_ADC_OL = NT_IFA_ADC_OL::V_2_7;
	} Channel_settings[4];

	struct NT_PLL_Settings {
		NT_PLL_Band PLL_Band = NT_PLL_Band::L1;
		NT_PLL_Enable PLL_EN = NT_PLL_Enable::enabled;
		std::uint32_t NDiv_R = 79;
		std::uint8_t RDiv_R = 1;
		NT_PLL_EXE PLL_EXE = NT_PLL_EXE::start;

		NT_Vco_CV Vco_CVL = NT_Vco_CV::valid;
		NT_Vco_CV Vco_CVH = NT_Vco_CV::valid;
		NT_PLL_Lock PLL_LI = NT_PLL_Lock::locked;
	} PLL_settings[2];

#pragma pack(push)
#pragma pack(1)
	struct byte_registers {
		std::uint8_t System_info_ID_h : 8;

		std::uint8_t System_info_Release : 3;
		std::uint8_t System_info_ID_l : 5;

		std::uint8_t General_settings_Mode : 2;
		std::uint8_t General_settings_reserved_0 : 6;

		std::uint8_t General_settings_LO_Source : 1;
		std::uint8_t General_settings_TCXO_sel : 1;
		std::uint8_t General_settings_reserved_1 : 6;

		std::uint8_t General_settings_LPF_EXE : 1;
		std::uint8_t General_settings_LPF_ACS_S : 1;
		std::uint8_t General_settings_reserved_2 : 6;

		std::uint8_t General_settings_TS_EXE : 1;
		std::uint8_t General_settings_TS_MD : 1;
		std::uint8_t General_settings_reserved_3 : 2;
		std::uint8_t General_settings_Ch_StNumSel : 2;
		std::uint8_t General_settings_Unused : 2;

		std::uint8_t General_settings_StdBy_AOK : 1;
		std::uint8_t General_settings_RF_AGC_AOK : 1;
		std::uint8_t General_settings_PLL_VCO_AOK : 1;
		std::uint8_t General_settings_PLL_LI_AOK : 1;
		std::uint8_t General_settings_LPF_ACS_AOK : 1;
		std::uint8_t General_settings_reserved_4 : 3;


		std::uint8_t General_settings_TS_code_h : 2;
		std::uint8_t General_settings_reserved_6 : 2;
		std::uint8_t General_settings_AOK : 1;
		std::uint8_t General_settings_reserved_5 : 3;

		std::uint8_t General_settings_TS_code_l : 8;

		std::uint8_t General_settings_RF_GainSt : 4;
		std::uint8_t General_settings_RF_AGC : 2;
		std::uint8_t General_settings_reserved_7 : 2;

		std::uint8_t General_settings_IFA_GainSt : 5;
		std::uint8_t General_settings_reserved_8 : 3;

		std::uint8_t Clock_settings_CDIV_R : 5;
		std::uint8_t Clock_settings_reserved_9 : 3;

		std::uint8_t Clock_settings_CLK_OL : 2;
		std::uint8_t Clock_settings_CLK_CC : 2;
		std::uint8_t Clock_settings_CLK_TP : 1;
		std::uint8_t Clock_settings_CLK_Source : 1;
		std::uint8_t Clock_settings_reserved_10 : 2;

		std::uint8_t Channel_settings_Ch1_En : 1;
		std::uint8_t Channel_settings_Ch1_LSB : 1;
		std::uint8_t Channel_settings_Ch1_reserved_0 : 6;

		std::uint8_t Channel_settings_Ch1_LPF_code : 7;
		std::uint8_t Channel_settings_Ch1_reserved_1 : 1;

		std::uint8_t Channel_settings_Ch1_IFA_OT : 1;
		std::uint8_t Channel_settings_Ch1_IFA_OP : 2;
		std::uint8_t Channel_settings_Ch1_IFA_AGC_MD : 1;
		std::uint8_t Channel_settings_Ch1_RF_AGC_MD : 1;
		std::uint8_t Channel_settings_Ch1_IFA_ResLoad : 1;
		std::uint8_t Channel_settings_Ch1_IFA_AmpLvl : 1;
		std::uint8_t Channel_settings_Ch1_reserved_2 : 1;

		std::uint8_t Channel_settings_Ch1_RF_AGC_LB : 3;
		std::uint8_t Channel_settings_Ch1_reserved_3 : 1;
		std::uint8_t Channel_settings_Ch1_RF_AGC_UB : 3;
		std::uint8_t Channel_settings_Ch1_reserved_4 : 1;

		std::uint8_t Channel_settings_Ch1_IFA_ManGC_h : 2;
		std::uint8_t Channel_settings_Ch1_reserved_5 : 2;
		std::uint8_t Channel_settings_Ch1_RF_Gain : 4;

		std::uint8_t Channel_settings_Ch1_IFA_Gain : 5;
		std::uint8_t Channel_settings_Ch1_IFA_ManGC_l : 3;

		std::uint8_t Channel_settings_Ch1_IFA_ADC_OL : 2;
		std::uint8_t Channel_settings_Ch1_IFA_ADC_Clk : 2;
		std::uint8_t Channel_settings_Ch1_reserved_6 : 4;

		std::uint8_t Channel_settings_Ch2_En : 1;
		std::uint8_t Channel_settings_Ch2_LSB : 1;
		std::uint8_t Channel_settings_Ch2_reserved_0 : 6;

		std::uint8_t Channel_settings_Ch2_LPF_code : 7;
		std::uint8_t Channel_settings_Ch2_reserved_1 : 1;

		std::uint8_t Channel_settings_Ch2_IFA_OT : 1;
		std::uint8_t Channel_settings_Ch2_IFA_OP : 2;
		std::uint8_t Channel_settings_Ch2_IFA_AGC_MD : 1;
		std::uint8_t Channel_settings_Ch2_RF_AGC_MD : 1;
		std::uint8_t Channel_settings_Ch2_IFA_ResLoad : 1;
		std::uint8_t Channel_settings_Ch2_IFA_AmpLvl : 1;
		std::uint8_t Channel_settings_Ch2_reserved_2 : 1;

		std::uint8_t Channel_settings_Ch2_RF_AGC_LB : 3;
		std::uint8_t Channel_settings_Ch2_reserved_3 : 1;
		std::uint8_t Channel_settings_Ch2_RF_AGC_UB : 3;
		std::uint8_t Channel_settings_Ch2_reserved_4 : 1;

		std::uint8_t Channel_settings_Ch2_IFA_ManGC_h : 2;
		std::uint8_t Channel_settings_Ch2_reserved_5 : 2;
		std::uint8_t Channel_settings_Ch2_RF_Gain : 4;

		std::uint8_t Channel_settings_Ch2_IFA_Gain : 5;
		std::uint8_t Channel_settings_Ch2_IFA_ManGC_l : 3;

		std::uint8_t Channel_settings_Ch2_IFA_ADC_OL : 2;
		std::uint8_t Channel_settings_Ch2_IFA_ADC_Clk : 2;
		std::uint8_t Channel_settings_Ch2_reserved_6 : 4;

		std::uint8_t Channel_settings_Ch3_En : 1;
		std::uint8_t Channel_settings_Ch3_LSB : 1;
		std::uint8_t Channel_settings_Ch3_reserved_0 : 6;

		std::uint8_t Channel_settings_Ch3_LPF_code : 7;
		std::uint8_t Channel_settings_Ch3_reserved_1 : 1;

		std::uint8_t Channel_settings_Ch3_IFA_OT : 1;
		std::uint8_t Channel_settings_Ch3_IFA_OP : 2;
		std::uint8_t Channel_settings_Ch3_IFA_AGC_MD : 1;
		std::uint8_t Channel_settings_Ch3_RF_AGC_MD : 1;
		std::uint8_t Channel_settings_Ch3_IFA_ResLoad : 1;
		std::uint8_t Channel_settings_Ch3_IFA_AmpLvl : 1;
		std::uint8_t Channel_settings_Ch3_reserved_2 : 1;

		std::uint8_t Channel_settings_Ch3_RF_AGC_LB : 3;
		std::uint8_t Channel_settings_Ch3_reserved_3 : 1;
		std::uint8_t Channel_settings_Ch3_RF_AGC_UB : 3;
		std::uint8_t Channel_settings_Ch3_reserved_4 : 1;

		std::uint8_t Channel_settings_Ch3_IFA_ManGC_h : 2;
		std::uint8_t Channel_settings_Ch3_reserved_5 : 2;
		std::uint8_t Channel_settings_Ch3_RF_Gain : 4;

		std::uint8_t Channel_settings_Ch3_IFA_Gain : 5;
		std::uint8_t Channel_settings_Ch3_IFA_ManGC_l : 3;

		std::uint8_t Channel_settings_Ch3_IFA_ADC_OL : 2;
		std::uint8_t Channel_settings_Ch3_IFA_ADC_Clk : 2;
		std::uint8_t Channel_settings_Ch3_reserved_6 : 4;

		std::uint8_t Channel_settings_Ch4_En : 1;
		std::uint8_t Channel_settings_Ch4_LSB : 1;
		std::uint8_t Channel_settings_Ch4_reserved_0 : 6;

		std::uint8_t Channel_settings_Ch4_LPF_code : 7;
		std::uint8_t Channel_settings_Ch4_reserved_1 : 1;

		std::uint8_t Channel_settings_Ch4_IFA_OT : 1;
		std::uint8_t Channel_settings_Ch4_IFA_OP : 2;
		std::uint8_t Channel_settings_Ch4_IFA_AGC_MD : 1;
		std::uint8_t Channel_settings_Ch4_RF_AGC_MD : 1;
		std::uint8_t Channel_settings_Ch4_IFA_ResLoad : 1;
		std::uint8_t Channel_settings_Ch4_IFA_AmpLvl : 1;
		std::uint8_t Channel_settings_Ch4_reserved_2 : 1;

		std::uint8_t Channel_settings_Ch4_RF_AGC_LB : 3;
		std::uint8_t Channel_settings_Ch4_reserved_3 : 1;
		std::uint8_t Channel_settings_Ch4_RF_AGC_UB : 3;
		std::uint8_t Channel_settings_Ch4_reserved_4 : 1;

		std::uint8_t Channel_settings_Ch4_IFA_ManGC_h : 2;
		std::uint8_t Channel_settings_Ch4_reserved_5 : 2;
		std::uint8_t Channel_settings_Ch4_RF_Gain : 4;

		std::uint8_t Channel_settings_Ch4_IFA_Gain : 5;
		std::uint8_t Channel_settings_Ch4_IFA_ManGC_l : 3;

		std::uint8_t Channel_settings_Ch4_IFA_ADC_OL : 2;
		std::uint8_t Channel_settings_Ch4_IFA_ADC_Clk : 2;
		std::uint8_t Channel_settings_Ch4_reserved_6 : 4;


		std::uint8_t PLL_settings_pllA_PLL_EN : 1;
		std::uint8_t PLL_settings_pllA_PLL_Band : 1;
		std::uint8_t PLL_settings_pllA_reserved_0 : 6;

		std::uint8_t PLL_settings_pllA_NDiv_R_h : 8;

		std::uint8_t PLL_settings_pllA_PLL_EXE : 1;
		std::uint8_t PLL_settings_pllA_reserved_1 : 2;
		std::uint8_t PLL_settings_pllA_RDiv_R : 4;
		std::uint8_t PLL_settings_pllA_NDiv_R_l : 1;

		std::uint8_t PLL_settings_pllA_PLL_LI : 1;
		std::uint8_t PLL_settings_pllA_Vco_CV : 2;
		std::uint8_t PLL_settings_pllA_reserved_2 : 5;

		std::uint8_t PLL_settings_pllB_PLL_EN : 1;
		std::uint8_t PLL_settings_pllB_PLL_Band : 1;
		std::uint8_t PLL_settings_pllB_reserved_0 : 6;

		std::uint8_t PLL_settings_pllB_NDiv_R_h : 8;

		std::uint8_t PLL_settings_pllB_PLL_EXE : 1;
		std::uint8_t PLL_settings_pllB_reserved_1 : 2;
		std::uint8_t PLL_settings_pllB_RDiv_R : 4;
		std::uint8_t PLL_settings_pllB_NDiv_R_l : 1;

		std::uint8_t PLL_settings_pllB_PLL_LI : 1;
		std::uint8_t PLL_settings_pllB_Vco_CV : 2;
		std::uint8_t PLL_settings_pllB_reserved_2 : 5;
	} raw_params;
#pragma pack(pop)

	std::int32_t CheckParamsForErrors() {
		if (Clock_settings.CDIV_R < 8 || Clock_settings.CDIV_R > 32)
			return 1;

		for (auto i = 0; i < 4; ++i) {
			if (Channel_settings[i].LPF_code < 11.22 || Channel_settings[i].LPF_code > 43.41)
				return 1;

			if (Channel_settings[i].RF_Gain < 11 || Channel_settings[i].RF_Gain > 25.5)
				return 1;
		}

		for (auto i = 0; i < 2; ++i) {
			if (PLL_settings[i].NDiv_R < 48 || PLL_settings[i].NDiv_R > 511)
				return 1;
			if (PLL_settings[i].RDiv_R < 1 || PLL_settings[i].RDiv_R > 15)
				return 1;
		}

		return 0;
	}

	void AssignBuffer(const std::uint8_t* buffer) {
		std::uint8_t* raw_ptr = reinterpret_cast<std::uint8_t*>(&raw_params);

		for (auto i = 0; i < registers_size; ++i) {
			*raw_ptr++ = buffer[i];
		}
	}

	void ParseBuffer() {
		System_Info.ID_h = raw_params.System_info_ID_h;
		System_Info.ID_l = raw_params.System_info_ID_l;
		System_Info.Release = raw_params.System_info_Release;

		General_settings.Mode = static_cast<NT_Mode>(raw_params.General_settings_Mode);
		General_settings.LO_Source = static_cast<NT_LO_Source>(raw_params.General_settings_LO_Source);
		General_settings.TCXO = static_cast<NT_TCXO>(raw_params.General_settings_TCXO_sel);
		General_settings.LPF_EXE = static_cast<NT_LPF_Autocalibration_Execute>(raw_params.General_settings_LPF_EXE);
		General_settings.LPF_ACS_S = static_cast<NT_LPF_Autocalibration_Status>(raw_params.General_settings_LPF_ACS_S);
		General_settings.TS_EXE = static_cast<NT_Temp_Execute>(raw_params.General_settings_TS_EXE);
		General_settings.TS_MD = static_cast<NT_Temp_Mode>(raw_params.General_settings_TS_MD);
		General_settings.Ch_StNumSel = static_cast<NT_Channel_Status_Monitor>(raw_params.General_settings_Ch_StNumSel);
		General_settings.StdBy_AOK = static_cast<NT_StdBy_AOK>(raw_params.General_settings_StdBy_AOK);
		General_settings.RF_AGC_AOK = static_cast<NT_RF_AGC_AOK>(raw_params.General_settings_RF_AGC_AOK);
		General_settings.PLL_VCO_AOK = static_cast<NT_PLL_VCO_AOK>(raw_params.General_settings_PLL_VCO_AOK);
		General_settings.PLL_LI_AOK = static_cast<NT_PLL_LI_AOK>(raw_params.General_settings_PLL_LI_AOK);
		General_settings.LPF_ACS_AOK = static_cast<NT_LPF_ACS_AOK>(raw_params.General_settings_LPF_ACS_AOK);
		General_settings.TS_code = (raw_params.General_settings_TS_code_h << 8) | raw_params.General_settings_TS_code_l;
		General_settings.AOK = static_cast<NT_AOK>(raw_params.General_settings_AOK);
		General_settings.RF_GainSt = raw_params.General_settings_RF_GainSt * 0.95 + 11;
		General_settings.RF_AGC_Up = static_cast<NT_RF_AGC>(raw_params.General_settings_RF_AGC);
		General_settings.RF_AGC_Down = static_cast<NT_RF_AGC>(raw_params.General_settings_RF_AGC);
		General_settings.IFA_GainSt = raw_params.General_settings_IFA_GainSt;

		Clock_settings.CDIV_R = raw_params.Clock_settings_CDIV_R;
		Clock_settings.CLK_OL = static_cast<NT_CLK_OL>(raw_params.Clock_settings_CLK_OL);
		Clock_settings.CLK_CC = static_cast<NT_CLK_CC>(raw_params.Clock_settings_CLK_CC);
		Clock_settings.CLK_TP = static_cast<NT_CLK_TP>(raw_params.Clock_settings_CLK_TP);
		Clock_settings.CLK_Source = static_cast<NT_CLK_Source>(raw_params.Clock_settings_CLK_Source);

		Channel_settings[0].Ch_EN = static_cast<NT_Channel_EN>(raw_params.Channel_settings_Ch1_En);
		Channel_settings[0].Ch_LSB = static_cast<NT_Channel_LSB>(raw_params.Channel_settings_Ch1_LSB);
		Channel_settings[0].LPF_code = (raw_params.Channel_settings_Ch1_LPF_code + 29.74) / 3.422;
		Channel_settings[0].IFA_OT = static_cast<NT_IFA_OT>(raw_params.Channel_settings_Ch1_IFA_OT);
		Channel_settings[0].IFA_OP = static_cast<NT_IFA_OP>(raw_params.Channel_settings_Ch1_IFA_OP);
		Channel_settings[0].IFA_AGC_MD = static_cast<NT_IFA_AGC_Mode>(raw_params.Channel_settings_Ch1_IFA_AGC_MD);
		Channel_settings[0].RF_AGC_MD = static_cast<NT_RF_AGC_Mode>(raw_params.Channel_settings_Ch1_RF_AGC_MD);
		Channel_settings[0].IFA_ResLoad = static_cast<NT_IFA_ResLoad>(raw_params.Channel_settings_Ch1_IFA_ResLoad);
		Channel_settings[0].IFA_AmpLvl = static_cast<NT_IFA_Amp_LVL>(raw_params.Channel_settings_Ch1_IFA_AmpLvl);
		Channel_settings[0].RF_AGC_LB = static_cast<NT_RF_AGC_LB>(raw_params.Channel_settings_Ch1_RF_AGC_LB);
		Channel_settings[0].RF_AGC_UB = static_cast<NT_RF_AGC_UB>(raw_params.Channel_settings_Ch1_RF_AGC_UB);
		Channel_settings[0].IFA_ManGC = static_cast<NT_IFA_Manual_Gain>((raw_params.Channel_settings_Ch1_IFA_ManGC_h << 3) | raw_params.Channel_settings_Ch1_IFA_ManGC_l);
		Channel_settings[0].RF_Gain = raw_params.Channel_settings_Ch1_RF_Gain * 0.95 + 11;
		Channel_settings[0].IFA_ADC_OL = static_cast<NT_IFA_ADC_OL>(raw_params.Channel_settings_Ch1_IFA_ADC_OL);
		Channel_settings[0].IFA_ADC_Clk = static_cast<NT_IFA_ADC_Clk>(raw_params.Channel_settings_Ch1_IFA_ADC_Clk);

		Channel_settings[1].Ch_EN = static_cast<NT_Channel_EN>(raw_params.Channel_settings_Ch2_En);
		Channel_settings[1].Ch_LSB = static_cast<NT_Channel_LSB>(raw_params.Channel_settings_Ch2_LSB);
		Channel_settings[1].LPF_code = (raw_params.Channel_settings_Ch2_LPF_code + 29.74) / 3.422;
		Channel_settings[1].IFA_OT = static_cast<NT_IFA_OT>(raw_params.Channel_settings_Ch2_IFA_OT);
		Channel_settings[1].IFA_OP = static_cast<NT_IFA_OP>(raw_params.Channel_settings_Ch2_IFA_OP);
		Channel_settings[1].IFA_AGC_MD = static_cast<NT_IFA_AGC_Mode>(raw_params.Channel_settings_Ch2_IFA_AGC_MD);
		Channel_settings[1].RF_AGC_MD = static_cast<NT_RF_AGC_Mode>(raw_params.Channel_settings_Ch2_RF_AGC_MD);
		Channel_settings[1].IFA_ResLoad = static_cast<NT_IFA_ResLoad>(raw_params.Channel_settings_Ch2_IFA_ResLoad);
		Channel_settings[1].IFA_AmpLvl = static_cast<NT_IFA_Amp_LVL>(raw_params.Channel_settings_Ch2_IFA_AmpLvl);
		Channel_settings[1].RF_AGC_LB = static_cast<NT_RF_AGC_LB>(raw_params.Channel_settings_Ch2_RF_AGC_LB);
		Channel_settings[1].RF_AGC_UB = static_cast<NT_RF_AGC_UB>(raw_params.Channel_settings_Ch2_RF_AGC_UB);
		Channel_settings[1].IFA_ManGC = static_cast<NT_IFA_Manual_Gain>((raw_params.Channel_settings_Ch2_IFA_ManGC_h << 3) | raw_params.Channel_settings_Ch2_IFA_ManGC_l);
		Channel_settings[1].RF_Gain = raw_params.Channel_settings_Ch2_RF_Gain * 0.95 + 11;
		Channel_settings[1].IFA_ADC_OL = static_cast<NT_IFA_ADC_OL>(raw_params.Channel_settings_Ch2_IFA_ADC_OL);
		Channel_settings[1].IFA_ADC_Clk = static_cast<NT_IFA_ADC_Clk>(raw_params.Channel_settings_Ch2_IFA_ADC_Clk);

		Channel_settings[2].Ch_EN = static_cast<NT_Channel_EN>(raw_params.Channel_settings_Ch3_En);
		Channel_settings[2].Ch_LSB = static_cast<NT_Channel_LSB>(raw_params.Channel_settings_Ch3_LSB);
		Channel_settings[2].LPF_code = (raw_params.Channel_settings_Ch3_LPF_code + 29.74) / 3.422;
		Channel_settings[2].IFA_OT = static_cast<NT_IFA_OT>(raw_params.Channel_settings_Ch3_IFA_OT);
		Channel_settings[2].IFA_OP = static_cast<NT_IFA_OP>(raw_params.Channel_settings_Ch3_IFA_OP);
		Channel_settings[2].IFA_AGC_MD = static_cast<NT_IFA_AGC_Mode>(raw_params.Channel_settings_Ch3_IFA_AGC_MD);
		Channel_settings[2].RF_AGC_MD = static_cast<NT_RF_AGC_Mode>(raw_params.Channel_settings_Ch3_RF_AGC_MD);
		Channel_settings[2].IFA_ResLoad = static_cast<NT_IFA_ResLoad>(raw_params.Channel_settings_Ch3_IFA_ResLoad);
		Channel_settings[2].IFA_AmpLvl = static_cast<NT_IFA_Amp_LVL>(raw_params.Channel_settings_Ch3_IFA_AmpLvl);
		Channel_settings[2].RF_AGC_LB = static_cast<NT_RF_AGC_LB>(raw_params.Channel_settings_Ch3_RF_AGC_LB);
		Channel_settings[2].RF_AGC_UB = static_cast<NT_RF_AGC_UB>(raw_params.Channel_settings_Ch3_RF_AGC_UB);
		Channel_settings[2].IFA_ManGC = static_cast<NT_IFA_Manual_Gain>((raw_params.Channel_settings_Ch3_IFA_ManGC_h << 3) | raw_params.Channel_settings_Ch3_IFA_ManGC_l);
		Channel_settings[2].RF_Gain = raw_params.Channel_settings_Ch3_RF_Gain * 0.95 + 11;
		Channel_settings[2].IFA_ADC_OL = static_cast<NT_IFA_ADC_OL>(raw_params.Channel_settings_Ch3_IFA_ADC_OL);
		Channel_settings[2].IFA_ADC_Clk = static_cast<NT_IFA_ADC_Clk>(raw_params.Channel_settings_Ch3_IFA_ADC_Clk);

		Channel_settings[3].Ch_EN = static_cast<NT_Channel_EN>(raw_params.Channel_settings_Ch4_En);
		Channel_settings[3].Ch_LSB = static_cast<NT_Channel_LSB>(raw_params.Channel_settings_Ch4_LSB);
		Channel_settings[3].LPF_code = (raw_params.Channel_settings_Ch4_LPF_code + 29.74) / 3.422;
		Channel_settings[3].IFA_OT = static_cast<NT_IFA_OT>(raw_params.Channel_settings_Ch4_IFA_OT);
		Channel_settings[3].IFA_OP = static_cast<NT_IFA_OP>(raw_params.Channel_settings_Ch4_IFA_OP);
		Channel_settings[3].IFA_AGC_MD = static_cast<NT_IFA_AGC_Mode>(raw_params.Channel_settings_Ch4_IFA_AGC_MD);
		Channel_settings[3].RF_AGC_MD = static_cast<NT_RF_AGC_Mode>(raw_params.Channel_settings_Ch4_RF_AGC_MD);
		Channel_settings[3].IFA_ResLoad = static_cast<NT_IFA_ResLoad>(raw_params.Channel_settings_Ch4_IFA_ResLoad);
		Channel_settings[3].IFA_AmpLvl = static_cast<NT_IFA_Amp_LVL>(raw_params.Channel_settings_Ch4_IFA_AmpLvl);
		Channel_settings[3].RF_AGC_LB = static_cast<NT_RF_AGC_LB>(raw_params.Channel_settings_Ch4_RF_AGC_LB);
		Channel_settings[3].RF_AGC_UB = static_cast<NT_RF_AGC_UB>(raw_params.Channel_settings_Ch4_RF_AGC_UB);
		Channel_settings[3].IFA_ManGC = static_cast<NT_IFA_Manual_Gain>((raw_params.Channel_settings_Ch4_IFA_ManGC_h << 3) | raw_params.Channel_settings_Ch4_IFA_ManGC_l);
		Channel_settings[3].RF_Gain = raw_params.Channel_settings_Ch4_RF_Gain * 0.95 + 11;
		Channel_settings[3].IFA_ADC_OL = static_cast<NT_IFA_ADC_OL>(raw_params.Channel_settings_Ch4_IFA_ADC_OL);
		Channel_settings[3].IFA_ADC_Clk = static_cast<NT_IFA_ADC_Clk>(raw_params.Channel_settings_Ch4_IFA_ADC_Clk);

		PLL_settings[0].PLL_EN = static_cast<NT_PLL_Enable>(raw_params.PLL_settings_pllA_PLL_EN);
		PLL_settings[0].PLL_Band = static_cast<NT_PLL_Band>(raw_params.PLL_settings_pllA_PLL_Band);
		PLL_settings[0].NDiv_R = (raw_params.PLL_settings_pllA_NDiv_R_h << 1) | raw_params.PLL_settings_pllA_NDiv_R_l;
		PLL_settings[0].PLL_EXE = static_cast<NT_PLL_EXE>(raw_params.PLL_settings_pllA_PLL_EXE);
		PLL_settings[0].RDiv_R = raw_params.PLL_settings_pllA_RDiv_R;
		PLL_settings[0].PLL_LI = static_cast<NT_PLL_Lock>(raw_params.PLL_settings_pllA_PLL_LI);
		PLL_settings[0].Vco_CVH = static_cast<NT_Vco_CV>(raw_params.PLL_settings_pllA_Vco_CV);
		PLL_settings[0].Vco_CVL = static_cast<NT_Vco_CV>(raw_params.PLL_settings_pllA_Vco_CV);

		PLL_settings[1].PLL_EN = static_cast<NT_PLL_Enable>(raw_params.PLL_settings_pllB_PLL_EN);
		PLL_settings[1].PLL_Band = static_cast<NT_PLL_Band>(raw_params.PLL_settings_pllB_PLL_Band);
		PLL_settings[1].NDiv_R = (raw_params.PLL_settings_pllB_NDiv_R_h << 1) | raw_params.PLL_settings_pllB_NDiv_R_l;
		PLL_settings[1].PLL_EXE = static_cast<NT_PLL_EXE>(raw_params.PLL_settings_pllB_PLL_EXE);
		PLL_settings[1].RDiv_R = raw_params.PLL_settings_pllB_RDiv_R;
		PLL_settings[1].PLL_LI = static_cast<NT_PLL_Lock>(raw_params.PLL_settings_pllB_PLL_LI);
		PLL_settings[1].Vco_CVH = static_cast<NT_Vco_CV>(raw_params.PLL_settings_pllB_Vco_CV);
		PLL_settings[1].Vco_CVL = static_cast<NT_Vco_CV>(raw_params.PLL_settings_pllB_Vco_CV);
	}

	void FormBuffer() {
		registers[0] = static_cast<std::uint8_t>(System_Info.ID_h);
		registers[1] = (static_cast<std::uint8_t>(System_Info.ID_l) << 3) | static_cast<std::uint8_t>(System_Info.Release);

		// General settings
		registers[2] = static_cast<std::uint8_t>(General_settings.Mode);
		registers[3] = (static_cast<std::uint8_t>(General_settings.TCXO) << 1) | static_cast<std::uint8_t>(General_settings.LO_Source);
		registers[4] = (static_cast<std::uint8_t>(General_settings.LPF_ACS_S) << 1) | static_cast<std::uint8_t>(General_settings.LPF_EXE);
		registers[5] = (static_cast<std::uint8_t>(General_settings.Ch_StNumSel) << 4) | (static_cast<std::uint8_t>(General_settings.TS_MD) << 1) |
			static_cast<std::uint8_t>(General_settings.TS_EXE);
		registers[6] = (static_cast<std::uint8_t>(General_settings.LPF_ACS_AOK) << 4) | (static_cast<std::uint8_t>(General_settings.PLL_LI_AOK) << 3) |
			(static_cast<std::uint8_t>(General_settings.PLL_VCO_AOK) << 2) | (static_cast<std::uint8_t>(General_settings.RF_AGC_AOK) << 1) | static_cast<std::uint8_t>(General_settings.StdBy_AOK);

		// Clock settings
		registers[11] = static_cast<std::uint8_t>(Clock_settings.CDIV_R);
		registers[12] = (static_cast<std::uint8_t>(Clock_settings.CLK_Source) << 5) | (static_cast<std::uint8_t>(Clock_settings.CLK_TP) << 4) |
			(static_cast<std::uint8_t>(Clock_settings.CLK_CC) << 2) | static_cast<std::uint8_t>(Clock_settings.CLK_OL);

		// Channel settings
		for (auto i = 0; i < 4; ++i) {
			registers[13 + 7 * i] = (static_cast<std::uint8_t>(Channel_settings[i].Ch_LSB) << 1) | static_cast<std::uint8_t>(Channel_settings[i].Ch_EN);
			registers[14 + 7 * i] = static_cast<std::uint8_t>(std::ceil(Channel_settings[i].LPF_code * 3.422 - 29.74)); // Linear approximation (p. 16 ver. 2.05)
			registers[15 + 7 * i] = (static_cast<std::uint8_t>(Channel_settings[i].IFA_AmpLvl) << 6) | (static_cast<std::uint8_t>(Channel_settings[i].IFA_ResLoad) << 5) |
				(static_cast<std::uint8_t>(Channel_settings[i].RF_AGC_MD) << 4) | (static_cast<std::uint8_t>(Channel_settings[i].IFA_AGC_MD) << 3) |
				(static_cast<std::uint8_t>(Channel_settings[i].IFA_OP) << 1) | static_cast<std::uint8_t>(Channel_settings[i].IFA_OT);
			registers[16 + 7 * i] = (static_cast<std::uint8_t>(Channel_settings[i].RF_AGC_UB) << 4) | static_cast<std::uint8_t>(Channel_settings[i].RF_AGC_LB);
			registers[17 + 7 * i] = (static_cast<std::uint8_t>((Channel_settings[i].RF_Gain - 11) / 0.95) << 4) | (static_cast<std::uint8_t>(Channel_settings[i].IFA_ManGC) >> 3);
			registers[18 + 7 * i] = ((static_cast<std::uint8_t>(Channel_settings[i].IFA_ManGC) & 0x7) << 4) | static_cast<std::uint8_t>(Channel_settings[i].IFA_Gain);
			registers[19 + 7 * i] = (static_cast<std::uint8_t>(Channel_settings[i].IFA_ADC_Clk) << 2) | static_cast<std::uint8_t>(Channel_settings[i].IFA_ADC_OL);
		}

		// PLL settings
		for (auto i = 0; i < 2; ++i) {
			registers[41 + 4 * i] = (static_cast<std::uint8_t>(PLL_settings[i].PLL_Band) << 1) | static_cast<std::uint8_t>(PLL_settings[i].PLL_EN);
			registers[42 + 4 * i] = static_cast<std::uint8_t>(PLL_settings[i].NDiv_R >> 1);
			registers[43 + 4 * i] = ((static_cast<std::uint8_t>(PLL_settings[i].NDiv_R) & 0x1) << 7) | (PLL_settings[i].RDiv_R << 3) | static_cast<std::uint8_t>(PLL_settings[i].PLL_EXE);
			registers[44 + 4 * i] = (static_cast<std::uint8_t>(PLL_settings[i].Vco_CVL) << 7) | static_cast<std::uint8_t>(PLL_settings[i].PLL_LI);
		}
	}

	void SaveParams(const std::string &filename = "Test.hex") {
		std::ofstream of(filename.c_str());
		if (of.is_open()) {
			of << ";NT1065.2\n";
			for (auto i = 0; i < sizeof(registers); ++i) {
				of << "Reg" << std::dec << i << "\t" << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << static_cast<int32_t>(registers[i]) << "\n";
			}
		}
		of.flush();
		of.close();
	}

	std::vector<std::uint8_t> GetBuffer() {
		std::vector<std::uint8_t> res(registers, registers + registers_size);
		return res;
	}

	std::uint8_t* GetBufferPtr() {
		auto res = registers;
		return res;
	}

	template <typename T>
	void SetBuffer(const std::vector<T> &src) {
		if (src.size() != registers_size)
			return;
		for (auto i = 0; i < registers_size; ++i)
			registers[i] = src[i];		
	}

private:
	static const std::size_t registers_size = 49;
	std::uint8_t registers[registers_size];
};

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4312)
#endif // WIN32
class NT1065_SPI_Setup {
public:
	enum class NT1065_Status {
		Ok,
		PLL_Lock_Ok,
		Error_NACK,
		PLL_Error,
		LPF_Error,
		Unknows_Error
	};

private:
	std::uint32_t SSP_Base = 0xFFF0D000;
	std::uint32_t SSPCR0 = SSP_Base + 0x000;
	std::uint32_t SSPCR1 = SSP_Base + 0x004;
	std::uint32_t SSPDR = SSP_Base + 0x008;
	std::uint32_t SSPSR = SSP_Base + 0x00C;
	std::uint32_t SSPCPSR = SSP_Base + 0x010;
	std::uint32_t SSPICR = SSP_Base + 0x020;
	std::uint32_t SSPDMACR = SSP_Base + 0x024;

	std::uint32_t ARMSC_Base = 0xFFF02000;
	std::uint32_t ARMSC_SPICSCTL = ARMSC_Base + 0x4;


	// Refer to the BBP2 user guide
	void Setup_SPI_Master() {
		// Clock setup (5 MHz)
		*reinterpret_cast<std::uint32_t*>(SSPCPSR) = 0x8;
	
		// SPI mode setup
		*reinterpret_cast<std::uint32_t*>(SSPCR0) = 0xF;

		// SPI master/slave setup 
		*reinterpret_cast<std::uint32_t*>(SSPCR1) = 0x2;	
	}

	template <typename T>
	void SPI_Set_Active_Device(T device_number) {
		if (device_number > 7) 
			return;
		
		*reinterpret_cast<std::uint32_t*>(ARMSC_SPICSCTL) = device_number;
	}

	NT1065_Status Send_Partition(const std::uint8_t *buf) {
		// Wait for previous data to be sent
		while (*reinterpret_cast<std::uint32_t*>(SSPSR) & 0x10) {
			;
		}

		// std::vector constructor would be more preferable, but STL by DS-5 doesn't support C++11
		std::uint32_t first_pack[] = { 2, 3, 41, 45, 42, 46, 43, 47, 43, 47, };
		for (auto i = 0; i < sizeof(first_pack) / sizeof(first_pack[0]); ++i)
			WriteRegistry(i, buf[i]);
		
		Delay(160000);

		std::uint32_t filter_pack[] = { 14, 21, 28, 35, 4, };
		for (auto i = 0; i < sizeof(filter_pack) / sizeof(filter_pack[0]); ++i)
			WriteRegistry(i, buf[i]);

		Delay(2200000);

		std::uint32_t second_pack[] = { 12, 11, 16, 23, 30, 37, 15, 22, 29, 36, 19, 26, 33, 40, 13, 20, 27, 34, };
		for (auto i = 0; i < sizeof(second_pack) / sizeof(second_pack[0]); ++i)
			WriteRegistry(i, buf[i]);

		// Wait for PLL to be set up
		std::uint16_t pll_status = 0;
		do{
			pll_status = ReadRegistry(43) << 8;
			pll_status |= ReadRegistry(47);
			pll_status &= 0x0101;
		} while (pll_status);

		pll_status = ReadRegistry(44) << 8;
		pll_status |= ReadRegistry(48);

		if ((pll_status & 0x0101) == 0x0101){
			auto LPF_status = ReadRegistry(4);
			if ((LPF_status & 0x2) == 0x2)
				return NT1065_Status::LPF_Error;
			return NT1065_Status::PLL_Lock_Ok;
		}

		return NT1065_Status::PLL_Error;
	}

	template <typename T>
	void WriteRegistry(T reg_num, std::uint8_t reg_data) {
		std::uint8_t data = reg_num & 0x7F;
		data <<= 8;
		data |= reg_data;

		// Wait for previous data to be sent
		while (*reinterpret_cast<std::uint32_t*>(SSPSR) & 0x10) {
			;
		}

		// Wait for SPI FIFO to empty
		while ((*reinterpret_cast<std::uint32_t*>(SSPSR) & 0x2) == 0) {
			;
		}

		*reinterpret_cast<std::uint32_t*>(SSPDR) = data;
	}

	template <typename T>
	std::uint8_t ReadRegistry(T reg) {
		// Wait for previous data to be sent
		while (*reinterpret_cast<std::uint32_t*>(SSPSR) & 0x10){
			;
		}

		// Read all the junk data
		while (*reinterpret_cast<std::uint32_t*>(SSPSR) & 0x4) {
			auto tmp_data = *reinterpret_cast<std::uint32_t*>(SSPDR);
		}

		reg |= 0x80;
		reg <<= 8;
		*reinterpret_cast<std::uint32_t*>(SSPDR) = reg;

		// Wait for transfer to complete
		while ((*reinterpret_cast<std::uint32_t*>(SSPSR) & 0x4) == 0) {
			;
		}

		Delay(200);
		std::uint32_t res = *reinterpret_cast<std::uint32_t*>(SSPDR);
		res &= 0xFF;
		return static_cast<std::uint8_t>(res);
	}

	template <typename T>
	void Delay(T n_Ticks) {
		// God knows what does it mean
		auto i = 0;
		if (n_Ticks > 25) {
			auto tmp = n_Ticks - 8;
			tmp /= 17;
			do {
				++i;
			} while (i < tmp);
		}
		else {
			do {
				++i;
			} while (i < n_Ticks);
		}
	}

public:
	NT1065_Params p;

	NT1065_Status Setup() {
		Setup_SPI_Master();
		SPI_Set_Active_Device(2);
		auto NT1065_ID = (ReadRegistry(0) << 8) | ReadRegistry(1);
		auto true_ID = 0x214A;
		if (NT1065_ID == true_ID) {
			std::cout << "NT1065_ID ok";
			auto result = Send_Partition(p.GetBufferPtr());
			if (result == NT1065_Status::PLL_Lock_Ok)
				return NT1065_Status::Ok;
			else
				return result;
		}
		else
			return NT1065_Status::Error_NACK;

	}
};
#ifdef _WIN32
#pragma warning(pop)
#endif // WIN32

#endif // !_NT_1065_SETUP_HPP_
