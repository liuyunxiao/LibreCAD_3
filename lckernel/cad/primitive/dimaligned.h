#pragma once

#include "cad/const.h"
#include "cad/interface/entitydispatch.h"

#include "cad/primitive/dimension.h"
#include "cad/base/cadentity.h"
#include "cad/vo/entitycoordinate.h"
#include "cad/math/lcmath.h"
#include <cad/primitive/point.h>
#include <cad/builders/dimaligned.h>
#include "cad/interface/draggable.h"

namespace lc {
namespace entity {

class DimAligned : public std::enable_shared_from_this<DimAligned>,
    public CADEntity,
    public Dimension,
    virtual public Visitable,
    public Draggable {
    friend class lc::builder::DimAlignedBuilder;
public:


    /**
    * @brief DimAligned, DimAligned constructor with metatypes
    * @param Dimension dimension
    * @param geo::Coordinate extension_point1
    * @param geo::Coordinate extension_point2
    * @param double oblique
    * @param Layer_CSPtr layer
    */
    DimAligned(geo::Coordinate definitionPoint,
               geo::Coordinate middleOfText,
               TextConst::AttachmentPoint attachmentPoint,
               double textAngle,
               double lineSpacingFactor,
               TextConst::LineSpacingStyle lineSpacingStyle,
               std::string explicitValue,
               geo::Coordinate definitionPoint2,
               geo::Coordinate definitionPoint3,
               meta::Layer_CSPtr layer,
               meta::MetaInfo_CSPtr metaInfo = nullptr,
               meta::Block_CSPtr block = nullptr);


    DimAligned(const DimAligned_CSPtr& other, bool sameID = false);

private:
    DimAligned(const lc::builder::DimAlignedBuilder& builder);

public:
    CADEntity_CSPtr move(const geo::Coordinate &offset) const override;
    CADEntity_CSPtr copy(const geo::Coordinate &offset) const override;
    CADEntity_CSPtr rotate(const geo::Coordinate &rotation_center, double rotation_angle) const override;
    CADEntity_CSPtr scale(const geo::Coordinate &scale_center,
                          const geo::Coordinate &scale_factor) const override;
    CADEntity_CSPtr mirror(const geo::Coordinate& axis1,
                           const geo::Coordinate& axis2) const override;
    const geo::Area boundingBox() const override;
    CADEntity_CSPtr modify(meta::Layer_CSPtr layer, meta::MetaInfo_CSPtr metaInfo, meta::Block_CSPtr block) const override;

    // Where p2 specifies the first point of the dimension, p3 specifies that second point of the dimension
    // defPoint specifies where the dimension is specified and notates the horizontal/vertical 'line' between the two points
    const geo::Coordinate &definitionPoint2() const noexcept;

    const geo::Coordinate &definitionPoint3() const noexcept;

protected:
    const geo::Coordinate _definitionPoint2;
    const geo::Coordinate _definitionPoint3;
public:
    void accept(GeoEntityVisitor &v) const override {
        v.visit(*this);
    }

    void dispatch(EntityDispatch &ed) const override {
        ed.visit(shared_from_this());
    }
public:
    std::map<unsigned int, lc::geo::Coordinate> dragPoints() const override;
    CADEntity_CSPtr setDragPoints(std::map<unsigned int, lc::geo::Coordinate> dragPoints) const override;

    PropertiesMap availableProperties() const override;

    CADEntity_CSPtr setProperties(const PropertiesMap& propertiesMap) const override;
};

DECLARE_SHORT_SHARED_PTR(DimAligned)
}
}

// DIMLINEAR_H
