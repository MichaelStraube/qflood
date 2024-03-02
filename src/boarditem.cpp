#include "boarditem.h"
#include <QBrush>

void BoardItem::setColor(QColor color)
{
	this->color = color;
	this->setBrush(QBrush(color));
}

QColor BoardItem::getColor()
{
	return this->color;
}

void BoardItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	Q_UNUSED(event)
	emit clicked(this->color);
}
