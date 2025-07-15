#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <fstream>
#include <QDir>
#include <QFileInfo>
#include <QRegularExpression>
#include <QTextStream>
#include <QCoreApplication>

void MainWindow::lancerAuDemarrage() {
    QString chemin = QCoreApplication::applicationDirPath() + "/run_beat.bat";
    QFile fichier(chemin);

    if (!fichier.exists()) {
        qDebug() << "Fichier run_beat.bat introuvable : " << chemin;
        return;
    }

    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier : " << chemin;
        return;
    }

    QTextStream stream(&fichier);
    QString ligneComplete;
    while (!stream.atEnd()) {
        QString ligne = stream.readLine().trimmed();
        if (ligne.endsWith("^")) {
            ligneComplete += ligne.left(ligne.length() - 1) + " ";
        } else {
            ligneComplete += ligne;
        }

        if (ligne.contains("python beat.py")) {
            break;
        }
    }
    fichier.close();
    if (ligneComplete.isEmpty()) {
        qDebug() << "Aucune ligne contenant 'python beat.py' trouvée.";
        return;
    }
    QRegularExpression regex("--(\\S+)\\s+(\\S+)");
    QRegularExpressionMatchIterator it = regex.globalMatch(ligneComplete);

    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        QString param = match.captured(1);
        QString valeur = match.captured(2);

        if (param == "port") ui->port->setText(valeur.replace("COM", ""));
        else if (param == "baudrate") ui->baudrate->setText(valeur);
        else if (param == "bp-low") ui->bplow->setText(valeur);
        else if (param == "bp-high") ui->bphigh->setText(valeur);
        else if (param == "bp-order") ui->bporder->setText(valeur);
        else if (param == "k-high") ui->khigh->setText(valeur);
        else if (param == "k-low") ui->klow->setText(valeur);
        else if (param == "min-interval") ui->mininterval->setText(valeur);
    }

    qDebug() << "Paramètres chargés depuis run_beat.bat";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lancerAuDemarrage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lunchButton_clicked()
{
    std::ofstream batchFile("run_beat.bat");

    batchFile << "@echo off\n"
              << "cd /d \"%~dp0\"\n"
              << "python --version >nul 2>&1\n"
              << "IF %ERRORLEVEL% NEQ 0 (\n"
              << "  echo Python n'est pas installe.\n"
              << "  start https://www.python.org/downloads/windows/\n"
              << "  pause\n"
              << "  exit\n"
              << ") ELSE (\n"
              << "  echo Python est installé\n"
              << ")\n"
              << "IF EXIST requirements.txt (\n"
              << "  echo Installation des bibliotheques...\n"
              << "  pip install -r requirements.txt\n"
              << ") ELSE (\n"
              << "  echo Le fichier requirements.txt est introuvable.\n"
              << "  echo numpy, scipy, pyserial, pyAudioWpatch\n"
              << ")\n"
              << "echo Lancement du programme...\n"
              << "python beat.py "
              << "--port COM" << ui->port->text().toStdString() << " "
              << "--baudrate " << ui->baudrate->text().toStdString() << " "
              << "--bp-low " << ui->bplow->text().toStdString() << " "
              << "--bp-high " << ui->bphigh->text().toStdString() << " "
              << "--k-high " << ui->khigh->text().toStdString() << " "
              << "--k-low " << ui->klow->text().toStdString() << " "
              << "--min-interval " << ui->mininterval->text().toStdString() << " "
              << "--bp-order " << ui->bporder->text().toStdString() << "\n"
              << "pause\n";

    batchFile.close();
    system("run_beat.bat");
}
