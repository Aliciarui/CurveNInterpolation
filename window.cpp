#include"window.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QTimer>
#include<QDebug>
#include<QtCore/QObject>
#include<QSpinBox>

window::window(QWidget* parent):QWidget(parent)
{
    layout();
}

void window::layout()
{
    w = new paintWindow();
    menuWindow = new QWidget();

    grainLabel = new QLabel("GRAIN | ");
    tensionLabel = new QLabel("TENSION | ");

    genButton = new QPushButton("show spline");
    startButton = new QPushButton("start move");
    clearButton = new QPushButton("clear");
    linearButton = new QPushButton("linear interpolation");
    vectorButton = new QPushButton("vector interpolation");
    secondButton = new QPushButton("second pattern");
    firstButton = new QPushButton("first pattern");
    transButton = new QPushButton("interpolation");
    interpolation = new QPushButton("show/hide points");

    startButton->setDisabled(true);
    firstButton->setDisabled(true);
    secondButton->setDisabled(true);
    linearButton->setDisabled(true);
    vectorButton->setDisabled(true);
    interpolation->setDisabled(true);

    grainLine = new QSpinBox();
    grainLine->setRange(1,30);
    grainLine->setSingleStep(1);
    grainLine->setValue(20);
    grainLine->setWrapping(true);


    tensionLine = new QDoubleSpinBox();
    tensionLine->setRange(0,1);
    tensionLine->setSingleStep(0.1);
    tensionLine->setValue(0.5);
    tensionLine->setWrapping(true);

    connect(genButton,SIGNAL(clicked()),this,SLOT(updatePaintWindow()));
    connect(clearButton,SIGNAL(clicked()),this,SLOT(clear()));
    connect(startButton,SIGNAL(clicked()),this,SLOT(start()));
    connect(firstButton,SIGNAL(clicked()),this,SLOT(firstpattern()));
    connect(secondButton,SIGNAL(clicked()),this,SLOT(secondpattern()));
    connect(linearButton,SIGNAL(clicked()),this,SLOT(linear_update()));
    connect(vectorButton,SIGNAL(clicked()),this,SLOT(vector_update()));
    connect(transButton,SIGNAL(clicked()),this,SLOT(start_trans()));
    connect(interpolation,SIGNAL(clicked()),this,SLOT(changein()));

    for(int i=0;i<5;i++){
        hlayout[i] = new QHBoxLayout;
        vlayout[i] = new QVBoxLayout;
    }
    mainlayout=new QVBoxLayout;
    menulayout=new QHBoxLayout;

    hlayout[0]->addWidget(grainLabel);
    hlayout[0]->addWidget(grainLine);

    hlayout[1]->addWidget(tensionLabel);
    hlayout[1]->addWidget(tensionLine);

    vlayout[0]->setMargin(30);
    vlayout[0]->addLayout(hlayout[0]);
    vlayout[0]->addLayout(hlayout[1]);
    vlayout[0]->addWidget(clearButton);

    vlayout[1]->setMargin(30);
    vlayout[1]->addWidget(genButton);
    vlayout[1]->addWidget(interpolation);
    vlayout[1]->addWidget(startButton);

    vlayout[2]->setMargin(30);
    vlayout[2]->addWidget(linearButton);
    vlayout[2]->addWidget(vectorButton);

    vlayout[3]->setMargin(30);
    vlayout[3]->addWidget(transButton);
    vlayout[3]->addWidget(firstButton);
    vlayout[3]->addWidget(secondButton);

    menulayout->setMargin(50);
    menulayout->addLayout(vlayout[0]);
    menulayout->addLayout(vlayout[1]);
    menulayout->addLayout(vlayout[3]);
    menulayout->addLayout(vlayout[2]);

    w->setFixedHeight(600);

    resize(900,900);
    mainlayout->addWidget(w);
    mainlayout->addLayout(menulayout);

    setLayout(mainlayout);
}

void window::updatePaintWindow()
{
    startButton->setDisabled(false);
    interpolation->setDisabled(false);
    w->setSpline(grainLine->text().toInt(),tensionLine->text().toDouble());
    w->flag=1;
    w->update();
}

void window::changein(){
    if(w->flag==1) w->flag=7;
    else if(w->flag==7) w->flag=1;
    w->update();
}

void window::clear()
{
    w->clearwindow();
    w->flag=0;
    startButton->setDisabled(true);
    firstButton->setDisabled(true);
    secondButton->setDisabled(true);
}

void window::start()
{
    w->flag=6;
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(70);
    w->new_count=0;
    interpolation->setDisabled(true);
}

void window::firstpattern()
{
    w->flag=2;
    secondButton->setDisabled(false);
    update();
}

void window::secondpattern()
{
    w->flag=3;
    linearButton->setDisabled(false);
    vectorButton->setDisabled(false);
    update();
}

void window::ten_update(){
    if(w->new_count<10){
        update();
    }
    else if(w->new_count>=10){
        timer->stop();
    }
}

void window::linear_update(){
    w->flag=4;
    w->new_count=0;
    connect(timer,SIGNAL(timeout()),this,SLOT(ten_update()));
    timer->start(500);
}

void window::vector_update(){
    w->flag=5;
    w->new_count=0;
    connect(timer,SIGNAL(timeout()),this,SLOT(ten_update()));
    timer->start(500);
}

void window::start_trans(){
    firstButton->setDisabled(false);
}
