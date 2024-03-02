#ifndef BOARDITEM_H
#define BOARDITEM_H

#include <QGraphicsRectItem>

class BoardItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	void setColor(QColor color);
	QColor getColor();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
	QColor color;

signals:
	void clicked(QColor color);

};

#endif // BOARDITEM_H
