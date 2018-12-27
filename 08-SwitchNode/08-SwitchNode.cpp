#include <osg/Switch>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

class CessnaCallback : public osg::NodeCallback
{
public:
	CessnaCallback() : osg::NodeCallback(), _fireStartFrame(120)
	{}

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::Switch* cessnaSwitch = dynamic_cast<osg::Switch*>(node);
		if (cessnaSwitch && nv)
		{
			const osg::FrameStamp* frameStamp = nv->getFrameStamp();
			if (frameStamp)
			{
				if (_fireStartFrame < frameStamp->getFrameNumber())
				{
					cessnaSwitch->setValue(0, false);
					cessnaSwitch->setValue(1, true);
				}
			}
		}

		traverse(node, nv);
	}

private:
	int _fireStartFrame;
};

int main()
{
	osg::ref_ptr<osg::Switch> root = new osg::Switch();
	root->addChild(osgDB::readNodeFile("cessna.osg"), true);
	root->addChild(osgDB::readNodeFile("cessnafire.osg"), false);
	root->setUpdateCallback(new CessnaCallback());

	osgViewer::Viewer viewer;
	viewer.setSceneData(root);
	return viewer.run();
}