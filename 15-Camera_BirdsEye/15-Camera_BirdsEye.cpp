#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

osg::Camera* createBirdsEye(const osg::BoundingSphere& bs)
{
	osg::ref_ptr<osg::Camera> camera = new osg::Camera();
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	double viewDistance = 2.0 * bs.radius();
	double znear = viewDistance - bs.radius();
	double zfar = viewDistance + bs.radius();
	double top = bs.radius();
	double right = bs.radius();
	camera->setProjectionMatrixAsOrtho(-right, right, -top, top, znear, zfar);

	osg::Vec3d upDirection(0.0, 1.0, 0.0);
	osg::Vec3d viewDirection(0.0, 0.0, 1.0);
	osg::Vec3d center = bs.center();
	osg::Vec3d eyePoint = center + viewDirection * viewDistance;
	camera->setViewMatrixAsLookAt(eyePoint, center, upDirection);

	return camera.release();
}

int main()
{
	osg::Node* model = osgDB::readNodeFile("lz.osg");
	osg::Camera* camera = createBirdsEye(model->getBound());
	camera->addChild(model);

	osgViewer::Viewer viewer;
	viewer.setSceneData(camera);
	return viewer.run();
}