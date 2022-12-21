#include "Main.h"

namespace ProductionDesigner {

	//Инициализация компонентов формы
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
	//Обновление изображения
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
		//Заполнение списка масштабов
		for (double i = MIN_SCALE; i <= MAX_SCALE; i += STEP_SCALE)
		{
			comboboxScale->Items->Add(i);
		}
		comboboxScale->Text = DEFAULT_SCALE.ToString();
		comboboxScale->DropDownStyle = ComboBoxStyle::DropDownList;
	}
	//Создание TextBox для редактирования
	TextBox^ Main::CreateTextBox(TemplatePaint^ obj)
	{
		//Определение положения TextBox
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
			//Создание элемента TextBox
			TextBox^ text = gcnew TextBox();
			text->Text = obj->text;
			array<int>^ rows_height = tableLayoutPanel4->GetRowHeights();
			loc.X += tableLayoutPanel4->Location.X - text->Width / 2;
			loc.Y += tableLayoutPanel4->Location.Y + tableLayoutPanel4->GetRowHeights()[0] - 8;
			text->Location = loc;
			//Установка событий TextBox
			text->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ProductionDesigner::Main::OnKeyDown);
			this->Controls->Add(text);
			//Настройка
			text->BringToFront();//Отображение на переднем плане формы
			text->Select();//Выделение текста
			return text;
		}
		else
		{
			return nullptr;
		}
	}
	//Сброс стилей
	void Main::ResetStyle()
	{
		buttonProcess->BackColor = MainColor;
		buttonConnection->BackColor = MainColor;
		toolMove->BackColor = MainColor;
		toolRemove->BackColor = MainColor;
		buttonCondition->BackColor = MainColor;
		buttonConnectionDotted->BackColor = MainColor;
	}
	//Изменение тектста на объектах рисования
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
	//Кнопка добавление элемента процесса
	System::Void Main::buttonProcess_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selected_button = ButtonType::Process;
		ResetStyle();
		buttonProcess->BackColor = SelectedColor;
	}
	//Кнопка добавления условия
	System::Void Main::buttonCondition_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selected_button = ButtonType::Condition;
		ResetStyle();
		buttonCondition->BackColor = SelectedColor;
	}

	//Кнопка добавление соединения
	System::Void Main::buttonConnection_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selected_button = ButtonType::Connection;
		ResetStyle();
		buttonConnection->BackColor = SelectedColor;
	}
	//Кнопка добавления пунктирного соединения
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
				MessageBox::Show("Изображение сохранено", "Уведомление", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (...)
			{
				MessageBox::Show("Ошибка при сохранении файла", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	System::Void Main::comboboxScale_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
		double scale_value = Convert::ToDouble(comboboxScale->Text);
		pole->SetScale(scale_value);
		UpdatePicture();
	}
	//Кнопка выбора средства перемещения
	System::Void Main::toolMove_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selected_button = ButtonType::Move;
		ResetStyle();
		toolMove->BackColor = SelectedColor;
	}
	//Кнопка выбора удаления объектов
	System::Void Main::toolRemove_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selected_button = ButtonType::Remove;
		ResetStyle();
		toolRemove->BackColor = SelectedColor;
	}
	//Полная очистка поля
	System::Void Main::toolClear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		pole->Clear();
		UpdatePicture();
	}
	//Сохранение файлов
	System::Void Main::buttonSave_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				String^ url = saveFileDialog1->FileName;
				file->Save(pole, url);
				MessageBox::Show("Данные сохранены", "Уведомление", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (...)
			{
				MessageBox::Show("Ошибка при сохранении файла", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	//Открытие файлов
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
				MessageBox::Show("Ошибка при открытии файла", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	//Обработка события нажатия левой кнопки мыши
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
	//Обработка события движения
	System::Void Main::pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		//Движение фигур
		if (object != nullptr && move_enable)
		{
			object->Location = e->Location;
			UpdatePicture();
		}
		//Движение конца соединения фигур
		if (line != nullptr && connect_enable)
		{
			line->FlowPoint = e->Location;
			UpdatePicture();
		}
	}
	//Обработка события отжатия клавиши
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
			case ProductionDesigner::Process://Добавление блока действия
			{
				double scale_value = Convert::ToDouble(comboboxScale->Text);
				pole->AddFigure(e->Location, ObjectType::_ActionBlock, scale_value);
				if (!multiselect)
					toolMove_Click(sender, e);
				break;
			}
			case ProductionDesigner::Condition://Добавление условия
			{
				double scale_value = Convert::ToDouble(comboboxScale->Text);
				pole->AddFigure(e->Location, ObjectType::_ConditionBlock, scale_value);
				if (!multiselect)
					toolMove_Click(sender, e);
				break;
			}
			case ProductionDesigner::Connection://Добавление линии
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
			case ProductionDesigner::ConnectionDotted://Добавление пунктирной линии
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
			case ProductionDesigner::Remove://Удаление
			{
				pole->RemoveObject(e->Location);
				break;
			}
			}
			move_enable = false;
			
			UpdatePicture();
		}
		//Отмена присоединения  линии к элементу схемы
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
	//Событие, обрабатываюшее редактирование объектов
	System::Void  Main::pictureBox1_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left &&
			selected_button == ButtonType::Move)
		{
			//Редактирование объектов поля
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

	//Обработка события изменения размера экрана
	System::Void Main::pictureBox1_SizeChanged(System::Object^ sender, System::EventArgs^ e)
	{
		pictureBox1->Image = pole->Resize(pictureBox1->Size);
		UpdatePicture();
	}
	//Сохранение измененной информации
	void Main::OnKeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
	{
		if (e->KeyCode == Keys::Enter)
		{
			ChangeText();
		}
	}

}

