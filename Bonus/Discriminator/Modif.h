#ifndef                 MODIF_H
#define                 MODIF_H

# include               <QDialog>
# include               <QApplication>
# include               <QObject>
# include               <QWidget>
# include               <QtWidgets>
# include               <QMenu>
# include               <QAction>
# include               <QMainWindow>
# include               <QSystemTrayIcon>
# include               <QLocale>
# include               <QTranslator>
# include               <QLibraryInfo>
# include               <iostream>
# include               <fstream>
# include               <sstream>

namespace               Ui
{
    class               Modif;
}

class                   Modif : public QDialog
{
    Q_OBJECT

public:
    explicit            Modif(QWidget *parent = 0);
                        ~Modif();

    void                putInText(std::string);
    std::string         QStringToString(QString);
    std::string         intToString(int);

private slots:
    void                on_Cancel_clicked();
    void                on_Save_clicked();
    void                on_EditText_textChanged();
    void                on_Reset_clicked();
    void                on_Save_on_clicked();

private:
    Ui::Modif           *ui;
    QString             text;
    QString             original;

};

#endif // MODIF_H
