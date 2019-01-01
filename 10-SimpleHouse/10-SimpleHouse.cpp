#include <osg/Texture2D>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgUtil/SmoothingVisitor>
#include <osgViewer/Viewer>

osg::Drawable* createHouseWall()
{
	// house vertices
	osg::ref_ptr<osg::Vec3dArray> vertices = new osg::Vec3dArray();
	vertices->push_back(osg::Vec3d(0.0, 0.0, 4.0)); // 0
	vertices->push_back(osg::Vec3d(0.0, 0.0, 0.0)); // 1
	vertices->push_back(osg::Vec3d(6.0, 0.0, 4.0)); // 2
	vertices->push_back(osg::Vec3d(6.0, 0.0, 0.0)); // 3
	vertices->push_back(osg::Vec3d(6.0, 4.0, 4.0)); // 4
	vertices->push_back(osg::Vec3d(6.0, 4.0, 0.0)); // 5
	vertices->push_back(osg::Vec3d(0.0, 4.0, 4.0)); // 6
	vertices->push_back(osg::Vec3d(0.0, 4.0, 0.0)); // 7
	vertices->push_back(osg::Vec3d(0.0, 0.0, 4.0)); // 8
	vertices->push_back(osg::Vec3d(0.0, 0.0, 0.0)); // 9

	// house normals
	osg::ref_ptr<osg::Vec3dArray> normals = new osg::Vec3dArray(10);
	(*normals)[0].set(-0.707, -0.707, 0.0);
	(*normals)[1].set(-0.707, -0.707, 0.0);
	(*normals)[2].set( 0.707, -0.707, 0.0);
	(*normals)[3].set( 0.707, -0.707, 0.0);
	(*normals)[4].set( 0.707,  0.707, 0.0);
	(*normals)[5].set( 0.707,  0.707, 0.0);
	(*normals)[6].set(-0.707,  0.707, 0.0);
	(*normals)[7].set(-0.707,  0.707, 0.0);
	(*normals)[8].set(-0.707, -0.707, 0.0);
	(*normals)[9].set(-0.707, -0.707, 0.0);

	// house texture coordinates
	osg::ref_ptr<osg::Vec2dArray> texcoords = new osg::Vec2dArray(10);
	(*texcoords)[0].set(0.0, 1.0);
	(*texcoords)[1].set(0.0, 0.0);
	(*texcoords)[2].set(0.3, 1.0);
	(*texcoords)[3].set(0.3, 0.0);
	(*texcoords)[4].set(0.5, 1.0);
	(*texcoords)[5].set(0.5, 0.0);
	(*texcoords)[6].set(0.8, 1.0);
	(*texcoords)[7].set(0.8, 0.0);
	(*texcoords)[8].set(1.0, 1.0);
	(*texcoords)[9].set(1.0, 0.0);

	// create wall geometry
	osg::ref_ptr<osg::Geometry> houseWall = new osg::Geometry();
	houseWall->setVertexArray(vertices);
	houseWall->setNormalArray(normals);
	houseWall->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	houseWall->setTexCoordArray(0, texcoords);
	houseWall->addPrimitiveSet(
		new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, 10));
	houseWall->getOrCreateStateSet()->setTextureAttributeAndModes(
		0, new osg::Texture2D(osgDB::readImageFile("Images/wall.png")));

	return houseWall.release();
}

osg::Drawable* createHouseRoof()
{
	// vertices
	osg::ref_ptr<osg::Vec3dArray> vertices = new osg::Vec3dArray();
	vertices->push_back(osg::Vec3d(-0.2, -0.5, 3.5)); // 0
	vertices->push_back(osg::Vec3d( 6.2, -0.5, 3.5)); // 1
	vertices->push_back(osg::Vec3d( 0.8,  2.0, 6.0)); // 2
	vertices->push_back(osg::Vec3d( 5.2,  2.0, 6.0)); // 3
	vertices->push_back(osg::Vec3d(-0.2,  4.5, 3.5)); // 4
	vertices->push_back(osg::Vec3d( 6.2,  4.5, 3.5)); // 5

	// roof primitives
	osg::ref_ptr<osg::DrawArrays> roof = new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, 6);
	osg::ref_ptr<osg::DrawElementsUInt> roofSide = new osg::DrawElementsUInt(osg::DrawElementsUInt::TRIANGLES, 6);
	(*roofSide)[0] = 0;
	(*roofSide)[1] = 2;
	(*roofSide)[2] = 4;
	(*roofSide)[3] = 5;
	(*roofSide)[4] = 3;
	(*roofSide)[5] = 1;

	// colors
	osg::ref_ptr<osg::Vec4dArray> colors = new osg::Vec4dArray();
	colors->push_back(osg::Vec4d(0.25, 0.0, 0.0, 1.0));

	//
	osg::ref_ptr<osg::Geometry> houseRoof = new osg::Geometry();
	houseRoof->setVertexArray(vertices);
	houseRoof->setColorArray(colors);
	houseRoof->setColorBinding(osg::Geometry::BIND_OVERALL);
	houseRoof->addPrimitiveSet(roof);
	houseRoof->addPrimitiveSet(roofSide);
	//
	osgUtil::SmoothingVisitor smv;
	smv.smooth(*houseRoof);

	return houseRoof.release();
}

int main()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(createHouseWall());
	geode->addDrawable(createHouseRoof());

	osgViewer::Viewer viewer;
	viewer.setSceneData(geode);
	return viewer.run();
}