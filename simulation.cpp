
#include "simulation.h"
#include "passenger.h"
#include"elevator.h"
#include "elevatormodern.h"
#include "elevatorclassic.h"
#include "elevatordestinationcontrol.h"
#include "elevatormanager.h"
#include "floor.h"
#include "directionkind.h"

Simulation::Simulation(QWidget* parent)
{
    this->parent = parent;
}

void Simulation::addFloor() {
    Floor *p = new Floor();
    floors.push_back(p);
}
template <class T>
void Simulation::addElevator() {
    int size = floors.size();
//    Zamiast szablonu przedtem mogłoby być coś takiego:
    //    ElevatorClassic*p = new ElevatorDestinationControl(size-1);
    //    ElevatorClassic*p = new ElevatorClassic(size-1);
    //    ElevatorModern *p = new ElevatorModern(size-1);
    T *p = new T(size-1);
    elevators.push_back(p);
}

void Simulation::createElevatorManager(){
    eManager  = new ElevatorManager(elevators, floors);
}

Passenger *Simulation::createPassenger(int start, int final){
    Passenger *p = new Passenger(start,final,
                             floors, elevators, eManager);
    passengers.push_back(p);
    return p;
}

void Simulation::initializeSimulation(int countFloors, int countElevators) {
    for (int i=0 ; i<countFloors ; i++)
        addFloor();
    // tu jest właśnie to miejsce, w którym sztucznie wykorzystuję szablon
    // inicjując różne rodzaje wind
    for (int i=0 ; i<countElevators-2 ; i++) {
        addElevator<ElevatorModern>();
    }
    addElevator<ElevatorClassic>();
    addElevator<ElevatorDestinationControl>();
    createElevatorManager();
    paint();
}

void Simulation::executeElevators(){
    for (size_t i=0; i<elevators.size(); i++) {
        elevators[i]->execute();
    }
}
void Simulation::executePassengers(){
    for (size_t i=0; i<passengers.size(); i++) {
        passengers[i]->execute();
    }
}
void Simulation::prepareButton(void(Simulation::*f)(), QString text) {
    QPushButton *button= new QPushButton(parent);
    button->setText(text);
    button->move(button->x()+button->width()*paintButtonPosition++,textField->height());
    QAbstractButton::connect(button, &QPushButton::clicked, parent, [=](){
        (this->*f)();
    });
    button->setParent(parent); // dzięki temu będę go mógł usunąć
    // zrezygnowałem z SIGNAL na rzecz nowszej lambdy, nie trzeba w niej SLOT-ów
    // tu zapamiętałem poprzednią wersję i porównanie:
    //    QAbstractButton::connect(buttonSimulTest, SIGNAL(clicked()), this, SLOT(printSimulation()));
    //    QAbstractButton::connect(buttonSimulTest, &QPushButton::clicked, parent, [=](){
    //        printSimulation();
    //    });

}
void Simulation::printSimulationTest(){
    QString s = QString("Wind: %1").arg(elevators.size());
    s += QString(" pięter: %1").arg(floors.size());
    s += QString(" pasażerów: %1").arg(passengers.size());
    textField->setText(s);
}
void Simulation::printContent(){
    QString s = "";
    for (size_t i=0; i<elevators.size(); i++) {
        s +=QString("f%1").arg(elevators[i]->currentFloor);
        s +=QString("[p%1/").arg(elevators[i]->passengers.size());
        s +=QString("s%1]\t").arg(elevators[i]->stops.size());

    }
    textField->setText(s);
    paintElevators();
}
void Simulation::paintElevators(){
    for(int i=0; i<int(elevators.size()); i++) {
        int x = floorPictures[i][elevators[i]->currentFloor].x;
        int y = floorPictures[i][elevators[i]->currentFloor].y;
        elevatorPictures[i]->move(x,y);
        elevatorPictures[i]->setStyleSheet("QWidget {background-color:#800;"
                                           "border: 4px solid gray;"
                                           "border-style: groove;}");
        if (elevators[i]->directory == staying)
            elevatorPictures[i]->setStyleSheet(elevatorPictures[i]->styleSheet() + QString("QWidget {background-color: #800;}"));
        if (elevators[i]->directory == up ||  elevators[i]->directory == down )
            elevatorPictures[i]->setStyleSheet(elevatorPictures[i]->styleSheet() + QString("QWidget {background-color: #d00;}"));
        if (elevators[i]->stateOpened)
            elevatorPictures[i]->setStyleSheet(elevatorPictures[i]->styleSheet() + QString("QWidget {background-color: #f33; border: 1px solid gray;}"));
    }
}
void Simulation::printSimulationStep(){
    executeElevators();
    executePassengers();
    printContent();
}
void Simulation::printSimulationPassenger(){
    // loswanie pięter dla pasażera
    int start = std::rand() % floors.size();
    int end = std::rand() % floors.size();
    while (start == end) {
        end = std::rand() % floors.size();
    }
    // testuję
    Passenger *p = createPassenger(start, end);
//    Passenger *p = createPassenger(1,4);
    // raportowanie
    QString s = QString("Pasażer");
    s += QString(" f%1").arg(p->currentFloor);
    s += QString(" -> %1").arg(p->finalFloor);
    textField->setText(s);
    executePassengers();
    printContent();
}

void Simulation::SimulationLoop(){
    int start = std::rand() % 5;
    if (start == 0)
        printSimulationPassenger();
    executeElevators();
    executePassengers();
    paintElevators();
}

void Simulation::printSimulationLoop(){
    simulationTimer = new QTimer(parent);
    // Stara wersja
//    QAbstractButton::connect(simulationTimer, SIGNAL(timeout()), parent, SLOT(Simulation::SimulationLoop));
    // zmodernizowana wersja, bez SIGNAL/SLOT:
    QAbstractButton::connect(simulationTimer, &QTimer::timeout,
            [=](){Simulation::SimulationLoop();});
    simulationTimer->start(200);
}
void Simulation::quitProgram() {
    QApplication::quit();
}

void Simulation::createFloorPictures(){
    for (int i=0 ; i < int(elevators.size()); i++) {
        std::vector<FramePosition> vectFloor;
        for (int j=0 ; j < int(floors.size()); j++) {
            // tworzę ramkę i zapisuję jej współrzędne
            QFrame *el = new QFrame(parent);
            el->setFixedSize(simWi,simHe);
            el->setStyleSheet("background-color: #555;"
                              "border: 2px solid gray;"
                              "border-style: groove;");
            el->move(simWi*(i),bottom_window-simHe*(1+j));
            FramePosition pos;
            pos.x = el->pos().x();
            pos.y = el->pos().y();
            vectFloor.push_back(pos);
        }
        floorPictures.push_back(vectFloor);
        // tworzę windę - symulację graficzną
        QFrame *el = new QFrame(parent);
        el->setFixedSize(simWi,simHe);
        elevatorPictures.push_back(el);
    }
}


void Simulation::paint(){
    parent->resize(600,800);
    bottom_window = parent->height();
    textField = new QTextEdit(parent);
    textField->setGeometry(0,0,parent->width(),textField->height());
    textField->setFontPointSize(14);
    paintButtonPosition = 0;
    prepareButton(&Simulation::printSimulationTest,"Info");
    prepareButton(&Simulation::printSimulationStep, "Step");
    prepareButton(&Simulation::printSimulationPassenger,"New passenger");
    prepareButton(&Simulation::printSimulationLoop,"Pętla");
    prepareButton(&Simulation::quitProgram, "Quit");
    createFloorPictures();
    paintElevators();
}
Simulation::~Simulation() {
    delete simulationTimer;
    delete textField;
    delete eManager;
    for (QFrame* frame: elevatorPictures) {
        delete frame;
    }
    for (Elevator* elevator: elevators) {
        delete elevator;
    }
    for (Floor * floor: floors) {
        delete floor;
    }
    for (Passenger* passenger: passengers) {
        delete passenger;
    }
}
