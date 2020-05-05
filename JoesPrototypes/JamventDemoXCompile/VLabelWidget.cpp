#include <QtCore/QDebug>

#include "VLabelWidget.h"


VLabelWidget::VLabelWidget(const QRect& rect, QWidget* parent)
    : QLabel(parent)
{
    // set the geometry
    setGeometry(rect);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    qDebug() << "VLabelWidget(). rect = " << rect;
}

void VLabelWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.setPen(QPen(Qt::black, 2));

    //qDebug() << "width =" << width() << "height =" << height() << ", text =" << text();

    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);

    qDebug() << "textRect = " << textRect;
    qDebug() << "rect() = " << rect();

    painter.translate(0, height());
    painter.rotate(270.0);

    painter.drawText(textRect, text(), alignment());

}

QSize VLabelWidget::sizeHint() const
{
    QSize s = QLabel::sizeHint();
    return QSize(s.height(), s.width());
}

QSize VLabelWidget::minimumSizeHint() const
{
    QSize s = QLabel::minimumSizeHint();
    return QSize(s.height(), s.width());
}