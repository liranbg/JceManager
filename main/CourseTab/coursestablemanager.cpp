#include "coursestablemanager.h"
coursesTableManager::coursesTableManager(QTableWidget *ptr, user *usrPtr)
{
    this->gp = NULL;
    this->gpCpy = NULL;
    this->us = usrPtr;
    this->courseTBL = ptr;

    /*
   *  Initilizing Table
   */
    courseTBL->setRowCount(0);
    courseTBL->setColumnCount(COURSE_FIELDS);
    QStringList mz;
    mz << QObject::tr("Number") << QObject::tr("Year") << QObject::tr("Semester") << QObject::tr("Serial") << QObject::tr("Name") << QObject::tr("Type") << QObject::tr("Points") << QObject::tr("Hours") << QObject::tr("Grade") << QObject::tr("Additions");
    courseTBL->setHorizontalHeaderLabels(mz);
    courseTBL->verticalHeader()->setVisible(false);
    courseTBL->setSelectionMode(QAbstractItemView::SingleSelection);
    courseTBL->setShowGrid(true);
    courseTBL->setStyleSheet("QTableView {selection-background-color: #004080;}");

    graph = new gradegraph(ptr);
}

coursesTableManager::~coursesTableManager()
{
    courseTBL = NULL;
    delete gp;
    delete gpCpy;
    gpCpy = NULL;
    gp = NULL;
}
/**
 * @brief coursesTableManager::insertJceCoursesIntoTable    phrasing the course list to rows in table
 */
void coursesTableManager::insertJceCoursesIntoTable()
{
    for (gradeCourse *c: gp->getCourses())
    {
      if (us->getInfluenceCourseOnly())
        {
          if (isCourseInfluence(c))
            addRow(c);
        }
      else
        addRow(c);
    }
}
/**
 * @brief coursesTableManager::setCoursesList   creating courses list with given html page
 * @param html
 */
void coursesTableManager::setCoursesList(QString &html)
{
    clearTable();
    gp = new GradePage(html);
    this->gpCpy = new GradePage(*gp);
    insertJceCoursesIntoTable();
    this->courseTBL->setCurrentCell(0,0);
}
/**
 * @brief coursesTableManager::changes  when user changes the table manually it updates it
 * @param change    string change
 * @param row       row index
 * @param col       col index
 * @return  if change has been done
 */
bool coursesTableManager::changes(QString change, int row, int col)
{
    bool isNumFlag = true;
    if (courseTBL->item(row,gradeCourse::CourseScheme::SERIAL) == NULL)
        return true;

    int serialCourse = courseTBL->item(row,gradeCourse::CourseScheme::SERIAL)->text().toInt();
    for (gradeCourse *c: gp->getCourses())
    {
      if (c->getSerialNum() == serialCourse)
        {
          switch (col)
            {
            case (gradeCourse::CourseScheme::COURSE_NUMBER_IN_LIST):
                c->setCourseNumInList(change.toInt());
                break;
            case (gradeCourse::CourseScheme::YEAR):
                c->setYear(change.toInt());
                break;
            case (gradeCourse::CourseScheme::SEMESTER):
                c->setSemester(change.toInt());
                break;
            case (gradeCourse::CourseScheme::NAME):
              c->setName(change);
              break;
            case (gradeCourse::CourseScheme::TYPE):
              c->setType(change);
              break;
            case (gradeCourse::CourseScheme::POINTS):
              {
                change.toDouble(&isNumFlag);

                if (!isNumFlag)
                  {
                    courseTBL->item(row,col)->setText(QString::number(c->getPoints()));
                  }
                else
                  c->setPoints(change.toDouble());
                break;
              }
            case (gradeCourse::CourseScheme::HOURS):
              {
                change.toDouble(&isNumFlag);

                if (!isNumFlag)
                  {
                    courseTBL->item(row,col)->setText(QString::number(c->getHours()));
                  }
                else
                  c->setHours(change.toDouble());
                break;
              }
            case (gradeCourse::CourseScheme::GRADE):
            {

                change.toDouble(&isNumFlag);

                if (!isNumFlag) //not a number
                {
                    courseTBL->item(row,col)->setText(QString::number(c->getGrade()));
                  }
                else
                  {
                    if ((change.toDouble() >= 0) && (change.toDouble() <= 100))
                    {
                        c->setGrade(change.toDouble());
                        colorTheGrade(row);
                    }
                    else
                      courseTBL->item(row,col)->setText(QString::number(c->getGrade()));
                  }
                break;
              }
            case (gradeCourse::CourseScheme::ADDITION):
              c->setAdditions(change);
              break;
            }
          break;
        }
    }
    this->courseTBL->setCurrentCell(row+1,col); //set focus to next grade
  return isNumFlag;

}
/**
 * @brief coursesTableManager::addRow   adds row with given information
 * @param courseToAdd                   if exists, add its information to table
 */
void coursesTableManager::addRow(const gradeCourse *courseToAdd)
{
    int i=1,j=1;

    j = 0;
    QTableWidgetItem *number,*year,*semester,*serial,*name,*type,*points,*hours,*grade,*addition;
    const gradeCourse * c;
    if (courseToAdd != NULL)
    {
      c = courseToAdd;
      if (!isCourseAlreadyInserted(c->getSerialNum()))
        {
            courseTBL->setRowCount(courseTBL->rowCount() + 1);
            i = courseTBL->rowCount()-1;

            number = new QTableWidgetItem();
            number->setData(Qt::EditRole, c->getCourseNumInList());
            number->setFlags(number->flags() & ~Qt::ItemIsEditable);

            year = new QTableWidgetItem();
            year->setData(Qt::EditRole,c->getYear());
            year->setFlags(year->flags() & ~Qt::ItemIsEditable);

            semester = new QTableWidgetItem();
            semester->setData(Qt::EditRole,c->getSemester());
            semester->setFlags(semester->flags() & ~Qt::ItemIsEditable);

            serial = new QTableWidgetItem();
            serial->setData(Qt::EditRole,c->getSerialNum());
            serial->setFlags(serial->flags() & ~Qt::ItemIsEditable);

            name = new QTableWidgetItem();
            name->setData(Qt::EditRole,c->getName());
            name->setFlags(name->flags() & ~Qt::ItemIsEditable);

            type = new QTableWidgetItem();
            type->setData(Qt::EditRole, c->getType());
            type->setFlags(type->flags() & ~Qt::ItemIsEditable);

            points = new QTableWidgetItem();
            points->setData(Qt::EditRole, c->getPoints());
            points->setFlags(points->flags() & ~Qt::ItemIsEditable);

            hours = new QTableWidgetItem();
            hours->setData(Qt::EditRole, c->getHours());
            hours->setFlags(hours->flags() & ~Qt::ItemIsEditable);

            grade = new QTableWidgetItem();
            //grade->setData(Qt::EditRole,c->getGrade());
            //BUG  QT bug
            //good for sorting, the problem is when you edit -> the cell indicator disappear
            grade->setText(QString::number(c->getGrade()));

            addition = new QTableWidgetItem();
            addition->setData(Qt::EditRole,c->getAddidtions());

            courseTBL->setItem(i,j++,number);
            courseTBL->setItem(i,j++,year);
            courseTBL->setItem(i,j++,semester);
            courseTBL->setItem(i,j++,serial);
            courseTBL->setItem(i,j++,name);
            courseTBL->setItem(i,j++,type);
            courseTBL->setItem(i,j++,points);
            courseTBL->setItem(i,j++,hours);
            courseTBL->setItem(i,j++,grade);
            courseTBL->setItem(i,j,addition);

            colorTheGrade(i);

        }
    }
  else
    {
        qCritical() << Q_FUNC_INFO << " no course to load!";
    }

    courseTBL->resizeColumnsToContents();
    courseTBL->resizeRowsToContents();

}
double coursesTableManager::getAvg()
{
  if (this->gp != NULL)
    return gp->getAvg();
  return 0;
}

bool coursesTableManager::showGraph()
{
    qDebug() << Q_FUNC_INFO;
    if (gp != NULL)
    {
        this->graph->showGraph(gp);
        return true;
    }
    qWarning() << Q_FUNC_INFO << "open with null grade page";
    return false;
}


void coursesTableManager::influnceCourseChanged(bool ignoreCourseStatus)
{
  if (ignoreCourseStatus)
    {
      int i = 0;
      while (i < courseTBL->rowCount())
        {
          if (courseTBL->item(i,gradeCourse::CourseScheme::POINTS)->text().compare("0") == 0)
            courseTBL->removeRow(i--);
          i++;
        }
    }
  else
    {
        if (this->gp != NULL)
            for (gradeCourse *c: gp->getCourses())
            {
                if (!(isCourseAlreadyInserted(c->getSerialNum())))
                    if (c->getPoints() == 0)
                        addRow(c);
            }
    }

}

void coursesTableManager::clearTable()
{
  if (courseTBL->rowCount() == 0)
    return;

  int i = 0; //starting point
  while (courseTBL->rowCount() > i)
    {
        if (gp != NULL)
            gp->removeCourse(courseTBL->item(i,gradeCourse::CourseScheme::SERIAL)->text());
        courseTBL->removeRow(i);
    }
    if (gp != NULL)
        delete gp;
    gp = NULL;
    courseTBL->repaint();
}
/**
 * @brief coursesTableManager::revertChanges
 *
 * restored data from the copy of grade page
 * TODO: revert-> make it efficient
 */
void coursesTableManager::revertChanges()
{
    if (courseTBL->rowCount() <= 0)
        return;
    if (this->gpCpy == NULL)
        return;
    if (this->gp == NULL)
        return;

    for (int i = 0; i < courseTBL->rowCount(); ++i)
    {
        gradeCourse * temp = getCourseByRow(i);
        for (gradeCourse * notChangedCourse: gpCpy->getCourses())
        {
        if ((temp->getGrade() != notChangedCourse->getGrade()) &&
                (temp->getSerialNum() == notChangedCourse->getSerialNum()))
        {
            courseTBL->item(i,gradeCourse::CourseScheme::GRADE)->setText(QString::number(notChangedCourse->getGrade()));
            break;
        }
        }
    }

}

gradeCourse *coursesTableManager::getCourseByRow(int row)
{
    QString courseSerial = courseTBL->item(row,gradeCourse::CourseScheme::SERIAL)->text();
    for (gradeCourse *c: gp->getCourses())
    {
      if (c->getSerialNum() == courseSerial.toDouble())
        return c;
    }
  return NULL;
}

bool coursesTableManager::isCourseAlreadyInserted(double courseID)
{
    int i;
    for (i = courseTBL->rowCount(); i >= 0; --i)
    {
        if (courseTBL->item(i,gradeCourse::CourseScheme::SERIAL) != NULL)
        {
            QString courseSerial = courseTBL->item(i,gradeCourse::CourseScheme::SERIAL)->text();
            if (QString::number(courseID) == courseSerial)
                return true;
        }
    }
  return false;
}

bool coursesTableManager::isCourseInfluence(const gradeCourse *courseToCheck)
{
  if (courseToCheck->getPoints() > 0)
    return true;
  return false;

}
/**
 * @brief coursesTableManager::colorTheGrade - color the course grade
 * @param rowIndex - course's row index
 */
void coursesTableManager::colorTheGrade(int rowIndex)
{
    gradeCourse * temp = getCourseByRow(rowIndex);
    if (temp != NULL)
    {
        if (temp->getGrade() != 0)
        {
            float green,red, blue = 0;
            float grade = ((float)temp->getGrade());

            green = qRound(grade * 255 / 100);
            red = qRound((255 * (100 - grade) / 100));
            blue  = 0;
            //higher the grade -> the greener it is
            courseTBL->item(rowIndex,gradeCourse::CourseScheme::GRADE)->setBackground(QColor(red,green,blue));
            courseTBL->item(rowIndex,gradeCourse::CourseScheme::GRADE)->setTextColor(Qt::black);
        }

    }

}
