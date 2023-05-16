#include "mainwindow.h"
#include "elementmodel.h"
#include "textfieldcustom.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(500, 520));
    this->model = new ElementModel(this);
    this->modelList = new QVector<ElementModel *>;
    this->modelList->append(this->model);
    this->ui->list_element->setModel(this->model);
    this->setWindowTitle("ChangelogMaker V.1.1");

    // progress bar
    progressBar = new QProgressBar(ui->statusBar);
    progressBar->setAlignment(Qt::AlignRight);
    progressBar->setMaximumSize(180, 19);
    ui->statusBar->addWidget(progressBar);
    progressBar->setVisible(false);

    connect(ui->filename_tf, SIGNAL(submitted()), this, SLOT(on_filename_btn_clicked()));
    connect(ui->element_tf, SIGNAL(submitted()), this, SLOT(on_send_btn_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_send_btn_clicked()
{
    if (this->ui->element_tf->text().isEmpty())
        return;
    addElement(getStatus() + " " + this->ui->element_tf->text());
    ui->element_tf->setText("");
}

void MainWindow::on_elementStatus_cb_currentIndexChanged(int index)
{
    switch (index) {
    case INDEX_ADD_ELEMENT:
        setStatus("+");
        break;
    case INDEX_MODIFY_ELEMENT:
        setStatus("~");
        break;
    case INDEX_REMOVE_ELEMENT:
        setStatus("-");
        break;
    }
}

void MainWindow::addElement(QString element)
{
    QStringList list = this->model->stringList();
    list << element;
    this->model->setStringList(list);
}

void MainWindow::setStatus(QString elem)
{
    this->status = elem;
}

QString MainWindow::getStatus()
{
    return this->status;
}

void MainWindow::on_actionEnregistrer_au_format_TXT_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Enregistrer", "", "TextFile (*.txt)");

    if (filename.isEmpty())
        return;

    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    setProgressBarVisible(true);
    progressBar->setValue(0);

    QTextStream out(&file);

    out << ui->title_tf->text() + "\n";
    out << "\n";
    out << "Changelog : \n\n";
    for (int i = 0; i < modelList->size(); i++) {
        if (ui->file_cb->itemText(i).compare("default") != 0)
            out << ui->file_cb->itemText(i) << " : \n";
        for (QString element : modelList->at(i)->stringList())
            out << "\t" << element << "\n";
        progressBar->setValue(100.0 / i);
    }

    file.close();
    progressBar->setValue(100);
    setProgressBarVisible(false);
}

void MainWindow::on_file_cb_currentIndexChanged(int index)
{
    model = modelList->at(index);
    ui->list_element->setModel(model);
}

void MainWindow::on_filename_btn_clicked()
{
    if (ui->filename_tf->text().isEmpty())
        return;
    ui->file_cb->addItem(ui->filename_tf->text());
    modelList->append(new ElementModel(this));
    model = modelList->last();
    ui->list_element->setModel(model);
    ui->filename_tf->setText("");
    ui->file_cb->setCurrentIndex(modelList->size() - 1);
}

void MainWindow::setProgressBarVisible(bool status)
{
    progressBar->setVisible(status);
}
