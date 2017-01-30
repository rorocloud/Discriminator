#include    "Discriminator.h"
#include    "ui_Discriminator.h"

Discriminator::Discriminator(QWidget *parent) : QMainWindow(parent), ui(new Ui::Discriminator)
{
    bool    quitWindow = true; /* true(quit window)/false(not quit window) */
    QApplication::setQuitOnLastWindowClosed(quitWindow);
    QIcon   *icon = new QIcon(QString(CLOUD));

    ui->setupUi(this);
    setWindowIcon(*icon);
    setWindowTitle("Discriminator");
    setFixedSize(1200, 700);

    initWallPaper();
    initMenuFile();
    initSystemTrayIcon(*icon);
    initPlayerSound();

    checkGraphWin = false;
    checkEditWin = false;
    checkModifWin = false;
}

Discriminator::~Discriminator()
{
    delete actionAbout;
    delete actionSound;
    delete actionQuit;
    delete menuFile;
    delete player;
    if (checkGraphWin)
        delete graphWin;
    if (checkEditWin)
        delete editWin;
    if (checkModifWin)
        delete modifWin;

    delete ui;
}

void            Discriminator::initWallPaper()
{
    QPixmap     bkgnd(WALL);
    QPalette    palette;

    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);
}

void            Discriminator::initPlayerSound()
{
    player = new QSoundEffect(this);
    player->setSource(QUrl::fromLocalFile(SOUND));
    player->setLoopCount(QSoundEffect::Infinite);
    player->setVolume(0.65f);
    player->play();
}

void            Discriminator::initSystemTrayIcon(QIcon icon)
{
    stIcon = new QSystemTrayIcon(this);
    stIcon->setContextMenu(menuFile);
    stIcon->setIcon(icon);
    stIcon->show();
    connect(stIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void            Discriminator::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick)
        show();
}

QAction         *Discriminator::initActionAbout()
{
    actionAbout = new QAction("&A propos", this);
    actionAbout->setIcon(QIcon(ABOUT));
    actionAbout->setShortcut(QKeySequence("Ctrl+A"));
    connect(actionAbout, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    return actionAbout;
}

void            Discriminator::checkSound()
{
    if (player->isMuted())
    {
        player->setMuted(false);
        actionSound->setIcon(QIcon(SP_UP));
    }
    else
    {
        player->setMuted(true);
        actionSound->setIcon(QIcon(SP_MUTE));
    }
}

QAction         *Discriminator::initActionSound()
{
    actionSound = new QAction("&Son", this);
    actionSound->setIcon(QIcon(SP_UP));
    actionSound->setShortcut(QKeySequence("Ctrl+S"));
    connect(actionSound, SIGNAL(triggered()), this, SLOT(checkSound()));
    return actionSound;
}

QAction         *Discriminator::initActionQuit()
{
    actionQuit = new QAction("&Quitter", this);
    actionQuit->setIcon(QIcon(QUIT));
    actionQuit->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    return actionQuit;
}

void            Discriminator::initMenuFile()
{
    menuFile = new QMenu(this);
    menuFile = menuBar()->addMenu("&Fichier");
    menuFile->setCursor(Qt::PointingHandCursor);
    menuFile->addAction(initActionSound());
    menuFile->addAction(initActionAbout());
    menuFile->addAction(initActionQuit());
}

int             Discriminator::checkFindFile()
{
    name = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichier Discriminator (*.dcm)");
    if (name.isEmpty())
        return 84;
    QString ext = name.section('.', -1);
    if (ext != "dcm")
    {
        QMessageBox::critical(this, tr("Erreur"), "Le type de fichier " + ext + " n'est pas reconnu. Extension de fichier reconnu : *.dcm");
        return 84;
    }
    return 0;
}

int             Discriminator::checkLine(QString textFile)
{
    bool        vir = false;
    int         nbVir;
    int         check;

    check = -2;
    nbVir = -1;
    for (int i = 0; textFile[i] != '\0'; i++)
    {
        if ((textFile[i] >= '0' && textFile[i] <= '9') && vir == false)
            check = -1;
        else if ((textFile[i] >= '0' && textFile[i] <= '9') && vir == true)
            check = 0;
        else if (textFile[i] == ';')
        {
            vir = true;
            nbVir++;
        }
    }
    if (nbVir > 0)
        vir = false;
    else if (check == 0 && vir == true)
        return 0;
    QMessageBox::warning(this, tr("Erreur"), "Syntax non conforme");
    return 84;
}

int             Discriminator::parseFile()
{
    file = new QFile(name);
    if (!file->exists())
    {
        QMessageBox::critical(this, tr("Erreur"), "Fichier inexistant");
        return 84;
    }
    else if (file->open(QFile::ReadOnly))
    {
        QTextStream flux(file);
        bool    empty = true;
        while (!flux.atEnd())
        {
            if (empty)
                empty = false;
            QString textFile = flux.readLine();
            if (checkLine(textFile))
                return 84;
            graphWin->putInMyList(QStringToString(textFile));
        }
        file->close();
        if (empty)
        {
            QMessageBox::warning(this, tr("Erreur"), "Fichier vide");
            return 84;
        }
        return 0;
    }
    QMessageBox::critical(this, tr("Erreur"), "Ce fichier ne peut pas être lu.");
    return 84;
}

void            Discriminator::on_OpenButton_clicked()
{
    graphWin = new Graph(this);
    checkGraphWin = true;
    if (checkFindFile())
        return ;
    else if (parseFile())
        return ;
    QFileInfo tmp(name);
    graphWin->setWindowTitle(tmp.fileName());
    graphWin->addCloudGraph();
    graphWin->show();
}

void            Discriminator::on_EditButton_clicked()
{
    editWin = new Edit(this);
    checkEditWin = true;
    editWin->show();
}

std::string     Discriminator::intToString(int nb)
{
    std::ostringstream  oss;

    oss << nb;
    return oss.str();
}

std::string     Discriminator::QStringToString(QString textChange)
{
    std::ostringstream  oss;

    oss << textChange.toStdString();
    return oss.str();
}

int             Discriminator::checkFindFileModif()
{
    name = QFileDialog::getOpenFileName(this, "Fichier à modifier", QString(), "");
    if (name.isEmpty())
        return 84;
    return 0;
}

int             Discriminator::getFile()
{
    file = new QFile(name);
    if (!file->exists())
    {
        QMessageBox::critical(this, tr("Erreur"), "Fichier inexistant");
        return 84;
    }
    else if (file->open(QFile::ReadOnly))
    {
        QTextStream flux(file);
        while (!flux.atEnd())
        {
            QString textFile = flux.readLine();
            modifWin->putInText(QStringToString(textFile));
        }
        file->close();
        return 0;
    }
    QMessageBox::critical(this, tr("Erreur"), "Ce fichier ne peut pas être lu.");
    return 84;
}

void            Discriminator::on_ModifButton_clicked()
{
    modifWin = new Modif(this);
    checkModifWin = true;
    if (checkFindFileModif())
        return ;
    else if (getFile())
        return ;
    QFileInfo tmp(name);
    modifWin->setWindowTitle("Modification : " + tmp.fileName());
    modifWin->show();
}
