#include        "Edit.h"
#include        "ui_Edit.h"

Edit::Edit(QWidget *parent) : QDialog(parent), ui(new Ui::Edit)
{
    ui->setupUi(this);
    setWindowTitle("Créer un fichier");
    setFixedSize(405, 472);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
    text.clear();
}

Edit::~Edit()
{
    delete ui;
}

void        Edit::on_Cancel_clicked()
{
    if (text.isEmpty() == false)
    {
        QMessageBox::StandardButton answer;
        answer = QMessageBox::question(this, "Créer un fichier", "Voulez vous sauvegarder votre fichier avant de quitter ?", QMessageBox::Save | QMessageBox::Ignore | QMessageBox::Cancel);
        if (answer == QMessageBox::Ignore)
        {
            text.clear();
            ui->EditText->clear();
            close();
        }
        else if (answer == QMessageBox::Save)
            on_Save_clicked();
    }
    else
        close();
}

void        Edit::on_Save_clicked()
{
    std::string     name = "discriminator_";
    int             nb = 1;
    bool            exist = true;

    while (exist)
    {
        std::ifstream   tryIt(name + intToString(nb));
        if (tryIt)
        {
            tryIt.close();
            nb++;
        }
        else
            exist = false;
    }
    name += intToString(nb) + ".dcm";
    std::ofstream   file(name, std::ios::out | std::ios::trunc);

    if (file)
    {
        std::string textFile;
        textFile = QStringToString(text);
        file << textFile;
        file.close();
    }
    else
        QMessageBox::warning(this, "Erreur", "Le fichier n'a pas été créé");
    text.clear();
    ui->EditText->clear();
    close();
}

void        Edit::on_EditText_textChanged()
{
    text = ui->EditText->toPlainText();
}

void        Edit::on_Reset_clicked()
{
    text.clear();
}

std::string Edit::QStringToString(QString textChange)
{
    std::ostringstream  oss;

    oss << textChange.toStdString();
    return oss.str();
}

std::string Edit::intToString(int nb)
{
    std::ostringstream  oss;

    oss << nb;
    return oss.str();
}

void Edit::on_Save_on_clicked()
{
    QString name = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Fichier Discriminator (*.dcm)");
    if (name.isEmpty())
        return ;
    std::ofstream   file(QStringToString(name), std::ios::out | std::ios::trunc);

    if (file)
    {
        std::string textFile;
        textFile = QStringToString(text);
        file << textFile;
        file.close();
    }
    else
        QMessageBox::warning(this, "Erreur", "Le fichier n'a pas été créé");
    text.clear();
    ui->EditText->clear();
    close();
}

