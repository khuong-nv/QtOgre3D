
/*
 * KBaseObject.cpp
 *
 *  Created on: Apr 1, 2023
 *      Author: khuongnv/0971388386
 */
#include "KBaseObject.h"
namespace KEngine
{
KEngine::KBaseObject::KBaseObject(Ogre::SceneManager *sceneManager,
		Ogre::SceneNode *parentNode)
: m_sceneManager(sceneManager)
{
	if (parentNode == nullptr)
	{
		parentNode = m_sceneManager->getRootSceneNode();
	}
	m_sceneNode = parentNode->createChildSceneNode();
}

KBaseObject::~KBaseObject()
{
	m_sceneManager->destroySceneNode(m_sceneNode);
}

void KBaseObject::setPosition(const Ogre::Vector3 &position)
{
	m_sceneNode->setPosition(position);
}

const Ogre::Vector3& KBaseObject::getPosition()
{
	return m_sceneNode->getPosition();
}

void KBaseObject::setOrientation(const Ogre::Quaternion &orientation)
{
	m_sceneNode->setOrientation(orientation);
}

const Ogre::Quaternion& KBaseObject::getOrientation()
{
	return m_sceneNode->getOrientation();
}

void KBaseObject::setScale(const Ogre::Vector3 &scale)
{
	m_sceneNode->setScale(scale);
}

void KBaseObject::setVisible(bool isVisible)
{
	m_sceneNode->setVisible(isVisible);
}

void KBaseObject::setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z)
{
	m_sceneNode->setPosition(Ogre::Vector3(x, y, z));
}

void KBaseObject::rotate(const Ogre::Vector3 &axis, const Ogre::Radian &angle,
		Ogre::Node::TransformSpace relativeTo)
{
	m_sceneNode->rotate(axis, angle, relativeTo);
}

}




