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

#include "spinner.h"
#include "lgui/keyevent.h"
#include "lgui/mouseevent.h"
#include <climits>

namespace lgui {

Spinner::Spinner()
    : mbt_increase(Style::HelperButtonType::IncreaseButton),
      mbt_decrease(Style::HelperButtonType::DecreaseButton),
      mvalue(0),
      mmin_value(INT_MIN),
      mmax_value(INT_MAX),
      mwriting_value(false)
{
    configure_new_child(mbt_increase);
    configure_new_child(mbt_decrease);
    mbt_increase.on_activated.connect([this](){ increase_pressed();});
    mbt_decrease.on_activated.connect([this](){ decrease_pressed();});
    on_text_changed.connect(&Spinner::text_changed, *this);
    style_changed();
}

void Spinner::draw(const DrawEvent& de) const
{
    TextField::draw(de);

    draw_child(mbt_increase, de);
    draw_child(mbt_decrease, de);
}

void Spinner::style_changed()
{
    TextField::style_changed();
    mbt_increase.set_style(&style());
    mbt_decrease.set_style(&style());

    int helper_width = std::max(style().get_helper_button_min_size(Style::HelperButtonType::IncreaseButton).w(),
                            style().get_helper_button_min_size(Style::HelperButtonType::DecreaseButton).w());
    mpadding.set_right(mpadding.right() + helper_width);
    layout_buttons();
}


void Spinner::_recursive_configure(const Widget::ConfigInfo& ci)
{
    _configure(ci);
    TextField::_recursive_configure(ci);
    mbt_increase._recursive_configure(ci);
    mbt_decrease._recursive_configure(ci);
}

bool Spinner::validate(const std::string& s) const
{
    // Could use a regex, but don't want to recompile it every time and do not want to expose it in the header.
    // Apart from that, it's really simple...
    if (s.empty())
        return true;
    if (s[0] < '0' || s[0] > '9') {
        if (mmin_value >= 0 || s[0] != '-')
            return false;
    }
    for (size_t i = 1; i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

void Spinner::change_value(int new_val, bool select)
{
    new_val = std::max(mmin_value, new_val);
    new_val = std::min(mmax_value, new_val);

    if (mvalue != new_val) {
        mbt_increase.set_active(new_val < mmax_value);
        mbt_decrease.set_active(new_val > mmin_value);
        mvalue = new_val;
        write_value(select);
        on_value_changed.emit(mvalue);
    }
}

void Spinner::text_changed(const std::string& text)
{
    if (!mwriting_value) {
        try {
            int value = std::stoi(text);
            change_value(value);
        } catch(std::exception) {
            change_value(0, true);
        }
    }
}

void Spinner::increase_pressed()
{
    change_value(mvalue+1);
}

void Spinner::decrease_pressed()
{
    change_value(mvalue-1);
}

Widget* Spinner::get_child_at(int x, int y)
{
    if(mbt_increase.is_visible() && mbt_increase.rect().contains(x, y))
        return &mbt_increase;
    else if(mbt_decrease.is_visible() && mbt_decrease.rect().contains(x, y))
        return &mbt_decrease;
    else
        return TextField::get_child_at(x, y);
}

void Spinner::child_about_to_die(Widget& child)
{
    if(&child == &mbt_increase || &child == &mbt_decrease)
        return;
    TextField::child_about_to_die(child);
}

void Spinner::resized(const Size& old_size)
{
    layout_buttons();
    TextField::resized(old_size);
}

void Spinner::set_value(int value)
{
    change_value(value);
    write_value();
}

void Spinner::set_min_value(int min_value)
{
    mmin_value = min_value;
    change_value(mvalue);
}

void Spinner::set_max_value(int max_value)
{
    mmax_value = max_value;
    change_value(mvalue);
}

void Spinner::key_char(KeyEvent& event)
{
    if (event.key_code() == Keycodes::KEY_UP) {
        increase_pressed();
        event.consume();
    }
    else if (event.key_code() == Keycodes::KEY_DOWN) {
        decrease_pressed();
        event.consume();
    }
    else {
        TextField::key_char(event);
    }
}

void Spinner::mouse_wheel_up(MouseEvent& event)
{
    increase_pressed();
    event.consume();
}

void Spinner::mouse_wheel_down(MouseEvent& event)
{
    decrease_pressed();
    event.consume();
}

bool Spinner::is_char_insertable(int c) const
{
    return (c >= '0' && c <= '9') || c == '-';
}

void Spinner::layout_buttons()
{
    Size incr = style().get_helper_button_min_size(Style::IncreaseButton);
    Size decr = style().get_helper_button_min_size(Style::DecreaseButton);
    int h  = (font().line_height() + mpadding.vert()) / 2;
    incr.set_h(h);
    decr.set_h(h);
    mbt_increase.set_size(incr);
    mbt_decrease.set_size(decr);
    mbt_increase.set_pos(width() - incr.w(), 0);
    mbt_decrease.set_pos(width() - incr.w(), height() - mbt_decrease.height());
}

void Spinner::write_value(bool select)
{
    mwriting_value = true;
    TextField::set_text(std::to_string(mvalue), select);
    mwriting_value = false;
}


}