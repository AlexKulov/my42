#include "mainwindow.h"
#include "ui_mainwindow.h"

Ui::MainWindow * extUi;
double mSimTime;  //Для передачи параметра в методы класса из внешней функции CppToPlot

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Simulation spacecraft");
    connect (ui->pushButtonSimulation,&QAbstractButton::clicked,this,&MainWindow::StartSimulation);
    setupPlots();

    ui->Plot11->addGraph();
    ui->Plot11->graph(0)->setPen(QColor(Qt::red));

    ui->Plot12->addGraph();
    ui->Plot12->graph(0)->setPen(QColor(Qt::red));
    ui->Plot12->addGraph();
    ui->Plot12->graph(1)->setPen(QColor(Qt::green));

    ui->Plot13->addGraph();
    ui->Plot13->graph(0)->setPen(QColor(Qt::red));
    ui->Plot13->addGraph();
    ui->Plot13->graph(1)->setPen(QColor(Qt::green));
    ui->Plot13->addGraph();
    ui->Plot13->graph(2)->setPen(QColor(Qt::blue));

    ui->Plot21->addGraph(); //plotKm
    ui->Plot21->graph(0)->setPen(QColor(Qt::red));
    ui->Plot22->addGraph();//plotWheelPower
    ui->Plot22->graph(0)->setPen(QColor(Qt::red));

    ui->Plot31->addGraph();//plotScMode
    ui->Plot31->graph(0)->setPen(QColor(Qt::red));
    ui->Plot32->addGraph();//plotWorkAndZRV
    ui->Plot32->graph(0)->setPen(QColor(Qt::red));

    uiPlotSampleCounter=0;
    uiPlotMaxCounter = 10;
    extUi = ui;
}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifdef __cplusplus
extern "C"{
#endif
void ToPlot(double Time);

int exec(int argc,char **argv);
#ifdef __cplusplus
}
#endif

extern double sunAng;
void ToPlot(double SimTime){
    mSimTime = SimTime;

    double ParamPlot12[3] = {0,1,2};
    double ParamPlot13[3] = {0,1,2};

    static unsigned int PlotSampleCounter=0;
    static unsigned int PlotMaxCounter = 10;

    PlotSampleCounter++;
    if(PlotSampleCounter>PlotMaxCounter){
        PlotSampleCounter = 0;
        if(true){
            extUi->Plot11->graph(0)->addData(SimTime,sunAng);
            extUi->Plot11->rescaleAxes();
            extUi->Plot11->replot();
        }

        if(false){
            extUi->Plot12->graph(0)->addData(SimTime,ParamPlot12[0]);
            extUi->Plot12->graph(1)->addData(SimTime,ParamPlot12[1]);
            extUi->Plot12->rescaleAxes();
            extUi->Plot12->replot();
        }

        if(false){
            extUi->Plot13->graph(0)->addData(SimTime,ParamPlot13[0]);
            extUi->Plot13->graph(1)->addData(SimTime,ParamPlot13[1]);
            extUi->Plot13->graph(2)->addData(SimTime,ParamPlot13[2]);
            extUi->Plot13->rescaleAxes();
            extUi->Plot13->replot();
        }

        if(false){
            extUi->Plot21->graph(0)->addData(SimTime,0);
            extUi->Plot21->rescaleAxes();
            extUi->Plot21->replot();
        }

        if(false){
            extUi->Plot22->graph(0)->addData(SimTime,1);
            extUi->Plot22->rescaleAxes();
            extUi->Plot22->replot();
        }

        if(false){
            extUi->Plot31->graph(0)->addData(SimTime,-1);
            extUi->Plot31->rescaleAxes();
            extUi->Plot31->replot();
        }

        if(false){
            extUi->Plot32->graph(0)->addData(SimTime,1);
            extUi->Plot32->rescaleAxes();
            extUi->Plot32->replot();
        }
        QApplication::processEvents();
    }

}

void MainWindow::StartSimulation(){
    exec(argc, argv);
}

void MainWindow::setupPlots()
{
    //Обработка двойных нажатий на графики
    connect(ui->Plot11, &QCustomPlot::mouseDoubleClick,     this,       &MainWindow::doubleClickSlot);
    connect(ui->Plot12, &QCustomPlot::mouseDoubleClick,     this,       &MainWindow::doubleClickSlot);
    connect(ui->Plot13, &QCustomPlot::mouseDoubleClick,     this,       &MainWindow::doubleClickSlot);
    connect(ui->Plot21, &QCustomPlot::mouseDoubleClick,     this,       &MainWindow::doubleClickSlot);
    connect(ui->Plot31, &QCustomPlot::mouseDoubleClick,     this,       &MainWindow::doubleClickSlot);
    connect(ui->Plot22, &QCustomPlot::mouseDoubleClick,     this,       &MainWindow::doubleClickSlot);
    connect(ui->Plot32, &QCustomPlot::mouseDoubleClick,     this,       &MainWindow::doubleClickSlot);

    //Обработка одиночных нажатий на графики
    connect(ui->Plot11, &QCustomPlot::mousePress,           this,       &MainWindow::pressEventSlot);
    connect(ui->Plot12, &QCustomPlot::mousePress,           this,       &MainWindow::pressEventSlot);
    connect(ui->Plot13, &QCustomPlot::mousePress,           this,       &MainWindow::pressEventSlot);
    connect(ui->Plot21, &QCustomPlot::mousePress,           this,       &MainWindow::pressEventSlot);
    connect(ui->Plot31, &QCustomPlot::mousePress,           this,       &MainWindow::pressEventSlot);
    connect(ui->Plot22, &QCustomPlot::mousePress,           this,       &MainWindow::pressEventSlot);
    connect(ui->Plot32, &QCustomPlot::mousePress,           this,       &MainWindow::pressEventSlot);

    //Обработка отпускания кнопки мыши над графиками
    connect(ui->Plot11, &QCustomPlot::mouseRelease,         this,       &MainWindow::releaseEventSlot);
    connect(ui->Plot12, &QCustomPlot::mouseRelease,         this,       &MainWindow::releaseEventSlot);
    connect(ui->Plot13, &QCustomPlot::mouseRelease,         this,       &MainWindow::releaseEventSlot);
    connect(ui->Plot21, &QCustomPlot::mouseRelease,         this,       &MainWindow::releaseEventSlot);
    connect(ui->Plot31, &QCustomPlot::mouseRelease,         this,       &MainWindow::releaseEventSlot);
    connect(ui->Plot22, &QCustomPlot::mouseRelease,         this,       &MainWindow::releaseEventSlot);
    connect(ui->Plot32, &QCustomPlot::mouseRelease,         this,       &MainWindow::releaseEventSlot);
}

void MainWindow::doubleClickSlot(QMouseEvent *event)
{
    Q_UNUSED(event)
    QCustomPlot* plot = qobject_cast<QCustomPlot*>(sender());
    if(!plot) return;
    plot->xAxis->setRange(0, mSimTime);
//    plot->yAxis->setRange(plot->yAxis->range().lower, plot->yAxis->range().upper);
    plot->replot();
}

void MainWindow::pressEventSlot(QMouseEvent *event)
{
    QCustomPlot * plot = qobject_cast<QCustomPlot*>(sender());
    if(!plot) return;
    if(event->button() & Qt::LeftButton) {
        plot->setSelectionRectMode(QCP::srmZoom);
    }
    if(event->button() & Qt::RightButton) {
        plot->setSelectionRectMode(QCP::srmNone);
        this->setCursor(Qt::ClosedHandCursor);
    }
}

void MainWindow::releaseEventSlot(QMouseEvent *event)
{
    if(event->button() & Qt::RightButton) {
        this->setCursor(Qt::ArrowCursor);
    }
}
