#ifndef CALENDARMANAGER_H
#define CALENDARMANAGER_H

#include "./src/jceData/Calendar/calendarPage.h"
#include "./src/jceData/Calendar/calendarSchedule.h"
#include "./src/jceData/CSV/csv_exporter.h"
#include <iostream>
#include <QMessageBox>

class CalendarManager
{
public:
    CalendarManager(calendarSchedule *ptr);
    ~CalendarManager()
    {
        delete caliSchedPtr;
    }
    void exportCalendarCSV();
    void setCalendar(std::string html);
    void resetTable() { if (caliSchedPtr != NULL) caliSchedPtr->clearTableItems(); }

private:
    calendarSchedule * caliSchedPtr;
};

#endif // CALENDARMANAGER_H
