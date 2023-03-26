#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include "KApplicationContext.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    OgreBites::KApplicationContext *context = new OgreBites::KApplicationContext();
    setCentralWidget(new QOgre3DWidget(context));
}

MainWindow::~MainWindow()
{
    delete ui;
}

