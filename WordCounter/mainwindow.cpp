#define DEBUG qDebug()
#define TEXT_SIZE 5

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QRegExp>
#include <QLabel>
#include <QFrame>
#include <QFileDialog>

#include <QDebug>

#include "word.h"


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::addSeparator()
{
    QFrame* hFrame = new QFrame;
    hFrame->setFrameShape(QFrame::HLine);

    ui->sa_outList->addWidget(hFrame);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::readFile(QList<Word> &inputList,QString filePath)
{
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this,"Erreur","Impossible d'ouvrir le fichier :\n"+filePath);
        return;
    }

    QString line = QString(file.readAll());
    processText(inputList,line);

    file.close();
}

void MainWindow::processText(QList<Word> &inputList, QString line)
{
    removePonct(line);
    line = line.replace(QRegExp("[\\s\\n\\r]+"), " ");//remove multiple spaces and newlines

    DEBUG << line;

    QList<QString> wordList = line.split(" ");

    bool wordFound = false;

    for(QString x : wordList)
    {
        int inputListLen = inputList.length();
        for(int i = 0; i < inputListLen;i++)
        {
            if(inputList[i].compare(x.remove(" ")))
            {
                wordFound = true;
                break;
            }
        }

        if(!wordFound)
        {
            inputList.append(Word(x));
        }
        wordFound = false;
    }
}


void MainWindow::sortList(QList<Word> &inputList,int sortMode)
{
    if(sortMode == SORT_MOST_COMMON)
    {
        std::sort(inputList.begin(),inputList.end(),countMoreThan());
    }
    else if(sortMode == SORT_ALPHAB)
    {
        std::sort(inputList.begin(),inputList.end(),alphabInferior());
    }

    curWordList = inputList;
}


void removePonct(QString &in)
{
    for(int i = 0; i < in.length();i++)
    {
        if(in.at(i).isPunct())
        {
            in.replace(i,1,' ');
        }
    }
}

void MainWindow::on_startButton_clicked()
{
    QString filePath("A:/Mathieu/Documents/Programmation/délire/WordCounter/base.txt");

    filePath = QFileDialog::getOpenFileName(this,"Ouvrir");
    if(filePath.isEmpty())
    {
        //QMessageBox::critical(this,"Erreur","Fichier introuvable");
        return;
    }

    QList<Word> wordList;
    curWordList = wordList;

    readFile(wordList,filePath);

    actOutput(wordList);
}

void MainWindow::actOutput(QList<Word> &inputList)
{
    sortList(inputList,currentSortMode);

    //clean layout
    cleanLayout(ui->sa_outList);


    for(Word w : inputList)
    {
        QLabel *temp = new QLabel("<font size=\""+QString::number(TEXT_SIZE)+"\"><b><font>"+w.getValue()+"</font></b> : <b><font color=\"red\">"
                                  +QString::number(w.getCount())+"</font></b></font>");
        ui->sa_outList->addWidget(temp);

        addSeparator();
    }
}

void MainWindow::on_sort_number_toggled(bool checked)
{
    if(checked)
        currentSortMode = MainWindow::SORT_MOST_COMMON;

    actOutput(curWordList);
}

void MainWindow::on_sort_alphab_toggled(bool checked)
{
    if(checked)
        currentSortMode = MainWindow::SORT_ALPHAB;

    actOutput(curWordList);
}


//-------------------------------------

void cleanLayout(QLayout* layout)
{
    QLayoutItem* child;
    while(layout->count()!=0)
    {
        child = layout->takeAt(0);
        if(child->layout() != nullptr)
        {
            cleanLayout(child->layout());
        }
        else if(child->widget() != nullptr)
        {
            delete child->widget();
        }

        delete child;
    }
}

void MainWindow::on_actionOuvrir_triggered()
{
    on_startButton_clicked();
}
