#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    main_thread = new MainThread();
    main_thread->logs = ui->label;
    renderer = new RenderArea(ui->widget);
    main_thread->renderer = renderer;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    main_thread->Connect();
}

void MainWindow::on_pushButton_2_clicked() {
    main_thread->Disconnect();
}
