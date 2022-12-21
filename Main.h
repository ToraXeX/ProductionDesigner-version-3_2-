#pragma once
#include "Renderer.h"
#include "FileControl.h"
#include "Paint.h"

namespace ProductionDesigner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace PaintSystem;

	//Тип нажатой кнопки
	enum ButtonType
	{
		Process, //Процесс
		Condition,//Условие
		Connection, //Соединение
		ConnectionDotted,//Пунктирное соединение
		Move, //Движение
		Remove, //Удаление
	};

	/// <summary>
	/// Сводка для Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	private:
		//Константы
		const double MIN_SCALE = 0.5;
		const double MAX_SCALE = 3;
		const double STEP_SCALE = 0.25;
		const double DEFAULT_SCALE = 1;
		//Свойства и объекты
		Color MainColor = System::Drawing::Color::Transparent;//Основной цвет заднего фона кнопок
		Color SelectedColor = Color::FromArgb(213, 185, 185);//Color::MistyRose;//Color::FromArgb(102,163,97);//Цвет наведения/выбора кнопки
		bool move_enable;//Флаг разрешения движения
		bool connect_enable;//Флаг разрешения соединения
		bool edit_enable;//Флаг разрешения редактирования
		ObjectPaint ^object;//Объект диаграммы(Элемент диаграммы или соединение)
		TemplatePaint ^edit;//Элемент диаграммы
		PaintSystem::Connection ^line;//Соединение
		Pole^ pole;//Поле рисования
		TextBox^ textbox;//Элемент управления редактированием
		FileControl^ file;//Менеджер файлов
	private: System::Windows::Forms::ToolStripLabel^ toolStripLabel2;
	private: System::Windows::Forms::ToolStripButton^ buttonCondition;
	private: System::Windows::Forms::ToolStripButton^ buttonConnectionDotted;
	private: System::Windows::Forms::ToolStripButton^ buttonExport;
	private: System::Windows::Forms::SaveFileDialog^ exportFileDialog;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ToolStrip^ toolStrip4;
	private: System::Windows::Forms::ToolStripLabel^ toolStripLabel1;
	private: System::Windows::Forms::ToolStripComboBox^ comboboxScale;







		   ButtonType selected_button;//Тип нажатой кнопки
		//Методы
		void Main::ChangeText();//Метод изменения текста
		TextBox^ CreateTextBox(TemplatePaint^ object);//Метод создания TextBox
		void ResetStyle();//Метод сброса стилей
		void IniControls();//Инициализация компонентов формы
		void UpdatePicture();//Обновление изображения PictureBox
	private: System::Windows::Forms::ToolStrip^ toolStrip3;
	private: System::Windows::Forms::ToolStripButton^ buttonOpen;

	private: System::Windows::Forms::ToolStripButton^ buttonSave;

	private: System::Windows::Forms::Label^ label2;



	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	public:
		Main(void);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:












	private: System::Windows::Forms::ToolStrip^ toolStrip2;
	private: System::Windows::Forms::ToolStripButton^ toolMove;
	private: System::Windows::Forms::ToolStripButton^ toolRemove;
	private: System::Windows::Forms::ToolStripButton^ toolClear;











	private: System::Windows::Forms::Label^ label1;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
	private: System::Windows::Forms::PictureBox^ pictureBox1;



	private: System::Windows::Forms::ToolStrip^ toolStrip1;







	private: System::Windows::Forms::ToolStripLabel^ toolStripLabel3;
	private: System::Windows::Forms::ToolStripButton^ buttonProcess;





	private: System::Windows::Forms::ToolStripLabel^ toolStripLabel4;
	private: System::Windows::Forms::ToolStripButton^ buttonConnection;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;










	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->toolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolMove = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolClear = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolRemove = (gcnew System::Windows::Forms::ToolStripButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->toolStrip3 = (gcnew System::Windows::Forms::ToolStrip());
			this->buttonOpen = (gcnew System::Windows::Forms::ToolStripButton());
			this->buttonSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->buttonExport = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripLabel3 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->buttonProcess = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripLabel2 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->buttonCondition = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripLabel4 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->buttonConnection = (gcnew System::Windows::Forms::ToolStripButton());
			this->buttonConnectionDotted = (gcnew System::Windows::Forms::ToolStripButton());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->toolStrip4 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->comboboxScale = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->exportFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->toolStrip2->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->toolStrip3->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->toolStrip4->SuspendLayout();
			this->SuspendLayout();
			// 
			// toolStrip2
			// 
			this->toolStrip2->AutoSize = false;
			this->toolStrip2->BackColor = System::Drawing::Color::RosyBrown;
			this->toolStrip2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->toolStrip2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->toolStrip2->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip2->ImageScalingSize = System::Drawing::Size(40, 40);
			this->toolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolMove, this->toolClear,
					this->toolRemove
			});
			this->toolStrip2->Location = System::Drawing::Point(0, 0);
			this->toolStrip2->Name = L"toolStrip2";
			this->toolStrip2->Size = System::Drawing::Size(677, 60);
			this->toolStrip2->TabIndex = 1;
			this->toolStrip2->Text = L"toolStrip2";
			this->toolStrip2->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Main::toolStrip_ItemClicked);
			// 
			// toolMove
			// 
			this->toolMove->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolMove->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolMove.Image")));
			this->toolMove->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolMove->Margin = System::Windows::Forms::Padding(10, 1, 0, 2);
			this->toolMove->Name = L"toolMove";
			this->toolMove->Size = System::Drawing::Size(44, 57);
			this->toolMove->Text = L"toolStripButton6";
			this->toolMove->ToolTipText = L"Указатель";
			this->toolMove->Click += gcnew System::EventHandler(this, &Main::toolMove_Click);
			// 
			// toolClear
			// 
			this->toolClear->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->toolClear->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolClear->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolClear.Image")));
			this->toolClear->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolClear->Margin = System::Windows::Forms::Padding(0, 1, 10, 2);
			this->toolClear->Name = L"toolClear";
			this->toolClear->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->toolClear->Size = System::Drawing::Size(44, 57);
			this->toolClear->Text = L"Очистить пространство";
			this->toolClear->Click += gcnew System::EventHandler(this, &Main::toolClear_Click);
			// 
			// toolRemove
			// 
			this->toolRemove->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->toolRemove->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolRemove->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolRemove.Image")));
			this->toolRemove->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolRemove->Margin = System::Windows::Forms::Padding(0, 1, 10, 2);
			this->toolRemove->Name = L"toolRemove";
			this->toolRemove->Size = System::Drawing::Size(44, 57);
			this->toolRemove->Text = L"Удалить объект";
			this->toolRemove->Click += gcnew System::EventHandler(this, &Main::toolRemove_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(165, 3);
			this->label1->Margin = System::Windows::Forms::Padding(5, 3, 3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(675, 21);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Инструменты";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				160)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel2->Controls->Add(this->label1, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->tableLayoutPanel3, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->tableLayoutPanel4, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->label2, 0, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(843, 561);
			this->tableLayoutPanel2->TabIndex = 9;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 1;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel3->Controls->Add(this->toolStrip3, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->toolStrip1, 0, 2);
			this->tableLayoutPanel3->Controls->Add(this->panel1, 0, 1);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(3, 27);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 3;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 60)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel3->Size = System::Drawing::Size(154, 531);
			this->tableLayoutPanel3->TabIndex = 10;
			// 
			// toolStrip3
			// 
			this->toolStrip3->AutoSize = false;
			this->toolStrip3->BackColor = System::Drawing::Color::RosyBrown;
			this->toolStrip3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->toolStrip3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->toolStrip3->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip3->ImageScalingSize = System::Drawing::Size(40, 40);
			this->toolStrip3->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->buttonOpen, this->buttonSave,
					this->buttonExport
			});
			this->toolStrip3->Location = System::Drawing::Point(0, 0);
			this->toolStrip3->Name = L"toolStrip3";
			this->toolStrip3->Size = System::Drawing::Size(154, 60);
			this->toolStrip3->TabIndex = 2;
			this->toolStrip3->Text = L"toolStrip3";
			this->toolStrip3->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Main::toolStrip_ItemClicked);
			// 
			// buttonOpen
			// 
			this->buttonOpen->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->buttonOpen->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonOpen.Image")));
			this->buttonOpen->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonOpen->Name = L"buttonOpen";
			this->buttonOpen->Size = System::Drawing::Size(44, 57);
			this->buttonOpen->Text = L"toolStripButton6";
			this->buttonOpen->ToolTipText = L"Открыть файл";
			this->buttonOpen->Click += gcnew System::EventHandler(this, &Main::buttonOpen_Click);
			// 
			// buttonSave
			// 
			this->buttonSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->buttonSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonSave.Image")));
			this->buttonSave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonSave->Margin = System::Windows::Forms::Padding(11, 1, 0, 2);
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(44, 57);
			this->buttonSave->Text = L"toolStripButton7";
			this->buttonSave->ToolTipText = L"Сохранить файл";
			this->buttonSave->Click += gcnew System::EventHandler(this, &Main::buttonSave_Click);
			// 
			// buttonExport
			// 
			this->buttonExport->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->buttonExport->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->buttonExport->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonExport.Image")));
			this->buttonExport->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonExport->Name = L"buttonExport";
			this->buttonExport->Size = System::Drawing::Size(44, 57);
			this->buttonExport->Text = L"toolStripButton1";
			this->buttonExport->ToolTipText = L"Экспортировать изображение";
			this->buttonExport->Click += gcnew System::EventHandler(this, &Main::buttonExport_Click);
			// 
			// toolStrip1
			// 
			this->toolStrip1->AutoSize = false;
			this->toolStrip1->BackColor = System::Drawing::Color::RosyBrown;
			this->toolStrip1->CanOverflow = false;
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->toolStrip1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->toolStrip1->ImageScalingSize = System::Drawing::Size(140, 80);
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->toolStripLabel3,
					this->buttonProcess, this->toolStripLabel2, this->buttonCondition, this->toolStripLabel4, this->buttonConnection, this->buttonConnectionDotted
			});
			this->toolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::Table;
			this->toolStrip1->Location = System::Drawing::Point(0, 90);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Padding = System::Windows::Forms::Padding(0, 10, 0, 0);
			this->toolStrip1->Size = System::Drawing::Size(154, 477);
			this->toolStrip1->TabIndex = 0;
			this->toolStrip1->Text = L"toolStrip1";
			this->toolStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Main::toolStrip_ItemClicked);
			// 
			// toolStripLabel3
			// 
			this->toolStripLabel3->Name = L"toolStripLabel3";
			this->toolStripLabel3->Size = System::Drawing::Size(71, 21);
			this->toolStripLabel3->Text = L"Процесс";
			// 
			// buttonProcess
			// 
			this->buttonProcess->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->buttonProcess->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonProcess.Image")));
			this->buttonProcess->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonProcess->Name = L"buttonProcess";
			this->buttonProcess->Size = System::Drawing::Size(144, 84);
			this->buttonProcess->Text = L"Процесс";
			this->buttonProcess->Click += gcnew System::EventHandler(this, &Main::buttonProcess_Click);
			// 
			// toolStripLabel2
			// 
			this->toolStripLabel2->Name = L"toolStripLabel2";
			this->toolStripLabel2->Size = System::Drawing::Size(68, 21);
			this->toolStripLabel2->Text = L"Условие";
			// 
			// buttonCondition
			// 
			this->buttonCondition->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->buttonCondition->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonCondition.Image")));
			this->buttonCondition->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonCondition->Name = L"buttonCondition";
			this->buttonCondition->Size = System::Drawing::Size(144, 84);
			this->buttonCondition->Text = L"toolStripButton1";
			this->buttonCondition->ToolTipText = L"Условие";
			this->buttonCondition->Click += gcnew System::EventHandler(this, &Main::buttonCondition_Click);
			// 
			// toolStripLabel4
			// 
			this->toolStripLabel4->Name = L"toolStripLabel4";
			this->toolStripLabel4->Overflow = System::Windows::Forms::ToolStripItemOverflow::Always;
			this->toolStripLabel4->Size = System::Drawing::Size(98, 21);
			this->toolStripLabel4->Text = L"Соединение";
			// 
			// buttonConnection
			// 
			this->buttonConnection->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->buttonConnection->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonConnection.Image")));
			this->buttonConnection->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonConnection->Name = L"buttonConnection";
			this->buttonConnection->Size = System::Drawing::Size(144, 84);
			this->buttonConnection->Text = L"toolStripButton4";
			this->buttonConnection->ToolTipText = L"Соединение";
			this->buttonConnection->Click += gcnew System::EventHandler(this, &Main::buttonConnection_Click);
			// 
			// buttonConnectionDotted
			// 
			this->buttonConnectionDotted->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->buttonConnectionDotted->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonConnectionDotted.Image")));
			this->buttonConnectionDotted->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonConnectionDotted->Name = L"buttonConnectionDotted";
			this->buttonConnectionDotted->Size = System::Drawing::Size(144, 84);
			this->buttonConnectionDotted->Text = L"toolStripButton2";
			this->buttonConnectionDotted->ToolTipText = L"Соединение";
			this->buttonConnectionDotted->Click += gcnew System::EventHandler(this, &Main::buttonConnectionDotted_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->label3);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(3, 63);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(148, 24);
			this->panel1->TabIndex = 3;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold));
			this->label3->Location = System::Drawing::Point(0, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(140, 21);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Элементы схемы";
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 1;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel4->Controls->Add(this->toolStrip2, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->pictureBox1, 0, 2);
			this->tableLayoutPanel4->Controls->Add(this->toolStrip4, 0, 1);
			this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel4->Location = System::Drawing::Point(163, 27);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 3;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 60)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel4->Size = System::Drawing::Size(677, 531);
			this->tableLayoutPanel4->TabIndex = 11;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Control;
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(3, 93);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(671, 471);
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->SizeChanged += gcnew System::EventHandler(this, &Main::pictureBox1_SizeChanged);
			this->pictureBox1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::pictureBox1_MouseDoubleClick);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::pictureBox1_MouseUp);
			// 
			// toolStrip4
			// 
			this->toolStrip4->BackColor = System::Drawing::Color::Transparent;
			this->toolStrip4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->toolStrip4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->toolStrip4->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip4->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripLabel1,
					this->comboboxScale
			});
			this->toolStrip4->Location = System::Drawing::Point(0, 60);
			this->toolStrip4->Name = L"toolStrip4";
			this->toolStrip4->Size = System::Drawing::Size(677, 30);
			this->toolStrip4->TabIndex = 4;
			this->toolStrip4->Text = L"toolStrip4";
			// 
			// toolStripLabel1
			// 
			this->toolStripLabel1->Name = L"toolStripLabel1";
			this->toolStripLabel1->Size = System::Drawing::Size(108, 27);
			this->toolStripLabel1->Text = L"Размер фигур:";
			// 
			// comboboxScale
			// 
			this->comboboxScale->BackColor = System::Drawing::Color::RosyBrown;
			this->comboboxScale->Name = L"comboboxScale";
			this->comboboxScale->Size = System::Drawing::Size(75, 30);
			this->comboboxScale->SelectedIndexChanged += gcnew System::EventHandler(this, &Main::comboboxScale_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Location = System::Drawing::Point(3, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(154, 24);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Файл";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// exportFileDialog
			// 
			this->exportFileDialog->FileName = L"Производственная схема";
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(165)), static_cast<System::Int32>(static_cast<System::Byte>(125)),
				static_cast<System::Int32>(static_cast<System::Byte>(125)));
			this->ClientSize = System::Drawing::Size(843, 561);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"Main";
			this->Text = L"Редактор производственной схемы";
			this->toolStrip2->ResumeLayout(false);
			this->toolStrip2->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->toolStrip3->ResumeLayout(false);
			this->toolStrip3->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->toolStrip4->ResumeLayout(false);
			this->toolStrip4->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void buttonProcess_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void buttonConnection_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void toolMove_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void toolRemove_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void toolClear_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void buttonSave_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void buttonOpen_Click(System::Object^ sender, System::EventArgs^ e);


private: System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

private: System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void pictureBox1_SizeChanged(System::Object^ sender, System::EventArgs^ e);
void OnKeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
private: System::Void pictureBox1_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void buttonCondition_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void buttonConnectionDotted_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void toolStrip_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e);
private: System::Void buttonExport_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void comboboxScale_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
};
}
