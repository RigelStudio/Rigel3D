#ifndef TEXTUREROLLING_H
#define TEXTUREROLLING_H
#include <RigelModel/GeometryStrip.h>
#include <osg/StateSet>

class TextureRolling : public osg::Group
{
public:
	TextureRolling();
	~TextureRolling();

	void createStrip();

	void createShader();

private:
	GeometryStrip* m_pStrip;
	osg::observer_ptr<osg::StateSet> m_pStateSet;
};

#endif//TEXTUREROLLING_H