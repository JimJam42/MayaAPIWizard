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

#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include "GraphNode.h"
#include "GraphEdge.h"
#include "NodeEdit.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QLayout>

class GraphScene : public QGraphicsView
{
    Q_OBJECT
    
public:
    explicit GraphScene(QWidget *parent = 0);
    ~GraphScene();

    // run through the nodes in the scene and build up a return string to pass back
    // return string is being used here as this is how the wizard reads data
    // it is not universal and would need to be changed for more generic use
    bool collectInformation(std::string *_string); // this function will only work if an end node exists

    // this is simply a test debug function to print out information on each node
    void printAllNodes();

    void init();

    void resize(float _x, float _y, float _w, float _h);

    void showView();

    void addEndNode(std::string _title);

    bool nodeAtPoint(QPoint _point);
    bool nodeAtPoint(qreal _x, qreal _y);

    void keyPressEvent(QKeyEvent *_event);
    void keyReleaseEvent(QKeyEvent *_event);
    void mouseMoveEvent(QMouseEvent *_event);
    void mousePressEvent(QMouseEvent *_event);
    void mouseDoubleClickEvent(QMouseEvent *_event);
    void mouseReleaseEvent(QMouseEvent *_event);
    void wheelEvent(QWheelEvent *_event);

    void resizeEvent(QResizeEvent *event);

    void addNodeToScene(VALUE_TYPE _valueTy, NODE_TYPE _type, QPointF _point, GraphScene *_parent, int _inboundSK=1, int _outboundSK=1, bool _editable=true, bool _deletable=true);
    void addEdgeToScene(GraphEdge *_edge);
    void addSocketToScene(NodeSocket *_socket);

    void removeFromScene(QGraphicsItem *_item);

signals:
    void nodeMenuRequested(const QPoint&);

public slots:
    // I am making the zoom  and translate functions public slots in case it needs to be updated from somewhere
    // other than this class
    // these can also then easily be called from the mouse wheel event
    void zoomIn();
    void zoomOut();
    void navScene(qreal _x, qreal _y) {translate(_x,_y);}

private slots:
    void createObjectNode(int _type);
    void createArgumentNode(int _type);
    void createMemberNode(int _type);
    
private:
    bool m_pan;
    bool m_moveNode;
    bool m_editingNode;
    bool m_creatingEdge;
    bool m_tempEdgeVisible;
    bool m_cursorOverOutboundSocket;
    bool m_cursorOverInboundSocket;

    QGraphicsScene *m_scene;
    NodeEdit *m_nodeEdit;

    std::vector<GraphNode*> *m_nodesInScene;
    int m_numNodesInScene;

    NodeSocket *m_tempSocketForEdgeDrawing;
    GraphEdge *m_tempEdgeForEdgeDrawing;

    NodeSocket *m_activeOutboundSocket;
    NodeSocket *m_activeInboundSocket;
    GraphNode *m_activeSelectedNode; // this is the node that is currently being interacted with by the user
    // for example if the user is a moving a node, this is the node they will move
    bool m_nodeActive; // boolean flag for if a node is active or not
    bool m_nodeSelected;

    QMenu *m_nodeSelectMenu;
    QMenu* m_objectMenus;
    std::vector<QAction*> m_objectMenuActions; // vector to hold all possible actions from the object menu
    QMenu* m_argumentMenus;
    std::vector<QAction*> m_argumentMenuActions; // vector to hold all possible actions from the argument menu
    QMenu* m_memberMenus;
    std::vector<QAction*> m_memberMenuActions; // vector to hold all possible actions from the member menu

    // need a global point to be able to create a ndoe at this point
    QPointF m_createNodeAt;

    int m_pastX;
    int m_pastY;

    bool removeNode(GraphNode *_nodeToRemove);
    void removeAllNodes();
    void activeNodeSelected(bool _select);

    bool findNodeIndex(GraphNode *_node, int *_index);

    void populateNodeSelectionMenu();

    bool m_endNodeInScene; // can only have one end node

private slots:
    void showNodeMenu(const QPoint&_pos);
};

#endif // GRAPHSCENE_H
