#include "Main.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace ProductionDesigner;

[STAThread]
void main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Main form;
    Application::Run(% form);
}
