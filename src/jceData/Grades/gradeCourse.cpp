#include "gradeCourse.h"

gradeCourse::gradeCourse(int serial,std::string name, std::string type, double points, double hours, double grade, std::string additions) :  Course(serial,name,type,points)
{
    this->hours = hours;
    this->grade = grade;
    this->additions = additions;
}

gradeCourse::~gradeCourse()
{

}
double gradeCourse::getGrade() const
{
    double noGrade = NO_GRADE_YET;
    if (grade == noGrade)
        return 0;
    else
        return this->grade;
}

void gradeCourse::setHours(double hours)
{
    this->hours = hours;
}

void gradeCourse::setGrade(double grade)
{
    this->grade = grade;
}

void gradeCourse::setAdditions(std::string additions)
{
    this->additions = additions;
}
