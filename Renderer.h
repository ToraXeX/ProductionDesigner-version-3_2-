#pragma once

using namespace System::Windows::Forms;
using namespace System::Drawing;


ref class Renderer:ToolStripProfessionalRenderer
{
private:
	Brush ^back_color;
protected:
	void OnRenderButtonBackground(ToolStripItemRenderEventArgs ^e) override;
public:
	Renderer(Color back_color_on_hower);
};

