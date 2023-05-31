#include "drawarea.h"
#include "mainwindow.h"
#include <QApplication>
#include <QPainter>
#include <QPainterPath>
#include <cmath>

DrawArea::DrawArea(QWidget *parent) :
    QWidget(parent),
    xmin(-8.),
    xmax(8.),
    ymin(-6.),
    ymax(6.),
    triangleComputed(false),
    inCenter(),
    inRadius(0.),
    nodes(),
    buttons(),
    draggingVertex(-1)
{
    drawArea = this;
    setMouseTracking(true);
}

void DrawArea::paintEvent(QPaintEvent* /* event */) {
    QPainter painter(this);
    painter.fillRect(
        QRect(0, 0, width(), height()),
        QBrush(Qt::lightGray)
    );
    drawCoordinates(&painter);
    drawNodes(&painter);
    if (triangleComputed) {
        drawTriangle(&painter);
    }
}

void DrawArea::drawCoordinates(QPainter* painter) {
    QPen grayPen(Qt::gray);
    QPen blackPen(Qt::black);

    painter->setPen(grayPen);
    // painter->drawLine(QPointF(0., 0.), QPointF(300., 300.));

    double x = round(xmin);
    while (x <= round(xmax)) {
        QPointF p0 = mapToPixels(R2Point(x, ymin));
        QPointF p1 = mapToPixels(R2Point(x, ymax));
        painter->drawLine(p0, p1);
        x += 1.;
    }

    double y = round(ymin);
    while (y <= round(ymax)) {
        QPointF p0 = mapToPixels(R2Point(xmin, y));
        QPointF p1 = mapToPixels(R2Point(xmax, y));
        painter->drawLine(p0, p1);
        y += 1.;
    }

    painter->setPen(blackPen);
    painter->drawLine(
        mapToPixels(R2Point(xmin, 0.)),
        mapToPixels(R2Point(xmax, 0.))
    );
    painter->drawLine(
        mapToPixels(R2Point(0., ymin)),
        mapToPixels(R2Point(0, ymax))
    );
}

void DrawArea::drawTriangle(QPainter* painter) {
    QPen blackPen(Qt::black, 3);
    QPen greenPen(Qt::darkGreen, 1);
    QPen bluePen(Qt::blue, 1);
    QPen redPen(Qt::red, 1);

    if (nodes.size() < 3)
        return;
    painter->setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.moveTo(
        mapToPixels(nodes[0])
    );
    path.lineTo(
        mapToPixels(nodes[1])
    );
    path.lineTo(
        mapToPixels(nodes[2])
    );
    path.closeSubpath();


    painter->setPen(blackPen);
    painter->drawPath(path);


    // Draw bisectors
    painter->setPen(greenPen);
    for (int i = 0; i < 3; ++i) {
        painter->drawLine(
            mapToPixels(nodes[i]), //начальная точка на треугольнике
            mapToPixels(bisector[i]) // конечная точка биссектрисы
        );
    }
    //Draw median
    painter->setPen(bluePen);
    for (int i = 0; i < 3; ++i) {
        painter->drawLine(
            mapToPixels(nodes[i]),
            mapToPixels(median[i])
        );
    }

    painter->setPen(redPen);
    for (int i = 0; i < 3; ++i) {
        painter->drawLine(
            mapToPixels(nodes[i]),
            mapToPixels(symedian[i])
        );
    }

    painter->setBrush(QBrush(Qt::red));
    painter->drawEllipse(mapToPixels(lemoinePoint), 4, 4);

    /*
    QPen redPen(Qt::red, 2);
    painter->setPen(redPen);
    double radiusInPixels = inRadius *
        double(width())/(xmax - xmin);
    painter->drawEllipse(
        mapToPixels(inCenter),
        radiusInPixels, radiusInPixels
    );

    QBrush redBrush(Qt::red);
    painter->setBrush(redBrush); // Qt::noBrush
    painter->drawEllipse(
        mapToPixels(inCenter),
        4, 4
    );*/
}

void DrawArea::drawNodes(QPainter* painter) {
    painter->setRenderHints(QPainter::Antialiasing);
    QPen blackPen(Qt::black, 3);
    QPen redPen(Qt::red, 3);
    QPen bluePen(Qt::blue, 3);
    QPen greenPen(Qt::darkGreen, 3);

    for (size_t i = 0; i < nodes.size(); ++i) {
        R2Point t = nodes[i];
        R2Vector dx(0.2, 0);
        R2Vector dy(0., 0.2);
        QPointF p0 = mapToPixels(t - dx);
        QPointF p1 = mapToPixels(t + dx);


        int button = buttons[i];
        if (button == Qt::LeftButton) {
            painter->setPen(blackPen);
        } else if (button == Qt::MiddleButton) {
            painter->setPen(greenPen);
        } else {
            painter->setPen(redPen);
        }
        painter->drawLine(p0, p1);

        p0 = mapToPixels(t - dy);
        p1 = mapToPixels(t + dy);
        painter->drawLine(p0, p1);
    }
}

void DrawArea::setCoordinates(double xMin, double xMax) {
    if (width() == 0 || height() == 0)
        return;
    if (xMax <= xMin)
        return;
    xmin = xMin;
    xmax = xMax;
    double aspect = double(width())/double(height());
    double ySize = (xmax - xmin)/aspect;
    ymin = (-ySize/2.);
    ymax = ySize/2.;
    update();
}

void DrawArea::resizeEvent(QResizeEvent* /* event */) {
    if (width() == 0 || height() == 0)
        return;
    setCoordinates(xmin, xmax);
}

void DrawArea::mousePressEvent(QMouseEvent* event) {
    int vIdx = findVertex(event->pos());
    if (vIdx >= 0) {
        draggingVertex = vIdx;
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
    }
}

void DrawArea::mouseMoveEvent(QMouseEvent* event) {
    QPointF mousePos = event->pos();
    if (draggingVertex >= 0) {
        nodes[draggingVertex] = mapFromPixels(mousePos);
        if (triangleComputed) {
            computeInscribedCircle();
        }
        update();
        event->accept();
        return;
    }
    int vertexIdx = findVertex(mousePos);
    if (vertexIdx < 0) {
        // cursor().setShape(Qt::ArrowCursor);
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    } else {
        // cursor().setShape(Qt::OpenHandCursor);
        QApplication::setOverrideCursor(Qt::OpenHandCursor);
    }
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event) {
    QPointF p = event->pos();
    int button = int(event->button());
    R2Point t = mapFromPixels(p);
    if (draggingVertex >= 0) {
        nodes[draggingVertex] = t;
        if (triangleComputed)
            computeInscribedCircle();
        draggingVertex = (-1);
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    } else {
        nodes.push_back(t);
        buttons.push_back(button);
    }
    update();
}

void DrawArea::clear() {
    nodes.clear();
    buttons.clear();
    triangleComputed = false;
    draggingVertex = (-1);
    update();
}

void DrawArea::computeInscribedCircle() {
    std::vector<R2Point> n = nodes;
    if (nodes.size() < 3)
        return;
    for (int i = 0; i < 3; ++i) {
        int iNext = i + 1;
        if (iNext >= 3)
            iNext = 0;
        int iPrev = i - 1;
        if (iPrev < 0)
            iPrev = 2;
        R2Vector nextEdge = nodes[iNext] - nodes[i];
        R2Vector prevEdge = nodes[iPrev] - nodes[i];
        R2Vector bisectrix = nextEdge.normalized() + prevEdge.normalized();
        bisectrix.normalize();
        intersectStraightLines(
            nodes[i], bisectrix,
            nodes[iNext], nodes[iNext] - nodes[iPrev],
            bisector[i]
        );

        median[i] = nodes[iNext] + (nodes[iPrev] - nodes[iNext])*0.5;

        R2Vector vecMedian = median[i] - nodes[i];
        R2Vector nBisec = bisectrix.normal();
        double x = vecMedian * bisectrix;
        double y = vecMedian * nBisec;
        R2Vector vecSymedian = x * bisectrix - y*nBisec;
        intersectStraightLines(
            nodes[i], vecSymedian,
            nodes[iNext], nodes[iNext] - nodes[iPrev],
            symedian[i]
        );
    }

    intersectStraightLines(
        nodes[0], symedian[0] - nodes[0],
        nodes[1], symedian[1] - nodes[1],
        lemoinePoint
    );

    intersectStraightLines(
        nodes[0], bisector[0] - nodes[0],
        nodes[1], bisector[1] - nodes[1],
        inCenter
    );
    intersectStraightLines(
        nodes[0], median[0] - nodes[0],
        nodes[1], median[1] - nodes[1],
        inCenter
    );
    inRadius = inCenter.distanceToLine(
        nodes[0], nodes[1] - nodes[0]
    );
    triangleComputed = true;
}

void DrawArea::onDraw() {
    if (nodes.size() >= 3) {
        computeInscribedCircle();
    }
    update();
}

static const double SEARCH_DIST = 0.1;

int DrawArea::findVertex(QPointF mousePos) const {
    R2Point t = mapFromPixels(mousePos);
    for (int i = 0; i < int(nodes.size()); ++i) {
        double dist = t.distance(nodes[i]);
        if (dist <= SEARCH_DIST) {
            return i;
        }
    }
    return (-1);
}
