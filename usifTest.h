#ifndef USIFTEST_H
#define USIFTEST_H

#include <pxr/pxr.h>
#include <pxr/usdImaging/usdImaging/api.h>
#include <pxr/imaging/hd/filteringSceneIndex.h>

PXR_NAMESPACE_USING_DIRECTIVE

TF_DECLARE_REF_PTRS(usifTest);

class usifTest : public pxr::HdSingleInputFilteringSceneIndexBase
{
public:
    static usifTestRefPtr New(
        const pxr::HdSceneIndexBaseRefPtr& inputSceneIndex,
        const pxr::HdContainerDataSourceHandle& inputArgs);

    virtual ~usifTest() override;

    virtual pxr::HdSceneIndexPrim GetPrim(const pxr::SdfPath& primPath) const override;
    virtual pxr::SdfPathVector GetChildPrimPaths(const pxr::SdfPath& primPath) const override;

protected:
    usifTest(
        const pxr::HdSceneIndexBaseRefPtr& inputSceneIndex,
        const pxr::HdContainerDataSourceHandle& inputArgs);

    void _PrimsAdded(
        const pxr::HdSceneIndexBase& sender,
        const pxr::HdSceneIndexObserver::AddedPrimEntries& entries) override;

    void _PrimsRemoved(
        const pxr::HdSceneIndexBase& sender,
        const pxr::HdSceneIndexObserver::RemovedPrimEntries& entries) override;

    void _PrimsDirtied(
        const pxr::HdSceneIndexBase& sender,
        const pxr::HdSceneIndexObserver::DirtiedPrimEntries& entries) override;

};

#endif