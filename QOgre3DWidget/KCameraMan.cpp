#include "KCameraMan.h"
#include "OgreSceneManager.h"
#include <QtCore/qnamespace.h>
#include <iostream>
using namespace std;
namespace KEngine {

using namespace OgreBites;

KCameraMan::KCameraMan(Ogre::SceneNode* camNode, Ogre::Camera* cam, Ogre::Light* light)
    : mYawSpace(Ogre::Node::TS_PARENT)
    , mCameraNode(0)
    , mTarget(0)
    , mOrbiting(false)
    , mMoving(false)
    , mOffset(0, 0, 0)
	, m_camera(cam)
	, m_light(light)
{

    setCamera(camNode);
    setup();
}

void KCameraMan::setCamera(Ogre::SceneNode *cam)
{
    mCameraNode = cam;
}

void KCameraMan::setTarget(Ogre::SceneNode *target)
{
    if (target == mTarget)
        return;

    mTarget = target;
}

void KCameraMan::setYawPitchDist(const Ogre::Radian&  yaw, const Ogre::Radian& pitch, Ogre::Real dist)
{
    OgreAssert(mTarget, "no target set");

    mOffset = Ogre::Vector3::ZERO;
    mCameraNode->setPosition(mTarget->_getDerivedPosition());
    mCameraNode->setOrientation(mTarget->_getDerivedOrientation());
    mCameraNode->yaw(yaw);
    mCameraNode->pitch(-pitch);
    mCameraNode->translate(Ogre::Vector3(0, 0, dist), Ogre::Node::TS_LOCAL);
}

void KCameraMan::setup()
{
	setTarget(mTarget ? mTarget : mCameraNode->getCreator()->getRootSceneNode());
	// fix the yaw axis if requested
	mCameraNode->setFixedYawAxis(mYawSpace == Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);

	// try to replicate the camera configuration
	Ogre::Real dist = getDistToTarget();
	const Ogre::Quaternion& q = mCameraNode->getOrientation();
	setYawPitchDist(q.getYaw(), q.getPitch(), dist == 0 ? 150 : dist); // enforce some distance
	mCameraNode->setAutoTracking(false);
}

Ogre::Real KCameraMan::getDistToTarget()
{
    Ogre::Vector3 offset = mCameraNode->getPosition() - mTarget->_getDerivedPosition() - mOffset;
    return offset.length();
}

void KCameraMan::setPivotOffset(const Ogre::Vector3& pivot)
{
    Ogre::Real dist = getDistToTarget();
    mOffset = pivot;
    mCameraNode->setPosition(mTarget->_getDerivedPosition() + mOffset);
    mCameraNode->translate(Ogre::Vector3(0, 0, dist), Ogre::Node::TS_LOCAL);
}

bool KCameraMan::mouseMoved(const MouseMotionEvent &evt)
{
	Ogre::Real dist = getDistToTarget();

	if (mOrbiting)   // yaw around the target, and pitch locally
	{
		mCameraNode->setPosition(mTarget->_getDerivedPosition() + mOffset);

		mCameraNode->roll(Ogre::Degree(-evt.xrel * 0.25f), mYawSpace);
		mCameraNode->pitch(Ogre::Degree(-evt.yrel * 0.25f));

		mCameraNode->translate(Ogre::Vector3(0, 0, dist), Ogre::Node::TS_LOCAL);
		// don't let the camera go over the top or around the bottom of the target
	}
	else if (mMoving)  // move the camera along the image plane
	{
		Ogre::Vector3 delta = mCameraNode->getOrientation() * Ogre::Vector3(-evt.xrel, evt.yrel, 0);
		// the further the camera is, the faster it moves
		delta *= dist / 1000.0f;
		mOffset += delta;
		mCameraNode->translate(delta);
	}

	m_light->setDirection(m_camera->getDerivedDirection());

	return InputListener::mouseMoved(evt);
}

bool KCameraMan::mouseWheelRolled(const MouseWheelEvent &evt) {
    if (evt.y != 0)
    {
        Ogre::Real dist = (mCameraNode->getPosition() - mTarget->_getDerivedPosition()).length();
        mCameraNode->translate(Ogre::Vector3(0, 0, -evt.y * 0.08f * dist), Ogre::Node::TS_LOCAL);
    	m_light->setDirection(m_camera->getDerivedDirection());
    }

    return InputListener::mouseWheelRolled(evt);
}

bool KCameraMan::mousePressed(const MouseButtonEvent &evt)
{
	if (evt.button == BUTTON_LEFT) mOrbiting = true;
	else if (evt.button == Qt::MiddleButton) mMoving = true;
	return InputListener::mousePressed(evt);
}

bool KCameraMan::mouseReleased(const MouseButtonEvent &evt)
{
	if (evt.button == BUTTON_LEFT) mOrbiting = false;
	else if (evt.button == Qt::MiddleButton) mMoving = false;
	return InputListener::mouseReleased(evt);
}

}
