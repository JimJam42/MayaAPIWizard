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

#ifndef __GRAPHNODE_H__
#define __GRAPHNODE_H__

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsTextItem>

#include "NodeSocket.h"

class GraphEdge;
class GraphScene;

enum SOCKET_CLEARENCE
{
    IN_OUT = 0,
    IN,
    OUT,
    NONE
};

enum VALUE_TYPE
{
    VT_NOTYPE = 0,
    VT_OBJECT,
    VT_ARGUMENTS,
    VT_MEMBER,
    VT_END
};

enum NODE_TYPE
{ // keeping it to just 3 types at the moment for testing and development
    // more can then be added later
    NT_NOTYPE = 0,
    NT_STRING,
    NT_INT,
    NT_FLOAT,
    NT_DOUBLE,
    NT_BOOLEAN,
    NT_CHAR,
    NT_VECTOR,
    NT_MATRIX,
    NT_OBJ_ANGLE,
    NT_OBJ_DISTANCE,
    NT_OBJ_TIME,
    NT_OBJ_LAST,
    NT_OBJ_COMPOUND,
    NT_OBJ_ENUM,
    NT_OBJ_GENERIC,
    NT_OBJ_MATRIX,
    NT_OBJ_MESSAGE,
    NT_OBJ_BOOLEAN,
    NT_OBJ_ONEBYTE,
    NT_OBJ_ONECHAR,
    NT_OBJ_ONESHORT,
    NT_OBJ_TWOSHORT,
    NT_OBJ_THREESHORT,
    NT_OBJ_ONELONG,
    NT_OBJ_ONEINT,
    NT_OBJ_TWOLONG,
    NT_OBJ_TWOINT,
    NT_OBJ_THREELONG,
    NT_OBJ_THREEINT,
    NT_OBJ_ONEFLOAT,
    NT_OBJ_TWOFLOAT,
    NT_OBJ_THREEFLOAT,
    NT_OBJ_ONEDOUBLE,
    NT_OBJ_TWODOUBLE,
    NT_OBJ_THREEDOUBLE,
    NT_OBJ_FOURDOUBLE,
    NT_OBJ_ADDRESS,
    NT_OBJ_NUM_LAST,
    NT_ENDNODE
};

class GraphNode : public QGraphicsItem
{
public:
    GraphNode(VALUE_TYPE _vType=VT_NOTYPE, NODE_TYPE _type=NT_NOTYPE, QGraphicsItem *_parent=0);
    GraphNode(QPointF _point=QPointF(0.0,0.0), VALUE_TYPE _vType=VT_NOTYPE, NODE_TYPE _type=NT_NOTYPE, QGraphicsItem *_parent=0);
    GraphNode(qreal _x, qreal _y, VALUE_TYPE _vType=VT_NOTYPE, NODE_TYPE _type=NT_NOTYPE, QGraphicsItem *_parent=0);
    ~GraphNode();

    void setSelectedNode(bool _selected) {prepareGeometryChange(); m_selected = _selected;}

    void updateSockets();

    void setParentScene(GraphScene *_scene);

    void addSocket(SOCKET_TYPE _type);

    std::string name() {return m_name;}
    std::string shortName() {return m_shortName;}

    NODE_TYPE nodeType() {return m_type;}
    VALUE_TYPE valueType() {return m_valueType;}

    bool nodeOverPoint(QPointF _point);
    bool nodeOverPoint(qreal _x, qreal _y);

    NodeSocket *cursorOverSocket(QPointF _point, SOCKET_TYPE _type);
    NodeSocket *cursorOverSocket(qreal _x, qreal _y, SOCKET_TYPE _type);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setWidth(qreal _w);
    void setHeight(qreal _h);

    void setName(std::string _name);
    void setShortName(std::string _name);

    void setDeletable(bool _del) {m_deletable = _del;}
    void setEditable(bool _edi) {m_editable = _edi;}
    void setEndNode(bool _end) {m_endNode = _end;}

    void setNodeTitle(std::string _title);// this will only be possible if the type is EndNode

    void setSocketClearence(SOCKET_CLEARENCE _clearence) {m_socketClearence = _clearence;}

    int zDepth() {return m_zDepth;}

    qreal getWidth() {return m_width;}
    qreal getHeight() {return m_height;}

    void setPoint(QPointF _point);
    QPointF getPoint() {return m_nodePoint;}

    QPointF getOffsetToCursor() {return m_offsetToCursor;}

    SOCKET_CLEARENCE getSocketClearence() {return m_socketClearence;}

    bool getIfSelected() {return m_selected;}

    GraphScene* parentScene() {return m_parentScene;}

    void mouseMoveEvent(QGraphicsSceneMouseEvent *_event);
    void mousePressEvent(QGraphicsSceneMouseEvent *_event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *_event);

    int numOutboundSockets() {return m_numOutboundSockets;}
    int numInboundSockets() {return m_numInboundSockets;}

    bool deletable() {return m_deletable;}
    bool editable() {return m_editable;}
    bool endNode() {return m_endNode;}

    void printNodeInfo();
    std::string getNodeInfo();

    bool gatherInboundSocketInfo(std::vector<std::string> *_vec);

    QPointF centre();

private:
    SOCKET_CLEARENCE m_socketClearence;
    std::string m_name;
    std::string m_shortName;

    qreal m_width;
    qreal m_height;

    QColor m_highlightEdgeColour;
    int m_highlightEdgeThickness;
    bool m_selected;

    QGraphicsTextItem *m_nodeTypeText;
    QGraphicsTextItem *m_nodeName;
    QGraphicsTextItem *m_nodeShortName;

    GraphScene *m_parentScene; // the scene within which the node exists - used for adding of edges

    std::vector<NodeSocket*> *m_outboundSockets;
    std::vector<NodeSocket*> *m_inboundSockets;
    int m_numOutboundSockets;
    int m_numInboundSockets;

    QPointF m_nodePoint;
    QPointF m_offsetToCursor;// used to determine the offset to where the user has clicked
    int m_zDepth; // used when two ndoes overlap each other, this value will be assigned
    // when it is not equal to -1, it means there are some nodes overlapping and each node will have its own value
    // when this occurs, when selecting the node, the node at that point with the highest zDepth will be selected

    bool m_move;

    bool m_deletable;
    bool m_editable;

    bool m_endNode;

    VALUE_TYPE m_valueType;
    NODE_TYPE m_type;

    void addInboundSocket();
    void addOutboundSocket();

    void calculateSocketPositions();
    void calculateInboundSocketsPositions();
    void calculateOutboundSocketsPositions();

    void init(VALUE_TYPE _vType, NODE_TYPE _type=NT_NOTYPE, QPointF _point=QPointF(0.0,0.0));
};

#endif /* __GRAPHNODE_H__ */
