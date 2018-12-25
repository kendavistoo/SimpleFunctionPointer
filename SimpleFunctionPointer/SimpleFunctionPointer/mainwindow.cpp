#include "mainwindow.h"

//---------- CONSTRUCTOR   MainWindow ----------

MainWindow :: MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ascendButt  = new QRadioButton("Ascend", this);
    descendButt = new QRadioButton("Descend", this);

    ascendButt->setGeometry (40, 50, 130, 24);
    descendButt->setGeometry(40, 90, 130, 24);

    buttGroup   = new QButtonGroup(this);
    buttGroup->addButton(ascendButt, 1);
    buttGroup->addButton(descendButt, 2);
    buttGroup->setExclusive(true);

    connect(ascendButt, &QAbstractButton::toggled, this, &MainWindow::SLOT_AscendClick);
    connect(descendButt, &QAbstractButton::toggled, this, &MainWindow::SLOT_DescendClick);
}

//---------- DESTRUCTOR   ~MainWindow ----------

MainWindow :: ~MainWindow()
{

}

//---------- paintEvent ----------

void MainWindow :: paintEvent(QPaintEvent* event){

    QPainter* painter = new QPainter(this);

    //paint indicator
    int x = 10 + (int)(20 + (rand() % 10));
    int y = (this->height() - 30);
    QRect myRect(x,y,8,8);
    painter->fillRect(myRect, Qt::red);

    //----------

    if (doSort){

        doSort = false;

        switch(order){

        case ORDER_ASCEND:
            valFcn = ascending;

            if (doBubble(valFcn)){
                doSort = true;
            }//if
            break;

        case ORDER_DESCEND:
            valFcn = descending;

            if (doBubble(valFcn)){
                doSort = true;
            }//if
        }//switch

        if ( ! doSort){
            drawArray();
        }//if
    }//if doSort

    delete painter;

    update();
}

//---------- ascending ----------

bool MainWindow :: ascending(int& a, int& b){
    return b < a;
}

//---------- descending ----------

bool MainWindow :: descending(int& a, int& b){
    return b > a;
}

//---------- doBubble ----------

bool MainWindow :: doBubble(ValidateFcn vFcn){

    bool didSwap = false;

    for (int i=0; i<(arraySize -1); i++){

        int a = array[i];
        int b = array[i+1];
        if ( (*vFcn)(a, b) ){
            int cpy = array[i];
            array[i] = array[i+1];
            array[i+1] = cpy;
            didSwap = true;
        }//if
    }//for i

    return didSwap;
}

//---------- drawArray ----------

void MainWindow :: drawArray(){

    QString str;
    for (int i=0; i<9; i++){
        str.append(QString::number(array[i]));
        str.append(" ");
    }
    qDebug()<<str;
}

//---------- SLOT_AscendClick ----------

void MainWindow :: SLOT_AscendClick(){

    if (ascendButt->isChecked()){
        order = ORDER_ASCEND;
        doSort = true;
        qDebug()<<"\nORDER_ASCEND";
        drawArray();
    }//if
}

//---------- SLOT_DescendClick ----------

void MainWindow :: SLOT_DescendClick(){

    if (descendButt->isChecked()){
        order = ORDER_DESCEND;
        doSort = true;
        qDebug()<<"\nORDER_DESCEND";
        drawArray();
    }//if
}






















