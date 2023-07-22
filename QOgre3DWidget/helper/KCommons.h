/*
 * KCommons.h
 *
 *  Created on: Apr 1, 2023
 *      Author: khuongnv/0971388386
 */

#ifndef QOGRE3DWIDGET_HELPERS_KCOMMONS_H_
#define QOGRE3DWIDGET_HELPERS_KCOMMONS_H_
#include <sstream>
#include <string>
#include <OgreSceneManager.h>
#include <OgreManualObject.h>
#include <iostream>
namespace KEngine
{
inline
std::string generateShapeName(const std::string& objectName)
{
	static uint32_t count = 0;
	std::stringstream ss;
	ss << objectName << count++;
	return ss.str();
}
}



#endif /* QOGRE3DWIDGET_HELPERS_KCOMMONS_H_ */
