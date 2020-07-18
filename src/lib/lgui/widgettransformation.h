/*   _                _
*   | |              (_)
*   | |  __ _  _   _  _
*   | | / _` || | | || |
*   | || (_| || |_| || |
*   |_| \__, | \__,_||_|
*        __/ |
*       |___/
*
* Copyright (c) 2015-20 frank256
*
* License (BSD):
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice, this
*    list of conditions and the following disclaimer in the documentation and/or
*    other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LGUI_WIDGETTRANSFORMATION_H
#define LGUI_WIDGETTRANSFORMATION_H

#include "platform/transform.h"
#include "widgettransformationstate.h"

namespace lgui {

class WidgetTransformation {
    public:
        WidgetTransformation();

        void set_translation(PointF translation);
        PointF get_translation() const { return mstate.translation; }

        void set_translation_z(float translation_z);
        float get_translation_z() const { return mstate.translation_z; }

        void set_pivot(PointF translation);
        PointF get_pivot() const { return mpivot; }

        void set_scale(PointF scale);
        PointF get_scale() const { return mstate.scale; }

        void set_rotation(float rotation_degrees);
        float get_rotation() const { return mstate.rotation_z; }

        void set_rotation_x(float rotation_x);
        float rotation_x() const {return mstate.rotation_x;}
        void set_rotation_y(float rotation_y);
        float rotation_y() const {return mstate.rotation_y;}

        void set_state(const WidgetTransformationState& state) {
            mstate = state;
            // FIXME: change detection?
            update_transform();
        }

        bool is_identity() const { return mis_identity; }

        const Transform& get_transform() const { return mtransform; }
        const Transform& get_inverse_transform() const { return minverse_transform; }

    private:
        void update_transform();
        bool _is_identity() const;

        WidgetTransformationState mstate;
        PointF mpivot;
        Transform mtransform, minverse_transform;
        bool mis_identity;
};

}

#endif //LGUI_WIDGETTRANSFORMATION_H
