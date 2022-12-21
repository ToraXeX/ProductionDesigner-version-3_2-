#include "Main.h"

namespace ProductionDesigner {

	//������������� ����������� �����
	void Main::IniControls()
	{
		tableLayoutPanel2->BorderStyle = BorderStyle::FixedSingle;
		tableLayoutPanel3->BorderStyle = BorderStyle::FixedSingle;
		tableLayoutPanel4->BorderStyle = BorderStyle::FixedSingle;
		toolStrip1->Renderer = gcnew Renderer(SelectedColor);
		toolStrip2->Renderer = gcnew Renderer(SelectedColor);
		toolStrip3->Renderer = gcnew Renderer(SelectedColor);
		openFileDialog1->Filter = "(*.xml)|*.xml";
		saveFileDialog1->Filter = "(*.xml)|*.xml";
		exportFileDialog->Filter = "(*.jpg)|*.jpg";
		toolMove->Select();
		selected_button= ButtonType::Move;
	}
	//���������� �����������
	void Main::UpdatePicture()
	{
		pole->Paint();
		pictureBox1->Refresh();

	}

	Main::Main(void)
	{
		InitializeComponent();
		IniControls();
		pole = gcnew Pole(pictureBox1->Size);
		pictureBox1->Image = pole->image;
		//���������� ������ ���������
		for (double i = MIN_SCALE; i <= MAX_SCALE; i += STEP_SCALE)
		{
			comboboxScale->Items->Add(i);
		}
		comboboxScale->Text = DEFAULT_SCALE.ToString();
		comboboxScale->DropDownStyle = ComboBoxStyle::DropDownList;
	}
	//�������� TextBox ��� ��������������
	TextBox^ Main::CreateTextBox(TemplatePaint^ obj)
	{
		//����������� ��������� TextBox
		Point loc;
		if (obj->GetType()== PaintSystem::Connection::typeid)
		{
			PaintSystem::Connection^ line_object = (PaintSystem::Connection^)obj;
			loc = middle(line_object->f1->Location, line_object->f2->Location);
		}
		else
		{
			ObjectPaint^ figure_object = (ObjectPaint^)obj;
			loc = figure_object->Location;
		}
		if (!loc.IsEmpty)
		{
			//�������� �������� TextBox
			TextBox^ text = gcnew TextBox();
			text->Text = obj->text;
			array<int>^ rows_height = tableLayoutPanel4->GetRowHeights();
			loc.X += tableLayoutPanel4->Location.X - text->Width / 2;
			loc.Y += tableLayoutPanel4->Location.Y + tableLayoutPanel4->GetRowHeights()[0] - 8;
			text->Location = loc;
			//��������� ������� TextBox
			text->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ProductionDesigner::Main::OnKeyDown);
			this->Controls->Add(text);
			//���������
			text->BringToFront();//����������� �� �������� ����� �����
			text->Select();//��������� ������
			return text;
		}
		else
		{
			return nullptr;
		}
	}
	//����� ������
	void Main::ResetStyle()
	{
		buttonProcess->BackColor = MainColor;
		buttonConnection->BackColor = MainColor;
		toolMove->BackColor = MainColor;
		toolRemove->BackColor = MainColor;
		buttonCondition->BackColor = MainColor;
		buttonConnectionDotted->BackColor = MainColor;
	}
	//��������� ������� �� �������� ���������
	void Main::ChangeText()
	{
		if (edit != nullptr && textbox != nullptr)
		{
			edit->text = textbox->Text;
			Controls->Remove(textbox);
			UpdatePicture();
			edit_enable = false;
		}
	}
	//������ ���������� �������� ��������
	System::Void Main::buttonProcess_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selected_button = ButtonType::Process;
		ResetStyle();
		buttonProcess->BackColor = SelectedColor;
	}
	//������ ���������� �������
	System::Void Main::buttonCondition_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selected_button = ButtonType::Condition;
		ResetStyle();
		buttonCondition->BackColor = SelectedColor;
	}

	//������ ���������� ����������
	System::Void Main::buttonConnection_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selected_button = ButtonType::Connection;
		ResetStyle();
		buttonConnection->BackColor = SelectedColor;
	}
	//������ ���������� ����������� ����������
	System::Void Main::buttonConnectionDotted_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selected_button = ButtonType::ConnectionDotted;
		ResetStyle();
		buttonConnectionDotted->BackColor = SelectedColor;
	}
	System::Void Main::toolStrip_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e)
	{

		if (line != nullptr && connect_enable)
		{
			pole->RemoveLine(line);
			connect_enable = false;
			UpdatePicture();
		}

	}
	System::Void Main::buttonExport_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (exportFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				String^ url = exportFileDialog->FileName;
				pictureBox1->Image->Save(url);
				MessageBox::Show("����������� ���������", "�����������", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (...)
			{
				MessageBox::Show("������ ��� ���������� �����", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	System::Void Main::comboboxScale_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
		double scale_value = Convert::ToDouble(comboboxScale->Text);
		pole->SetScale(scale_value);
		UpdatePicture();
	}
	//������ ������ �������� �����������
	System::Void Main::toolMove_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selected_button = ButtonType::Move;
		ResetStyle();
		toolMove->BackColor = SelectedColor;
	}
	//������ ������ �������� ��������
	System::Void Main::toolRemove_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selected_button = ButtonType::Remove;
		ResetStyle();
		toolRemove->BackColor = SelectedColor;
	}
	//������ ������� ����
	System::Void Main::toolClear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		pole->Clear();
		UpdatePicture();
	}
	//���������� ������
	System::Void Main::buttonSave_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				String^ url = saveFileDialog1->FileName;
				file->Save(pole, url);
				MessageBox::Show("������ ���������", "�����������", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (...)
			{
				MessageBox::Show("������ ��� ���������� �����", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	//�������� ������
	System::Void Main::buttonOpen_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				String^ url = openFileDialog1->FileName;
				Pole^ new_area = file->Load(url);
				if (new_area != nullptr)
				{
					comboboxScale->Text = new_area->GetScale().ToString();
					pole = new_area;
					UpdatePicture();
				}
			}
			catch (...)
			{
				MessageBox::Show("������ ��� �������� �����", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	//��������� ������� ������� ����� ������ ����
	System::Void Main::pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if(e->Button == System::Windows::Forms::MouseButtons::Left && selected_button == ProductionDesigner::Move && !edit_enable)
		{
			object = pole->GetFigure(e->Location);
			if (object != nullptr) 
			{ 
				move_enable = true; 
			}
		}
	}
	//��������� ������� ��������
	System::Void Main::pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		//�������� �����
		if (object != nullptr && move_enable)
		{
			object->Location = e->Location;
			UpdatePicture();
		}
		//�������� ����� ���������� �����
		if (line != nullptr && connect_enable)
		{
			line->FlowPoint = e->Location;
			UpdatePicture();
		}
	}
	//��������� ������� ������� �������
	System::Void Main::pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			if (edit_enable)
			{
				TemplatePaint^ base = pole->GetObject(e->Location);
				if (base == nullptr || base != edit)
				{
					ChangeText();
				}
			}
			bool multiselect = false;
			if (System::Windows::Input::Keyboard::IsKeyDown(System::Windows::Input::Key::LeftCtrl))
				multiselect = true;
			
			switch (selected_button)
			{
			case ProductionDesigner::Process://���������� ����� ��������
			{
				double scale_value = Convert::ToDouble(comboboxScale->Text);
				pole->AddFigure(e->Location, ObjectType::_ActionBlock, scale_value);
				if (!multiselect)
					toolMove_Click(sender, e);
				break;
			}
			case ProductionDesigner::Condition://���������� �������
			{
				double scale_value = Convert::ToDouble(comboboxScale->Text);
				pole->AddFigure(e->Location, ObjectType::_ConditionBlock, scale_value);
				if (!multiselect)
					toolMove_Click(sender, e);
				break;
			}
			case ProductionDesigner::Connection://���������� �����
			{
				ObjectPaint^ f = pole->GetFigure(e->Location);
				if (f != nullptr)
				{
					if (!connect_enable)
					{
						line = gcnew PaintSystem::Connection(f, e->Location, "");
					}
					else
					{
						line->ConnectFigure(f);
						if (!multiselect)
							toolMove_Click(sender, e);

					}
					connect_enable = pole->AddLine(line);									
				}
				break;
			}
			case ProductionDesigner::ConnectionDotted://���������� ���������� �����
			{
				ObjectPaint^ f = pole->GetFigure(e->Location);
				if (f != nullptr)
				{
					if (!connect_enable)
					{
						line = gcnew PaintSystem::Connection(f, e->Location, "");
					}
					else
					{
						line->ConnectFigure(f);
						if (!multiselect)
							toolMove_Click(sender, e);
					}
					line->IsDotted = true;
					connect_enable = pole->AddLine(line);
				}
				break;
			}
			case ProductionDesigner::Remove://��������
			{
				pole->RemoveObject(e->Location);
				break;
			}
			}
			move_enable = false;
			
			UpdatePicture();
		}
		//������ �������������  ����� � �������� �����
		else if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			if (line != nullptr && connect_enable)
			{
				pole->RemoveLine(line);
				connect_enable = false;
				UpdatePicture();
			}
		}
		
	}
	//�������, �������������� �������������� ��������
	System::Void  Main::pictureBox1_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left &&
			selected_button == ButtonType::Move)
		{
			//�������������� �������� ����
			edit = pole->GetObject(e->Location);
			if (edit != nullptr)
			{
				textbox = CreateTextBox(edit);
				if (textbox != nullptr)
				{
					edit_enable = true;
					UpdatePicture();
				}
			}
		}
	}

	//��������� ������� ��������� ������� ������
	System::Void Main::pictureBox1_SizeChanged(System::Object^ sender, System::EventArgs^ e)
	{
		pictureBox1->Image = pole->Resize(pictureBox1->Size);
		UpdatePicture();
	}
	//���������� ���������� ����������
	void Main::OnKeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
	{
		if (e->KeyCode == Keys::Enter)
		{
			ChangeText();
		}
	}

}

