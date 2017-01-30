#ifndef                 DISCRIMINATOR_H
#define                 DISCRIMINATOR_H

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
# include               <QMediaPlayer>
# include               <QtMultimedia>
# include               <QSoundEffect>
# include               <sstream>
# include               "Edit.h"
# include               "Modif.h"
# include               "Graph.h"

#if defined(_WIN32)
# define                ABOUT       "C:/Users/Romain/Documents/Qt/Discriminator/images/About.png"
# define                CLOUD       "C:/Users/Romain/Documents/Qt/Discriminator/images/cloud.png"
# define                SOUND       "C:/Users/Romain/Documents/Qt/Discriminator/wind.wav"
# define                SP_UP       "C:/Users/Romain/Documents/Qt/Discriminator/images/speaker_up.png"
# define                SP_MUTE     "C:/Users/Romain/Documents/Qt/Discriminator/images/speaker_mute.png"
# define                QUIT        "C:/Users/Romain/Documents/Qt/Discriminator/images/Quit.png"
# define                WALL        "C:/Users/Romain/Documents/Qt/Discriminator/images/wall.jpg"
#endif

#if defined(__unix__)
# define                ABOUT       "/home/romain/Projet/Tek3/Qt/Discriminator/images/About.png"
# define                CLOUD       "/home/romain/Projet/Tek3/Qt/Discriminator/images/cloud.png"
# define                SOUND       "/home/romain/Projet/Tek3/Qt/Discriminator/wind.wav"
# define                SP_UP       "/home/romain/Projet/Tek3/Qt/Discriminator/images/speaker_up.png"
# define                SP_MUTE     "/home/romain/Projet/Tek3/Qt/Discriminator/images/speaker_mute.png"
# define                QUIT        "/home/romain/Projet/Tek3/Qt/Discriminator/images/Quit.png"
# define                WALL        "/home/romain/Projet/Tek3/Qt/Discrimninator/images/wall.jpg"
#endif

namespace               Ui
{
    class               Discriminator;
}

class                   Discriminator : public QMainWindow
{
    Q_OBJECT

public:
    explicit            Discriminator(QWidget *parent = 0);
                        ~Discriminator();

    void                initMenuFile();
    void                initWallPaper();
    QAction             *initActionSound();
    QAction             *initActionAbout();
    QAction             *initActionQuit();
    void                initSystemTrayIcon(QIcon);
    void                initPlayerSound();
    std::string         intToString(int);
    std::string         QStringToString(QString);
    int                 checkFindFile();
    int                 parseFile();
    int                 checkFindFileModif();
    int                 getFile();
    int                 checkParse();
    int                 checkLine(QString);

public slots:
    void                iconActivated(QSystemTrayIcon::ActivationReason);
    void                on_OpenButton_clicked();
    void                on_EditButton_clicked();
    void                on_ModifButton_clicked();
    void                checkSound();

private:
    Ui::Discriminator   *ui;
    QMenu               *menuFile;
    QAction             *actionAbout;
    QAction             *actionSound;
    QAction             *actionQuit;
    QSystemTrayIcon     *stIcon;
    QSoundEffect        *player;
    QString             name;
    QFile               *file;
    Edit                *editWin;
    Modif               *modifWin;
    Graph               *graphWin;
    bool                checkGraphWin;
    bool                checkEditWin;
    bool                checkModifWin;

};

#endif // DISCRIMINATOR_H
