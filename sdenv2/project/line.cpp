#include "line.h"

Line::Line()
{
}

Line::~Line()
{
}

void Line::addPoint(glm::vec3 point){
	_points.push_back(point);
}

std::vector<glm::vec3> Line::getPoints(){
	return _points;
}
