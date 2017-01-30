#ifndef                 EDIT_H
# define                EDIT_H

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
    class               Edit;
}

class                   Edit : public QDialog
{
    Q_OBJECT

public:
    explicit            Edit(QWidget *parent = 0);
                        ~Edit();

    std::string         QStringToString(QString);
    std::string         intToString(int);

private slots:
    void                on_Cancel_clicked();
    void                on_Save_clicked();
    void                on_EditText_textChanged();
    void                on_Reset_clicked();
    void                on_Save_on_clicked();

private:
    Ui::Edit            *ui;
    QString             text;

};

#endif // EDIT_H
