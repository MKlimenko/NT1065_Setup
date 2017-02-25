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
			std::vector<NT1065_Params::NT_Mode> params;
			for (auto i = 0; i < 4; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_Mode>(i));
			}
			TestRoutine(params, p.General_settings.Mode);
		}

		TEST_METHOD(Test_TCXO)
		{
			std::vector<NT1065_Params::NT_TCXO> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_TCXO>(i));
			}
			TestRoutine(params, p.General_settings.TCXO);
		}

		TEST_METHOD(Test_LO_Source)
		{
			std::vector<NT1065_Params::NT_LO_Source> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_LO_Source>(i));
			}
			TestRoutine(params, p.General_settings.LO_Source);
		}

		TEST_METHOD(Test_LPF_Autocalibration_Status)
		{
			std::vector<NT1065_Params::NT_LPF_Autocalibration_Status> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_LPF_Autocalibration_Status>(i));
			}
			TestRoutine(params, p.General_settings.LPF_ACS_S);
		}

		TEST_METHOD(Test_LPF_Autocalibration_Execute)
		{
			std::vector<NT1065_Params::NT_LPF_Autocalibration_Execute> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_LPF_Autocalibration_Execute>(i));
			}
			TestRoutine(params, p.General_settings.LPF_EXE);
		}

		TEST_METHOD(Test_Channel_Status_Monitor)
		{
			std::vector<NT1065_Params::NT_Channel_Status_Monitor> params;
			for (auto i = 0; i < 4; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_Channel_Status_Monitor>(i));
			}
			TestRoutine(params, p.General_settings.Ch_StNumSel);
		}

		TEST_METHOD(Test_Temp_Mode)
		{
			std::vector<NT1065_Params::NT_Temp_Mode> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_Temp_Mode>(i));
			}
			TestRoutine(params, p.General_settings.TS_MD);
		}

		TEST_METHOD(Test_Temp_Execute)
		{
			std::vector<NT1065_Params::NT_Temp_Execute> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_Temp_Execute>(i));
			}
			TestRoutine(params, p.General_settings.TS_EXE);
		}
		
		TEST_METHOD(Test_LPF_ACS_AOK)
		{
			std::vector<NT1065_Params::NT_LPF_ACS_AOK> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_LPF_ACS_AOK>(i));
			}
			TestRoutine(params, p.General_settings.LPF_ACS_AOK);
		}

		TEST_METHOD(Test_LPF_LI_AOK)
		{
			std::vector<NT1065_Params::NT_PLL_LI_AOK> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_PLL_LI_AOK>(i));
			}
			TestRoutine(params, p.General_settings.PLL_LI_AOK);
		}

		TEST_METHOD(Test_PLL_VCO_AOK)
		{
			std::vector<NT1065_Params::NT_PLL_VCO_AOK> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_PLL_VCO_AOK>(i));
			}
			TestRoutine(params, p.General_settings.PLL_VCO_AOK);
		}

		TEST_METHOD(Test_RF_AGC_AOK)
		{
			std::vector<NT1065_Params::NT_RF_AGC_AOK> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_RF_AGC_AOK>(i));
			}
			TestRoutine(params, p.General_settings.RF_AGC_AOK);
		}

		TEST_METHOD(Test_StdBy_AOK)
		{
			std::vector<NT1065_Params::NT_StdBy_AOK> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_StdBy_AOK>(i));
			}
			TestRoutine(params, p.General_settings.StdBy_AOK);
		}

		TEST_METHOD(Test_CDIV_R)
		{
			std::vector<std::uint8_t> params;
			for (auto i = 8; i < 32; ++i) {
				params.push_back(i);
			}
			TestRoutine(params, p.Clock_settings.CDIV_R);
		}

		TEST_METHOD(Test_CLK_Source)
		{
			std::vector<NT1065_Params::NT_CLK_Source> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_CLK_Source>(i));
			}
			TestRoutine(params, p.Clock_settings.CLK_Source);
		}

		TEST_METHOD(Test_CLK_TP)
		{
			std::vector<NT1065_Params::NT_CLK_TP> params;
			for (auto i = 0; i < 2; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_CLK_TP>(i));
			}
			TestRoutine(params, p.Clock_settings.CLK_TP);
		}

		TEST_METHOD(Test_CLK_CC)
		{
			std::vector<NT1065_Params::NT_CLK_CC> params;
			for (auto i = 0; i < 4; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_CLK_CC>(i));
			}
			TestRoutine(params, p.Clock_settings.CLK_CC);
		}

		TEST_METHOD(Test_CLK_OL)
		{
			std::vector<NT1065_Params::NT_CLK_OL> params;
			for (auto i = 0; i < 4; ++i) {
				params.push_back(static_cast<NT1065_Params::NT_CLK_OL>(i));
			}
			TestRoutine(params, p.Clock_settings.CLK_OL);
		}
	};
}