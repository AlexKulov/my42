#include "mainwindow.h"
#include "ui_mainwindow.h"

Ui::MainWindow * extUi;

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Simulation spacecraft");

    connect (ui->pushButtonSimulation,&QAbstractButton::clicked,this,&MainWindow::StartSimulation);

    ui->customPlot1->addGraph();
    ui->customPlot1->graph(0)->setPen(QColor(Qt::red));
    ui->customPlot1->addGraph();
    ui->customPlot1->graph(1)->setPen(QColor(Qt::green));
    ui->customPlot1->addGraph();
    ui->customPlot1->graph(2)->setPen(QColor(Qt::blue));

    ui->customPlot2->addGraph();
    ui->customPlot2->graph(0)->setPen(QColor(Qt::red));
    ui->customPlot2->addGraph();
    ui->customPlot2->graph(1)->setPen(QColor(Qt::green));
    ui->customPlot2->addGraph();
    ui->customPlot2->graph(2)->setPen(QColor(Qt::blue));

    ui->customPlot3->addGraph();
    ui->customPlot3->graph(0)->setPen(QColor(Qt::red));
    ui->customPlot3->addGraph();
    ui->customPlot3->graph(1)->setPen(QColor(Qt::green));
    ui->customPlot3->addGraph();
    ui->customPlot3->graph(2)->setPen(QColor(Qt::blue));
    ui->customPlot3->addGraph();
    ui->customPlot3->graph(3)->setPen(QColor(Qt::black));

    ui->plotKm->addGraph();
    ui->plotKm->graph(0)->setPen(QColor(Qt::red));
    ui->plotKm->addGraph();
    ui->plotKm->graph(1)->setPen(QColor(Qt::green));
    ui->plotKm->addGraph();
    ui->plotKm->graph(2)->setPen(QColor(Qt::blue));
    ui->plotKm->addGraph();
    ui->plotKm->graph(3)->setPen(QColor(Qt::black));

    ui->plotWheelPower->addGraph();
    ui->plotWheelPower->graph(0)->setPen(QColor(Qt::red));
    ui->plotWheelPower->addGraph();
    ui->plotWheelPower->graph(1)->setPen(QColor(Qt::green));
    ui->plotWheelPower->addGraph();
    ui->plotWheelPower->graph(2)->setPen(QColor(Qt::blue));
    ui->plotWheelPower->addGraph();
    ui->plotWheelPower->graph(3)->setPen(QColor(Qt::black));

    ui->plotScMode->addGraph();
    ui->plotScMode->graph(0)->setPen(QColor(Qt::red));
    ui->plotScMode->addGraph();
    ui->plotScMode->graph(1)->setPen(QColor(Qt::blue));

    ui->plotWorkAndZRV->addGraph();
    ui->plotWorkAndZRV->graph(0)->setPen(QColor(Qt::red));
    ui->plotWorkAndZRV->addGraph();
    ui->plotWorkAndZRV->graph(1)->setPen(QColor(Qt::blue));
    ui->plotWorkAndZRV->addGraph();
    ui->plotWorkAndZRV->graph(2)->setPen(QColor(Qt::green));

    uiPlotSampleCounter=0;
    uiPlotMaxCounter = 10;
    extUi = ui;
}

MainWindow::~MainWindow()
{
    delete ui;
}

double ParamForPlot[4];
double ParamForPlot3[4];
double ParamForPlot2[4];

double ParamForPlotVitality[4];
double ParamForPlotCapSource[4];

double ParamForPlotScMode[4];
double ParamForPlotWorkAndZRV[4];

double ParamForPlotPower;
double ParamForPlotCharge;
void CppToPlot(double SimTime){

        double anglOSK[3] = {0,1,2};

        ParamForPlot2[0] = anglOSK[0];
        ParamForPlot2[1] = anglOSK[1];
        ParamForPlot2[2] = anglOSK[2];

        double testAngle[3] = {0,1,2};
        ParamForPlot3[0]= -testAngle[0]; //SC[0].B->wn[0]* R2D
        ParamForPlot3[1]= -testAngle[1]; //SC[0].B->wn[1]* R2D
        ParamForPlot3[2]= -testAngle[2]; //SC[0].B->wn[2]* R2D

        ParamForPlotVitality[0] = 0;//;
        ParamForPlotVitality[1] = 1;

        static unsigned int PlotSampleCounter=0;
        static unsigned int PlotMaxCounter = 10;

        PlotSampleCounter++;
        if(PlotSampleCounter>PlotMaxCounter){
            PlotSampleCounter = 0;
            extUi->customPlot3->graph(0)->addData(SimTime,ParamForPlot3[0]); //wx
            extUi->customPlot3->graph(1)->addData(SimTime,ParamForPlot3[1]);//wy
            extUi->customPlot3->graph(2)->addData(SimTime,ParamForPlot3[2]);//wz
            //ui->customPlot3->graph(3)->addData(SimTime,ParamForPlot3[3]);//wz

            extUi->customPlot2->graph(0)->addData(SimTime,ParamForPlot2[0]);
            extUi->customPlot2->graph(1)->addData(SimTime,ParamForPlot2[1]);
            extUi->customPlot2->graph(2)->addData(SimTime,ParamForPlot2[2]);

            extUi->customPlot1->graph(0)->addData(SimTime,ParamForPlot[0]);

            extUi->plotScMode->graph(0)->addData(SimTime,ParamForPlotScMode[0]);
            extUi->plotScMode->graph(1)->addData(SimTime,ParamForPlotScMode[1]);

            extUi->plotWorkAndZRV->graph(0)->addData(SimTime,ParamForPlotWorkAndZRV[0]);
            extUi->plotWorkAndZRV->graph(1)->addData(SimTime,ParamForPlotWorkAndZRV[1]);
            extUi->plotWorkAndZRV->graph(2)->addData(SimTime,ParamForPlotWorkAndZRV[2]);

            extUi->plotKm->graph(0)->addData(SimTime,0);
            extUi->plotKm->graph(1)->addData(SimTime,1);
            extUi->plotKm->graph(2)->addData(SimTime,2);

            extUi->plotWheelPower->graph(0)->addData(SimTime,0);
            extUi->plotWheelPower->graph(1)->addData(SimTime,1);
            extUi->plotWheelPower->graph(2)->addData(SimTime,2);

            extUi->customPlot1->rescaleAxes();
            extUi->customPlot1->replot();
            extUi->customPlot2->rescaleAxes();
            extUi->customPlot2->replot();
            extUi->customPlot3->rescaleAxes();
            extUi->customPlot3->replot();

            extUi->plotKm->rescaleAxes();
            extUi->plotKm->replot();
            extUi->plotWheelPower->rescaleAxes();
            extUi->plotWheelPower->replot();
            extUi->plotScMode->rescaleAxes();
            extUi->plotScMode->replot();
            extUi->plotWorkAndZRV->rescaleAxes();
            extUi->plotWorkAndZRV->replot();

            QApplication::processEvents();
        }
}

#ifdef __cplusplus
extern "C"{
#endif
void ToPlot(double Time){
    CppToPlot(Time);
}

int exec(int argc,char **argv);
#ifdef __cplusplus
};
#endif

void MainWindow::StartSimulation()
{
    int argc = 1;
    exec(argc, NULL);
}
