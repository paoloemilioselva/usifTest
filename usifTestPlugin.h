#ifndef USIFTESTPLUGIN_H
#define USIFTESTPLUGIN_H

#include <pxr/imaging/hd/sceneIndexPlugin.h>
#include <pxr/pxr.h>

class usifTestPlugin: public pxr::HdSceneIndexPlugin
{
public:
    usifTestPlugin();
    ~usifTestPlugin() override;

protected:
    pxr::HdSceneIndexBaseRefPtr _AppendSceneIndex(
        const pxr::HdSceneIndexBaseRefPtr& inputScene,
        const pxr::HdContainerDataSourceHandle& inputArgs) override;
};

#endif