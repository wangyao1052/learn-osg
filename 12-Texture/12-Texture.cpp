#include <osg/Texture1D>
#include <osg/Texture2D>
#include <osg/TextureCubeMap>
#include <osg/TexGen>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

void createTexture1D(osg::StateSet& ss)
{
	osg::ref_ptr<osg::Image> image = new osg::Image();
	image->setImage(256, 1, 1, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE,
		new unsigned char[4 * 256], osg::Image::USE_NEW_DELETE);
	unsigned char* ptr = image->data();
	for (unsigned int i=0; i < 256; ++i)
	{
		*ptr++ = i;
		*ptr++ = i;
		*ptr++ = 255;
		*ptr++ = 255;
	}

	osg::ref_ptr<osg::Texture1D> texture = new osg::Texture1D();
	texture->setImage(image.get());
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	ss.setTextureAttributeAndModes(0, texture);
}

void createTexture2D(osg::StateSet& ss)
{
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
	texture->setImage(osgDB::readImageFile("Images/clockface.jpg"));
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	texture->setWrap(
		osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_BORDER);
	texture->setWrap(
		osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_BORDER);
	texture->setBorderColor(osg::Vec4(1.0, 1.0, 0.0, 1.0));
	ss.setTextureAttributeAndModes(0, texture.get());
}

void createTextureCubeMap(osg::StateSet& ss)
{
	osg::ref_ptr<osg::TextureCubeMap> texture = new osg::TextureCubeMap();
	texture->setImage(osg::TextureCubeMap::POSITIVE_X,
		osgDB::readImageFile("Cubemap_snow/posx.jpg"));
	texture->setImage(osg::TextureCubeMap::NEGATIVE_X,
		osgDB::readImageFile("Cubemap_snow/negx.jpg"));
	texture->setImage(osg::TextureCubeMap::POSITIVE_Y,
		osgDB::readImageFile("Cubemap_snow/posy.jpg"));
	texture->setImage(osg::TextureCubeMap::NEGATIVE_Y,
		osgDB::readImageFile("Cubemap_snow/negy.jpg"));
	texture->setImage(osg::TextureCubeMap::POSITIVE_Z,
		osgDB::readImageFile("Cubemap_snow/posz.jpg"));
	texture->setImage(osg::TextureCubeMap::NEGATIVE_Z,
		osgDB::readImageFile("Cubemap_snow/negz.jpg"));
	texture->setWrap(
		osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
	texture->setWrap(
		osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
	texture->setWrap(
		osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	ss.setTextureAttributeAndModes(0, texture.get());
	ss.setTextureAttributeAndModes(0, new osg::TexGen());
}

int main()
{
	osg::ref_ptr<osg::Geode> quad1 = new osg::Geode();
	quad1->addDrawable(osg::createTexturedQuadGeometry(
		osg::Vec3(-3.0, 0.0, -0.5), osg::Vec3(1.0, 0.0, 0.0),
		osg::Vec3(0.0, 0.0, 1.0), 0.0, 0.0, 3.0, 1.0));
	createTexture1D(*(quad1->getOrCreateStateSet()));

	osg::ref_ptr<osg::Geode> quad2 = new osg::Geode();
	quad2->addDrawable(osg::createTexturedQuadGeometry(
		osg::Vec3(-0.5, 0.0, -0.5), osg::Vec3(1.0, 0.0, 0.0),
		osg::Vec3(0.0, 0.0, 1.0), -0.1, -0.1, 1.1, 1.1));
	createTexture2D(*(quad2->getOrCreateStateSet()));

	osg::ref_ptr<osg::Geode> box = new osg::Geode();
	box->addDrawable(new osg::ShapeDrawable(
		new osg::Box(osg::Vec3(3.0, 0.0, 0.0), 1.0, 1.0, 1.0)));
	createTextureCubeMap(*(box->getOrCreateStateSet()));

	osg::ref_ptr<osg::Group> root = new osg::Group();
	root->addChild(quad1);
	root->addChild(quad2);
	root->addChild(box);

	osgViewer::Viewer viewer;
	viewer.setSceneData(root);
	return viewer.run();
}