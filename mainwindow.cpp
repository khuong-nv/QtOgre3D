#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include "MyTestWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(new KEngine::MyTestWidget());
}

MainWindow::~MainWindow()
{
    delete ui;
}

