#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QMainWindow>
#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <vector>
#include "R2Graph.h"

class DrawArea : public QWidget
{
    Q_OBJECT
public:
    // Mathematical coordinates
    double xmin;
    double xmax;
    double ymin;
    double ymax;

    bool triangleComputed;
    R2Point bisector[3];
    R2Point median[3];
    R2Point symedian[3];
    R2Point lemoinePoint;
    R2Point inCenter; // Center of inscribed circle
    double inRadius;  // Radius of inscribed circle

    std::vector<R2Point> nodes;
    std::vector<int> buttons;

    int draggingVertex;

    // Map mathematic coordinates to pixel coodinates
    QPointF mapToPixels(const R2Point& t) const {
        double x = width()*(t.x - xmin)/(xmax - xmin);
        double y = height()*(ymax - t.y)/(ymax - ymin);
        return QPointF(x, y);
    }

    R2Point mapFromPixels(const QPointF& p) const {
        double x = 0.;
        if (width() > 0) {
            x = xmin +
                (p.x()/double(width()))*(xmax - xmin);
        }
        double y = 0.;
        if (height() > 0) {
            y = ymax -
                (p.y()/double(height()))*(ymax - ymin);
        }
        return R2Point(x, y);
    }

    explicit DrawArea(QWidget *parent = nullptr);

    void setCoordinates(double xMin, double xMax);

    void computeInscribedCircle();
    void onDraw();
    int findVertex(QPointF mousePos) const;

    void drawCoordinates(QPainter* painter);
    void drawNodes(QPainter* painter);
    void drawTriangle(QPainter* painter);
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void clear();

signals:

public slots:
};

#endif // DRAWAREA_H
