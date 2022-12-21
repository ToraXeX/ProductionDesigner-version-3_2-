#pragma once

using namespace System;
using namespace System::Drawing;

//‘ункци€, определ€юща€ принадлежность точки отрезку
bool Exist(Point point1, Point point2, Point search_point);
//‘ункци€, определ€юща€ точку пересечени€ двух пр€мых по точкам
Point cross(Point line_begin, Point line_end, Point figure_begin, Point figure_end);
//‘ункци€, определ€юща€ точку середины отрезка
Point middle(Point line_begin, Point line_end);

