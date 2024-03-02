#ifndef BOARDITEM_H
#define BOARDITEM_H

#include <QGraphicsRectItem>

class BoardItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

public:
	int color;

signals:
	void clicked(int color);

};

#endif // BOARDITEM_H
