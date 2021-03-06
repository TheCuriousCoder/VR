#ifndef THUMBNAILGENERATOR_H
#define THUMBNAILGENERATOR_H

#include "../irisgl/src/irisglfwd.h"
#include "../irisgl/src/scenegraph/meshnode.h"
#include "../irisgl/src/materials/custommaterial.h"
#include "../irisgl/src/materials/defaultmaterial.h"

#include <QThread>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_2_Core>
#include <QMutex>
#include <QSemaphore>
#include <QImage>
#include <QJsonObject>

enum class ThumbnailRequestType
{
    Material,
    Mesh
};

struct ThumbnailRequest
{
    ThumbnailRequestType type;
    QString path;
    QString id;
};

struct ThumbnailResult
{
    ThumbnailRequestType type;
    QString path;
    QString id;
    QImage thumbnail;
};

class RenderThread : public QThread
{
    Q_OBJECT

public:
    QOffscreenSurface *surface;
    QOpenGLContext *context;

    iris::Texture2DPtr tex;
    iris::RenderTargetPtr renderTarget;

    iris::ForwardRendererPtr renderer;
    iris::ScenePtr scene;
    iris::SceneNodePtr sceneNode;

	iris::MeshNodePtr materialNode;

    iris::CameraNodePtr cam;
    iris::CustomMaterialPtr material;

    QMutex requestMutex;
    QList<ThumbnailRequest> requests;
    QSemaphore requestsAvailable;

	iris::SceneSource *ssource;
    bool shutdown;

    void run() override;
    void initScene();
    void cleanupScene();
    void requestThumbnail(const ThumbnailRequest& request);
    void prepareScene(const ThumbnailRequest& request);

	void createMaterial(QJsonObject &matObj, iris::CustomMaterialPtr mat);

signals:
    void thumbnailComplete(ThumbnailResult* result);

private:
    float getBoundingRadius(iris::SceneNodePtr node);
    void getBoundingSpheres(iris::SceneNodePtr node, QList<iris::BoundingSphere>& spheres);
};

// http://doc.qt.io/qt-5/qtquick-scenegraph-textureinthread-threadrenderer-cpp.html
class ThumbnailGenerator
{
public:
    RenderThread* renderThread;
    static ThumbnailGenerator* getSingleton();
    void requestThumbnail(ThumbnailRequestType type, QString path, QString id = "");

    // must be called to properly shutdown ui components
    void shutdown();

private:
	static ThumbnailGenerator* instance;
	ThumbnailGenerator();
};

#endif // THUMBNAILGENERATOR_H
