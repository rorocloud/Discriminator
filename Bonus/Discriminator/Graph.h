#ifndef                                     GRAPH_H
# define                                    GRAPH_H

# include                                   <QApplication>
# include                                   <QObject>
# include                                   <QWidget>
# include                                   <QtWidgets>
# include                                   <QMenu>
# include                                   <QAction>
# include                                   <QMainWindow>
# include                                   <QSystemTrayIcon>
# include                                   <QLocale>
# include                                   <QTranslator>
# include                                   <QLibraryInfo>
# include                                   <iostream>
# include                                   <string>
# include                                   <list>

namespace                                   Ui
{
    class                                   Graph;
}

# define        BLACK           Qt::black
# define        BLUE            Qt::blue
# define        DARK_BLUE       Qt::darkBlue
# define        GREEN           Qt::green
# define        DARK_GREEN      Qt::darkGreen
# define        GRAY            Qt::gray
# define        DARK_GRAY       Qt::darkGray
# define        LIGHT_GRAY      Qt::lightGray
# define        CYAN            Qt::cyan
# define        DARK_CYAN       Qt::darkCyan
# define        MAGENTA         Qt::magenta
# define        DARK_MAGENTA    Qt::darkMagenta
# define        RED             Qt::red
# define        DARK_RED        Qt::darkRed
# define        YELLOW          Qt::yellow
# define        DARK_YELLOW     Qt::darkYellow


class                                       Graph : public QWidget
{
    Q_OBJECT

    enum                                    formatPoint
    {
        UNKNOWN,
        RECT,
        ELLIPSE
    };

    struct                                  listPoint
    {
        float                               x;
        float                               y;
        QColor                              myColorPoint;
        enum formatPoint                    myFormatPoint;
    };

public:
    explicit                                Graph(QWidget *parent = 0);
                                            ~Graph();

    void                                    putInMyList(std::string);
    void                                    addCloudGraph();
    float                                   findMinX();
    float                                   findMinY();
    float                                   findMaxX();
    float                                   findMaxY();

private:
    Ui::Graph                               *ui;
    QGraphicsScene                          *scene;
    std::list<struct listPoint>             myList;
};

#endif // GRAPH_H
