#include "MyForm.h"
#include "Integer.h"
#include "Decimal.h"
using namespace System::Windows::Forms;

void main(cli::array<System::String^>^ args)
{
	Integer i = "123";
	Decimal d = "123.3";
	vector<Number*> nums;
	nums.push_back(&i);
	nums.push_back(&d);
	for (const auto& num : nums)
		cout << *num << endl;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	BigNumClaculator::MyForm myForm;
	Application::Run(%myForm);
}
