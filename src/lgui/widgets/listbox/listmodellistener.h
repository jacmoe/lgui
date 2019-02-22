/*   _                _
*   | |              (_)
*   | |  __ _  _   _  _
*   | | / _` || | | || |
*   | || (_| || |_| || |
*   |_| \__, | \__,_||_|
*        __/ |
*       |___/
*
* Copyright (c) 2015-19 frank256
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

#ifndef LGUI_LIST_MODEL_LISTENER_H
#define LGUI_LIST_MODEL_LISTENER_H

namespace  lgui {

    /** An interface class to listen to changes of a list model. */
    class IListModelListener {
        public:
            /** Called to announce that the model is going to insert items. */
            virtual void about_to_add_items(int start_idx, int n) { (void) start_idx; (void) n; }
            /** Called to announce that the model is going to remove items. */
            virtual void about_to_remove_items(int start_idx, int n) { (void) start_idx; (void) n; }
            /** Called to announce that the model is going to change completely. */
            virtual void about_to_invalidate_items() {}
            /** Called to inform that the model has inserted new items. */
            virtual void items_added(int start_idx, int n) { (void) start_idx; (void) n; }
            /** Called to inform that the model has removed items. */
            virtual void items_removed(int start_idx, int n) { (void) start_idx; (void) n; }
            /** Called to inform that the model has changed completely. */
            virtual void items_invalidated() {}
            /** Called to announce that the model is going to be destroyed.
                This has always to be implemented. */
            virtual void model_about_to_die() = 0;
    };
}

#endif // LGUI_LIST_MODEL_LISTENER_H
