#pragma once

using namespace System;
using namespace System::Drawing;

//�������, ������������ �������������� ����� �������
bool Exist(Point point1, Point point2, Point search_point);
//�������, ������������ ����� ����������� ���� ������ �� ������
Point cross(Point line_begin, Point line_end, Point figure_begin, Point figure_end);
//�������, ������������ ����� �������� �������
Point middle(Point line_begin, Point line_end);

