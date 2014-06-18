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

#include "NodePluginSelectionPage.h"
#include "ui_NodePluginSelectionPage.h"

#include "Utilities.h"

#include "MainWindow.h"

NodePluginSelectionPage::NodePluginSelectionPage(int _id, std::string _name, PLUGIN_TYPE _type, MainWindow* _parentWindow, QWidget *_parent) :
    WizardPage(_name, _type, _id, _parent, _parentWindow), m_ui(new Ui::NodePluginSelectionPage)
{
    m_ui->setupUi(this);

    connectAndInit();
}

NodePluginSelectionPage::~NodePluginSelectionPage()
{
    delete m_ui;
}

std::string NodePluginSelectionPage::getAttributes()
{
    std::string returnString = "";
    returnString += std::string(m_nodePluginName + ATTRIB_DELIM);
    returnString += std::string(Utilities::nodePluginTypeToName(m_chosenType) + ATTRIB_DELIM);
    returnString += std::string(m_inheritsFrom + ATTRIB_DELIM);
    returnString += std::string(m_mayaNodeType + ATTRIB_DELIM);
    returnString += std::string(Utilities::boolToString(m_addObjs) + ATTRIB_DELIM);
    return returnString;
}

void NodePluginSelectionPage::connectAndInit()
{
    m_supportedNodePluginTypes = new std::vector<ND_TYPE>;
    m_supportedNodePluginTypes->clear();
    m_numSuportedNodeTypes = 0;

    m_nodePluginName = "";
    m_inheritsFrom = "";
    m_mayaNodeType = "";
    m_addObjs = false;

    setDefaultSupportedNodeTypes();
    populateNodeTypeSelection();
}

WizardPage* NodePluginSelectionPage::nextPage(int _id)
{
    if (m_addObjs)
    {
        return new NodeGraphPage(_id,"AddObjs",pluginType(),m_chosenType,getParentMainWindow());
    }
    return new LinkLibrariesPage(_id,"LinkLibraries",pluginType(),m_chosenType,getParentMainWindow());
}

WizardError::WIZARD_ERROR_CODE NodePluginSelectionPage::gatherInformation()
{
    // check to make sure that the class name has not been left empty
    QString className = m_ui->line_className->text();

    if (className.isEmpty())
    {
        return WizardError::ERR_NO_NAME_SPECIFIED;
    }

    // check to also make sure that the class name does not contain any spaces
    if (className.contains(" "))
    {
        return WizardError::ERR_INVALID_NAME;
    }

    // if there is a name then we can continue
    m_nodePluginName = className.toStdString();
    m_chosenType = m_supportedNodePluginTypes->at(m_ui->cmbo_nodeType->currentIndex());
    m_inheritsFrom = nodePluginTypeInheritsFrom(m_chosenType);
    m_mayaNodeType = nodePluginTypeToMPxNodeType(m_chosenType);
    m_addObjs = m_ui->cbx_addObjs->isChecked();

    return WizardError::NO_ERROR;
}

void NodePluginSelectionPage::addSupportedNodeType(ND_TYPE _type)
{
    bool alreadySupported = false;
    int count = 0;
    // check to make sure it hasnt already been added first
    while (!alreadySupported && count < m_numSuportedNodeTypes)
    {
        if (m_supportedNodePluginTypes->at(count) == _type)
        {
            alreadySupported = true;
        }
        count++;
    }

    if (!alreadySupported)
    {
        m_supportedNodePluginTypes->push_back(_type);
    }

    m_numSuportedNodeTypes = m_supportedNodePluginTypes->size();
}

void NodePluginSelectionPage::setDefaultSupportedNodeTypes()
{
    addSupportedNodeType(ND_BASIC_NODE);
    addSupportedNodeType(ND_LOCATOR_NODE);
    addSupportedNodeType(ND_DEFORMER_NODE);
    addSupportedNodeType(ND_MANIP_CONTAIN);
    addSupportedNodeType(ND_IK_SOLVER);
    addSupportedNodeType(ND_HW_SHADER_NODE);
    addSupportedNodeType(ND_TRANSFORM);
    addSupportedNodeType(ND_OBJECT);
    addSupportedNodeType(ND_IMAGE_PLANE);
    addSupportedNodeType(ND_PARTICLE_ATTRIB_MAPPER);
    addSupportedNodeType(ND_CONSTRAINT);
    addSupportedNodeType(ND_MANIP);
}

void NodePluginSelectionPage::populateNodeTypeSelection()
{
    for (int i =0; i < m_numSuportedNodeTypes; i++)
    {
        m_ui->cmbo_nodeType->addItem(Utilities::nodePluginTypeToName(m_supportedNodePluginTypes->at(i)).c_str());
    }
}

std::string NodePluginSelectionPage::nodePluginTypeInheritsFrom(ND_TYPE _type)
{
    switch(_type)
    {
        case(ND_BASIC_NODE): return std::string("MPxNode"); break;
        case(ND_LOCATOR_NODE): return std::string("MPxLocatorNode"); break;
        case(ND_DEFORMER_NODE): return std::string("MPxDeformerNode"); break;
        case(ND_MANIP_CONTAIN): return std::string("MPxManipContainer"); break;
        case(ND_IK_SOLVER): return std::string("MPxIkSolverNode"); break;
        case(ND_TRANSFORM): return std::string("MPxTransform"); break;
        case(ND_HW_SHADER_NODE): return std::string("MPxHwShaderNode"); break;
        case(ND_OBJECT): return std::string("MPxObjectSet"); break;
        case(ND_IMAGE_PLANE): return std::string("MPxImagePlane"); break;
        case(ND_PARTICLE_ATTRIB_MAPPER): return std::string("MPxParticleAttributeMapperNode"); break;
        case(ND_CONSTRAINT): return std::string("MPxConstraint"); break;
        case(ND_MANIP): return std::string("MPxManipulatorNode"); break;
        default: return std::string("__no_type__"); break;
    }
}

std::string NodePluginSelectionPage::nodePluginTypeToMPxNodeType(ND_TYPE _type)
{
    switch(_type)
    {
        case(ND_BASIC_NODE): return std::string("MPxNode::kDependNode"); break;
        case(ND_LOCATOR_NODE): return std::string("MPxNode::kLocatorNode"); break;
        case(ND_DEFORMER_NODE): return std::string("MPxNode::kDeformerNode"); break;
        case(ND_MANIP_CONTAIN): return std::string("MPxNode::kManipContainer"); break;
        case(ND_IK_SOLVER): return std::string(" MPxNode::kIkSolverNode"); break;
        case(ND_TRANSFORM): return std::string("MPxNode::kTransformNode"); break;
        case(ND_HW_SHADER_NODE): return std::string("MPxNode::kHwShaderNode"); break;
        case(ND_OBJECT): return std::string("MPxNode::kObjectSet"); break;
        case(ND_IMAGE_PLANE): return std::string("MPxNode::kImagePlaneNode"); break;
        case(ND_PARTICLE_ATTRIB_MAPPER): return std::string("MPxNode::kParticleAttributeMapperNode"); break;
        case(ND_CONSTRAINT): return std::string("MPxNode::kConstraintNode"); break;
        case(ND_MANIP): return std::string("MPxNode::kManipulatorNode"); break;
        default: return std::string("__no_type__"); break;
    }
}
