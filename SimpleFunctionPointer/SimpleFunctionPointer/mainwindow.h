#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

static const int ORDER_NONE     = 0;
static const int ORDER_ASCEND   = 1;
static const int ORDER_DESCEND  = 2;

//----------

typedef bool (*ValidateFcn)(int&, int&);

//---------- class MainWindow ----------

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static bool    ascending(int&, int&);
    static bool    descending(int&, int&);

    void    drawArray();

    int array[9] = { 3, 7, 9, 5, 6, 1, 8, 2, 4 };
    int arraySize = 9;

    QRadioButton*   ascendButt;
    QRadioButton*   descendButt;

    QButtonGroup*   buttGroup;

    ValidateFcn valFcn;

    int order = ORDER_NONE;

    bool doSort = false;

    bool doBubble(ValidateFcn);

protected:
    void paintEvent(QPaintEvent*);

public slots:
    void SLOT_AscendClick();
    void SLOT_DescendClick();
};

#endif // MAINWINDOW_H
