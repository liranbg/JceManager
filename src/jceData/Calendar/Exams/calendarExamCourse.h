#ifndef CALENDAREXAMCOURSE_H
#define CALENDAREXAMCOURSE_H

#include "../../course.h"

#include <QTime>
#include <QString>
#include <QDate>

#define	EXAM_SCHEDULE_FIELDS	9

#define LECTURER_DEFAULT_STRING "nullLecturer"
#define HOUR_DEFAULT_STRING "00:00"
#define SECOND_DATE_DEFAULT_STRING "nullSECOND_DATE"

class calendarExamCourse  : public Course
{

public:

    enum ExamScheme
    {
        SERIAL,
        NAME,
        LECTURER,
        FIELD,
        TYPE,
        FIRST_DATE,
        FIRST_HOUR_BEGIN,
        SECOND_DATE,
        SECOND_HOUR_BEGIN
    };

    calendarExamCourse(int serial, QString name, QString lecturer, QString field,
                       QString type, QString firstDate, QString firstHourbegin,
                       QString secondDate, QString secondHourbegin);


    QString getLecturer() const;
    void setLecturer(const QString &value);

    QString getField() const;
    void setField(const QString &value);

    QDate getFirstDate() const;
    void setFirstDate(const QDate &value);

    QTime getFirstHourbegin() const;
    void setFirstHourbegin(const QTime &value);

    QDate getSecondDate() const;
    void setSecondDate(const QDate &value);

    QTime getSecondHourbegin() const;
    void setSecondHourbegin(const QTime &value);

private:

    void setDate(QString date, bool isFirst); //isFirst = true > first. otherwise > second
    void setTime(QString time, bool isFirst); //isFirst = true > first. otherwise > second

    QString lecturer;
    QString field;
    QDate firstDate;
    QTime firstHourbegin;
    QDate secondDate;
    QTime secondHourbegin;
};

#endif // CALENDAREXAMCOURSE_H
