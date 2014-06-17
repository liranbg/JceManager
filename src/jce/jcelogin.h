#ifndef JCELOGIN_H
#define JCELOGIN_H

#include <string>
#include <fstream>

#include "../connection/qtsslsocket.h"
#include "../user.h"
#include "jceLoginHtmlScripts.h"




class jceLogin
{
public:

    enum jceStatus {
        JCE_NOT_CONNECTED,
        ERROR_ON_VALIDATION,
        ERROR_ON_VALIDATION_USER_BLOCKED,
        ERROR_ON_INPUT,
        ERROR_ON_CONNECTING,
        ERROR_ON_OPEN_SOCKET,
        ERROR_ON_GETTING_INFO,
        ERROR_ON_GETTING_GRADES,
        ERROR_ON_SEND_REQUEST,
        JCE_START_VALIDATING_PROGRESS,
        JCE_FIRST_VALIDATION_PASSED,
        JCE_SECOND_VALIDATION_PASSED,
        JCE_YOU_ARE_IN,
        JCE_GRADE_PAGE_PASSED
    };

    jceLogin(user* username);
    ~jceLogin();
    void makeConnection()  throw (jceStatus);
    bool checkConnection();
    void reConnect() throw (jceStatus);
    void closeAll();
    int getGrades();
    bool isLoginFlag() const;

    std::string getPage();



private:
    int makeFirstVisit();
    bool checkValidation();
    int makeSecondVisit();
    void setLoginFlag(bool x);

    bool loginFlag;
    std::string * recieverPage;
    user * jceA;
    qtsslsocket * JceConnector;

};

#endif // JCELOGIN_H