#include "Graph.h"
#include "ui_Graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph)
{
    ui->setupUi(this);
    setFixedSize(690, 690);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
}

Graph::~Graph()
{
    delete ui;
}

void        Graph::addCloudGraph()
{
    QPen    colorPen(Qt::black);

    ui->myGraphView->setFixedHeight(670);
    ui->myGraphView->setFixedWidth(670);
    scene = new QGraphicsScene(findMinX() - 10, findMinY() - 10, findMaxX() + 10, findMaxY() + 10, ui->myGraphView);
    scene->setBackgroundBrush(Qt::white);
    for (std::list<struct listPoint>::iterator it = myList.begin(); it != myList.end(); ++it)
    {
        if ((*it).myFormatPoint == RECT)
            scene->addRect((*it).x, (*it).y, 1, 1, colorPen, QBrush((*it).myColorPoint));
        else if ((*it).myFormatPoint == ELLIPSE)
            scene->addEllipse((*it).x, (*it).y, 1, 1, colorPen, QBrush((*it).myColorPoint));
    }
    ui->myGraphView->setScene(scene);
}

float           Graph::findMinX()
{
    float       nb;
    std::list<struct listPoint>::iterator first = myList.begin();

    nb = (*first).x;
    for (std::list<struct listPoint>::iterator it = myList.begin(); it != myList.end(); ++it)
    {
        if (nb > (*it).x)
             nb = (*it).x;
    }
    return (nb);
}

float       Graph::findMaxX()
{
    float   nb;
    std::list<struct listPoint>::iterator first = myList.begin();

    nb = (*first).x;
    for (std::list<struct listPoint>::iterator it = myList.begin(); it != myList.end(); ++it)
    {
        if (nb < (*it).x)
             nb = (*it).x;
    }
    return (nb);
}

float       Graph::findMinY()
{
    float   nb;
    std::list<struct listPoint>::iterator first = myList.begin();

    nb = (*first).y;
    for (std::list<struct listPoint>::iterator it = myList.begin(); it != myList.end(); ++it)
    {
        if (nb > (*it).y)
             nb = (*it).y;
    }
    return (nb);
}

float       Graph::findMaxY()
{
    float   nb;
    std::list<struct listPoint>::iterator first = myList.begin();

    nb = (*first).y;
    for (std::list<struct listPoint>::iterator it = myList.begin(); it != myList.end(); ++it)
    {
        if (nb < (*it).y)
             nb = (*it).y;
    }
    return (nb);
}

void        Graph::putInMyList(std::string textFile)
{
    std::string nbX = "";
    std::string nbY = "";
    bool        vir = false;

    for (int i = 0; textFile[i] != '\0'; i++)
    {
        if (textFile[i] == ';')
            vir = true;
        else if (!vir)
            nbX += textFile[i];
        else if (vir)
            nbY += textFile[i];
    }

    struct listPoint    elemList;

    elemList.x = std::stof(nbX);
    elemList.y = std::stof(nbY);
    elemList.myColorPoint = BLACK;
    elemList.myFormatPoint = RECT;
    myList.push_back(elemList);
}
