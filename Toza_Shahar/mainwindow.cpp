#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuick>
#include <QtQuickWidgets/QQuickWidget>
#include <QSplitter>
#include <QLabel>
MainWindow::~MainWindow(){    delete ui;}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createGUI();
    sqlModel = new SqlQueryModel(this);
    bool check = createConnection();
    if(check==true)
    {
        sqlModel->setQuery("select ID,originTime,tip,"
                           "tipDescription,lat,lon from datainfo");
        viewTable->setModel(sqlModel);

    }
//    else
//    {
//        qDebug() << "Cannot open database:" << db.lastError();
//    }


    //==========QML===============
    QQuickView *view = new QQuickView();

    container = QWidget::createWindowContainer(view,this);


    QQmlContext *ctxt = view->rootContext();
    ctxt->setContextProperty("sqlModel", sqlModel);
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    //==========QML===============
    QSplitter *spl = new QSplitter(Qt::Vertical);

    spl->addWidget(container);
    spl->addWidget(viewTable);




    tabWidget->addTab(spl,"MAP");
    tabWidget->addTab(widTableView,"Events");
    ui->gridLayout->addWidget(tabWidget);
    //ui->gridLayout->addWidget(tabWidget);


    connect(btnReadDataBase,&QPushButton::clicked,this,&MainWindow::getDataFromDB);
    showMaximized();
    setWindowTitle("Clean City");
}

void MainWindow::createGUI()
{
    widTableView = new QWidget;
    meetingEdit = new QDateTimeEdit(QDateTime::currentDateTime());
    meetingEdit1 = new QDateTimeEdit(QDateTime::currentDateTime());
    tableEvent = new QTableView;
    btnReadDataBase = new QPushButton("Read");
    QHBoxLayout *hBox = new QHBoxLayout;
    hBox->addStretch(1);
    hBox->addWidget(new QLabel("From"));

    hBox->addWidget(meetingEdit);
    hBox->addWidget(new QLabel("To"));
    hBox->addWidget(meetingEdit1);
    hBox->addWidget(btnReadDataBase);
    QVBoxLayout *vBox = new QVBoxLayout;
    vBox->addWidget(tableEvent);
    vBox->addLayout(hBox);
    widTableView->setLayout(vBox);


    //QTABWIDGET
    tabWidget = new QTabWidget (this) ;
    //tabWidget->hide();
    //QTABLEVIEW
    viewTable = new QTableView;
    viewTable->setMaximumHeight(250);
    viewTable->setSelectionBehavior(QAbstractItemView::SelectRows);


    //FILE MENU
    quitAction = new QAction(tr("&Quit"),this);
    connect(quitAction,&QAction::triggered,this,&MainWindow::close);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(quitAction);
    //helpMenu = menuBar()->addMenu(tr("&Help"));
}

void MainWindow::getDataFromDB()
{

    sqlModel->setQuery("select * from datainfo");
    tableEvent->setModel(sqlModel);
}

bool MainWindow::createConnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("toza_shahar");
    db.setUserName("root");
    //db.setPassword("");
    db.setPassword("1234");
    if(!db.open())
    {
        return false;

    }
    return true;
}
