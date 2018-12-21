#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Image>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

osg::Node* createScene()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	{
		// vertices
		osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(4);
		(*vertices)[0] = osg::Vec3(-1.0f,  1.0f, 0.0f);
		(*vertices)[1] = osg::Vec3(-1.0f, -1.0f, 0.0f);
		(*vertices)[2] = osg::Vec3( 1.0f, -1.0f, 0.0f);
		(*vertices)[3] = osg::Vec3( 1.0f,  1.0f, 0.0f);
		geom->setVertexArray(vertices);

		// normals
		osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(1);
		(*normals)[0] = osg::Vec3(0.0f, 0.0f, 1.0f);
		geom->setNormalArray(normals, osg::Array::BIND_OVERALL);

		// colors
		osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(1);
		(*colors)[0] = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f);
		geom->setColorArray(colors, osg::Array::BIND_OVERALL);

		// texcoords
		osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array(4);
		(*texcoords)[0] = osg::Vec2(0.0f, 1.0f);
		(*texcoords)[1] = osg::Vec2(0.0f, 0.0f);
		(*texcoords)[2] = osg::Vec2(1.0f, 0.0f);
		(*texcoords)[3] = osg::Vec2(1.0f, 1.0f);
		geom->setTexCoordArray(0, texcoords, osg::Array::BIND_PER_VERTEX);

		//
		geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
	}
	geode->addDrawable(geom);

	// texture
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Images/awesomeface.png");
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
	texture->setImage(image);
	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

	//
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	return geode.release();
}

int main()
{
	osgViewer::Viewer viewer;
	viewer.setSceneData(createScene());
	return viewer.run();
}