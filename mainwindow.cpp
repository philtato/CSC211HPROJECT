#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap image("C:/Users/phili/OneDrive/Desktop/scale.png");
    ui->img->setPixmap(image);



    //link
    ui->test->setText("<a href=\"https://www.youtube.com/watch?v=BHY0FxzoKZE/\">Click Here!</a>");
    ui->test->setTextFormat(Qt::RichText);
    ui->test->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->test->setOpenExternalLinks(true);

    //database
    QSqlDatabase mydb= QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/db/mydb.db");
    if(!mydb.open())
        ui->status->setText("Failed to open the database");
    else
        ui->status->setText("Connected...");



}




MainWindow::~MainWindow()
{
    delete ui;
}

//sql





void MainWindow::on_signIn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_signUp_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}




//goes back to homepage
void MainWindow::on_returnHome_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//goes back to homepage
void MainWindow::on_returnHome_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_finishSignUp_clicked()
{
    QString username1 = ui->usernameinput->text();
    QString password1 = ui->passinput->text();

    QSqlDatabase mydb= QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/db/mydb.db");
    if(!mydb.open()){
        qDebug()<<"Failed to open the database";
        return;
    }
    QSqlQuery qry1;
    //
    qry1.prepare("insert into login(username,password) values(:username, :password)");
    qry1.bindValue(":username", username1);
    qry1.bindValue(":password", password1);


    if(qry1.exec()){
        QMessageBox::critical(this,tr("Save"),tr("Saved"));
    }
    else{
        QMessageBox::critical(this,tr("Error:"),qry1.lastError().text());
    }

    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_signIn_2_clicked()
{
    QString username = ui->line_username->text();
    QString password = ui->line_password->text();

    QSqlDatabase mydb= QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/db/mydb.db");
    if(!mydb.open()){
        qDebug()<<"Failed to open the database";
        return;
    }
    QSqlQuery qry;
    if(qry.exec("select * from login where username='"+username +"'and password='"+password+"'")){
            int count=0;
            while (qry.next()){
                count++;
            }
            if(count==1){
                ui->loginstatus->setText("Success ");
                ui->stackedWidget->setCurrentIndex(3);
            }
            if(count>1){
                ui->loginstatus->setText("duplicate username or password");
            }
            if(count<1){
                ui->loginstatus->setText("invalid username or password");
            }
        }
}



void MainWindow::on_pushButton_clicked()
{
    QString Name = ui->nameInput->text();
    QString Location = ui->locationInput->text();
    QString Catagory = ui->catagoryinput->text();
    QString Price = ui->priceinput->text();

    QSqlDatabase mydb= QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/db/mydb.db");
    if(!mydb.open()){
        qDebug()<<"Failed to open the database";
        return;
    }
    QSqlQuery qry;
    //
    qry.prepare("insert into Locations(Name,Location,Catagory,Price) values(:Name, :Location, :Catagory, :Price)");
    qry.bindValue(":Name", Name);
    qry.bindValue(":Location", Location);
    qry.bindValue(":Catagory", Catagory);
    qry.bindValue(":Price", Price);

    if(qry.exec()){
        QMessageBox::critical(this,tr("Save"),tr("Saved"));
    }
    else{
        QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
    }
}


void MainWindow::on_loadtable_clicked()
{
    QSqlDatabase mydb= QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/db/mydb.db");
    if(!mydb.open()){
        qDebug()<<"Failed to open the database";
        return;
    }
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery(mydb);
    qry->prepare("select * from Locations");
    qry->exec();
    model->setQuery(std::move(*qry));
    ui->tableView->setModel(model);
    delete qry;
}


void MainWindow::on_signout_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("CSC 211H project to promote phyiscal activity");
    msgBox.exec();
}


void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Some benefits of physical activity on brain health happen right after a session of moderate-to-vigorous physical activity. Benefits include improved thinking or cognition for children 6 to 13 years of age and reduced short-term feelings of anxiety for adults. Regular physical activity can help keep your thinking, learning, and judgment skills sharp as you age. It can also reduce your risk of depression and anxiety and help you sleep better.  Both diet and physical activity play a critical role in maintaining a healthy body weight, losing excess body weight, or maintaining successful weight loss. You gain weight when you consume more calories through eating and drinking than the amount of calories you burn, including those burned during physical activity. It’s important to balance calories. When it comes to weight management, people vary greatly in how much physical activity they need. You may need to be more active than others to reach or maintain a healthy weight. Science shows that physical activity can reduce your risk of dying early from leading causes of death, like heart disease and some cancers. ");
    msgBox.exec();
}



void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


