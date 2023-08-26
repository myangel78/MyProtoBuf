#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Client.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Client");
    m_pClient = std::make_shared<Client>();
    m_pClient->StartThread();
}

MainWindow::~MainWindow()
{
    delete ui;
}

