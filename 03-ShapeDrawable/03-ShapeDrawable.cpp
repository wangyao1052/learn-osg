#include <iostream>
#include <osgViewer\Viewer>
#include <osg\ShapeDrawable>

osg::Node* createScene(const std::string& shapeType)
{
	osg::Geode* geode = new osg::Geode();

	osg::ref_ptr<osg::ShapeDrawable> shapeDrawable = new osg::ShapeDrawable();
	osg::ref_ptr<osg::Shape> shape;
	if (shapeType == "box")
	{
		shape = new osg::Box(osg::Vec3d(0, 0, 0), 1.0, 1.0, 1.0);
	}
	else if (shapeType == "sphere")
	{
		shape = new osg::Sphere(osg::Vec3d(0, 0, 0), 1.0);
	}
	else if (shapeType == "cylinder")
	{
		shape = new osg::Cylinder(osg::Vec3d(0, 0, 0), 1.0, 3.0);
	}
	else if (shapeType == "cone")
	{
		shape = new osg::Cone(osg::Vec3d(0, 0, 0), 2.0, 3.0);
	}
	else if (shapeType == "capsule")
	{
		shape = new osg::Capsule(osg::Vec3d(0, 0, 0), 2.0, 3.0);
	}
	shapeDrawable->setShape(shape);

	geode->addDrawable(shapeDrawable);
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	return geode;
}

int main()
{
	osgViewer::Viewer viewer;

	std::cout << "输入形状类型: " << "box sphere cylinder cone capsule" << std::endl;
	std::string shapeType;
	std::cin >> shapeType;

	viewer.setSceneData(createScene(shapeType));
	return viewer.run();
}