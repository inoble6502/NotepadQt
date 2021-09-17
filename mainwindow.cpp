#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//erase current file name and the text in the textEdit areas
void MainWindow::on_actionNew_triggered()
{
    this->openedFile.clear();
    ui->textEdit->setText(QString());
}

//open file window
void MainWindow::on_actionOpen_triggered()
{
    QString f = QFileDialog::getOpenFileName(this, "Open text file");
    QFile file(f);
    this->openedFile = f;

    if(!file.open(QFile::Text | QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Error", "Couldn't open file: " + file.errorString());
        return;
    }

    setWindowTitle(f);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();

}

void MainWindow::on_actionSave_triggered()
{
    QString f = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(f);

    if(!file.open(QFile::Text | QFile::WriteOnly))
    {
        QMessageBox::warning(this, "Error", "Cannot save file" + file.errorString() );
        return;
    }

    openedFile = f;
    //setWindowTitle(f);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();

}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter p;
    p.setPrinterName("Printer Name");
    QPrintDialog printDialog(&p, this);
    if(printDialog.exec() == QDialog::Rejected)
    {
        QMessageBox::warning(this, "Error", "Unable to access printer");
        return;
    }
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
