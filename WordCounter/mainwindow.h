#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QLayoutItem>

#include "word.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void addSeparator();

    int currentSortMode = 0;

    QList<Word> curWordList;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void readFile(QList<Word> &inputList,QString filePath);
    void processText(QList<Word> &inputList, QString line);
    void sortList(QList<Word> &inputList,int sortMode);

    void actOutput(QList<Word> &inputList);

    static const int SORT_MOST_COMMON = 0;
    static const int SORT_ALPHAB = 1;

private slots:
    void on_startButton_clicked();

    void on_sort_number_toggled(bool checked);

    void on_sort_alphab_toggled(bool checked);

    void on_actionOuvrir_triggered();

private:
    Ui::MainWindow *ui;
};

void removePonct(QString &in);

void cleanLayout(QLayout* layout);

#endif // MAINWINDOW_H
