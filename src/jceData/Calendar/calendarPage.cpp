#include "calendarPage.h"

QString CalendarPage::htmlToString()
{
  return tempHtml;
}

void CalendarPage::setPage(QString html)
{

  courses = new std::list<calendarCourse*>();
  tempHtml = getString(html);
  calendarListInit(tempHtml);

}

void CalendarPage::calendarListInit(QString &linesTokinzedString)
{
  std::list<QString> stringHolder;
  QString temp;
  calendarCourse * cTemp = NULL;
  char* tok;
  char* textToTok = strdup(linesTokinzedString.toStdString().c_str());
  tok = strtok(textToTok,"\n");
  while (tok != NULL)
    {
      temp = tok;
      stringHolder.push_back(temp);
      tok = strtok(NULL, "\n");
    }
  for (QString temp: stringHolder)
    {
      cTemp = lineToCourse(temp);
      if (cTemp != NULL)
        courses->push_back(cTemp);
    }
}

calendarCourse *CalendarPage::lineToCourse(QString line)
{

  calendarCourse *tempC = NULL;
  QString templinearray[CALENDAR_COURSE_FIELDS];//[serial,name,type,lecturer,points,semesterhours,dayandhours,room]
  int serial;
  double points,semesterHours;
  QString name,type, lecturer,dayAndHour,room;
  QString tempS = "";
  int i = 0;
  char* tok;
  char* cLine = strdup(line.toStdString().c_str());
  tok = strtok(cLine, "\t");
  while(tok != NULL)
    {
      tempS = QString(tok);

      if (i >= 1) //skips on semester character
        {
          templinearray[i-1] = tempS.trimmed();
        }

      i++;
      if (i > 8)
        break;
      tok=strtok(NULL, "\t");
    }
  if (templinearray[0] == "") //empty parsing
    return NULL;

  serial = templinearray[calendarCourse::CourseScheme::SERIAL].toInt();
  name = templinearray[calendarCourse::CourseScheme::NAME];
  type = templinearray[calendarCourse::CourseScheme::TYPE];


  if (!templinearray[calendarCourse::CourseScheme::LECTURER].isEmpty())
    lecturer = templinearray[calendarCourse::CourseScheme::LECTURER];
  else
    lecturer = LECTURER_DEFAULT_STRING;

  if (!templinearray[calendarCourse::CourseScheme::POINTS].isEmpty())
    points = templinearray[calendarCourse::CourseScheme::POINTS].toDouble();
  else
    points = 0;
  if (!templinearray[calendarCourse::CourseScheme::SEM_HOURS].isEmpty())
    semesterHours = templinearray[calendarCourse::CourseScheme::SEM_HOURS].toDouble();
  else
    semesterHours = 0;

  dayAndHour = templinearray[calendarCourse::CourseScheme::DAY_AND_HOURS];

  if (!templinearray[calendarCourse::CourseScheme::ROOM].isEmpty())
    room = templinearray[calendarCourse::CourseScheme::ROOM];
  else
    room = ROOM_DEFAULT_STRING;


  tempC = new calendarCourse(serial,name,type,lecturer,points,semesterHours,dayAndHour,room);
//  qDebug() << "serial is: " << tempC->getSerialNum();
//  qDebug() << tempC->getName();
//  qDebug() << tempC->getType();
//  qDebug() << tempC->getLecturer();
//  qDebug() << tempC->getPoints();
//  qDebug() << tempC->getHourBegin() << ":" <<  tempC->getMinutesBegin();
//  qDebug() << tempC->getHourEnd() << ":" <<  tempC->getMinutesEnd();

//  qDebug() << tempC->getDay();
//  qDebug() << tempC->getRoom();

  return tempC;
}
