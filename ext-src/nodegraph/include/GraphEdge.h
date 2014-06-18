/*
 Copyright (C) 2014 Callum James
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CONNECTINGEDGE_H__
#define __CONNECTINGEDGE_H__

#include <QGraphicsItem>
#include "GraphNode.h"

class GraphEdge : public QGraphicsItem
{
public:
    GraphEdge();
    GraphEdge(NodeSocket *_source, NodeSocket *_destination);

    ~GraphEdge();

    void init();

    void updateEdge();

    void setSourceDestinationSockets(NodeSocket *_source, NodeSocket *_destination);

    void setSourceSocket(NodeSocket *_source);
    void setDestinationSocket(NodeSocket *_destination);

    void setArrowSize(float _size);

    GraphNode *sourceNode() {return m_sourceNode;}
    NodeSocket *sourceSocket() {return m_sourceSocket;}
    GraphNode *destinationNode() {return m_destinationNode;}
    NodeSocket *destinationSocket() {return m_destinationSocket;}

    float arrowSize() {return m_arrowSize;}

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    GraphNode *m_sourceNode;
    GraphNode *m_destinationNode;
    NodeSocket *m_sourceSocket;
    NodeSocket *m_destinationSocket;

    QPointF m_sourcePoint; // these are both stored within the ndoes but as item space
    QPointF m_destinationPoint; // these two attributes are the conversion from this

    float m_arrowSize; // will be defaulted to 10

};

#endif /* __CONNECTINGEDGE_H__ */
