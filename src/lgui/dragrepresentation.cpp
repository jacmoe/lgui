/*   _                _
*   | |              (_)
*   | |  __ _  _   _  _
*   | | / _` || | | || |
*   | || (_| || |_| || |
*   |_| \__, | \__,_||_|
*        __/ |
*       |___/
*
* Copyright (c) 2015 frank256
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

#include "dragrepresentation.h"

#include "platform/bitmap.h"
#include "platform/graphics.h"
#include "platform/error.h"

namespace lgui {

    DragRepresentation::DragRepresentation(Widget& src_widget, const Position& hotspot,
                                           const std::string& content_descr)
        : msrc_widget(&src_widget), mtarget_widget(nullptr),
          mhotspot(hotspot), mrequested_src_action(None),
          mcontent_descr(content_descr), mdata(nullptr)
    {
    }

    DragRepresentation::~DragRepresentation()
    {
    }

    void DragRepresentation::draw(Graphics& gfx) const
    {
        (void) gfx;
    }

    void DragRepresentation::set_size(const Size& s)
    {
        mrect.set_size(s);
    }

    ImageDragRepresentation::ImageDragRepresentation(Widget& src_widget, const Position& hotspot,
                                                     const std::string& content_descr, const Bitmap& bmp)
        : DragRepresentation(src_widget, hotspot, content_descr), mbmp(bmp)
    {
        set_size(Size(bmp.w(), bmp.h()));
    }

    void ImageDragRepresentation::draw(Graphics& gfx) const
    {
        gfx.draw_bmp(mbmp, 0, 0);
    }

}