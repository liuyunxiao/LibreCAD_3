#pragma once

#include <cad/primitive/insert.h>
#include <cad/dochelpers/entitycontainer.h>
#include <cad/document/document.h>
#include <unordered_set>
#include "lcvdrawitem.h"

namespace LCViewer {
    class LCVInsert : public lc::entity::Insert, public LCVDrawItem {
        public:
            LCVInsert(lc::entity::Insert_CSPtr insert);
            virtual ~LCVInsert();

            void draw(LcPainter& _painter, const LcDrawOptions& options, const lc::geo::Area& updateRect) const override;

        private:
            void append(lc::entity::CADEntity_CSPtr entity);

            void on_addEntityEvent(const lc::AddEntityEvent&);
            void on_removeEntityEvent(const lc::RemoveEntityEvent&);

        private:
            lc::geo::Coordinate _offset;
            std::unordered_set<lc::entity::CADEntity_CSPtr> _entities; //This should contains only instances of LCVDrawItem
    };
}