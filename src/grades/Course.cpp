#include "Course.h"

Course::Course(int serial, std::string name, std::string type, double points, double hours, double grade, std::string additions)
{
    this->serialNum = serial;
    this->name = name;
    this->type = type;
    this->points = points;
    this->hours = hours;
    this->grade = grade;
    this->additions = additions;
}

Course::~Course()
{

}
double Course::getGrade() const
{
    double noGrade = NO_GRADE_YET;
    if (grade == noGrade)
        return 0;
    else
        return this->grade;
}

void Course::setName(std::string name)
{
    this->name = name;
}

void Course::setType(std::string type)
{
    this->type = type;
}

void Course::setPoints(double points)
{
    this->points=points;
}

void Course::setHours(double hours)
{
    this->hours = hours;
}

void Course::setGrade(double grade)
{
    this->grade = grade;
}

void Course::setAdditions(std::string additions)
{
    this->additions = additions;
}