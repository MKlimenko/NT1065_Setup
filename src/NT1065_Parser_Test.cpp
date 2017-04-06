#include "CppUnitTest.h"
#include "NT1065_Params.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NT1065_Parser_Test
{		
	TEST_CLASS(NT1065_Parser_Test)
	{
	private:
		NT1065_Params p;

		template<typename T>
		bool Compare(const T& first, const T& second) {
			return first != second;
		}

		bool Compare(double first, double second) {
			std::int64_t f = static_cast<std::int64_t>(std::ceil(first * 10));
			std::int64_t s = static_cast<std::int64_t>(std::ceil(second * 10));
			return f != s;
		}

		template<typename T>
		void TestRoutine(const std::vector<T> &params, T &param_to_compare) {
			for (auto &el : params) {
				param_to_compare = el;
				p.FormBuffer();
				auto result_pre = p.GetBuffer();
				p.SetBuffer(result_pre);
				if (Compare(param_to_compare, el)) {
					std::string msg = "Failed on " + std::string(typeid(T).name()) + " test: " + std::to_string(static_cast<double>(param_to_compare))
						+ ", " + std::to_string(static_cast<double>(el));
					Logger::WriteMessage(msg.c_str());
					Assert::Fail();
				}
			}
		}

		template <typename T>
		void CommonTest(T &param_to_test, const std::vector<T> &params) {
			TestRoutine(params, param_to_test);
		}

		template <typename T>
		void CommonTest(T &param_to_test, std::size_t num_of_params) {
			std::vector<T> params;
			for (auto i = 0; i < num_of_params; ++i)
				params.push_back(static_cast<T>(i));
			CommonTest(param_to_test, params);
		}
					
	public:
		TEST_METHOD(Save_and_Load)
		{
			auto pre_buffer = p.GetBuffer();
			p.SaveParams();
			p.LoadParams();
			auto post_buffer = p.GetBuffer();
			Assert::IsTrue(pre_buffer == post_buffer);
		}

		TEST_METHOD(Mode)
		{
			CommonTest(p.s.General_Settings.Mode, 4);
		}

		TEST_METHOD(TCXO)
		{
			CommonTest(p.s.General_Settings.TCXO, 2);
		}

		TEST_METHOD(LO_Source)
		{
			CommonTest(p.s.General_Settings.LO_Source, 2);
		}

		TEST_METHOD(LPF_Autocalibration_Status)
		{
			CommonTest(p.s.General_Settings.LPF_ACS_S, 2);
		}

		TEST_METHOD(LPF_Autocalibration_Execute)
		{
			CommonTest(p.s.General_Settings.LPF_EXE, 2);
		}

		TEST_METHOD(Channel_Status_Monitor)
		{
			CommonTest(p.s.General_Settings.Ch_StNumSel, 4);
		}

		TEST_METHOD(Temp_Mode)
		{
			CommonTest(p.s.General_Settings.TS_MD, 2);
		}

		TEST_METHOD(Temp_Execute)
		{
			CommonTest(p.s.General_Settings.TS_EXE, 2);
		}
		
		TEST_METHOD(LPF_ACS_AOK)
		{
			CommonTest(p.s.General_Settings.LPF_ACS_AOK, 2);
		}

		TEST_METHOD(LPF_LI_AOK)
		{
			CommonTest(p.s.General_Settings.PLL_LI_AOK, 2);
		}

		TEST_METHOD(PLL_VCO_AOK)
		{
			CommonTest(p.s.General_Settings.PLL_VCO_AOK, 2);
		}

		TEST_METHOD(RF_AGC_AOK)
		{
			CommonTest(p.s.General_Settings.RF_AGC_AOK, 2);
		}

		TEST_METHOD(StdBy_AOK)
		{
			CommonTest(p.s.General_Settings.StdBy_AOK, 2);
		}

		TEST_METHOD(CDIV_R)
		{
			std::vector<std::uint8_t> params;
			for (auto i = 8; i < 32; ++i) 
				params.push_back(i);
			CommonTest(p.s.Clock_Settings.CDIV_R, params);
		}

		TEST_METHOD(CLK_Source)
		{
			CommonTest(p.s.Clock_Settings.CLK_Source, 2);
		}

		TEST_METHOD(CLK_TP)
		{
			CommonTest(p.s.Clock_Settings.CLK_TP, 2);
		}

		TEST_METHOD(CLK_CC)
		{
			CommonTest(p.s.Clock_Settings.CLK_CC, 4);
		}

		TEST_METHOD(CLK_OL)
		{
			CommonTest(p.s.Clock_Settings.CLK_OL, 4);
		}
		
		TEST_METHOD(Channel_LSB)
		{
			for (auto channel = 0; channel < 4; ++channel) 
				CommonTest(p.s.Channel_Settings[channel].Ch_LSB, 2);
		}

		TEST_METHOD(Channel_En)
		{
			for (auto channel = 0; channel < 4; ++channel) 
				CommonTest(p.s.Channel_Settings[channel].Ch_EN, 2);
		}

		TEST_METHOD(Channel_LPF_code)
		{
			for (auto channel = 0; channel < 4; ++channel) {
				std::vector<double> params = { 11.22, 14.83, 15.12, 15.69, 16.59, 17.60, 18.33, 19.36, 20.31, 21.13,
					21.92, 21.89, 23.82, 24.94, 25.45, 26.50, 27.38, 28.31, 29.02, 29.64, 30.47, 31.19, 31.55, 43.41, };
				CommonTest(p.s.Channel_Settings[channel].LPF_code, params);
			}
		}

		TEST_METHOD(Channel_IFA_OT)
		{
			for (auto channel = 0; channel < 4; ++channel) 
				CommonTest(p.s.Channel_Settings[channel].IFA_OT, 2);
		}

		TEST_METHOD(Channel_IFA_OP)
		{
			for (auto channel = 0; channel < 4; ++channel) 
				CommonTest(p.s.Channel_Settings[channel].IFA_OP, 4);
		}

		TEST_METHOD(Channel_IFA_AGC_MD)
		{
			for (auto channel = 0; channel < 4; ++channel)
				CommonTest(p.s.Channel_Settings[channel].IFA_AGC_MD, 2);
		}

		TEST_METHOD(Channel_RF_AGC_MD)
		{
			for (auto channel = 0; channel < 4; ++channel)
				CommonTest(p.s.Channel_Settings[channel].RF_AGC_MD, 2);
		}

		TEST_METHOD(Channel_IFA_ResLoad)
		{
			for (auto channel = 0; channel < 4; ++channel)
				CommonTest(p.s.Channel_Settings[channel].IFA_ResLoad, 2);
		}

		TEST_METHOD(Channel_IFA_AmpLvl)
		{
			for (auto channel = 0; channel < 4; ++channel)
				CommonTest(p.s.Channel_Settings[channel].IFA_AmpLvl, 2);
		}

		TEST_METHOD(Channel_RF_AGC_LB)
		{
			std::vector<NT1065_Params::RF_AGC_LB> params;
			for (auto i = 3; i < 8; ++i) 
				params.push_back(static_cast<NT1065_Params::RF_AGC_LB>(i));
			for (auto channel = 0; channel < 4; ++channel)
				CommonTest(p.s.Channel_Settings[channel].RF_AGC_LB, params);
		}

		TEST_METHOD(Channel_RF_AGC_UB)
		{
			for (auto channel = 0; channel < 4; ++channel)
				CommonTest(p.s.Channel_Settings[channel].RF_AGC_UB, 6);
		}

		TEST_METHOD(Channel_RF_Gain)
		{
			std::vector<double> params;
			for (auto i = 11.0; i <= 25.5; i += 0.95)
				params.push_back(i);
			for (auto channel = 0; channel < 4; ++channel)
				CommonTest(p.s.Channel_Settings[channel].RF_Gain, params);
		}

		TEST_METHOD(Channel_IFA_ManGC)
		{
			std::vector<std::int32_t> params_tmp = { 0, 3, 7, 10, 14, 17, 21, 23 };
			std::vector<NT1065_Params::IFA_Manual_Gain> params;
			for (auto i = 0; i < params_tmp.size(); ++i)
				params.push_back(static_cast<NT1065_Params::IFA_Manual_Gain>(params_tmp[i]));
			for (auto channel = 0; channel < 4; ++channel)
				CommonTest(p.s.Channel_Settings[channel].IFA_ManGC, params);
		}

		TEST_METHOD(Channel_IFA_Gain)
		{
			std::vector<NT1065_Params::IFA_Gain> params;
			for (auto i = 7; i < 26; ++i)
				params.push_back(static_cast<NT1065_Params::IFA_Gain>(i));

			for (auto channel = 0; channel < 4; ++channel)
				CommonTest(p.s.Channel_Settings[channel].IFA_Gain, params);
		}

		TEST_METHOD(Channel_IFA_ADC_Clk)
		{
			std::vector<NT1065_Params::IFA_ADC_Clk> params;
			for (auto i = 1; i < 4; ++i)
				params.push_back(static_cast<NT1065_Params::IFA_ADC_Clk>(i));

			for (auto channel = 0; channel < 4; ++channel)
				CommonTest(p.s.Channel_Settings[channel].IFA_ADC_Clk, params);
		}

		TEST_METHOD(Channel_IFA_ADC_OL)
		{
			for (auto channel = 0; channel < 4; ++channel)
				CommonTest(p.s.Channel_Settings[channel].IFA_ADC_OL, 4);
		}

		TEST_METHOD(PLL_Band)
		{
			for (auto PLL = 0; PLL < 2; ++PLL)
				CommonTest(p.s.PLL_Settings[PLL].PLL_Band, 2);
		}

		TEST_METHOD(PLL_En)
		{
			for (auto PLL = 0; PLL < 2; ++PLL)
				CommonTest(p.s.PLL_Settings[PLL].PLL_EN, 2);
		}

		TEST_METHOD(PLL_NDiv_R)
		{
			std::vector<std::uint32_t> params;
			for (auto i = 48; i < 512; ++i)
				params.push_back(i);
			for (auto PLL = 0; PLL < 2; ++PLL)
				CommonTest(p.s.PLL_Settings[PLL].NDiv_R, params);
		}

		TEST_METHOD(PLL_RDiv_R)
		{
			std::vector<std::uint8_t> params;
			for (auto i = 1; i < 16; ++i)
				params.push_back(i);
			for (auto PLL = 0; PLL < 2; ++PLL)
				CommonTest(p.s.PLL_Settings[PLL].RDiv_R, params);
		}

		TEST_METHOD(PLL_EXE)
		{
			for (auto PLL = 0; PLL < 2; ++PLL)
				CommonTest(p.s.PLL_Settings[PLL].PLL_EXE, 2);
		}

		TEST_METHOD(PLL_Vco_CV)
		{
			for (auto PLL = 0; PLL < 2; ++PLL)
				CommonTest(p.s.PLL_Settings[PLL].Vco_CV, 3);
		}
		
		TEST_METHOD(PLL_LI)
		{
			for (auto PLL = 0; PLL < 2; ++PLL)
				CommonTest(p.s.PLL_Settings[PLL].PLL_LI, 2);
		}
	};
}