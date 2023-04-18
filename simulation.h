
#ifndef SIMULATION_H
#define SIMULATION_H
#include<vector>
#include<QWidget>
#include<QFrame>
#include<QTextEdit>
#include<QString>
#include<QPushButton>
#include<QtCore>
#include<QObject>
#include<QAbstractButton>
#include<QApplication>
#include<QTimer>


class Passenger;
class Floor;
class Elevator;
class ElevatorClassic;
class ElevatorModern;
class ElevatorDestinationControl;
class ElevatorManager;

//symulacja jest tu zorganizowana jako pętla symulacyjna:
//winda się rusza a potem wszyscy pasażerowie są uruchamiani

class Simulation
{
    const int simWi = 40;
    const int simHe = 60;
    struct FramePosition {
        int x;
        int y;
    };

private:
    std::vector<Floor*> floors;
    std::vector<Elevator*> elevators;
    std::vector<Passenger*> passengers;
    ElevatorManager *eManager;
    QWidget* parent;
    int bottom_window;
    QTextEdit *textField;
    int paintButtonPosition;
    std::vector<std::vector<FramePosition>> floorPictures;
    std::vector<QFrame*> elevatorPictures;
    QTimer *simulationTimer;
    void prepareButton(void(Simulation::*f)(),QString);
    void addFloor();
    template <class T> void addElevator();
    void createFloorPictures();
    void createElevatorManager();
    void executeElevators();
    void executePassengers();
    void printContent();
    void paint();
//public slots:
    Passenger *createPassenger(int, int);
    void printSimulationTest();
    void printSimulationStep();
    void printSimulationPassenger();
    void printSimulationLoop();
    void SimulationLoop();
    void paintElevators();
    void quitProgram();
public:
    Simulation(QWidget*);
    ~Simulation();
    void initializeSimulation(int,int);
};


#endif // SIMULATION_H
