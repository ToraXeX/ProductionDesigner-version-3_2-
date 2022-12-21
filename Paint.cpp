#include "Paint.h"

namespace PaintSystem
{
	//СВОЙСТВА ОБЪЕКТОВ РИСОВАНИЯ
	Property::Property()
	{
		//Установка значений по умолчанию
		this->brush_line = gcnew SolidBrush(Color::Black);
		this->brush_text = gcnew SolidBrush(Color::Green);
		this->backcolor = gcnew SolidBrush(Color::White);
		this->pen_figure = gcnew Pen(brush_line, 2);
		this->pen_line = gcnew Pen(brush_line, 2);
		this->pen_line->CustomEndCap = gcnew AdjustableArrowCap(8, 8, true);
		this->font_text = gcnew Font("Arial", 12);
	}
	//Базовый элемент рисования
	void TemplatePaint::AfterDeserialize(StreamingContext context)
	{
		this->p = gcnew Property();
	}
	TemplatePaint::TemplatePaint(String^ text)
	{
		this->text = text;
		p = gcnew Property();
	}
	//Базовый элемент производственной схемы
	void ObjectPaint::ChangeLocation(Point new_location)
	{
		Point LeftTop = Point(Location.X - Size.Width / 2, Location.Y - Size.Height / 2);
		Rectangle r = Rectangle(LeftTop, Size);
		points = gcnew array<Point>(4)
		{
			Point(r.Left, r.Top),
				Point(r.Right, r.Top),
				Point(r.Right, r.Bottom),
				Point(r.Left, r.Bottom)
		};
	}

	ObjectPaint::ObjectPaint(Point loc, System::Drawing::Size size, String^ text) :TemplatePaint(text)
	{
		scale = DEFAULT_SCALE_VALUE;
		this->size = size;
		this->Location = loc;
		this->text = text;
	}
	ObjectPaint::ObjectPaint(Point loc, System::Drawing::Size size, String^ text, double scale) :TemplatePaint(text)
	{
		this->scale = scale;
		this->size = size;
		this->Location = loc;
		this->text = text;
	}
	void ObjectPaint::DrawText(Rectangle r)
	{
		//Рисование текста
		StringFormat^ format = gcnew StringFormat(StringFormatFlags::NoClip);
		format->Alignment = StringAlignment::Center;
		format->LineAlignment = StringAlignment::Center;
		Pole::g->DrawString(text, p->font_text, p->brush_line, r, format);
	}
	Point ObjectPaint::Intersect(Point p1, Point p2)
	{
		array<array<Point>^>^ pairs = gcnew array<array<Point>^>(4)
		{
			gcnew array<Point>(2) { points[0], points[1] },
				gcnew array<Point>(2) { points[1], points[2] },
				gcnew array<Point>(2) { points[2], points[3] },
				gcnew array<Point>(2) { points[3], points[0] }
		};
		for each (array<Point> ^ pair in pairs)
		{
			Point intersect_point = cross(p1, p2, pair[0], pair[1]);
			if (intersect_point != Point::Empty)
			{
				return intersect_point;
			}
		}
		return Point::Empty;
	}

	//Объект, соединяющий элементы производственной схемы

	float Connection::Function(Point p1, Point p2, Point search_point, float offset)
	{
		float x = (float)(search_point.X - p1.X + offset) * (float)(p2.Y - p1.Y);
		float y = (float)(search_point.Y - p1.Y + offset) * (float)(p2.X - p1.X);
		return x - y;
	}

	Connection::Connection(ObjectPaint^ f1, Point flow_point, String^ text) : TemplatePaint(text)
	{
		this->f1 = f1;
		this->FlowPoint = flow_point;
	}

	void Connection::ConnectFigure(ObjectPaint^ f)
	{
		this->f2 = f;
	}

	void Connection::DrawText(Point p1, Point p2)
	{
		Point middle_point = middle(p1, p2);
		Pole::g->DrawString(text, p->font_text, p->brush_text, middle_point);
	}

	bool Connection::Exist(Point point)
	{
		float t1 = Function(f1->Location, f2->Location, point, OFFSET);
		float t2 = Function(f1->Location, f2->Location, point, -OFFSET);
		float x_min = Math::Min(f1->Location.X, f2->Location.X) - OFFSET / 2;
		float x_max = Math::Max(f1->Location.X, f2->Location.X) + OFFSET / 2;
		float y_min = Math::Min(f1->Location.Y, f2->Location.Y) - OFFSET / 2;
		float y_max = Math::Max(f1->Location.Y, f2->Location.Y) + OFFSET / 2;
		if (((t1 < 0 && t2 > 0) || (t2 < 0 && t1 > 0)) &&
			point.X > x_min && point.X < x_max &&
			point.Y > y_min && point.Y < y_max)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Connection::Paint()
	{

		if (f2 == nullptr)
		{
			Point p1 = f1->Intersect(f1->Location, FlowPoint);
			if (!p1.IsEmpty)
			{
				Pole::g->DrawLine(p->pen_line, p1, FlowPoint);
				DrawText(p1, FlowPoint);
			}
		}
		else
		{
			Point p1 = f1->Intersect(f1->Location, f2->Location);
			Point p2 = f2->Intersect(f1->Location, f2->Location);
			if (!p1.IsEmpty && !p2.IsEmpty)
			{
				Pole::g->DrawLine(p->pen_line, p1, p2);
				DrawText(p1, p2);
			}
		}

	}

	//ПОЛЕ РИСОВАНИЯ

	void Pole::RemoveLines(ObjectPaint^ f)
	{
		for (int i = 0; i < lines->Count; i++)
		{
			if (lines[i]->f1 == f || lines[i]->f2 == f)
			{
				lines->Remove(lines[i]);
				i--;
			}
		}
	}

	bool Pole::ExistLine(Connection^ line)
	{
		for each (Connection ^c in lines)
		{
			if (c == line)
			{
				return true;
			}
		}
		return false;
	}

	Pole::Pole(System::Drawing::Size size)
	{
		objects = gcnew List<ObjectPaint^>();
		lines = gcnew List<Connection^>();
		//Создание холста рисования (Bitmap)
		this->image = gcnew Bitmap(size.Width, size.Height);
		//Инициализация инструмента рисования
		g = Graphics::FromImage(image);
		//Сглаживание линий
		g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
	}

	Image^ Pole::Resize(System::Drawing::Size new_Size)
	{
		if (!new_Size.IsEmpty)
		{
			this->image = gcnew Bitmap(new_Size.Width, new_Size.Height);
			g = Graphics::FromImage(image);
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
			return image;
		}
		else
		{
			return nullptr;
		}
	}

	int Pole::Count()
	{
		return objects->Count;
	}

	void Pole::AddFigure(Point Location, ObjectType type, double scale_value)
	{
		
		ObjectPaint^ obj;
		switch (type)
		{
		case ObjectType::_ActionBlock:
		{
			obj = gcnew ObjectBlock(Location, Size(150, 80), "", scale_value);
			obj->Scale = scale;
			break;
		}
		case ObjectType::_ConditionBlock:
		{
			obj = gcnew ConditionBlock(Location, Size(120, 80), "",scale_value);
			obj->Scale = scale;
			break;
		}
		}
		objects->Add(obj);
		scale = scale_value;
	}

	bool Pole::AddLine(Connection^ line)
	{
		bool result = false;
		if (!ExistLine(line))
		{
			if (line->f1 != nullptr)
			{
				if (line->f2 == nullptr)
				{
					lines->Add(line);
					result = true;
				}
				else
				{
					if (line->f1 == line->f2)
					{
						lines->Remove(line);
					}
				}
			}
		}
		return result;
	}

	void Pole::RemoveObject(Point point)
	{
		//Выбор фигуры для удаления
		ObjectPaint^ f = GetFigure(point);
		//Удаление связанных с ним связей
		if (f != nullptr)
		{
			RemoveLines(f);
		}
		//Выбор линии для удаления
		Connection^ l = GetLine(point);
		//Удаление фигуры
		objects->Remove(f);
		//Удаление линии
		lines->Remove(l);
	}

	void Pole::RemoveLine(Connection^ line)
	{
		lines->Remove(line);
	}

	ObjectPaint^ Pole::GetFigure(Point point)
	{
		for (int i = objects->Count - 1; i >= 0; i--)
		{
			if (objects[i]->Exist(point))
			{
				ObjectPaint^ tmp = objects[i];
				objects->Remove(tmp);
				objects->Add(tmp);
				return tmp;
			}
		}
		return nullptr;
	}

	Connection^ Pole::GetLine(Point point)
	{
		for (int i = lines->Count - 1; i >= 0; i--)
		{
			if (lines[i]->Exist(point))
			{
				return lines[i];
			}
		}
		return nullptr;
	}

	TemplatePaint^ Pole::GetObject(Point point)
	{
		TemplatePaint^ obj = nullptr;
		obj = GetFigure(point);
		if (obj == nullptr)
		{
			obj = GetLine(point);
		}
		return obj;
	}

	List<Connection^>^ Pole::GetLines(ObjectPaint^ r)
	{
		List<Connection^>^ l = gcnew List<Connection^>();
		for each (Connection ^ line in lines)
		{
			if (r == line->f1 || r == line->f2)
			{
				l->Add(line);
			}
		}
		return l;
	}

	void Pole::Clear()
	{
		objects->Clear();
		lines->Clear();
		Paint();
	}

	void Pole::Paint()
	{
		g->Clear(SystemColors::Control);
		for each (Connection ^ obj in lines)
		{
			obj->Paint();
		}
		for each (ObjectPaint ^ obj in objects)
		{
			obj->Paint();
		}
	}

	void Pole::SetScale(double scale_value)
	{
		for each (ObjectPaint ^ obj in objects)
		{
			obj->Scale = scale_value;
		}
		scale = scale_value;
	}

	double Pole::GetScale()
	{
		return scale;
	}

	//ОБЪЕКТЫ РИСОВАНИЯ


	//Класс, определяющий блок действия

	ObjectBlock::ObjectBlock(Point loc, System::Drawing::Size size, String^ text, double scale_value) :
		ObjectPaint(loc, size, text, scale_value) {}

	void ObjectBlock::Paint()
	{
		//Рисование прямоугольника
		Point LeftTop = Point(Location.X - Size.Width / 2, Location.Y - Size.Height / 2);
		System::Drawing::Rectangle rectangle = System::Drawing::Rectangle(LeftTop, Size);
		Pole::g->DrawRectangle(p->pen_figure, rectangle);
		Pole::g->FillRectangle(p->backcolor, rectangle);
		//Рисование текста
		DrawText(rectangle);
	}

	bool ObjectBlock::Exist(Point point)
	{
		Point LeftTop = Point(Location.X - Size.Width / 2, Location.Y - Size.Height / 2);
		if (point.X > LeftTop.X && point.X<LeftTop.X + Size.Width &&
			point.Y>LeftTop.Y && point.Y < LeftTop.Y + Size.Height)
		{
			return true;
		}
		else { return false; }
	}
	
	void ConditionBlock::ChangeLocation(Point new_location)
	{
		//Определение точек ромба
		points = gcnew array<Point>(4)
		{
			Point(new_location.X - Size.Width / 2, new_location.Y),
				Point(new_location.X, new_location.Y - Size.Height / 2),
				Point(new_location.X + Size.Width / 2, new_location.Y),
				Point(new_location.X, new_location.Y + Size.Height / 2),
		};
	}

	ConditionBlock::ConditionBlock(Point loc, System::Drawing::Size size, String^ text, double scale_value) :
		ObjectPaint(loc, size, text, scale_value) {}

	bool ConditionBlock::Exist(Point point)
	{
		float a = (float)(Size.Width / 2);//ѕоловина длины диагонали ромба
		float b = (float)(Size.Height / 2);//ѕоловина длины диагонали ромба
		float Ux = (points[2].X - points[0].X) / (2 * a);//–асчет вектора в направлении оси X
		float Vy = (points[3].Y - points[1].Y) / (2 * b);//–асчет вектора в направлении оси Y
		int Wx = point.X - Location.X;
		int Wy = point.Y - Location.Y;
		//
		float x = Math::Abs(Ux * Wx);
		float y = Math::Abs(Vy * Wy);
		//
		if ((x / a + y / b) <= 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void ConditionBlock::Paint()
	{
		// Рисование прямоугольника
		Point LeftTop = Point(Location.X - Size.Width / 2, Location.Y - Size.Height / 2);
		System::Drawing::Rectangle rectangle = System::Drawing::Rectangle(LeftTop, Size);
		Pole::g->DrawPolygon(p->pen_figure, points);
		Pole::g->FillPolygon(p->backcolor, points);
		//Рисование текста
		DrawText(rectangle);
	}

}
