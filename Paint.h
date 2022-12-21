#pragma once
#include "LineMethods.h"

namespace PaintSystem
{
	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::Runtime::Serialization;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::IO;

	//Тип объекта рисовани¤
	public enum class ObjectType
	{
		_ActionBlock,//Прямоугольник
		_ConditionBlock,//Ромб
	};

	//СВОЙСТВА ОБЪЕКТОВ РИСОВАНИЯ

	//Свойства рисования объектов
	public ref struct  Property
	{
		Brush^ brush_line;//Цвет линий объектов
		Brush^ brush_text;//Цвет текста
		Brush^ backcolor;//Цвет фона
		Pen^ pen_figure;//Линия фигуры
		Pen^ pen_line;//Линия соединений
		Font^ font_text;//Шрифт
		Property();
	};
	
	//Базовый элемент рисования
	[DataContract]
	public ref class TemplatePaint abstract
	{
	private:
		//Метод, срабатывающий после десериализации, для установления значений по умолчанию
		[OnDeserializing] void AfterDeserialize(StreamingContext context);
	public:
		Property^ p;//Свойства графики
		[DataMember] String^ text;//Текст объекта
		TemplatePaint(String^ text);
		//Метод, определяющий существование своей отрисованной фигуры на поле по точке
		virtual bool Exist(Point point) = 0;
		//Метод отрисовки объекта
		virtual void Paint() = 0;
	};
	//Базовый элемент производственной схемы
	[DataContract]
	public ref class ObjectPaint abstract :TemplatePaint
	{
		const double DEFAULT_SCALE_VALUE = 1;
		Point location;//Координаты элемента
		[DataMember(Order = 1)] System::Drawing::Size size;//Размер
		double scale;//Масштаб
	protected:
		array<Point>^ points;//Точки построения фигуры
		virtual void ChangeLocation(Point new_point);
	public:
		[DataMember(Order = 0)] property double Scale
		{
			double get() { return scale; }
			void set(double value)
			{
				if (value > 0)
				{
					this->scale = value;
					//Обновление точек построения фигуры при масштабировании
					if (points != nullptr)
						ChangeLocation(location);
				}	
			}
		}
		property System::Drawing::Size Size
		{
			System::Drawing::Size get() { return System::Drawing::Size(size.Width* scale, size.Height* scale); }
			void set(System::Drawing::Size size) { this->size = size; }
		}
		[DataMember(Order = 2)] property Point Location
		{
			Point get() { return location; }
			void set(Point loc)
			{
				location = loc;
				ChangeLocation(loc);
			}
		}
		ObjectPaint(Point loc, System::Drawing::Size size, String^ text);
		ObjectPaint(Point loc, System::Drawing::Size size, String^ text, double scale);
		//Методо рисования текста
		void DrawText(Rectangle r);
		//Метод, определяющий точку пересечения своего контура с заданной линией
		virtual Point Intersect(Point p1, Point p2);
	};

	//Объект, соединяющий элементы производственной схемы
	[DataContract]
	public ref class Connection :TemplatePaint
	{
	public:
		[DataMember] static const float OFFSET = 5;//Погрешность при попадании курсора на линии
		//Метод, определяющий попадание точки на линию с учетом погрешности
		static float Function(Point p1, Point p2, Point search_point, float offset);
		[DataMember] ObjectPaint^ f1;//Элемент 1
		[DataMember] ObjectPaint^ f2;//Элемент 2
		Point FlowPoint;//Временная точка, когда неопределен 2 элемент 
		Connection(ObjectPaint^ f1, Point flow_point, String^ text);
		//Метод, присоединяющий конец линии к заданному элементу
		void ConnectFigure(ObjectPaint^ f2);
		//Метод рисования текста
		void DrawText(Point p1, Point p2);
		bool Exist(Point point) override;
		void Paint() override;
		//Установление пунктирной линии
		[DataMember] property bool IsDotted
		{
			bool get() 
			{
				if (p->pen_line->DashStyle == DashStyle::Dash)
					return true;
				else
					return false;
			}
			void set(bool value)
			{
				if (value)
				{
					p->pen_line->DashStyle = DashStyle::Dash;
				}
				else 
				{
					p->pen_line->DashStyle = DashStyle::Solid;
				}
			}
		}
	};

	//ПОЛЕ РИСОВАНИЯ

	[DataContract]
	public ref class Pole
	{
	private:
		[DataMember(Order = 0)] double scale;//Масштаб объектов
		[DataMember(Order = 1)] List<ObjectPaint^>^ objects;//Список элементов производственной схемы
		[DataMember(Order = 2)] List<Connection^>^ lines;//Список соединений
		//Метод, удаляющий соединения с заданным элементом
		void RemoveLines(ObjectPaint^ f);
		bool ExistLine(Connection^ line);
	public:
		static Graphics^ g;//Инструмент рисования
		Image^ image;//Область рисования
		Pole(System::Drawing::Size size);
		//Метод, изменяющий размер поля
		Image^ Resize(System::Drawing::Size new_size);
		//Количество объектов
		int Count();
		//Метод добавления фигуры
		void AddFigure(Point Location, ObjectType type,double scale_value);
		//Метод добавления соединения
		bool AddLine(Connection^ line);
		//Метод удаления фигуры
		void RemoveObject(Point point);
		//Метод удаления линии
		void RemoveLine(Connection^ line);
		//Получение фигуры по координатам
		ObjectPaint^ GetFigure(Point point);
		//Получение линии по координатам
		Connection^ GetLine(Point point);
		//Получение объекта поля рисования по координатам
		TemplatePaint^ GetObject(Point point);
		//Получение списка соединений, соединенных с заданным элементом
		List<Connection^>^ GetLines(ObjectPaint^ r);
		//Удаление всех объектов с поля
		void Clear();
		//Метод рисования объектов на поле
		void Paint();
		//Метод изменения размера объектов
		void SetScale(double scale_value);
		//Получение значения масштабирования
		double GetScale();
	};


	//ОБЪЕКТЫ РИСОВАНИЯ
	
	//Класс, определяющий блок действия
	[DataContract]
	public ref class ObjectBlock : public ObjectPaint
	{
	public:
		ObjectBlock(Point loc, System::Drawing::Size size, String^ text, double scale_value);
		bool Exist(Point point) override;
		void Paint() override;
	};
	// Класс, определяющий блок условия
	[DataContract]
	public ref class ConditionBlock : public ObjectPaint
	{
	protected:
		void ChangeLocation(Point new_location) override;
	public:
		ConditionBlock(Point loc, System::Drawing::Size size, String^ text, double scale_value);
		bool Exist(Point point) override;
		void Paint() override;
	};

}

