/*
 * KBaseObject.h
 *
 *  Created on: Mar 30, 2023
 *      Author: khuongnv/0971388386
 */

#ifndef QOGRE3DWIDGET_HELPERS_KBASEOBJECT_H_
#define QOGRE3DWIDGET_HELPERS_KBASEOBJECT_H_
#include "KCommons.h"

namespace KEngine
{
class KBaseObject
{
public:
	KBaseObject(Ogre::SceneManager* sceneManager,
			Ogre::SceneNode* parentNode = nullptr);
	virtual ~KBaseObject();

public:
	// Position of object
	virtual void setPosition(const Ogre::Vector3& position);
	void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);
	virtual const Ogre::Vector3& getPosition();

	// Orientation of object
	virtual void setOrientation(const Ogre::Quaternion& orientation);
	virtual const Ogre::Quaternion& getOrientation();
    void rotate(const Ogre::Vector3& axis, const Ogre::Radian& angle, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);

	// Setting display
	virtual void setScale(const Ogre::Vector3& scale);
	virtual void setColor(const Ogre::ColourValue& c) { (void) c;}
	virtual void setOffset(const Ogre::Vector3& offset) {(void)offset;}

	virtual void setVisible(bool isVisible);
	void show() {setVisible(true);}
	void hide() {setVisible(false);}
	virtual void showAABBoudingBox(bool isShow) {m_sceneNode->showBoundingBox(isShow);}
	virtual void showOBBoudingBox(bool) {};

	// Set user data
	virtual void setUserData(const Ogre::Any& data) {(void) data;};

	Ogre::SceneNode* sceneNode() {return m_sceneNode;}
	Ogre::SceneNode* parentNode() {return m_sceneNode->getParentSceneNode();}
protected:
	Ogre::SceneManager* m_sceneManager;
	Ogre::SceneNode* m_sceneNode;
};

} /* namespace KEngine */

#endif /* QOGRE3DWIDGET_HELPERS_KBASEOBJECT_H_ */
