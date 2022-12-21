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

	//��� ������� ��������
	public enum class ObjectType
	{
		_ActionBlock,//�������������
		_ConditionBlock,//����
	};

	//�������� �������� ���������

	//�������� ��������� ��������
	public ref struct  Property
	{
		Brush^ brush_line;//���� ����� ��������
		Brush^ brush_text;//���� ������
		Brush^ backcolor;//���� ����
		Pen^ pen_figure;//����� ������
		Pen^ pen_line;//����� ����������
		Font^ font_text;//�����
		Property();
	};
	
	//������� ������� ���������
	[DataContract]
	public ref class TemplatePaint abstract
	{
	private:
		//�����, ������������� ����� ��������������, ��� ������������ �������� �� ���������
		[OnDeserializing] void AfterDeserialize(StreamingContext context);
	public:
		Property^ p;//�������� �������
		[DataMember] String^ text;//����� �������
		TemplatePaint(String^ text);
		//�����, ������������ ������������� ����� ������������ ������ �� ���� �� �����
		virtual bool Exist(Point point) = 0;
		//����� ��������� �������
		virtual void Paint() = 0;
	};
	//������� ������� ���������������� �����
	[DataContract]
	public ref class ObjectPaint abstract :TemplatePaint
	{
		const double DEFAULT_SCALE_VALUE = 1;
		Point location;//���������� ��������
		[DataMember(Order = 1)] System::Drawing::Size size;//������
		double scale;//�������
	protected:
		array<Point>^ points;//����� ���������� ������
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
					//���������� ����� ���������� ������ ��� ���������������
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
		//������ ��������� ������
		void DrawText(Rectangle r);
		//�����, ������������ ����� ����������� ������ ������� � �������� ������
		virtual Point Intersect(Point p1, Point p2);
	};

	//������, ����������� �������� ���������������� �����
	[DataContract]
	public ref class Connection :TemplatePaint
	{
	public:
		[DataMember] static const float OFFSET = 5;//����������� ��� ��������� ������� �� �����
		//�����, ������������ ��������� ����� �� ����� � ������ �����������
		static float Function(Point p1, Point p2, Point search_point, float offset);
		[DataMember] ObjectPaint^ f1;//������� 1
		[DataMember] ObjectPaint^ f2;//������� 2
		Point FlowPoint;//��������� �����, ����� ����������� 2 ������� 
		Connection(ObjectPaint^ f1, Point flow_point, String^ text);
		//�����, �������������� ����� ����� � ��������� ��������
		void ConnectFigure(ObjectPaint^ f2);
		//����� ��������� ������
		void DrawText(Point p1, Point p2);
		bool Exist(Point point) override;
		void Paint() override;
		//������������ ���������� �����
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

	//���� ���������

	[DataContract]
	public ref class Pole
	{
	private:
		[DataMember(Order = 0)] double scale;//������� ��������
		[DataMember(Order = 1)] List<ObjectPaint^>^ objects;//������ ��������� ���������������� �����
		[DataMember(Order = 2)] List<Connection^>^ lines;//������ ����������
		//�����, ��������� ���������� � �������� ���������
		void RemoveLines(ObjectPaint^ f);
		bool ExistLine(Connection^ line);
	public:
		static Graphics^ g;//���������� ���������
		Image^ image;//������� ���������
		Pole(System::Drawing::Size size);
		//�����, ���������� ������ ����
		Image^ Resize(System::Drawing::Size new_size);
		//���������� ��������
		int Count();
		//����� ���������� ������
		void AddFigure(Point Location, ObjectType type,double scale_value);
		//����� ���������� ����������
		bool AddLine(Connection^ line);
		//����� �������� ������
		void RemoveObject(Point point);
		//����� �������� �����
		void RemoveLine(Connection^ line);
		//��������� ������ �� �����������
		ObjectPaint^ GetFigure(Point point);
		//��������� ����� �� �����������
		Connection^ GetLine(Point point);
		//��������� ������� ���� ��������� �� �����������
		TemplatePaint^ GetObject(Point point);
		//��������� ������ ����������, ����������� � �������� ���������
		List<Connection^>^ GetLines(ObjectPaint^ r);
		//�������� ���� �������� � ����
		void Clear();
		//����� ��������� �������� �� ����
		void Paint();
		//����� ��������� ������� ��������
		void SetScale(double scale_value);
		//��������� �������� ���������������
		double GetScale();
	};


	//������� ���������
	
	//�����, ������������ ���� ��������
	[DataContract]
	public ref class ObjectBlock : public ObjectPaint
	{
	public:
		ObjectBlock(Point loc, System::Drawing::Size size, String^ text, double scale_value);
		bool Exist(Point point) override;
		void Paint() override;
	};
	//������, ������������ ���� �������
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

