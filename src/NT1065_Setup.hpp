#ifndef _NT1065_SETUP_HPP_
#define _NT1065_SETUP_HPP_

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

///<summary>Class for holding the NT1065 parameters</summary>
class NT1065_Params {
public:
	NT1065_Params() {
		std::fill(registers, registers + sizeof(registers) / sizeof(registers[0]), 0);
		raw_params = reinterpret_cast<byte_registers*>(registers);
		FormBuffer();
	}

#pragma region enums
	///<summary>NT1065 mode</summary>
	enum class Mode {
		standby = 0,
		PLL_A,
		PLL_B,
		active,
	};

	///<summary>Base frequency</summary>
	enum class TCXO {
		MHz_10 = 0,
		MHz_24_84,
	};

	///<summary>Heterodyne source</summary>
	enum class LO_Source {
		PLL_A_Only = 0,		///<summary>PLL A for all of the channels</summary>
		PLL_A_B,			///<summary>PLL A for channels 1 and 2, PLL B for 3 and 4</summary>
	};

	///<summary>LPF Auto-calibration system status</summary>
	enum class LPF_Autocalibration_Status {
		error = 0,
		success,
	};

	///<summary>LPF Auto-calibration system execute</summary>
	enum class LPF_Autocalibration_Execute {
		finished = 0,
		start
	};

	///<summary>Channel to be monitored for status</summary>
	enum class Channel_Status_Monitor {
		channel_1 = 0,
		channel_2,
		channel_3,
		channel_4,
	};

	///<summary>Temperature measurement mode</summary>
	enum class Temp_Mode {
		single = 0,
		continuous,
	};

	///<summary>Temperature measurement system execute</summary>
	enum class Temp_Execute {
		finished = 0,
		start,
	};

	///<summary>LPF auto-calibration system status as AOK component</summary>
	enum class LPF_ACS_AOK {
		forbidden = 0,
		permitted
	};

	///<summary>PLL lock indicator status as AOK component</summary>
	enum class PLL_LI_AOK {
		forbidden = 0,
		permitted
	};

	///<summary>PLL VCO input voltage comparator status as AOK component</summary>
	enum class PLL_VCO_AOK {
		forbidden = 0,
		permitted
	};

	///<summary>RF AGC indicator status as AOK component</summary>
	enum class RF_AGC_AOK {
		forbidden = 0,
		permitted
	};

	///<summary>IC standby mode status as AOK component</summary>
	enum class StdBy_AOK {
		forbidden = 0,
		permitted
	};

	///<summary>Cumulative status indicator</summary>
	enum class AOK {
		fail = 0,
		valid
	};

	///<summary>RF AGC indicator</summary>
	enum class RF_AGC {
		input_ok = 0,
		input_lower,
		input_higher,
		impossible_AGC_damaged,
	};

	///<summary>Clock frequency source</summary>
	enum class CLK_Source {
		PLL_A = 0,
		PLL_B
	};

	///<summary>Clock type</summary>
	enum class CLK_TP {
		CMOS = 0,
		LVDS
	};

	///<summary>Clock amplitude</summary>
	enum class CLK_CC {
		V_0_23 = 0,
		V_0_34,
		V_0_45,
		V_0_56,
	};

	///<summary>Clock output DC for LVDS type</summary>
	enum class CLK_OL {
		level_1_8 = 0,
		level_2_4,
		level_2_7,
		level_external,
	};

	///<summary>Channel sideband</summary>
	enum class Channel_LSB {
		USB = 0,
		LSB,
	};

	///<summary>Channel enable</summary>
	enum class Channel_EN {
		disabled = 0,
		enabled
	};

	///<summary>IF AGC threshold</summary>
	enum class IFA_Amp_LVL {
		mV_200 = 0,
		mV_400
	};

	///<summary>Channel output load 200 Ohm external resistor</summary>
	enum class IFA_ResLoad {
		not_mounted = 0,
		mounted
	};

	///<summary>RF gain control mode</summary>
	enum class RF_AGC_Mode {
		manual = 0,
		AGC
	};

	///<summary>IFA gain control mode</summary>
	enum class IFA_AGC_Mode {
		manual = 0,
		AGC
	};

	///<summary>IFA output DC level</summary>
	enum class IFA_OP {
		level_1_55 = 0,
		level_1_75,
		level_1_90,
		level_2_00
	};

	///<summary>Output interface</summary>
	enum class IFA_OT {
		analog = 0,
		sg_mg
	};

	///<summary>RF AGC upper threshold</summary>
	enum class RF_AGC_UB {
		minus_47_dBm = 0,
		minus_45_dBm,
		minus_43_dBm,
		minus_42_dBm,
		minus_41_dBm,
		minus_40_dBm,
	};

	///<summary>RF AGC lower threshold</summary>
	enum class RF_AGC_LB {
		minus_49_dBm = 3,
		minus_46_dBm,
		minus_45_dBm,
		minus_43_dBm,
		minus_42_dBm,
	};

	///<summary>IFA coarse gain value in manual mode</summary>
	enum class IFA_Manual_Gain {
		minus_0_5_dB = 0,
		plus_10_5_dB = 3,
		plus_22_7_dB = 7,
		plus_31_5_dB = 10,
		plus_41_dB = 14,
		plus_50_7_dB = 17,
		plus_61_dB = 21,
		plus_63_dB = 23,
	};

	///<summary>IFA fine gain value</summary>
	enum class IFA_Gain {
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

	///<summary>ADC type</summary>
	enum class IFA_ADC_Clk {
		asyncronous = 1,
		rising_edge,
		falling_edge
	};

	///<summary>ADC output logic-level high</summary>
	enum class IFA_ADC_OL {
		V_1_8 = 0,
		V_2_4,
		V_2_7,
		V_external
	};

	///<summary>PLL frequency band</summary>
	enum class PLL_Band {
		L2_L3_L5 = 0,
		L1
	};

	///<summary>PLL enable</summary>
	enum class PLL_Enable {
		disabled = 0,
		enabled
	};

	///<summary>PLL tuning system execute</summary>
	enum class PLL_EXE {
		finished = 0,
		start
	};

	///<summary>VCO input voltage indication</summary>
	enum class Vco_CV {
		valid = 0,
		upper_exceeded,
		lower_exceeded
	};

	///<summary>PLL lock indicator</summary>
	enum class PLL_Lock {
		not_locked = 0,
		locked
	};
#pragma endregion enums

	///<summary>System information struct</summary>
	struct System_Info {
		std::uint32_t ID_h = 0x42;
		std::uint32_t ID_l = 0x9;
		std::uint32_t Release = 0x2;

#pragma pack(push)
#pragma pack(1)
		///<summary>Binary representation</summary>
		struct binary {
			std::uint8_t ID_h : 8;

			std::uint8_t Release : 3;
			std::uint8_t ID_l : 5;
		};
#pragma pack(pop)

		///<summary>Convert from binary representaion to the standalone variables</summary>
		///<param name='b'>Binary object</param>
		void ConvertFromBinary(const binary &b) {
			ID_h = b.ID_h;
			ID_l = b.ID_l;
			Release = b.Release;
		}
	};

	///<summary>NT1065 general settings</summary>
	struct General_Settings {
		Mode Mode = Mode::active;
		TCXO TCXO = TCXO::MHz_10;
		LO_Source LO_Source = LO_Source::PLL_A_B;
		LPF_Autocalibration_Status LPF_ACS_S = LPF_Autocalibration_Status::success;
		LPF_Autocalibration_Execute LPF_EXE = LPF_Autocalibration_Execute::start;
		Channel_Status_Monitor Ch_StNumSel = Channel_Status_Monitor::channel_1;
		Temp_Mode TS_MD = Temp_Mode::single;
		Temp_Execute TS_EXE = Temp_Execute::finished;

		LPF_ACS_AOK LPF_ACS_AOK = LPF_ACS_AOK::permitted;
		PLL_LI_AOK PLL_LI_AOK = PLL_LI_AOK::permitted;
		PLL_VCO_AOK PLL_VCO_AOK = PLL_VCO_AOK::permitted;
		RF_AGC_AOK RF_AGC_AOK = RF_AGC_AOK::forbidden;
		StdBy_AOK StdBy_AOK = StdBy_AOK::permitted;
		AOK AOK = AOK::valid;

		double TS_code = 0;

		RF_AGC RF_AGC_Down = RF_AGC::input_ok;
		RF_AGC RF_AGC_Up = RF_AGC::input_ok;
		double RF_GainSt = 0;

		IFA_Manual_Gain IFA_GainSt = IFA_Manual_Gain::minus_0_5_dB;

#pragma pack(push)
#pragma pack(1)
		///<summary>Binary representation</summary>
		struct binary {
			std::uint8_t General_Settings_Mode : 2;
			std::uint8_t General_Settings_reserved_0 : 6;

			std::uint8_t General_Settings_LO_Source : 1;
			std::uint8_t General_Settings_TCXO_sel : 1;
			std::uint8_t General_Settings_reserved_1 : 6;

			std::uint8_t General_Settings_LPF_EXE : 1;
			std::uint8_t General_Settings_LPF_ACS_S : 1;
			std::uint8_t General_Settings_reserved_2 : 6;

			std::uint8_t General_Settings_TS_EXE : 1;
			std::uint8_t General_Settings_TS_MD : 1;
			std::uint8_t General_Settings_reserved_3 : 2;
			std::uint8_t General_Settings_Ch_StNumSel : 2;
			std::uint8_t General_Settings_Unused : 2;

			std::uint8_t General_Settings_StdBy_AOK : 1;
			std::uint8_t General_Settings_RF_AGC_AOK : 1;
			std::uint8_t General_Settings_PLL_VCO_AOK : 1;
			std::uint8_t General_Settings_PLL_LI_AOK : 1;
			std::uint8_t General_Settings_LPF_ACS_AOK : 1;
			std::uint8_t General_Settings_reserved_4 : 3;


			std::uint8_t General_Settings_TS_code_h : 2;
			std::uint8_t General_Settings_reserved_6 : 2;
			std::uint8_t General_Settings_AOK : 1;
			std::uint8_t General_Settings_reserved_5 : 3;

			std::uint8_t General_Settings_TS_code_l : 8;

			std::uint8_t General_Settings_RF_GainSt : 4;
			std::uint8_t General_Settings_RF_AGC : 2;
			std::uint8_t General_Settings_reserved_7 : 2;

			std::uint8_t General_Settings_IFA_GainSt : 5;
			std::uint8_t General_Settings_reserved_8 : 3;
		};
#pragma pack(pop)

		///<summary>Convert from binary representaion to the standalone variables</summary>
		///<param name='b'>Binary object</param>
		void ConvertFromBinary(const binary &b) {
			Mode = static_cast<NT1065_Params::Mode>(b.General_Settings_Mode);
			LO_Source = static_cast<NT1065_Params::LO_Source>(b.General_Settings_LO_Source);
			TCXO = static_cast<NT1065_Params::TCXO>(b.General_Settings_TCXO_sel);
			LPF_EXE = static_cast<NT1065_Params::LPF_Autocalibration_Execute>(b.General_Settings_LPF_EXE);
			LPF_ACS_S = static_cast<NT1065_Params::LPF_Autocalibration_Status>(b.General_Settings_LPF_ACS_S);
			TS_EXE = static_cast<NT1065_Params::Temp_Execute>(b.General_Settings_TS_EXE);
			TS_MD = static_cast<NT1065_Params::Temp_Mode>(b.General_Settings_TS_MD);
			Ch_StNumSel = static_cast<Channel_Status_Monitor>(b.General_Settings_Ch_StNumSel);
			StdBy_AOK = static_cast<NT1065_Params::StdBy_AOK>(b.General_Settings_StdBy_AOK);
			RF_AGC_AOK = static_cast<NT1065_Params::RF_AGC_AOK>(b.General_Settings_RF_AGC_AOK);
			PLL_VCO_AOK = static_cast<NT1065_Params::PLL_VCO_AOK>(b.General_Settings_PLL_VCO_AOK);
			PLL_LI_AOK = static_cast<NT1065_Params::PLL_LI_AOK>(b.General_Settings_PLL_LI_AOK);
			LPF_ACS_AOK = static_cast<NT1065_Params::LPF_ACS_AOK>(b.General_Settings_LPF_ACS_AOK);
			TS_code = 417.2 - 0.722 * ((b.General_Settings_TS_code_h << 8) | b.General_Settings_TS_code_l);
			AOK = static_cast<NT1065_Params::AOK>(b.General_Settings_AOK);
			RF_GainSt = b.General_Settings_RF_GainSt * 0.95 + 11;
			RF_AGC_Up = static_cast<NT1065_Params::RF_AGC>(b.General_Settings_RF_AGC);
			RF_AGC_Down = static_cast<NT1065_Params::RF_AGC>(b.General_Settings_RF_AGC);
			IFA_GainSt = static_cast<NT1065_Params::IFA_Manual_Gain>(b.General_Settings_IFA_GainSt);
		}
	};

	///<summary>NT1065 clock settings</summary>
	struct Clock_Settings {
		std::uint8_t CDIV_R = 15;
		CLK_Source CLK_Source = CLK_Source::PLL_A;
		CLK_TP CLK_TP = CLK_TP::LVDS;
		CLK_CC CLK_CC = CLK_CC::V_0_45;
		CLK_OL CLK_OL = CLK_OL::level_1_8;

#pragma pack(push)
#pragma pack(1)
		///<summary>Binary representation</summary>
		struct binary {
			std::uint8_t Clock_Settings_CDIV_R : 5;
			std::uint8_t Clock_Settings_reserved_9 : 3;

			std::uint8_t Clock_Settings_CLK_OL : 2;
			std::uint8_t Clock_Settings_CLK_CC : 2;
			std::uint8_t Clock_Settings_CLK_TP : 1;
			std::uint8_t Clock_Settings_CLK_Source : 1;
			std::uint8_t Clock_Settings_reserved_10 : 2;
		};
#pragma pack(pop)

		///<summary>Convert from binary representaion to the standalone variables</summary>
		///<param name='b'>Binary object</param>
		void ConvertFromBinary(const binary &b) {
			CDIV_R = b.Clock_Settings_CDIV_R;
			CLK_OL = static_cast<NT1065_Params::CLK_OL>(b.Clock_Settings_CLK_OL);
			CLK_CC = static_cast<NT1065_Params::CLK_CC>(b.Clock_Settings_CLK_CC);
			CLK_TP = static_cast<NT1065_Params::CLK_TP>(b.Clock_Settings_CLK_TP);
			CLK_Source = static_cast<NT1065_Params::CLK_Source>(b.Clock_Settings_CLK_Source);
		}

	};

	///<summary>NT1065 channel settings</summary>
	struct Channel_Settings {
		Channel_LSB Ch_LSB = Channel_LSB::LSB;
		Channel_EN Ch_EN = Channel_EN::enabled;
		double LPF_code = 32.4;

		IFA_Amp_LVL IFA_AmpLvl = IFA_Amp_LVL::mV_200;
		IFA_ResLoad IFA_ResLoad = IFA_ResLoad::mounted;
		RF_AGC_Mode RF_AGC_MD = RF_AGC_Mode::manual;
		IFA_AGC_Mode IFA_AGC_MD = IFA_AGC_Mode::AGC;
		IFA_OP IFA_OP = IFA_OP::level_1_75;
		IFA_OT IFA_OT = IFA_OT::analog;
		RF_AGC_UB RF_AGC_UB = RF_AGC_UB::minus_42_dBm;
		RF_AGC_LB RF_AGC_LB = RF_AGC_LB::minus_46_dBm;

		double RF_Gain = 25.5;
		IFA_Manual_Gain IFA_ManGC = IFA_Manual_Gain::plus_41_dB;
		IFA_Gain IFA_Gain = IFA_Gain::plus_0_3_dB;
		IFA_ADC_Clk IFA_ADC_Clk = IFA_ADC_Clk::rising_edge;
		IFA_ADC_OL IFA_ADC_OL = IFA_ADC_OL::V_2_7;

#pragma pack(push)
#pragma pack(1)
		///<summary>Binary representation</summary>
		struct binary {
			std::uint8_t Channel_Settings_En : 1;
			std::uint8_t Channel_Settings_LSB : 1;
			std::uint8_t Channel_Settings_reserved_0 : 6;

			std::uint8_t Channel_Settings_LPF_code : 7;
			std::uint8_t Channel_Settings_reserved_1 : 1;

			std::uint8_t Channel_Settings_IFA_OT : 1;
			std::uint8_t Channel_Settings_IFA_OP : 2;
			std::uint8_t Channel_Settings_IFA_AGC_MD : 1;
			std::uint8_t Channel_Settings_RF_AGC_MD : 1;
			std::uint8_t Channel_Settings_IFA_ResLoad : 1;
			std::uint8_t Channel_Settings_IFA_AmpLvl : 1;
			std::uint8_t Channel_Settings_reserved_2 : 1;

			std::uint8_t Channel_Settings_RF_AGC_LB : 3;
			std::uint8_t Channel_Settings_reserved_3 : 1;
			std::uint8_t Channel_Settings_RF_AGC_UB : 3;
			std::uint8_t Channel_Settings_reserved_4 : 1;

			std::uint8_t Channel_Settings_IFA_ManGC_h : 2;
			std::uint8_t Channel_Settings_reserved_5 : 2;
			std::uint8_t Channel_Settings_RF_Gain : 4;

			std::uint8_t Channel_Settings_IFA_Gain : 5;
			std::uint8_t Channel_Settings_IFA_ManGC_l : 3;

			std::uint8_t Channel_Settings_IFA_ADC_OL : 2;
			std::uint8_t Channel_Settings_IFA_ADC_Clk : 2;
			std::uint8_t Channel_Settings_reserved_6 : 4;
		};
#pragma pack(pop)

		///<summary>Convert from binary representaion to the standalone variables</summary>
		///<param name='b'>Binary object</param>
		void ConvertFromBinary(const binary &b) {
			Ch_EN = static_cast<NT1065_Params::Channel_EN>(b.Channel_Settings_En);
			Ch_LSB = static_cast<NT1065_Params::Channel_LSB>(b.Channel_Settings_LSB);
			LPF_code = (b.Channel_Settings_LPF_code + 29.74) / 3.422;
			IFA_OT = static_cast<NT1065_Params::IFA_OT>(b.Channel_Settings_IFA_OT);
			IFA_OP = static_cast<NT1065_Params::IFA_OP>(b.Channel_Settings_IFA_OP);
			IFA_AGC_MD = static_cast<NT1065_Params::IFA_AGC_Mode>(b.Channel_Settings_IFA_AGC_MD);
			RF_AGC_MD = static_cast<NT1065_Params::RF_AGC_Mode>(b.Channel_Settings_RF_AGC_MD);
			IFA_ResLoad = static_cast<NT1065_Params::IFA_ResLoad>(b.Channel_Settings_IFA_ResLoad);
			IFA_AmpLvl = static_cast<NT1065_Params::IFA_Amp_LVL>(b.Channel_Settings_IFA_AmpLvl);
			RF_AGC_LB = static_cast<NT1065_Params::RF_AGC_LB>(b.Channel_Settings_RF_AGC_LB);
			RF_AGC_UB = static_cast<NT1065_Params::RF_AGC_UB>(b.Channel_Settings_RF_AGC_UB);
			IFA_ManGC = static_cast<NT1065_Params::IFA_Manual_Gain>((b.Channel_Settings_IFA_ManGC_h << 3) | b.Channel_Settings_IFA_ManGC_l);
			RF_Gain = b.Channel_Settings_RF_Gain * 0.95 + 11;
			IFA_ADC_OL = static_cast<NT1065_Params::IFA_ADC_OL>(b.Channel_Settings_IFA_ADC_OL);
			IFA_ADC_Clk = static_cast<NT1065_Params::IFA_ADC_Clk>(b.Channel_Settings_IFA_ADC_Clk);
		}
	};

	///<summary>NT1065 PLL settings</summary>
	struct PLL_Settings {
		PLL_Band PLL_Band = PLL_Band::L1;
		PLL_Enable PLL_EN = PLL_Enable::enabled;
		std::uint32_t NDiv_R = 159;
		std::uint8_t RDiv_R = 1;
		PLL_EXE PLL_EXE = PLL_EXE::start;

		Vco_CV Vco_CV = Vco_CV::valid;
		PLL_Lock PLL_LI = PLL_Lock::locked;

#pragma pack(push)
#pragma pack(1)
		///<summary>Binary representation</summary>
		struct binary {
			std::uint8_t PLL_Settings_PLL_EN : 1;
			std::uint8_t PLL_Settings_PLL_Band : 1;
			std::uint8_t PLL_Settings_reserved_0 : 6;

			std::uint8_t PLL_Settings_NDiv_R_h : 8;

			std::uint8_t PLL_Settings_PLL_EXE : 1;
			std::uint8_t PLL_Settings_reserved_1 : 2;
			std::uint8_t PLL_Settings_RDiv_R : 4;
			std::uint8_t PLL_Settings_NDiv_R_l : 1;

			std::uint8_t PLL_Settings_PLL_LI : 1;
			std::uint8_t PLL_Settings_Vco_CV : 2;
			std::uint8_t PLL_Settings_reserved_2 : 5;
		};
#pragma pack(pop)

		///<summary>Convert from binary representaion to the standalone variables</summary>
		///<param name='b'>Binary object</param>
		void ConvertFromBinary(const binary &b) {
			PLL_EN = static_cast<NT1065_Params::PLL_Enable>(b.PLL_Settings_PLL_EN);
			PLL_Band = static_cast<NT1065_Params::PLL_Band>(b.PLL_Settings_PLL_Band);
			NDiv_R = (b.PLL_Settings_NDiv_R_h << 1) | b.PLL_Settings_NDiv_R_l;
			PLL_EXE = static_cast<NT1065_Params::PLL_EXE>(b.PLL_Settings_PLL_EXE);
			RDiv_R = b.PLL_Settings_RDiv_R;
			PLL_LI = static_cast<NT1065_Params::PLL_Lock>(b.PLL_Settings_PLL_LI);
			Vco_CV = static_cast<NT1065_Params::Vco_CV>(b.PLL_Settings_Vco_CV);
		}
	};

	///<summary>All of the NT1065 settings</summary>
	struct Settings {
		System_Info System_Info;
		General_Settings General_Settings;
		Clock_Settings Clock_Settings;
		Channel_Settings Channel_Settings[4];
		PLL_Settings PLL_Settings[2];
	} s;

	///<summary>Get std::uint8_t pointer with buffer content</summary>
	///<returns>std::uint8_t pointer with buffer content</returns>
	std::uint8_t* GetBufferPtr() {
		auto res = registers;
		return res;
	}

	///<summary>Get std::vector with buffer content</summary>
	///<returns>std::vector with buffer content</returns>
	std::vector<std::uint8_t> GetBuffer() {
		std::vector<std::uint8_t> res(registers, registers + registers_size);
		return res;
	}

	///<summary>Set internal buffer values to external std::vector</summary>
	///<param name='src'>External array with register values</param>
	template <typename T>
	void SetBuffer(const T *src, std::size_t src_size) {
		if (src_size > registers_size)
			return;
		for (auto i = 0; i < registers_size; ++i)
			registers[i] = src[i];

		ParseBuffer();
	}

	///<summary>Set internal buffer values to external std::vector</summary>
	///<param name='src'>External std::vector with register values</param>
	template <typename T>
	void SetBuffer(const std::vector<T> &src) {
		SetBuffer(&src[0], src.size());
	}

	///<summary>Get NT1065 settings</summary>
	///<returns>Settings object</returns>
	Settings GetSettings() {
		return s;
	}

	///<summary>Set the settings struct</summary>
	///<param name='settings'>External Settings object</param>
	void SetSettings(const Settings &settings) {
		s = settings;
		FormBuffer();
	}
	
	///<summary>Parse the binary representation to get values</summary>
	void ParseBuffer() {
		s.System_Info.ConvertFromBinary(raw_params->System_Info);
		s.General_Settings.ConvertFromBinary(raw_params->General_Settings);
		s.Clock_Settings.ConvertFromBinary(raw_params->Clock_Settings);

		for (auto i = 0; i < 4; ++i)
			s.Channel_Settings[i].ConvertFromBinary(raw_params->Channel_Settings[i]);

		for (auto i = 0; i < 2; ++i)
			s.PLL_Settings[i].ConvertFromBinary(raw_params->PLL_Settings[i]);
	}

	///<summary>Get buffer from the s values</summary>
	void FormBuffer() {
		registers[0] = static_cast<std::uint8_t>(s.System_Info.ID_h);
		registers[1] = (static_cast<std::uint8_t>(s.System_Info.ID_l) << 3) | static_cast<std::uint8_t>(s.System_Info.Release);

		// General s
		registers[2] = static_cast<std::uint8_t>(s.General_Settings.Mode);
		registers[3] = (static_cast<std::uint8_t>(s.General_Settings.TCXO) << 1) | static_cast<std::uint8_t>(s.General_Settings.LO_Source);
		registers[4] = (static_cast<std::uint8_t>(s.General_Settings.LPF_ACS_S) << 1) | static_cast<std::uint8_t>(s.General_Settings.LPF_EXE);
		registers[5] = (static_cast<std::uint8_t>(s.General_Settings.Ch_StNumSel) << 4) | (static_cast<std::uint8_t>(s.General_Settings.TS_MD) << 1) |
			static_cast<std::uint8_t>(s.General_Settings.TS_EXE);
		registers[6] = (static_cast<std::uint8_t>(s.General_Settings.LPF_ACS_AOK) << 4) | (static_cast<std::uint8_t>(s.General_Settings.PLL_LI_AOK) << 3) |
			(static_cast<std::uint8_t>(s.General_Settings.PLL_VCO_AOK) << 2) | (static_cast<std::uint8_t>(s.General_Settings.RF_AGC_AOK) << 1) | static_cast<std::uint8_t>(s.General_Settings.StdBy_AOK);

		// Clock s
		registers[11] = s.Clock_Settings.CDIV_R;
		registers[12] = (static_cast<std::uint8_t>(s.Clock_Settings.CLK_Source) << 5) | (static_cast<std::uint8_t>(s.Clock_Settings.CLK_TP) << 4) |
			(static_cast<std::uint8_t>(s.Clock_Settings.CLK_CC) << 2) | static_cast<std::uint8_t>(s.Clock_Settings.CLK_OL);

		// Channel s
		for (auto i = 0; i < 4; ++i) {
			registers[13 + 7 * i] = (static_cast<std::uint8_t>(s.Channel_Settings[i].Ch_LSB) << 1) | static_cast<std::uint8_t>(s.Channel_Settings[i].Ch_EN);
			registers[14 + 7 * i] = static_cast<std::uint8_t>(std::floor(s.Channel_Settings[i].LPF_code * 3.422 - 29.74 + 0.5)); // Linear approximation (p. 16 ver. 2.05)
			registers[15 + 7 * i] = (static_cast<std::uint8_t>(s.Channel_Settings[i].IFA_AmpLvl) << 6) | (static_cast<std::uint8_t>(s.Channel_Settings[i].IFA_ResLoad) << 5) |
				(static_cast<std::uint8_t>(s.Channel_Settings[i].RF_AGC_MD) << 4) | (static_cast<std::uint8_t>(s.Channel_Settings[i].IFA_AGC_MD) << 3) |
				(static_cast<std::uint8_t>(s.Channel_Settings[i].IFA_OP) << 1) | static_cast<std::uint8_t>(s.Channel_Settings[i].IFA_OT);
			registers[16 + 7 * i] = (static_cast<std::uint8_t>(s.Channel_Settings[i].RF_AGC_UB) << 4) | static_cast<std::uint8_t>(s.Channel_Settings[i].RF_AGC_LB);
			registers[17 + 7 * i] = (static_cast<std::uint8_t>(static_cast<std::uint32_t>(std::floor(0.5 + (s.Channel_Settings[i].RF_Gain - 11) / 0.95))) << 4) | (static_cast<std::uint8_t>(s.Channel_Settings[i].IFA_ManGC) >> 3);
			registers[18 + 7 * i] = ((static_cast<std::uint8_t>(s.Channel_Settings[i].IFA_ManGC) & 0x7) << 5) | static_cast<std::uint8_t>(s.Channel_Settings[i].IFA_Gain);
			registers[19 + 7 * i] = (static_cast<std::uint8_t>(s.Channel_Settings[i].IFA_ADC_Clk) << 2) | static_cast<std::uint8_t>(s.Channel_Settings[i].IFA_ADC_OL);
		}

		// PLL s
		for (auto i = 0; i < 2; ++i) {
			registers[41 + 4 * i] = (static_cast<std::uint8_t>(s.PLL_Settings[i].PLL_Band) << 1) | static_cast<std::uint8_t>(s.PLL_Settings[i].PLL_EN);
			registers[42 + 4 * i] = static_cast<std::uint8_t>(s.PLL_Settings[i].NDiv_R >> 1);
			registers[43 + 4 * i] = ((static_cast<std::uint8_t>(s.PLL_Settings[i].NDiv_R) & 0x1) << 7) | (s.PLL_Settings[i].RDiv_R << 3) | static_cast<std::uint8_t>(s.PLL_Settings[i].PLL_EXE);
			registers[44 + 4 * i] = (static_cast<std::uint8_t>(s.PLL_Settings[i].Vco_CV) << 1) | static_cast<std::uint8_t>(s.PLL_Settings[i].PLL_LI);
		}
	}

	///<summary>Save parameters to file</summary>
	///<param name='filename'>File address</param>
	void SaveParams(const std::string &filename = "Test.hex") {
		std::ofstream of(filename.c_str());
		if (of.is_open()) {
			of << ";NT1065.2\n";
			for (auto i = 0; i < sizeof(registers); ++i) {
				of << "Reg" << std::dec << i << "\t" << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << static_cast<std::int32_t>(registers[i]) << "\n";
			}
		}
		of.flush();
		of.close();
	}

private:
	static const std::size_t registers_size = 49;

	///<summary>Internal array to store register values</summary>
	std::uint8_t registers[registers_size];

#pragma pack(push)
#pragma pack(1)
	///<summary>Service struct to combine all of the binary representations</summary>
	struct byte_registers {
		System_Info::binary System_Info;
		General_Settings::binary General_Settings;
		Clock_Settings::binary Clock_Settings;
		Channel_Settings::binary Channel_Settings[4];
		PLL_Settings::binary PLL_Settings[2];

		byte_registers() {
			std::memset(this, 0, sizeof(byte_registers));
		}
	} *raw_params;
#pragma pack(pop)
};

#define outl(val, addr) (*(volatile unsigned int*)(addr) = (unsigned int)(val))
#define inl(addr) *(volatile unsigned int*)(addr)

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4312)
#endif // WIN32
///<summary>Class for performing the SPI flashing on the MC127.01 board</summary>
class NT1065_SPI_Setup {
public:
	///<summary>Setup status</summary>
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


	///<summary>Setup SPI as master device. Refer to the BBP2 user guide</summary>
	void Setup_SPI_Master() {
		// Clock setup (5 MHz)
		*reinterpret_cast<std::uint32_t*>(SSPCPSR) = 0x8;
	
		// SPI mode setup
		*reinterpret_cast<std::uint32_t*>(SSPCR0) = 0xF;

		// SPI master/slave setup 
		*reinterpret_cast<std::uint32_t*>(SSPCR1) = 0x2;	
	}

	///<summary>Set active device number</summary>
	///<param name='device_number'>SPI device number</param>
	template <typename T>
	void SPI_Set_Active_Device(T device_number) {
		if (device_number > 7) 
			return;
		
		*reinterpret_cast<std::uint32_t*>(ARMSC_SPICSCTL) = device_number;
	}

	///<summary>Send data to the NT1065. Some unknown legacy code runs here</summary>
	///<param name='buf'>Partition to send</param>
	NT1065_Status Send_Partition(const std::uint8_t *buf) {
		// Wait for previous data to be sent
		while (*reinterpret_cast<std::uint32_t*>(SSPSR) & 0x10) {
			;
		}

		// std::vector constructor would be more preferable, but STL by DS-5 doesn't support C++11
		std::uint32_t first_pack[] = { 2, 3, 41, 45, 42, 46, 43, 47, };
		for (auto i = 0; i < sizeof(first_pack) / sizeof(first_pack[0]); ++i)
			WriteRegistry(first_pack[i], buf[first_pack[i]]);

		// Execute PLL tuning
		WriteRegistry(43, buf[43] | 0x1);
		WriteRegistry(47, buf[47] | 0x1);

		Delay(160000);

		std::uint32_t filter_pack[] = { 14, 21, 28, 35, 4, };
		for (auto i = 0; i < sizeof(filter_pack) / sizeof(filter_pack[0]); ++i)
			WriteRegistry(filter_pack[i], buf[filter_pack[i]]);

		Delay(2200000);

		std::uint32_t second_pack[] = { 12, 11, 16, 23, 30, 37, 15, 22, 29, 36, 19, 26, 33, 40, 13, 20, 27, 34, };
		for (auto i = 0; i < sizeof(second_pack) / sizeof(second_pack[0]); ++i)
			WriteRegistry(second_pack[i], buf[second_pack[i]]);

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

	///<summary>Read single NT1065 registry</summary>
	///<param name='reg'>Number of registry</param>
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
	
	///<summary>Delay</summary>
	///<param name='n_Ticks'>Number of ticks to wait (?)</param>
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
	///<summary>Object of NT1065_Params with values</summary>
	NT1065_Params p;

	///<summary>Main setup function</summary>
	///<returns>Setup status</returns>
	NT1065_Status Setup() {
		Setup_SPI_Master();
		SPI_Set_Active_Device(2);
		auto NT1065_ID = (ReadRegistry(0) << 8) | ReadRegistry(1);
		auto true_ID = 0x214A;
		if (NT1065_ID == true_ID) {
			std::printf("NT1065_ID ok\n");
			auto result = Send_Partition(p.GetBufferPtr());
			if (result == NT1065_Status::PLL_Lock_Ok){
				std::printf("NT1065_PLL_Lock ok\n");
				return NT1065_Status::Ok;
			}
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

#endif // !_NT1065_SETUP_HPP_
