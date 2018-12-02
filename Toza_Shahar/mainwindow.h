#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include "sqlquerymodel.h"
#include <QTableView>
#include <QSplitter>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createGUI();
    bool createConnection();
public slots:
    void getDataFromDB();

private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *quitAction;
    QAction *helpAction;

    QSqlDatabase db;
    QTableView *viewTable;
    QTabWidget *tabWidget;
    SqlQueryModel *sqlModel;
    QWidget *container;
    QWidget *widTableView;
    QTableView *tableEvent;
    QDateTimeEdit *meetingEdit;
    QDateTimeEdit *meetingEdit1;
    QPushButton *btnReadDataBase;
};

#endif // MAINWINDOW_H
