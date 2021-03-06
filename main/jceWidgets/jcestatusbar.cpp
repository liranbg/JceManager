#include "jcestatusbar.h"

jceStatusBar::jceStatusBar(QWidget *parent) :
    QStatusBar(parent)
{
    this->setFixedHeight(STATUS_ICON_HEIGH+30);
    this->showMessage(tr("Ready"));
    this->setStyleSheet("QStatusBar {"
                        "border: 0px solid black;"
                        "background: rgba(255, 255, 255, 255);"
                        "padding: 3px;"
                        "padding-left: 1px;"
                        "padding-right: 1px;"
                        "min-height: 50px;"
                        "max-height: 50px;"
                        "}");
    //Icon
    iconButtomStatusLabel = new QLabel(this);
    iconButtomStatusLabel->setStyleSheet("QLabel {"
                                         "border: 0px solid black"
                                         "border-radius: 16px;"
                                         "padding: 1px;"
                                         "padding-left: 1px;"
                                         "padding-right: 1px;"
                                         "min-width: 48px;"
                                         "max-width: 48px;"
                                         "min-height: 48px;"
                                         "max-height: 48px;"
                                         "}");
    iconButtomStatusLabel->setMaximumHeight(STATUS_ICON_HEIGH+2);
    iconButtomStatusLabel->setMinimumHeight(STATUS_ICON_HEIGH+2);
    iconButtomStatusLabel->setAlignment(Qt::AlignHCenter);

    //ProgressBar
    progressBar = new QProgressBar(this);
    connect(progressBar,SIGNAL(valueChanged(int)),this,SLOT(setProgressValue(int)));
    connect(this,SIGNAL(progressHasPacket(int)),this,SLOT(addValueToProgressBar(int)));

    progressBar->setFixedWidth(120);
    progressBar->setFixedHeight(STATUS_ICON_HEIGH);
    progressBar->setStyleSheet("QProgressBar {"
                               "border: 1px solid gray;"
                               "border-radius: 3px;"
                               "background: transparent;"
                               "padding: 1px;"
                               "}"
                               "QProgressBar::chunk {"
                               "background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 #b4e391 , stop: 1 #61c419);"
                               "}");
    progressBar->setRange(0,100);
    progressBar->setValue(0);
    progressBar->setAlignment(Qt::AlignHCenter  | Qt::AlignVCenter);
    progressBar->setTextVisible(true);
    progressBar->setFormat("%p%");
    progressBar->setOrientation(Qt::Horizontal);


    addPermanentWidget(progressBar,0);
    addPermanentWidget(iconButtomStatusLabel,0);

}

void jceStatusBar::setIconConnectionStatus(jceProgressStatus update)
{
    QPixmap iconPix;
    switch (update)
    {
    case jceProgressStatus::Error:
        setProgressValue(0);
        iconPix.load(":/icons/disconnected.png");
        showMessage(tr("Error"));
        break;
    case jceProgressStatus::Disconnected:
        setProgressValue(0);
        iconPix.load(":/icons/disconnected.png");
        showMessage(tr("Disconnected"));
        break;
    case jceProgressStatus::Ready:
        setProgressValue(0);
        iconPix.load(":/icons/disconnected.png");
        showMessage(tr("Ready"));
        break;
    case jceProgressStatus::Connecting:
        setProgressValue(5);
        iconPix.load(":/icons/busy.png");
        showMessage(tr("Connecting..."));
        break;
    case jceProgressStatus::Sending:
        if (progressBar->value() < 10)
            setProgressValue(10);
        iconPix.load(":/icons/busy.png");
        showMessage(tr("Sending..."));
        break;
    case jceProgressStatus::Recieving:
        if (progressBar->value() < 15)
            setProgressValue(15);
        iconPix.load(":/icons/busy.png");
        showMessage(tr("Recieving..."));
        break;
    case jceProgressStatus::Connected:
        setProgressValue(30);
        iconPix.load(":/icons/busy.png");
        showMessage(tr("Connected"));
        break;
    case jceProgressStatus::Inserting:
        setProgressValue(80);
        iconPix.load(":/icons/busy.png");
        showMessage(tr("Inserting"));
        break;
    case jceProgressStatus::LoggedIn:
        setProgressValue(100);
        iconPix.load(":/icons/connected.png");
        showMessage(tr("Logged In."));
        break;
    case jceProgressStatus::Done:
        setProgressValue(100);
        iconPix.load(":/icons/connected.png");
        showMessage(tr("Done"));
        break;

    }
    iconButtomStatusLabel->setPixmap(iconPix);

    repaint();

}
/**
* @brief Every time the value changes this method will be called
* @param value = the value of the progress Bar
*/
void jceStatusBar::setProgressValue(int value)
{
    if (value == 0 || value == 100)
    {
        progressBar->setVisible(false);
        progressBar->setValue(0);
    }
    else
    {
        progressBar->setValue(value);
        progressBar->setVisible(true);
    }

}

void jceStatusBar::addValueToProgressBar(int value)
{
    progressBar->setValue(progressBar->value() + value);

}
