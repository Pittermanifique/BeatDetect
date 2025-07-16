#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <fstream>
#include <QDir>
#include <QFileInfo>
#include <QRegularExpression>
#include <QTextStream>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>

void MainWindow::lancerAuDemarrage() {
    QDir::setCurrent(QCoreApplication::applicationDirPath());
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
    chargerFichiersBatch();

    connect(ui->preset,
            &QComboBox::currentTextChanged,
            this,
            &MainWindow::on_preset_currentIndexChanged);

    // Connexion pour le bouton suppression
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);

    if (ui->preset->count() > 0) {
        on_preset_currentIndexChanged(ui->preset->currentText());
    }

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
              << "  echo Python est installe\n"
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

void MainWindow::chargerFichiersBatch() {
    QString path = QCoreApplication::applicationDirPath();
    QDir dir(path);
    QStringList filtres;
    filtres << "*.bat";
    QFileInfoList fichiers = dir.entryInfoList(filtres, QDir::Files);

    ui->preset->clear();

    for (const QFileInfo &fileInfo : fichiers) {
        ui->preset->addItem(fileInfo.fileName());
    }

    ui->preset->addItem("new");

    ui->preset->setCurrentIndex(0);
}

void MainWindow::on_preset_currentIndexChanged(const QString &fichierNom) {
    if (fichierNom == "new") {
        // Clear tous les champs
        ui->Name->clear();
        ui->port->clear();
        ui->baudrate->clear();
        ui->bplow->clear();
        ui->bphigh->clear();
        ui->bporder->clear();
        ui->khigh->clear();
        ui->klow->clear();
        ui->mininterval->clear();

        qDebug() << "Nouveau preset vide sélectionné.";
        return;
    }

    QString chemin = QCoreApplication::applicationDirPath() + "/" + fichierNom;
    QFile fichier(chemin);

    if (!fichier.exists()) {
        qDebug() << "Fichier introuvable : " << chemin;
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

    ui->Name->setText(fichierNom.left(fichierNom.length() - 4));

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

    qDebug() << "Paramètres chargés depuis " << fichierNom;
}

void MainWindow::on_save_clicked()
{
    QString nomFichier = ui->Name->text().trimmed();
    if (nomFichier.isEmpty()) {
        qDebug() << "Le nom du preset ne peut pas être vide.";
        return;
    }

    if (!nomFichier.endsWith(".bat"))
        nomFichier += ".bat";

    QString chemin = QCoreApplication::applicationDirPath() + "/" + nomFichier;

    std::ofstream fichier(chemin.toStdString());
    if (!fichier.is_open()) {
        qDebug() << "Impossible de créer le fichier : " << chemin;
        return;
    }

    fichier << "@echo off\n"
            << "cd /d \"%~dp0\"\n"
            << "python --version >nul 2>&1\n"
            << "IF %ERRORLEVEL% NEQ 0 (\n"
            << "  echo Python n'est pas installe.\n"
            << "  start https://www.python.org/downloads/windows/\n"
            << "  pause\n"
            << "  exit\n"
            << ") ELSE (\n"
            << "  echo Python est installe\n"
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

    fichier.close();

    qDebug() << "Preset sauvegardé : " << nomFichier;

    // Recharge la liste des presets pour inclure le nouveau
    chargerFichiersBatch();

    // Sélectionne automatiquement le nouveau preset
    int index = ui->preset->findText(nomFichier);
    if (index >= 0) {
        ui->preset->setCurrentIndex(index);
    }
}


void MainWindow::on_deleteButton_clicked()
{
    QString fichierNom = ui->preset->currentText();

    // On ne supprime rien si l'utilisateur a sélectionné "new" ou un champ vide
    if (fichierNom.isEmpty() || fichierNom == "new") {
        qDebug() << "Aucun preset valide sélectionné pour la suppression.";
        return;
    }

    QString chemin = QCoreApplication::applicationDirPath() + "/" + fichierNom;
    QFile fichier(chemin);

    if (!fichier.exists()) {
        qDebug() << "Le fichier n'existe pas : " << chemin;
        return;
    }

    bool removed = fichier.remove();

    if (removed) {
        qDebug() << "Preset supprimé : " << fichierNom;
        chargerFichiersBatch();  // Recharge la liste
        ui->preset->setCurrentText("new");  // Sélectionne "new"
    } else {
        qDebug() << "Échec de la suppression de : " << fichierNom;
    }
}
