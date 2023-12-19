#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <QLineEdit>
#include <QCheckBox>
#include <QProgressBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

QTimer timerPlotPaint;
//----------------------------------------------------------
public:
explicit MainWindow(QWidget *parent = nullptr);
~MainWindow();

public:
void StartSimulation();

private:
Ui::MainWindow *ui;

private:
    unsigned int uiPlotSampleCounter;
    unsigned int uiPlotMaxCounter;
};

#endif // MAINWINDOW_H
