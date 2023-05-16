#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QProgressBar>
#include <QStringListModel>
#include <QTextStream>

#include "elementmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*
 * Définition des index des GroupBox
*/
#define INDEX_ADD_ELEMENT (0)
#define INDEX_MODIFY_ELEMENT (1)
#define INDEX_REMOVE_ELEMENT (2)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addElement(QString element);
    void setStatus(QString elem);
    QString getStatus();
    void setProgressBarVisible(bool status);

private slots:

    void on_send_btn_clicked();

    void on_elementStatus_cb_currentIndexChanged(int index);

    void on_actionEnregistrer_au_format_TXT_triggered();

    void on_file_cb_currentIndexChanged(int index);

    void on_filename_btn_clicked();

private:
    Ui::MainWindow *ui;
    QString status = "+";
    ElementModel *model;
    QVector<ElementModel *> *modelList;
    QProgressBar *progressBar;
};
#endif // MAINWINDOW_H
