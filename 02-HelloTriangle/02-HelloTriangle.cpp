#include <osgViewer\Viewer>

osg::Node* createScene()
{
	osg::Geode* geode = new osg::Geode();

	osg::ref_ptr<osg::Geometry> triangleGeometry = new osg::Geometry();
	{
		// vertices
		osg::Vec3Array* vertices = new osg::Vec3Array();
		vertices->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
		vertices->push_back(osg::Vec3(-1.0f, -1.0f, 0.0f));
		vertices->push_back(osg::Vec3(1.0f, -1.0f, 0.0f));
		triangleGeometry->setVertexArray(vertices);

		// normals
		osg::Vec3Array* normals = new osg::Vec3Array();
		normals->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
		triangleGeometry->setNormalArray(normals, osg::Array::BIND_OVERALL);

		// colors
		osg::Vec4Array* colors = new osg::Vec4Array();
		colors->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
		triangleGeometry->setColorArray(colors, osg::Array::BIND_OVERALL);

		// primitive set
		triangleGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, vertices->size()));
	}
	geode->addDrawable(triangleGeometry);

	return geode;
}

int main()
{
	osgViewer::Viewer viewer;
	viewer.setSceneData(createScene());
	return viewer.run();
}