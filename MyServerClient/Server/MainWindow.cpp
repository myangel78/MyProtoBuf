#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Server.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Server");
    m_pServer = std::make_shared<Server>();
    m_pServer->StartThread();
}

MainWindow::~MainWindow()
{
    delete ui;
}
