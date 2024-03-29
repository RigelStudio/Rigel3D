#include "TextureRolling.h"

#include <osg/Program>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>

#include "RigelCore/FileUtils.h"
#include "RigelCore/Core.h"
#include "RigelModel/GeometryLine.h"
#include "RigelModel/GeometryPipe.h"

TextureRolling::TextureRolling()
{
	m_pStrip = nullptr;
	m_pStateSet = getOrCreateStateSet();
	m_pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON |
		osg::StateAttribute::OVERRIDE);
	createStrip();
}


TextureRolling::~TextureRolling()
{
}

void TextureRolling::createStrip()
{
	auto mtNode = new osg::MatrixTransform;;
	if (m_pStrip == nullptr)
	{
		auto _array = new osg::Vec3Array;
 		_array->push_back(osg::Vec3(0, 0, 0) );
 		_array->push_back(osg::Vec3(50, 0, 0));
  		_array->push_back(osg::Vec3(50, 0, 50));
   	//	_array->push_back(osg::Vec3(50, 50, 50));
   // 	_array->push_back(osg::Vec3(50, 50, 0));
   // 	_array->push_back(osg::Vec3(50, 10, 0));
   //		_array->push_back(osg::Vec3(20, 15, 30));
   //		_array->push_back(osg::Vec3(35, 30, 30));
// 		_array->push_back(osg::Vec3(35, 30, 30));
// 		_array->push_back(osg::Vec3(35, 30, 30));
// 		_array->push_back(osg::Vec3(50, 10, 0));
// 		_array->push_back(osg::Vec3(50, 50, 50));
// 		_array->push_back(osg::Vec3(50, 50, 0));

 		//m_pStrip = new GeometryStrip(_array);
 		//m_pStrip->setTexture(FileUtils::ins()->getPath(std::string("Data/Images/arraw_strip.png")));
 		//mtNode->addChild(m_pStrip);
 		//mtNode->setMatrix(osg::Matrix::rotate(osg::PI_2, osg::X_AXIS));

		auto pipe = new GeometryPipe(_array);
		pipe->setColor(osg::Vec4(1, 0, 0, 1));
		//pipe->addTexture(0, FileUtils::ins()->getPath(std::string("Data/Images/arraw_strip.png")));
		pipe->addTexture(1, FileUtils::ins()->getPath(std::string("Data/Images/water.png")));
		addChild(pipe);
	}
	//addChild(m_pStrip);

	createShader();
}

void TextureRolling::createShader()

{
	osg::Program* profram = new osg::Program;
	osg::Shader* vertShader = osgDB::readShaderFile(osg::Shader::VERTEX, 
		FileUtils::ins()->getPath(std::string("Data/Shaders/texRolling.vert")));

	osg::Shader* fragShader = osgDB::readShaderFile(osg::Shader::FRAGMENT, 
		FileUtils::ins()->getPath(std::string("Data/Shaders/texRolling.frag")));

	profram->addShader(vertShader);
	profram->addShader(fragShader);

	m_pStateSet->addUniform(new osg::Uniform("sampler", 0));
	m_pStateSet->addUniform(new osg::Uniform("sampler", 1));

	m_pStateSet->setAttributeAndModes(profram);
}
