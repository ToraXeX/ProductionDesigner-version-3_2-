#include "Renderer.h"

void Renderer::OnRenderButtonBackground(ToolStripItemRenderEventArgs ^e)
{
    ToolStripButton^ button = (ToolStripButton^)e->Item;
    if (button != nullptr && button->Selected)
    {
        Rectangle bounds = Rectangle(Point::Empty, button->Size);
        e->Graphics->FillRectangle(back_color, bounds);
    }
    else
    {
        ToolStripProfessionalRenderer::OnRenderButtonBackground(e);
    }
}

Renderer::Renderer(Color back_color)
{
    this->back_color = gcnew SolidBrush(back_color);
}
