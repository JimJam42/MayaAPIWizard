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

#ifndef __NODESOCKET_H__
#define __NODESOCKET_H__

#include <QGraphicsItem>

enum SOCKET_TYPE
{
    SK_INBOUND,
    SK_OUTBOUND
};

class GraphNode;
class GraphEdge;
class GraphScene;

class NodeSocket : public QGraphicsItem
{
public:
    NodeSocket(SOCKET_TYPE _type);
    NodeSocket( SOCKET_TYPE _type, qreal _x, qreal _y, float _w = 10.0f, float _h = 10.0f);
    NodeSocket(SOCKET_TYPE _type, QPointF _point, float _w = 10.0f, float _h = 10.0f);
    ~NodeSocket();

    void init();

    void addEdge(NodeSocket *_dest);
    void addEdgeReference(GraphEdge *_edge);

    void updateEdges();

    bool removeEdge(GraphEdge *_edge);
    bool removeEdgeReference(GraphEdge *_edge);
    void removeAllEdges();

    bool socketOverPoint(QPointF _point);
    bool socketOverPoint(qreal _x, qreal _y);

    void setPosition(QPointF _position);
    void setPosition(qreal _x, qreal _y);

    void setColour(QColor _colour);
    void setColour(int _r, int _g, int _b, int _a=255);

    void setWidth(float _w);
    void setHeight(float _h);

    void setParentNode(GraphNode *_parent);
    void setParentScene(GraphScene *_scene);

    QPointF position() {return m_position;}
    QPointF centre();
    QColor colour() {return m_colour;}

    float width() {return m_width;}
    float height() {return m_height;}

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    GraphNode *getParentNode() {return m_parentNode;}
    GraphScene *getParentScene() {return m_parentScene;}

    void printSocketInfo();

    bool getConnectedNodeDetails(std::vector<std::string> *_vec);

private:
    GraphNode *m_parentNode;
    GraphScene *m_parentScene;
    std::vector<GraphEdge*> *m_edges;
    int m_numEdges;

    SOCKET_TYPE m_socketType;

    QPointF m_position;
    QColor m_colour;

    float m_width;
    float m_height;

    bool findEdgeIndex(GraphEdge *_edge, int *_index);

};

#endif /* __NODESOCKET_H__ */
