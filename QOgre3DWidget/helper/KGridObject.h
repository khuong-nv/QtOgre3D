/*
 * KGridObject.h
 *
 *  Created on: Mar 28, 2023
 *      Author: khuongnv/0971388386
 */

#ifndef QOGRE3DWIDGET_KGRIDOBJECT_H_
#define QOGRE3DWIDGET_KGRIDOBJECT_H_
#include <OgreCommon.h>
#include "KBaseObject.h"
namespace KEngine
{

class KGridObject : public KBaseObject
{
public:
	KGridObject(Ogre::SceneManager* sceneManager,
			Ogre::ColourValue colorGrid,
			Ogre::ColourValue colorXAxis,
			Ogre::ColourValue colorYAxis,
			int numAxisX, int numAxisY,
			int stepX, int stepY,
			Ogre::SceneNode* parentNode = nullptr);
	virtual ~KGridObject();
protected:
	static void create(Ogre::ManualObject* object, Ogre::ColourValue colorGrid,
			Ogre::ColourValue colorXAxis,
			Ogre::ColourValue colorYAxis,
			int numAxisX, int numAxisY,
			int stepX, int stepY);

protected:
	Ogre::ManualObject* m_manualObject;
};

} /* namespace KEngine */

#endif /* QOGRE3DWIDGET_KGRIDOBJECT_H_ */
