#include "gradePage.h"

GradePage::GradePage(std::string html) : Page()
{
    this->courses = new std::list<gradeCourse*>();
    this->tempHtml = getString(html);
    this->tempHtml = tokenToLines(this->tempHtml);
    coursesListInit(this->tempHtml);

}
GradePage::~GradePage()
{
    for(Course* c : *courses)
        delete c;
    delete courses;
}

void GradePage::addCourse(gradeCourse *a)
{
    GradePage::courses->push_back(a);
    return;
}

void GradePage::removeCourse(std::string courseSerialID)
{
    for(gradeCourse* c : *courses)
    {
        if (c->getSerialNum() == stoi(courseSerialID))
        {
            courses->remove(c);
            delete c;
            return;
        }
    }

}
void GradePage::coursesListInit(std::string& linesTokinzedString)
{
    std::list<std::string> stringHolder;
    std::string temp;
    gradeCourse* cTemp = NULL;
    char* tok;
    char* textToTok = strdup(linesTokinzedString.c_str());
    tok = strtok(textToTok,"\n");
    while (tok != NULL)
    {
        temp = tok;
        stringHolder.push_back(temp);
        tok = strtok(NULL, "\n");
    }
    for(std::string temp: stringHolder)
    {
        cTemp = lineToCourse(temp);
        if (cTemp != NULL)
            addCourse(cTemp);
    }
}

std::string GradePage::tokenToLines(std::string& textToPhrase)
{
    int ctr = 0;
    std::string temp = "";
    char *tok;
    char* textToTok = strdup(textToPhrase.c_str());
    tok = strtok(textToTok, "\n");
    while(tok != NULL)
    {
        //amount of data before the actual needed data and no empty lines
        if (strcmp(tok," \t ") != 0)
        {
            temp += tok;
            temp += "\n";
        }
        ctr++;
        tok = strtok(NULL, "\n");
    }
    return temp;

}
gradeCourse* GradePage::lineToCourse(std::string line)
{
    gradeCourse *tempC = NULL;
    std::string templinearray[COURSE_FIELDS];//[serial,name,type,points,hours,grade,additions]
    int serial;
    double points,hours,grade;
    std::string name,type, additions;
    std::string tempS = "";
    int i = 0;
    char* tok;
    char* cLine = strdup(line.c_str());
    tok = strtok(cLine, "\t");
    while(tok != NULL)
    {

        tempS = tok;
        if (i == 1) //skip the tokenizing loop just once
        {
            tempS = "";
            char *tokTemp;
            tokTemp = tok;

            while (!(isdigit((int)*tokTemp)))
                tokTemp++;

            while (isdigit((int)*tokTemp))
            {
                tempS += *tokTemp;
                tokTemp++;
            }
            templinearray[i-1] = tempS;
            templinearray[i] = tokTemp;

        }
        else if (i > 1)
            templinearray[i] = tempS;
        i++;
        tok=strtok(NULL, "\t");
    }
    if (templinearray[0] == "") //empty phrasing
        return NULL;

    serial = stoi(templinearray[gradeCourse::CourseScheme::SERIAL]);

    name = templinearray[gradeCourse::CourseScheme::NAME];
    type = templinearray[gradeCourse::CourseScheme::TYPE];

    points = stod(templinearray[gradeCourse::CourseScheme::POINTS]);
    hours = stod(templinearray[gradeCourse::CourseScheme::HOURS]);

    if (isGradedYet(templinearray[gradeCourse::CourseScheme::GRADE]))
        grade = stod(templinearray[gradeCourse::CourseScheme::GRADE]);
    else
        grade = NO_GRADE_YET;

    additions = templinearray[gradeCourse::CourseScheme::ADDITION];

    tempC = new gradeCourse(serial,name,type,points,hours,grade,additions);
    return tempC;
}

//checking if one of the chars inside grade is not a number
bool GradePage::isGradedYet(std::string grade)
{
    if (strlen(grade.c_str()) <= 1)
        return false;

    for (char c: grade)
    {
        if (c == '\0')
            break;
        if (((!isdigit((int)c))  && (!isspace((int)c)))) //48 = 0, 57 = 9
            return false;

    }
    return true;
}
double GradePage::getAvg()
{
    double avg = 0;
    double points = 0;
    for(gradeCourse* c : *courses)
    {
        if ((c->getGrade() != 0))
        {
            avg += c->getGrade() * c->getPoints();
            points += c->getPoints();
        }
    }

    avg /= points;
    return avg;
}
