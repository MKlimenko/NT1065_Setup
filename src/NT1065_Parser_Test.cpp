#include "CppUnitTest.h"
#include "NT1065_Setup.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NT1065_Parser_Test
{		
	TEST_CLASS(NT1065_Parser_Test)
	{
	private:
		NT1065_Params p;

		template<typename T>
		void TestRoutine(const std::vector<T> &params, T &param_to_compare) {
			for (auto &el : params) {
				param_to_compare = el;
				p.FormBuffer();
				auto result_pre = p.GetBuffer();
				p.AssignBuffer(result_pre.data());
				p.ParseBuffer();
				if (param_to_compare != el)
					Assert::Fail();
			}
		}
	
	public:
		TEST_METHOD(Test_Mode)
		{
			std::vector<NT1065_Params::Mode> params;
			for (auto i = 0; i < 4; ++i) {
				params.push_back(static_cast<NT1065_Params::Mode>(i));
			}
			TestRoutine(params, p.General_Settings.Mode);
		}

		TEST_METHOD(Test_TCXO)
		{
			std::vector<NT1065_Params::TCXO> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::TCXO>(i));
			}
			TestRoutine(params, p.General_Settings.TCXO);
		}

		TEST_METHOD(Test_LO_Source)
		{
			std::vector<NT1065_Params::LO_Source> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::LO_Source>(i));
			}
			TestRoutine(params, p.General_Settings.LO_Source);
		}

		TEST_METHOD(Test_LPF_Autocalibration_Status)
		{
			std::vector<NT1065_Params::LPF_Autocalibration_Status> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::LPF_Autocalibration_Status>(i));
			}
			TestRoutine(params, p.General_Settings.LPF_ACS_S);
		}

		TEST_METHOD(Test_LPF_Autocalibration_Execute)
		{
			std::vector<NT1065_Params::LPF_Autocalibration_Execute> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::LPF_Autocalibration_Execute>(i));
			}
			TestRoutine(params, p.General_Settings.LPF_EXE);
		}

		TEST_METHOD(Test_Channel_Status_Monitor)
		{
			std::vector<NT1065_Params::Channel_Status_Monitor> params;
			for (auto i = 0; i < 4; ++i) {
				params.push_back(static_cast<NT1065_Params::Channel_Status_Monitor>(i));
			}
			TestRoutine(params, p.General_Settings.Ch_StNumSel);
		}

		TEST_METHOD(Test_Temp_Mode)
		{
			std::vector<NT1065_Params::Temp_Mode> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::Temp_Mode>(i));
			}
			TestRoutine(params, p.General_Settings.TS_MD);
		}

		TEST_METHOD(Test_Temp_Execute)
		{
			std::vector<NT1065_Params::Temp_Execute> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::Temp_Execute>(i));
			}
			TestRoutine(params, p.General_Settings.TS_EXE);
		}
		
		TEST_METHOD(Test_LPF_ACS_AOK)
		{
			std::vector<NT1065_Params::LPF_ACS_AOK> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::LPF_ACS_AOK>(i));
			}
			TestRoutine(params, p.General_Settings.LPF_ACS_AOK);
		}

		TEST_METHOD(Test_LPF_LI_AOK)
		{
			std::vector<NT1065_Params::PLL_LI_AOK> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::PLL_LI_AOK>(i));
			}
			TestRoutine(params, p.General_Settings.PLL_LI_AOK);
		}

		TEST_METHOD(Test_PLL_VCO_AOK)
		{
			std::vector<NT1065_Params::PLL_VCO_AOK> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::PLL_VCO_AOK>(i));
			}
			TestRoutine(params, p.General_Settings.PLL_VCO_AOK);
		}

		TEST_METHOD(Test_RF_AGC_AOK)
		{
			std::vector<NT1065_Params::RF_AGC_AOK> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::RF_AGC_AOK>(i));
			}
			TestRoutine(params, p.General_Settings.RF_AGC_AOK);
		}

		TEST_METHOD(Test_StdBy_AOK)
		{
			std::vector<NT1065_Params::StdBy_AOK> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::StdBy_AOK>(i));
			}
			TestRoutine(params, p.General_Settings.StdBy_AOK);
		}

		TEST_METHOD(Test_CDIV_R)
		{
			std::vector<std::uint8_t> params;
			for (auto i = 8; i < 32; ++i) {
				params.push_back(i);
			}
			TestRoutine(params, p.Clock_Settings.CDIV_R);
		}

		TEST_METHOD(Test_CLK_Source)
		{
			std::vector<NT1065_Params::CLK_Source> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::CLK_Source>(i));
			}
			TestRoutine(params, p.Clock_Settings.CLK_Source);
		}

		TEST_METHOD(Test_CLK_TP)
		{
			std::vector<NT1065_Params::CLK_TP> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::CLK_TP>(i));
			}
			TestRoutine(params, p.Clock_Settings.CLK_TP);
		}

		TEST_METHOD(Test_CLK_CC)
		{
			std::vector<NT1065_Params::CLK_CC> params;
			for (auto i = 0; i < 4; ++i) {
				params.push_back(static_cast<NT1065_Params::CLK_CC>(i));
			}
			TestRoutine(params, p.Clock_Settings.CLK_CC);
		}

		TEST_METHOD(Test_CLK_OL)
		{
			std::vector<NT1065_Params::CLK_OL> params;
			for (auto i = 0; i < 4; ++i) {
				params.push_back(static_cast<NT1065_Params::CLK_OL>(i));
			}
			TestRoutine(params, p.Clock_Settings.CLK_OL);
		}
	};
}