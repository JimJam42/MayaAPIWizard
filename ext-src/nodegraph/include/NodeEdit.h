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

#ifndef __NODEEDIT_H__
#define __NODEEDIT_H__

#include <QDialog>
#include <QAbstractButton>
#include <QKeyEvent>
#include "GraphNode.h"

namespace Ui
{
    class NodeEdit;
}

class NodeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit NodeEdit(QWidget *parent = 0);
    ~NodeEdit();

    void keyPressEvent(QKeyEvent *_event);

    void setNodeToEdit(GraphNode *_node);

private slots:
    void setNodeName();
    void setNodeShortName();

private:
    Ui::NodeEdit *m_ui;

    void connectAndInit();

    GraphNode *m_nodeToEdit;
};

#endif /* __NODEEDIT_H__ */
