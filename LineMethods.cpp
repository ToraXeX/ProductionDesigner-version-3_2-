#include "LineMethods.h"

//‘ункци€, определ€юща€ принадлежность точки отрезку
bool Exist(Point point1, Point point2, Point search_point)
{
    int max_x = Math::Max(point1.X, point2.X);
    int min_x = Math::Min(point1.X, point2.X);
    int max_y = Math::Max(point1.Y, point2.Y);
    int min_y = Math::Min(point1.Y, point2.Y);
    if (search_point.X >= min_x && search_point.X <= max_x &&
        search_point.Y >= min_y && search_point.Y <= max_y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//‘ункци€, определ€юща€ точку пересечени€ двух пр€мых по точкам
Point cross(Point line_begin, Point line_end, Point figure_begin, Point figure_end) {
    float n;
    if (line_end.Y - line_begin.Y != 0) {  // a(y)
        float q = (float)(line_end.X - line_begin.X) / (float)(line_begin.Y - line_end.Y);
        float sn = (float)(figure_begin.X - figure_end.X) + (float)(figure_begin.Y - figure_end.Y) * q;
        if (!sn) { return Point::Empty; }  // c(x) + c(y)*q
        float fn = (float)(figure_begin.X - line_begin.X) + (float)(figure_begin.Y - line_begin.Y) * q;   // b(x) + b(y)*q
        n = fn / sn;
    }
    else {
        if (!(figure_begin.Y - figure_end.Y)) { return Point::Empty; }  // b(y)
        n = (float)(figure_begin.Y - line_begin.Y) / (float)(figure_begin.Y - figure_end.Y);   // c(y)/b(y)
    }
    float X = figure_begin.X + (float)(figure_end.X - figure_begin.X) * n;  // figure_begin.X + (-b(x))*n
    float Y = figure_begin.Y + (float)(figure_end.Y - figure_begin.Y) * n;  // figure_begin.Y +(-b(y))*n
    Point point = Point(X, Y);
    if (Exist(line_begin, line_end, point) && Exist(figure_begin, figure_end, point))
    {
        return point;
    }
    return Point::Empty;
}
//‘ункци€, определ€юща€ точку середины отрезка
Point middle(Point line_begin, Point line_end)
{
    Point point;
    point.X = (line_begin.X + line_end.X) / 2;
    point.Y = (line_begin.Y + line_end.Y) / 2;
    return point;
}
