#ifndef JCELOGIN_H
#define JCELOGIN_H

#include "./src/jceConnection/jcesslclient.h"
#include "./src/jceSettings/user.h"
#include "jceLoginHtmlScripts.h"

#include <QString>

class jceLogin
{
public:

    enum jceStatus {
        JCE_NOT_CONNECTED,
        ERROR_ON_VALIDATION,
        ERROR_ON_VALIDATION_USER_BLOCKED,
        ERROR_ON_OPEN_SOCKET,
        ERROR_ON_SEND_REQUEST,
        ERROR_ON_GETTING_INFO,
        ERROR_ON_GETTING_GRADES,

        JCE_START_VALIDATING_PROGRESS,
        JCE_VALIDATION_PASSED,
        JCE_YOU_ARE_IN,
        JCE_GRADE_PAGE_PASSED
    };

    jceLogin(user* username);
    ~jceLogin();

    void makeConnection()  throw (jceStatus);
    void reConnect() throw (jceStatus);
    void closeAll();

    bool checkConnection() const;
    bool isLoginFlag() const;

    int getCalendar(int year, int semester);
    int getGrades(int fromYear, int toYear, int fromSemester, int toSemester);

    QString getPage();

private:

    int makeFirstVisit();
    int makeSecondVisit();
    bool checkValidation();
    void setLoginFlag(bool x);

    bool loginFlag;
    QString * recieverPage;
    user * jceA;
    jceSSLClient * JceConnector;


};

#endif // JCELOGIN_H