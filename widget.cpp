
#include "widget.h"
#include "ui_widget.h"
#include "simulation.h"
#include<QFrame>
#include<QLineEdit>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Windy - wersja druga");

    // najpierw stworzyć piętra (wektor)
    // stworzyć windy [, dodac do każdej wektor pięter]
    // ----------------------------------------------
    // pętla symulacyjna:
    // [opcjonalnie] tworzyć pasażera, dodając mu wektory pięter i wind
    // execute wszystkich wind [wektor wind w symulatorze]
    // execute wszystkich pasażerów [wektor pasażerów w symulatorze]
    Simulation *simulation = new Simulation(this);
    // najpierw buduję budynek (np. 10 pięter), a potem
    // dodaję windy (np. 5 wind)
    simulation->initializeSimulation(10, 5);
//    setFixedSize(40,120);

//    simulation->paint();


}

Widget::~Widget()
{
    delete ui;
}


