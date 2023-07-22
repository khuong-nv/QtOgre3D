/*
 * KKCameraMan.h
 *
 *  Created on: Mar 29, 2023
 *      Author: khuongnv/0971388386
 */

#ifndef QOGRE3DWIDGET_KKCameraMan_H_
#define QOGRE3DWIDGET_KKCameraMan_H_
#include <OgreInput.h>
#include <OgreSceneNode.h>

namespace KEngine
{


/**
    Utility class for controlling the camera.
 */
class KCameraMan : public OgreBites::InputListener
{
public:


	KCameraMan(Ogre::SceneNode* camNode, Ogre::Camera* cam, Ogre::Light* light);

	/**
        Swaps the camera on our camera man for another camera.
	 */
	void setCamera(Ogre::SceneNode* cam);

	Ogre::SceneNode* getCamera()
	{
		return mCameraNode;
	}

	/**
        Sets the target we will revolve around. Only applies for orbit style.
	 */
	virtual void setTarget(Ogre::SceneNode* target);

	Ogre::SceneNode* getTarget()
	{
		return mTarget;
	}

	/**
        Sets the spatial offset from the target. Only applies for orbit style.
	 */
	void setYawPitchDist(const Ogre::Radian& yaw, const Ogre::Radian& pitch, Ogre::Real dist);

	/**
	 * fix the yaw axis to be Vector3::UNIT_Y of the parent node (tabletop mode)
	 *
	 * otherwise the yaw axis can change freely
	 */
	void setFixedYaw(bool fixed)
	{
		mYawSpace = fixed ? Ogre::Node::TS_PARENT : Ogre::Node::TS_LOCAL;
	}

	void setPivotOffset(const Ogre::Vector3& offset);

protected:
	/**
        Processes mouse movement differently for each style.
	 */
	bool mouseMoved(const OgreBites::MouseMotionEvent& evt);

	bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt);

	/**
        Processes mouse presses. Only applies for orbit style.
        Left button is for orbiting, and right button is for zooming.
	 */
	bool mousePressed(const OgreBites::MouseButtonEvent& evt);

	/**
        Processes mouse releases. Only applies for orbit style.
        Left button is for orbiting, and right button is for zooming.
	 */
	bool mouseReleased(const OgreBites::MouseButtonEvent& evt);

	void setup();
protected:
	Ogre::Real getDistToTarget();
	Ogre::Node::TransformSpace mYawSpace;
	Ogre::SceneNode* mCameraNode;
	Ogre::SceneNode* mTarget;
	Ogre::Camera* m_camera;
	Ogre::Light* m_light;
	bool mOrbiting;
	bool mMoving;
	Ogre::Vector3 mOffset;
};
} /* namespace KEngine */

#endif /* QOGRE3DWIDGET_KKCameraMan_H_ */
