#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lunchButton_clicked();
    void on_save_clicked();
    void on_preset_currentIndexChanged(const QString &fichierNom);
    void on_deleteButton_clicked();  // <-- slot pour suppression

private:
    Ui::MainWindow *ui;

    void chargerFichiersBatch();
    void lancerAuDemarrage();
};

#endif // MAINWINDOW_H
