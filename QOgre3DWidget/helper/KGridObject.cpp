/*
 * KGridObject.cpp
 *
 *  Created on: Mar 28, 2023
 *      Author: khuongnv/0971388386
 */

#include "KGridObject.h"
namespace KEngine
{

KGridObject::KGridObject(Ogre::SceneManager* sceneManager,
		Ogre::ColourValue colorGrid,
		Ogre::ColourValue colorXAxis,
		Ogre::ColourValue colorYAxis,
		int numAxisX, int numAxisY,
		int stepX, int stepY,
		Ogre::SceneNode* parentNode)
: KBaseObject(sceneManager, parentNode)
{
	m_manualObject = new Ogre::ManualObject(generateShapeName("Grid"));
	this->create(m_manualObject, colorGrid, colorXAxis, colorYAxis, numAxisX, numAxisY, stepX, stepY);
	m_sceneNode->attachObject(m_manualObject);
}

KGridObject::~KGridObject()
{
	m_sceneManager->destroyManualObject(m_manualObject);
}

void KGridObject::create(Ogre::ManualObject* object, Ogre::ColourValue colorGrid,
		Ogre::ColourValue colorXAxis,
		Ogre::ColourValue colorYAxis,
		int numAxisX, int numAxisY, int stepX, int stepY)
{
	object->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);

	for (int x = -numAxisX; x <= numAxisX; x += 1)
	{
		Ogre::ColourValue finalColor = colorGrid;
	    if(x == 0)
	    {
	    	finalColor = colorYAxis;
	    }

	    object->position(x * stepX, - stepY * numAxisY, 0);  object->colour(finalColor);
	    object->position(x * stepX, stepY * numAxisY, 0);  object->colour(finalColor);
	}
	for (int y = -numAxisY; y <= numAxisY; y += 1)
	{
		Ogre::ColourValue finalColor = colorGrid;
	    if(y == 0)
	    {
	    	finalColor = colorXAxis;
	    }
	    object->position(- stepX * numAxisX, y * stepY, 0);  object->colour(finalColor);
	    object->position(stepX * numAxisX, y * stepY, 0);  object->colour(finalColor);
	}
	object->end();
}

} /* namespace KEngine */
