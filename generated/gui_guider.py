# Copyright 2020-2023 NXP
# All rights reserved.
#
# SPDX-License-Identifier: MIT
#
# NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
# accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
# activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
# comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
# terms, then you may not retain, install, activate or otherwise use the software.

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct
import fs_driver

lv.init()
SDL.init(w=480,h=320)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(480*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 480
disp_drv.ver_res = 320
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init()
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

fs_drv = lv.fs_drv_t()
fs_driver.fs_register(fs_drv, 'Z')

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def anim_width_cb(obj, v):
    obj.set_width(v)

def anim_height_cb(obj, v):
    obj.set_height(v)

def anim_img_zoom_cb(obj, v):
    obj.set_zoom(v)

def anim_img_rotate_cb(obj, v):
    obj.set_angle(v)

global_font_cache = {}
def test_font(font_family, font_size):
    global global_font_cache
    if font_family + str(font_size) in global_font_cache:
        return global_font_cache[font_family + str(font_size)]
    if font_size % 2:
        candidates = [
            (font_family, font_size),
            (font_family, font_size-font_size%2),
            (font_family, font_size+font_size%2),
            ("montserrat", font_size-font_size%2),
            ("montserrat", font_size+font_size%2),
            ("montserrat", 16)
        ]
    else:
        candidates = [
            (font_family, font_size),
            ("montserrat", font_size),
            ("montserrat", 16)
        ]
    for (family, size) in candidates:
        try:
            if eval(f'lv.font_{family}_{size}'):
                global_font_cache[font_family + str(font_size)] = eval(f'lv.font_{family}_{size}')
                if family != font_family or size != font_size:
                    print(f'WARNING: lv.font_{family}_{size} is used!')
                return eval(f'lv.font_{family}_{size}')
        except AttributeError:
            try:
                load_font = lv.font_load(f"Z:MicroPython/lv_font_{family}_{size}.fnt")
                global_font_cache[font_family + str(font_size)] = load_font
                return load_font
            except:
                if family == font_family and size == font_size:
                    print(f'WARNING: lv.font_{family}_{size} is NOT supported!')

global_image_cache = {}
def load_image(file):
    global global_image_cache
    if file in global_image_cache:
        return global_image_cache[file]
    try:
        with open(file,'rb') as f:
            data = f.read()
    except:
        print(f'Could not open {file}')
        sys.exit()

    img = lv.img_dsc_t({
        'data_size': len(data),
        'data': data
    })
    global_image_cache[file] = img
    return img

def calendar_event_handler(e,obj):
    code = e.get_code()

    if code == lv.EVENT.VALUE_CHANGED:
        source = e.get_current_target()
        date = lv.calendar_date_t()
        if source.get_pressed_date(date) == lv.RES.OK:
            source.set_highlighted_dates([date], 1)

def spinbox_increment_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.increment()
def spinbox_decrement_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.decrement()

def digital_clock_cb(timer, obj, current_time, show_second, use_ampm):
    hour = int(current_time[0])
    minute = int(current_time[1])
    second = int(current_time[2])
    ampm = current_time[3]
    second = second + 1
    if second == 60:
        second = 0
        minute = minute + 1
        if minute == 60:
            minute = 0
            hour = hour + 1
            if use_ampm:
                if hour == 12:
                    if ampm == 'AM':
                        ampm = 'PM'
                    elif ampm == 'PM':
                        ampm = 'AM'
                if hour > 12:
                    hour = hour % 12
    hour = hour % 24
    if use_ampm:
        if show_second:
            obj.set_text("%02d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%02d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%02d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%02d:%02d" %(hour, minute))
    current_time[0] = hour
    current_time[1] = minute
    current_time[2] = second
    current_time[3] = ampm

def analog_clock_cb(timer, obj):
    datetime = time.localtime()
    hour = datetime[3]
    if hour >= 12: hour = hour - 12
    obj.set_time(hour, datetime[4], datetime[5])

def datetext_event_handler(e, obj):
    code = e.get_code()
    target = e.get_target()
    if code == lv.EVENT.FOCUSED:
        if obj is None:
            bg = lv.layer_top()
            bg.add_flag(lv.obj.FLAG.CLICKABLE)
            obj = lv.calendar(bg)
            scr = target.get_screen()
            scr_height = scr.get_height()
            scr_width = scr.get_width()
            obj.set_size(int(scr_width * 0.8), int(scr_height * 0.8))
            datestring = target.get_text()
            year = int(datestring.split('/')[0])
            month = int(datestring.split('/')[1])
            day = int(datestring.split('/')[2])
            obj.set_showed_date(year, month)
            highlighted_days=[lv.calendar_date_t({'year':year, 'month':month, 'day':day})]
            obj.set_highlighted_dates(highlighted_days, 1)
            obj.align(lv.ALIGN.CENTER, 0, 0)
            lv.calendar_header_arrow(obj)
            obj.add_event_cb(lambda e: datetext_calendar_event_handler(e, target), lv.EVENT.ALL, None)
            scr.update_layout()

def datetext_calendar_event_handler(e, obj):
    code = e.get_code()
    target = e.get_current_target()
    if code == lv.EVENT.VALUE_CHANGED:
        date = lv.calendar_date_t()
        if target.get_pressed_date(date) == lv.RES.OK:
            obj.set_text(f"{date.year}/{date.month}/{date.day}")
            bg = lv.layer_top()
            bg.clear_flag(lv.obj.FLAG.CLICKABLE)
            bg.set_style_bg_opa(lv.OPA.TRANSP, 0)
            target.delete()

def scrOverview_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def scrRide1_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def scrRide2_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

# Create scrOverview
scrOverview = lv.obj()
scrOverview.set_size(480, 320)
scrOverview.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview.set_style_bg_color(lv.color_hex(0x161d27), lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_img_Header
scrOverview_img_Header = lv.img(scrOverview)
scrOverview_img_Header.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_header_bg_480_51.png"))
scrOverview_img_Header.add_flag(lv.obj.FLAG.CLICKABLE)
scrOverview_img_Header.set_pivot(50,50)
scrOverview_img_Header.set_angle(0)
scrOverview_img_Header.set_pos(0, 0)
scrOverview_img_Header.set_size(480, 51)
scrOverview_img_Header.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_img_Header, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_img_Header.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Date
scrOverview_label_Date = lv.label(scrOverview)
scrOverview_label_Date.set_text("Aug 19,2023")
scrOverview_label_Date.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Date.set_pos(20, 2)
scrOverview_label_Date.set_size(133, 18)
scrOverview_label_Date.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Date, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Date.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Date.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Title
scrOverview_label_Title = lv.label(scrOverview)
scrOverview_label_Title.set_text("OVERVIEW")
scrOverview_label_Title.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Title.set_pos(170, 8)
scrOverview_label_Title.set_size(143, 24)
scrOverview_label_Title.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Time
scrOverview_label_Time = lv.label(scrOverview)
scrOverview_label_Time.set_text("10:28 AM")
scrOverview_label_Time.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Time.set_pos(370, 3)
scrOverview_label_Time.set_size(102, 18)
scrOverview_label_Time.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Time.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_img_GPS_Icon
scrOverview_img_GPS_Icon = lv.img(scrOverview)
scrOverview_img_GPS_Icon.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_gps_arrow_28_48.png"))
scrOverview_img_GPS_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
scrOverview_img_GPS_Icon.set_pivot(50,50)
scrOverview_img_GPS_Icon.set_angle(0)
scrOverview_img_GPS_Icon.set_pos(274, 60)
scrOverview_img_GPS_Icon.set_size(28, 48)
scrOverview_img_GPS_Icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_img_GPS_Icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_img_GPS_Icon.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Distance
scrOverview_label_Distance = lv.label(scrOverview)
scrOverview_label_Distance.set_text("3.1")
scrOverview_label_Distance.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Distance.set_pos(329, 49)
scrOverview_label_Distance.set_size(36, 19)
scrOverview_label_Distance.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Distance, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Distance.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Direction
scrOverview_label_Direction = lv.label(scrOverview)
scrOverview_label_Direction.set_text("Turn right to")
scrOverview_label_Direction.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Direction.set_pos(320, 74)
scrOverview_label_Direction.set_size(147, 18)
scrOverview_label_Direction.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Direction, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Direction.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Direction.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Street
scrOverview_label_Street = lv.label(scrOverview)
scrOverview_label_Street.set_text("Ed Bluestein Blvd")
scrOverview_label_Street.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Street.set_pos(288, 97)
scrOverview_label_Street.set_size(184, 17)
scrOverview_label_Street.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Street, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Street.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Street.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_ima_Travell_Icon
scrOverview_ima_Travell_Icon = lv.img(scrOverview)
scrOverview_ima_Travell_Icon.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_distance_travelled_21_14.png"))
scrOverview_ima_Travell_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
scrOverview_ima_Travell_Icon.set_pivot(50,50)
scrOverview_ima_Travell_Icon.set_angle(0)
scrOverview_ima_Travell_Icon.set_pos(220, 130)
scrOverview_ima_Travell_Icon.set_size(21, 14)
scrOverview_ima_Travell_Icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_ima_Travell_Icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_ima_Travell_Icon.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Travelled_1
scrOverview_label_Travelled_1 = lv.label(scrOverview)
scrOverview_label_Travelled_1.set_text("Distance \nTravelled")
scrOverview_label_Travelled_1.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Travelled_1.set_pos(250, 118)
scrOverview_label_Travelled_1.set_size(94, 38)
scrOverview_label_Travelled_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Travelled_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Travelled_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Travelled_2
scrOverview_label_Travelled_2 = lv.label(scrOverview)
scrOverview_label_Travelled_2.set_text("12.7")
scrOverview_label_Travelled_2.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Travelled_2.set_pos(220, 157)
scrOverview_label_Travelled_2.set_size(70, 25)
scrOverview_label_Travelled_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Travelled_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Travelled_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Travelled_3
scrOverview_label_Travelled_3 = lv.label(scrOverview)
scrOverview_label_Travelled_3.set_text("km")
scrOverview_label_Travelled_3.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Travelled_3.set_pos(300, 157)
scrOverview_label_Travelled_3.set_size(40, 20)
scrOverview_label_Travelled_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Travelled_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Travelled_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Travelled_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Speed_3
scrOverview_label_Speed_3 = lv.label(scrOverview)
scrOverview_label_Speed_3.set_text("km/h")
scrOverview_label_Speed_3.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Speed_3.set_pos(410, 157)
scrOverview_label_Speed_3.set_size(60, 17)
scrOverview_label_Speed_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Speed_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Speed_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Speed_2
scrOverview_label_Speed_2 = lv.label(scrOverview)
scrOverview_label_Speed_2.set_text("16.1")
scrOverview_label_Speed_2.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Speed_2.set_pos(357, 157)
scrOverview_label_Speed_2.set_size(70, 25)
scrOverview_label_Speed_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Speed_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Speed_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Speed_1
scrOverview_label_Speed_1 = lv.label(scrOverview)
scrOverview_label_Speed_1.set_text("Average \nSpeed")
scrOverview_label_Speed_1.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Speed_1.set_pos(387, 118)
scrOverview_label_Speed_1.set_size(87, 41)
scrOverview_label_Speed_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Speed_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Speed_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Speed_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_img_Speed_Icon
scrOverview_img_Speed_Icon = lv.img(scrOverview)
scrOverview_img_Speed_Icon.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_average_speed_21_14.png"))
scrOverview_img_Speed_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
scrOverview_img_Speed_Icon.set_pivot(50,50)
scrOverview_img_Speed_Icon.set_angle(0)
scrOverview_img_Speed_Icon.set_pos(357, 130)
scrOverview_img_Speed_Icon.set_size(21, 14)
scrOverview_img_Speed_Icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_img_Speed_Icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_img_Speed_Icon.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_img_Remain_Icon
scrOverview_img_Remain_Icon = lv.img(scrOverview)
scrOverview_img_Remain_Icon.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_remaining_distance_21_20.png"))
scrOverview_img_Remain_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
scrOverview_img_Remain_Icon.set_pivot(50,50)
scrOverview_img_Remain_Icon.set_angle(0)
scrOverview_img_Remain_Icon.set_pos(220, 193)
scrOverview_img_Remain_Icon.set_size(21, 20)
scrOverview_img_Remain_Icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_img_Remain_Icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_img_Remain_Icon.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Remain_1
scrOverview_label_Remain_1 = lv.label(scrOverview)
scrOverview_label_Remain_1.set_text("Remain \nDistance")
scrOverview_label_Remain_1.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Remain_1.set_pos(250, 190)
scrOverview_label_Remain_1.set_size(94, 38)
scrOverview_label_Remain_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Remain_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Remain_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Remain_3
scrOverview_label_Remain_3 = lv.label(scrOverview)
scrOverview_label_Remain_3.set_text("km")
scrOverview_label_Remain_3.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Remain_3.set_pos(300, 229)
scrOverview_label_Remain_3.set_size(40, 20)
scrOverview_label_Remain_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Remain_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Remain_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Remain_2
scrOverview_label_Remain_2 = lv.label(scrOverview)
scrOverview_label_Remain_2.set_text("18.3")
scrOverview_label_Remain_2.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Remain_2.set_pos(220, 229)
scrOverview_label_Remain_2.set_size(70, 25)
scrOverview_label_Remain_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Remain_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Remain_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Remain_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_img_Elapsed_Icon
scrOverview_img_Elapsed_Icon = lv.img(scrOverview)
scrOverview_img_Elapsed_Icon.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_elapsed_time_20_25.png"))
scrOverview_img_Elapsed_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
scrOverview_img_Elapsed_Icon.set_pivot(50,50)
scrOverview_img_Elapsed_Icon.set_angle(0)
scrOverview_img_Elapsed_Icon.set_pos(357, 193)
scrOverview_img_Elapsed_Icon.set_size(20, 25)
scrOverview_img_Elapsed_Icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_img_Elapsed_Icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_img_Elapsed_Icon.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Elapsed_1
scrOverview_label_Elapsed_1 = lv.label(scrOverview)
scrOverview_label_Elapsed_1.set_text("Elapsed \nTime")
scrOverview_label_Elapsed_1.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Elapsed_1.set_pos(387, 190)
scrOverview_label_Elapsed_1.set_size(85, 35)
scrOverview_label_Elapsed_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Elapsed_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Elapsed_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Elapsed_2
scrOverview_label_Elapsed_2 = lv.label(scrOverview)
scrOverview_label_Elapsed_2.set_text("46:28")
scrOverview_label_Elapsed_2.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Elapsed_2.set_pos(357, 229)
scrOverview_label_Elapsed_2.set_size(70, 25)
scrOverview_label_Elapsed_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Elapsed_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Elapsed_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Elapsed_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_line_V_Seperator
scrOverview_line_V_Seperator = lv.line(scrOverview)
scrOverview_line_V_Seperator_line_points = [{"x":0, "y":0},{"x":0, "y":240},]
scrOverview_line_V_Seperator.set_points(scrOverview_line_V_Seperator_line_points, 2)
scrOverview_line_V_Seperator.set_pos(345, 119)
scrOverview_line_V_Seperator.set_size(5, 138)
scrOverview_line_V_Seperator.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_line_V_Seperator, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_line_V_Seperator.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_line_V_Seperator.set_style_line_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_line_V_Seperator.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_line_V_Seperator.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_img_Footer
scrOverview_img_Footer = lv.img(scrOverview)
scrOverview_img_Footer.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_footer_bg_480_35.png"))
scrOverview_img_Footer.add_flag(lv.obj.FLAG.CLICKABLE)
scrOverview_img_Footer.set_pivot(50,50)
scrOverview_img_Footer.set_angle(0)
scrOverview_img_Footer.set_pos(0, 279)
scrOverview_img_Footer.set_size(480, 35)
scrOverview_img_Footer.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_img_Footer, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_img_Footer.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_line_H_Seperator
scrOverview_line_H_Seperator = lv.line(scrOverview)
scrOverview_line_H_Seperator_line_points = [{"x":0, "y":0},{"x":240, "y":0},]
scrOverview_line_H_Seperator.set_points(scrOverview_line_H_Seperator_line_points, 2)
scrOverview_line_H_Seperator.set_pos(225, 180)
scrOverview_line_H_Seperator.set_size(240, 1)
scrOverview_line_H_Seperator.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_line_H_Seperator, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_line_H_Seperator.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_line_H_Seperator.set_style_line_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_line_H_Seperator.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_line_H_Seperator.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Indicator_L
scrOverview_label_Indicator_L = lv.label(scrOverview)
scrOverview_label_Indicator_L.set_text("")
scrOverview_label_Indicator_L.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Indicator_L.set_pos(181, 301)
scrOverview_label_Indicator_L.set_size(28, 8)
scrOverview_label_Indicator_L.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Indicator_L, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Indicator_L.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_radius(4, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_bg_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_L.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Indicator_M
scrOverview_label_Indicator_M = lv.label(scrOverview)
scrOverview_label_Indicator_M.set_text("")
scrOverview_label_Indicator_M.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Indicator_M.set_pos(229, 301)
scrOverview_label_Indicator_M.set_size(28, 8)
scrOverview_label_Indicator_M.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Indicator_M, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Indicator_M.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_radius(4, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_bg_color(lv.color_hex(0xa8a6ad), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_M.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Indicator_R
scrOverview_label_Indicator_R = lv.label(scrOverview)
scrOverview_label_Indicator_R.set_text("")
scrOverview_label_Indicator_R.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Indicator_R.set_pos(277, 301)
scrOverview_label_Indicator_R.set_size(28, 8)
scrOverview_label_Indicator_R.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Indicator_R, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Indicator_R.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_radius(4, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_bg_color(lv.color_hex(0xa8a6ad), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Indicator_R.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_Distance_Unit
scrOverview_label_Distance_Unit = lv.label(scrOverview)
scrOverview_label_Distance_Unit.set_text("KM")
scrOverview_label_Distance_Unit.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_Distance_Unit.set_pos(368, 49)
scrOverview_label_Distance_Unit.set_size(48, 19)
scrOverview_label_Distance_Unit.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_Distance_Unit, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_Distance_Unit.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_Distance_Unit.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_meter_Speed
scrOverview_meter_Speed = lv.meter(scrOverview)
#add scale scrOverview_meter_Speed_scale_1
scrOverview_meter_Speed_scale_1 = scrOverview_meter_Speed.add_scale()
scrOverview_meter_Speed.set_scale_ticks(scrOverview_meter_Speed_scale_1, 51, 3, 10, lv.color_hex(0x4a69ff))
scrOverview_meter_Speed.set_scale_major_ticks(scrOverview_meter_Speed_scale_1, 5, 3, 14, lv.color_hex(0xffffff), 15)
scrOverview_meter_Speed.set_scale_range(scrOverview_meter_Speed_scale_1, 0, 50, 300, 120)
# add arc for scrOverview_meter_Speed_scale_1
scrOverview_meter_Speed_scale_1_arc_0 = scrOverview_meter_Speed.add_arc(scrOverview_meter_Speed_scale_1, 10, lv.color_hex(0xb3dc00), 0)
scrOverview_meter_Speed.set_indicator_start_value(scrOverview_meter_Speed_scale_1_arc_0, 0)
scrOverview_meter_Speed.set_indicator_end_value(scrOverview_meter_Speed_scale_1_arc_0, 20)
# add arc for scrOverview_meter_Speed_scale_1
scrOverview_meter_Speed_scale_1_arc_1 = scrOverview_meter_Speed.add_arc(scrOverview_meter_Speed_scale_1, 10, lv.color_hex(0x00d6c2), 0)
scrOverview_meter_Speed.set_indicator_start_value(scrOverview_meter_Speed_scale_1_arc_1, 20)
scrOverview_meter_Speed.set_indicator_end_value(scrOverview_meter_Speed_scale_1_arc_1, 35)
# add arc for scrOverview_meter_Speed_scale_1
scrOverview_meter_Speed_scale_1_arc_2 = scrOverview_meter_Speed.add_arc(scrOverview_meter_Speed_scale_1, 10, lv.color_hex(0x950080), 0)
scrOverview_meter_Speed.set_indicator_start_value(scrOverview_meter_Speed_scale_1_arc_2, 35)
scrOverview_meter_Speed.set_indicator_end_value(scrOverview_meter_Speed_scale_1_arc_2, 50)
# add needle line for scrOverview_meter_Speed_scale_1
scrOverview_meter_Speed_scale_1_needleLine_0 = scrOverview_meter_Speed.add_needle_line(scrOverview_meter_Speed_scale_1, 4, lv.color_hex(0xff0000), 1)
scrOverview_meter_Speed.set_indicator_value( scrOverview_meter_Speed_scale_1_needleLine_0, 20)
scrOverview_meter_Speed.set_pos(9, 60)
scrOverview_meter_Speed.set_size(200, 200)
scrOverview_meter_Speed.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_meter_Speed, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_meter_Speed.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_meter_Speed.set_style_bg_color(lv.color_hex(0x142c58), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_meter_Speed.set_style_radius(100, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_meter_Speed.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_meter_Speed.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_meter_Speed.set_style_border_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_meter_Speed.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for scrOverview_meter_Speed, Part: lv.PART.TICKS, State: lv.STATE.DEFAULT.
scrOverview_meter_Speed.set_style_text_color(lv.color_hex(0xffffff), lv.PART.TICKS|lv.STATE.DEFAULT)
scrOverview_meter_Speed.set_style_text_font(test_font("montserratMedium", 12), lv.PART.TICKS|lv.STATE.DEFAULT)

# Create scrOverview_label_MeterSpeed
scrOverview_label_MeterSpeed = lv.label(scrOverview)
scrOverview_label_MeterSpeed.set_text("20")
scrOverview_label_MeterSpeed.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_MeterSpeed.set_pos(90, 190)
scrOverview_label_MeterSpeed.set_size(39, 25)
scrOverview_label_MeterSpeed.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_MeterSpeed, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_MeterSpeed.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_label_MeterSpeed_Unit
scrOverview_label_MeterSpeed_Unit = lv.label(scrOverview)
scrOverview_label_MeterSpeed_Unit.set_text("Km/h")
scrOverview_label_MeterSpeed_Unit.set_long_mode(lv.label.LONG.WRAP)
scrOverview_label_MeterSpeed_Unit.set_pos(82, 215)
scrOverview_label_MeterSpeed_Unit.set_size(55, 24)
scrOverview_label_MeterSpeed_Unit.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_label_MeterSpeed_Unit, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_label_MeterSpeed_Unit.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrOverview_label_MeterSpeed_Unit.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrOverview_img_Logo
scrOverview_img_Logo = lv.img(scrOverview)
scrOverview_img_Logo.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\logo_49_10.png"))
scrOverview_img_Logo.add_flag(lv.obj.FLAG.CLICKABLE)
scrOverview_img_Logo.set_pivot(50,50)
scrOverview_img_Logo.set_angle(0)
scrOverview_img_Logo.set_pos(84, 239)
scrOverview_img_Logo.set_size(49, 10)
scrOverview_img_Logo.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrOverview_img_Logo, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrOverview_img_Logo.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

scrOverview.update_layout()
# Create scrRide1
scrRide1 = lv.obj()
scrRide1.set_size(480, 320)
scrRide1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1.set_style_bg_color(lv.color_hex(0x161d27), lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_img_Header
scrRide1_img_Header = lv.img(scrRide1)
scrRide1_img_Header.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_header_bg_480_51.png"))
scrRide1_img_Header.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide1_img_Header.set_pivot(50,50)
scrRide1_img_Header.set_angle(0)
scrRide1_img_Header.set_pos(0, 0)
scrRide1_img_Header.set_size(480, 51)
scrRide1_img_Header.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_img_Header, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_img_Header.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Time
scrRide1_label_Time = lv.label(scrRide1)
scrRide1_label_Time.set_text("10:28 AM")
scrRide1_label_Time.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Time.set_pos(370, 3)
scrRide1_label_Time.set_size(102, 18)
scrRide1_label_Time.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Time.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Title
scrRide1_label_Title = lv.label(scrRide1)
scrRide1_label_Title.set_text("RIDE DETAILS")
scrRide1_label_Title.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Title.set_pos(155, 3)
scrRide1_label_Title.set_size(170, 24)
scrRide1_label_Title.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Date
scrRide1_label_Date = lv.label(scrRide1)
scrRide1_label_Date.set_text("Aug 19,2023")
scrRide1_label_Date.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Date.set_pos(20, 3)
scrRide1_label_Date.set_size(133, 18)
scrRide1_label_Date.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Date, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Date.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Date.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_img_Footer
scrRide1_img_Footer = lv.img(scrRide1)
scrRide1_img_Footer.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_footer_bg_480_35.png"))
scrRide1_img_Footer.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide1_img_Footer.set_pivot(50,50)
scrRide1_img_Footer.set_angle(0)
scrRide1_img_Footer.set_pos(0, 279)
scrRide1_img_Footer.set_size(480, 35)
scrRide1_img_Footer.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_img_Footer, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_img_Footer.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Indicator_R
scrRide1_label_Indicator_R = lv.label(scrRide1)
scrRide1_label_Indicator_R.set_text("")
scrRide1_label_Indicator_R.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Indicator_R.set_pos(277, 301)
scrRide1_label_Indicator_R.set_size(28, 8)
scrRide1_label_Indicator_R.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Indicator_R, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Indicator_R.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_radius(4, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_bg_color(lv.color_hex(0xa8a6ad), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_R.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Indicator_M
scrRide1_label_Indicator_M = lv.label(scrRide1)
scrRide1_label_Indicator_M.set_text("")
scrRide1_label_Indicator_M.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Indicator_M.set_pos(229, 301)
scrRide1_label_Indicator_M.set_size(28, 8)
scrRide1_label_Indicator_M.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Indicator_M, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Indicator_M.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_radius(4, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_bg_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_M.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Indicator_L
scrRide1_label_Indicator_L = lv.label(scrRide1)
scrRide1_label_Indicator_L.set_text("")
scrRide1_label_Indicator_L.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Indicator_L.set_pos(181, 301)
scrRide1_label_Indicator_L.set_size(28, 8)
scrRide1_label_Indicator_L.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Indicator_L, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Indicator_L.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_radius(4, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_bg_color(lv.color_hex(0xa8a6ad), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Indicator_L.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Distance_1
scrRide1_label_Distance_1 = lv.label(scrRide1)
scrRide1_label_Distance_1.set_text("Distance Travelled")
scrRide1_label_Distance_1.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Distance_1.set_pos(280, 55)
scrRide1_label_Distance_1.set_size(189, 16)
scrRide1_label_Distance_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Distance_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Distance_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_img_Distance
scrRide1_img_Distance = lv.img(scrRide1)
scrRide1_img_Distance.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_distance_travelled_big_42_28.png"))
scrRide1_img_Distance.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide1_img_Distance.set_pivot(50,50)
scrRide1_img_Distance.set_angle(0)
scrRide1_img_Distance.set_pos(230, 80)
scrRide1_img_Distance.set_size(42, 28)
scrRide1_img_Distance.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_img_Distance, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_img_Distance.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Distance_3
scrRide1_label_Distance_3 = lv.label(scrRide1)
scrRide1_label_Distance_3.set_text("km")
scrRide1_label_Distance_3.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Distance_3.set_pos(410, 90)
scrRide1_label_Distance_3.set_size(40, 20)
scrRide1_label_Distance_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Distance_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Distance_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Distance_2
scrRide1_label_Distance_2 = lv.label(scrRide1)
scrRide1_label_Distance_2.set_text("12.7")
scrRide1_label_Distance_2.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Distance_2.set_pos(290, 90)
scrRide1_label_Distance_2.set_size(70, 25)
scrRide1_label_Distance_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Distance_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Distance_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Distance_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_line_H_Seperator_1
scrRide1_line_H_Seperator_1 = lv.line(scrRide1)
scrRide1_line_H_Seperator_1_line_points = [{"x":0, "y":0},{"x":240, "y":0},]
scrRide1_line_H_Seperator_1.set_points(scrRide1_line_H_Seperator_1_line_points, 2)
scrRide1_line_H_Seperator_1.set_pos(230, 120)
scrRide1_line_H_Seperator_1.set_size(240, 1)
scrRide1_line_H_Seperator_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_line_H_Seperator_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_line_H_Seperator_1.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_line_H_Seperator_1.set_style_line_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_line_H_Seperator_1.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_line_H_Seperator_1.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Speed_3
scrRide1_label_Speed_3 = lv.label(scrRide1)
scrRide1_label_Speed_3.set_text("km/h")
scrRide1_label_Speed_3.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Speed_3.set_pos(410, 170)
scrRide1_label_Speed_3.set_size(60, 20)
scrRide1_label_Speed_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Speed_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Speed_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Speed_2
scrRide1_label_Speed_2 = lv.label(scrRide1)
scrRide1_label_Speed_2.set_text("16.1")
scrRide1_label_Speed_2.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Speed_2.set_pos(290, 170)
scrRide1_label_Speed_2.set_size(70, 25)
scrRide1_label_Speed_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Speed_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Speed_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Speed_1
scrRide1_label_Speed_1 = lv.label(scrRide1)
scrRide1_label_Speed_1.set_text("Average Speed")
scrRide1_label_Speed_1.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Speed_1.set_pos(280, 132)
scrRide1_label_Speed_1.set_size(189, 16)
scrRide1_label_Speed_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Speed_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Speed_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Speed_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_img_Speed
scrRide1_img_Speed = lv.img(scrRide1)
scrRide1_img_Speed.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_average_speed_big_40_31.png"))
scrRide1_img_Speed.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide1_img_Speed.set_pivot(50,50)
scrRide1_img_Speed.set_angle(0)
scrRide1_img_Speed.set_pos(230, 160)
scrRide1_img_Speed.set_size(40, 31)
scrRide1_img_Speed.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_img_Speed, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_img_Speed.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_line_H_Seperator_2
scrRide1_line_H_Seperator_2 = lv.line(scrRide1)
scrRide1_line_H_Seperator_2_line_points = [{"x":0, "y":0},{"x":240, "y":0},]
scrRide1_line_H_Seperator_2.set_points(scrRide1_line_H_Seperator_2_line_points, 2)
scrRide1_line_H_Seperator_2.set_pos(230, 200)
scrRide1_line_H_Seperator_2.set_size(240, 1)
scrRide1_line_H_Seperator_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_line_H_Seperator_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_line_H_Seperator_2.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_line_H_Seperator_2.set_style_line_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_line_H_Seperator_2.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_line_H_Seperator_2.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_img_Eleva_Gain
scrRide1_img_Eleva_Gain = lv.img(scrRide1)
scrRide1_img_Eleva_Gain.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_elevation_gained_22_18.png"))
scrRide1_img_Eleva_Gain.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide1_img_Eleva_Gain.set_pivot(50,50)
scrRide1_img_Eleva_Gain.set_angle(0)
scrRide1_img_Eleva_Gain.set_pos(210, 215)
scrRide1_img_Eleva_Gain.set_size(22, 18)
scrRide1_img_Eleva_Gain.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_img_Eleva_Gain, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_img_Eleva_Gain.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Gain_1
scrRide1_label_Gain_1 = lv.label(scrRide1)
scrRide1_label_Gain_1.set_text("ElevationGained")
scrRide1_label_Gain_1.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Gain_1.set_pos(240, 210)
scrRide1_label_Gain_1.set_size(95, 33)
scrRide1_label_Gain_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Gain_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Gain_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_line_V_Seperator
scrRide1_line_V_Seperator = lv.line(scrRide1)
scrRide1_line_V_Seperator_line_points = [{"x":0, "y":0},{"x":0, "y":80},]
scrRide1_line_V_Seperator.set_points(scrRide1_line_V_Seperator_line_points, 2)
scrRide1_line_V_Seperator.set_pos(340, 200)
scrRide1_line_V_Seperator.set_size(3, 80)
scrRide1_line_V_Seperator.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_line_V_Seperator, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_line_V_Seperator.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_line_V_Seperator.set_style_line_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_line_V_Seperator.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_line_V_Seperator.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Gain_2
scrRide1_label_Gain_2 = lv.label(scrRide1)
scrRide1_label_Gain_2.set_text("25.1")
scrRide1_label_Gain_2.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Gain_2.set_pos(210, 255)
scrRide1_label_Gain_2.set_size(70, 25)
scrRide1_label_Gain_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Gain_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Gain_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Gain_3
scrRide1_label_Gain_3 = lv.label(scrRide1)
scrRide1_label_Gain_3.set_text("m")
scrRide1_label_Gain_3.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Gain_3.set_pos(310, 259)
scrRide1_label_Gain_3.set_size(23, 21)
scrRide1_label_Gain_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Gain_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Gain_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Gain_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Lost_3
scrRide1_label_Lost_3 = lv.label(scrRide1)
scrRide1_label_Lost_3.set_text("m")
scrRide1_label_Lost_3.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Lost_3.set_pos(450, 259)
scrRide1_label_Lost_3.set_size(23, 21)
scrRide1_label_Lost_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Lost_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Lost_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Lost_2
scrRide1_label_Lost_2 = lv.label(scrRide1)
scrRide1_label_Lost_2.set_text("10.2")
scrRide1_label_Lost_2.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Lost_2.set_pos(350, 255)
scrRide1_label_Lost_2.set_size(70, 25)
scrRide1_label_Lost_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Lost_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Lost_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Lost_1
scrRide1_label_Lost_1 = lv.label(scrRide1)
scrRide1_label_Lost_1.set_text("ElevationLost")
scrRide1_label_Lost_1.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Lost_1.set_pos(380, 210)
scrRide1_label_Lost_1.set_size(95, 33)
scrRide1_label_Lost_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Lost_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Lost_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Lost_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_img_Eleva_Lost
scrRide1_img_Eleva_Lost = lv.img(scrRide1)
scrRide1_img_Eleva_Lost.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_elevation_lost_22_18.png"))
scrRide1_img_Eleva_Lost.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide1_img_Eleva_Lost.set_pivot(50,50)
scrRide1_img_Eleva_Lost.set_angle(0)
scrRide1_img_Eleva_Lost.set_pos(350, 215)
scrRide1_img_Eleva_Lost.set_size(22, 18)
scrRide1_img_Eleva_Lost.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_img_Eleva_Lost, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_img_Eleva_Lost.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_chart_Elevation
scrRide1_chart_Elevation = lv.chart(scrRide1)
scrRide1_chart_Elevation.set_type(lv.chart.TYPE.LINE)
scrRide1_chart_Elevation.set_range(lv.chart.AXIS.PRIMARY_Y, 0, 100)
scrRide1_chart_Elevation.set_div_line_count(4, 5)
scrRide1_chart_Elevation.set_point_count(10)
scrRide1_chart_Elevation_series_0 = scrRide1_chart_Elevation.add_series(lv.color_hex(0xff007a), lv.chart.AXIS.PRIMARY_Y)
scrRide1_chart_Elevation.set_next_value(scrRide1_chart_Elevation_series_0, 10)
scrRide1_chart_Elevation.set_next_value(scrRide1_chart_Elevation_series_0, 20)
scrRide1_chart_Elevation.set_next_value(scrRide1_chart_Elevation_series_0, 30)
scrRide1_chart_Elevation.set_next_value(scrRide1_chart_Elevation_series_0, 40)
scrRide1_chart_Elevation.set_next_value(scrRide1_chart_Elevation_series_0, 20)
scrRide1_chart_Elevation.set_next_value(scrRide1_chart_Elevation_series_0, 50)
scrRide1_chart_Elevation.set_next_value(scrRide1_chart_Elevation_series_0, 40)
scrRide1_chart_Elevation.set_next_value(scrRide1_chart_Elevation_series_0, 30)
scrRide1_chart_Elevation.set_next_value(scrRide1_chart_Elevation_series_0, 40)
scrRide1_chart_Elevation.set_next_value(scrRide1_chart_Elevation_series_0, 30)
scrRide1_chart_Elevation.set_pos(35, 75)
scrRide1_chart_Elevation.set_size(161, 144)
scrRide1_chart_Elevation.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_chart_Elevation, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_chart_Elevation.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_chart_Elevation.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_chart_Elevation.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_chart_Elevation.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_chart_Elevation.set_style_border_color(lv.color_hex(0xe8e8e8), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_chart_Elevation.set_style_radius(11, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_chart_Elevation.set_style_line_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_chart_Elevation.set_style_line_color(lv.color_hex(0x161d27), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_chart_Elevation.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_chart_Elevation.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Elev_H
scrRide1_label_Elev_H = lv.label(scrRide1)
scrRide1_label_Elev_H.set_text("5 10 15 20 25 30\n          Km")
scrRide1_label_Elev_H.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Elev_H.set_pos(40, 230)
scrRide1_label_Elev_H.set_size(154, 32)
scrRide1_label_Elev_H.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Elev_H, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Elev_H.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_H.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Elev_V
scrRide1_label_Elev_V = lv.label(scrRide1)
scrRide1_label_Elev_V.set_text("\n50\n\n40\n\n30\n\n20\n\n10")
scrRide1_label_Elev_V.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Elev_V.set_pos(6, 65)
scrRide1_label_Elev_V.set_size(26, 165)
scrRide1_label_Elev_V.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Elev_V, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Elev_V.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_V.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Elev_Title
scrRide1_label_Elev_Title = lv.label(scrRide1)
scrRide1_label_Elev_Title.set_text("Meter")
scrRide1_label_Elev_Title.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Elev_Title.set_pos(6, 45)
scrRide1_label_Elev_Title.set_size(61, 20)
scrRide1_label_Elev_Title.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Elev_Title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Elev_Title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Elev_Title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Eleva_Content
scrRide1_label_Eleva_Content = lv.label(scrRide1)
scrRide1_label_Eleva_Content.set_text("Eleva Graph")
scrRide1_label_Eleva_Content.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Eleva_Content.set_pos(57, 90)
scrRide1_label_Eleva_Content.set_size(120, 17)
scrRide1_label_Eleva_Content.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Eleva_Content, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Eleva_Content.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Content.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Eleva_Num
scrRide1_label_Eleva_Num = lv.label(scrRide1)
scrRide1_label_Eleva_Num.set_text("15.3")
scrRide1_label_Eleva_Num.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Eleva_Num.set_pos(58, 122)
scrRide1_label_Eleva_Num.set_size(60, 16)
scrRide1_label_Eleva_Num.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Eleva_Num, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Eleva_Num.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Num.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide1_label_Eleva_Unit
scrRide1_label_Eleva_Unit = lv.label(scrRide1)
scrRide1_label_Eleva_Unit.set_text("m")
scrRide1_label_Eleva_Unit.set_long_mode(lv.label.LONG.WRAP)
scrRide1_label_Eleva_Unit.set_pos(149, 122)
scrRide1_label_Eleva_Unit.set_size(22, 16)
scrRide1_label_Eleva_Unit.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide1_label_Eleva_Unit, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide1_label_Eleva_Unit.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide1_label_Eleva_Unit.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

scrRide1.update_layout()
# Create scrRide2
scrRide2 = lv.obj()
scrRide2.set_size(480, 320)
scrRide2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2.set_style_bg_color(lv.color_hex(0x161d27), lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_img_Header
scrRide2_img_Header = lv.img(scrRide2)
scrRide2_img_Header.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_header_bg_480_51.png"))
scrRide2_img_Header.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide2_img_Header.set_pivot(50,50)
scrRide2_img_Header.set_angle(0)
scrRide2_img_Header.set_pos(0, 0)
scrRide2_img_Header.set_size(480, 51)
scrRide2_img_Header.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_img_Header, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_img_Header.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Date
scrRide2_label_Date = lv.label(scrRide2)
scrRide2_label_Date.set_text("Aug 19,2023")
scrRide2_label_Date.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Date.set_pos(20, 2)
scrRide2_label_Date.set_size(133, 18)
scrRide2_label_Date.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Date, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Date.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Date.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Title
scrRide2_label_Title = lv.label(scrRide2)
scrRide2_label_Title.set_text("RIDE DETAILS")
scrRide2_label_Title.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Title.set_pos(155, 8)
scrRide2_label_Title.set_size(170, 24)
scrRide2_label_Title.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Time
scrRide2_label_Time = lv.label(scrRide2)
scrRide2_label_Time.set_text("10:28 AM")
scrRide2_label_Time.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Time.set_pos(370, 3)
scrRide2_label_Time.set_size(102, 18)
scrRide2_label_Time.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Time.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_img_GPS_Icon
scrRide2_img_GPS_Icon = lv.img(scrRide2)
scrRide2_img_GPS_Icon.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_gps_arrow_28_48.png"))
scrRide2_img_GPS_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide2_img_GPS_Icon.set_pivot(50,50)
scrRide2_img_GPS_Icon.set_angle(0)
scrRide2_img_GPS_Icon.set_pos(274, 60)
scrRide2_img_GPS_Icon.set_size(28, 48)
scrRide2_img_GPS_Icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_img_GPS_Icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_img_GPS_Icon.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Distance
scrRide2_label_Distance = lv.label(scrRide2)
scrRide2_label_Distance.set_text("3.1")
scrRide2_label_Distance.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Distance.set_pos(329, 49)
scrRide2_label_Distance.set_size(36, 19)
scrRide2_label_Distance.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Distance, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Distance.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Direction
scrRide2_label_Direction = lv.label(scrRide2)
scrRide2_label_Direction.set_text("Turn right to")
scrRide2_label_Direction.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Direction.set_pos(320, 74)
scrRide2_label_Direction.set_size(147, 18)
scrRide2_label_Direction.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Direction, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Direction.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Direction.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Street
scrRide2_label_Street = lv.label(scrRide2)
scrRide2_label_Street.set_text("Ed Bluestein Blvd")
scrRide2_label_Street.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Street.set_pos(288, 97)
scrRide2_label_Street.set_size(184, 17)
scrRide2_label_Street.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Street, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Street.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Street.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_ima_Calories_Icon
scrRide2_ima_Calories_Icon = lv.img(scrRide2)
scrRide2_ima_Calories_Icon.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_calories_burned_19_21.png"))
scrRide2_ima_Calories_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide2_ima_Calories_Icon.set_pivot(50,50)
scrRide2_ima_Calories_Icon.set_angle(0)
scrRide2_ima_Calories_Icon.set_pos(220, 130)
scrRide2_ima_Calories_Icon.set_size(19, 21)
scrRide2_ima_Calories_Icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_ima_Calories_Icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_ima_Calories_Icon.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Calories_1
scrRide2_label_Calories_1 = lv.label(scrRide2)
scrRide2_label_Calories_1.set_text("CaloriesBurned")
scrRide2_label_Calories_1.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Calories_1.set_pos(250, 118)
scrRide2_label_Calories_1.set_size(94, 38)
scrRide2_label_Calories_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Calories_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Calories_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Calories_2
scrRide2_label_Calories_2 = lv.label(scrRide2)
scrRide2_label_Calories_2.set_text("12.7")
scrRide2_label_Calories_2.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Calories_2.set_pos(220, 157)
scrRide2_label_Calories_2.set_size(70, 25)
scrRide2_label_Calories_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Calories_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Calories_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Calories_3
scrRide2_label_Calories_3 = lv.label(scrRide2)
scrRide2_label_Calories_3.set_text("Kcal")
scrRide2_label_Calories_3.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Calories_3.set_pos(293, 157)
scrRide2_label_Calories_3.set_size(57, 20)
scrRide2_label_Calories_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Calories_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Calories_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Calories_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Heart_3
scrRide2_label_Heart_3 = lv.label(scrRide2)
scrRide2_label_Heart_3.set_text("BPM")
scrRide2_label_Heart_3.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Heart_3.set_pos(410, 157)
scrRide2_label_Heart_3.set_size(60, 17)
scrRide2_label_Heart_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Heart_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Heart_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Heart_2
scrRide2_label_Heart_2 = lv.label(scrRide2)
scrRide2_label_Heart_2.set_text("16.1")
scrRide2_label_Heart_2.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Heart_2.set_pos(357, 157)
scrRide2_label_Heart_2.set_size(70, 25)
scrRide2_label_Heart_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Heart_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Heart_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Heart_1
scrRide2_label_Heart_1 = lv.label(scrRide2)
scrRide2_label_Heart_1.set_text("Heart\nRate")
scrRide2_label_Heart_1.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Heart_1.set_pos(387, 118)
scrRide2_label_Heart_1.set_size(87, 41)
scrRide2_label_Heart_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Heart_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Heart_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Heart_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_img_Heart_Icon
scrRide2_img_Heart_Icon = lv.img(scrRide2)
scrRide2_img_Heart_Icon.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_heart_rate_24_21.png"))
scrRide2_img_Heart_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide2_img_Heart_Icon.set_pivot(50,50)
scrRide2_img_Heart_Icon.set_angle(0)
scrRide2_img_Heart_Icon.set_pos(357, 130)
scrRide2_img_Heart_Icon.set_size(24, 21)
scrRide2_img_Heart_Icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_img_Heart_Icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_img_Heart_Icon.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_img_Cadence_Icon
scrRide2_img_Cadence_Icon = lv.img(scrRide2)
scrRide2_img_Cadence_Icon.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_round_per_minute_20_20.png"))
scrRide2_img_Cadence_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide2_img_Cadence_Icon.set_pivot(50,50)
scrRide2_img_Cadence_Icon.set_angle(0)
scrRide2_img_Cadence_Icon.set_pos(220, 193)
scrRide2_img_Cadence_Icon.set_size(20, 20)
scrRide2_img_Cadence_Icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_img_Cadence_Icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_img_Cadence_Icon.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Cadence_1
scrRide2_label_Cadence_1 = lv.label(scrRide2)
scrRide2_label_Cadence_1.set_text("Cadence")
scrRide2_label_Cadence_1.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Cadence_1.set_pos(250, 190)
scrRide2_label_Cadence_1.set_size(94, 38)
scrRide2_label_Cadence_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Cadence_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Cadence_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Cadence_3
scrRide2_label_Cadence_3 = lv.label(scrRide2)
scrRide2_label_Cadence_3.set_text("RPM")
scrRide2_label_Cadence_3.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Cadence_3.set_pos(293, 229)
scrRide2_label_Cadence_3.set_size(57, 20)
scrRide2_label_Cadence_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Cadence_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Cadence_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Cadence_2
scrRide2_label_Cadence_2 = lv.label(scrRide2)
scrRide2_label_Cadence_2.set_text("86")
scrRide2_label_Cadence_2.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Cadence_2.set_pos(220, 229)
scrRide2_label_Cadence_2.set_size(70, 25)
scrRide2_label_Cadence_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Cadence_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Cadence_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Cadence_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_img_Elapsed_Icon
scrRide2_img_Elapsed_Icon = lv.img(scrRide2)
scrRide2_img_Elapsed_Icon.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_icn_elapsed_time_20_25.png"))
scrRide2_img_Elapsed_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide2_img_Elapsed_Icon.set_pivot(50,50)
scrRide2_img_Elapsed_Icon.set_angle(0)
scrRide2_img_Elapsed_Icon.set_pos(357, 193)
scrRide2_img_Elapsed_Icon.set_size(20, 25)
scrRide2_img_Elapsed_Icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_img_Elapsed_Icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_img_Elapsed_Icon.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Elapsed_1
scrRide2_label_Elapsed_1 = lv.label(scrRide2)
scrRide2_label_Elapsed_1.set_text("Elapsed \nTime")
scrRide2_label_Elapsed_1.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Elapsed_1.set_pos(387, 190)
scrRide2_label_Elapsed_1.set_size(85, 35)
scrRide2_label_Elapsed_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Elapsed_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Elapsed_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_text_color(lv.color_hex(0x9e9e9e), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Elapsed_2
scrRide2_label_Elapsed_2 = lv.label(scrRide2)
scrRide2_label_Elapsed_2.set_text("46:28")
scrRide2_label_Elapsed_2.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Elapsed_2.set_pos(357, 229)
scrRide2_label_Elapsed_2.set_size(70, 25)
scrRide2_label_Elapsed_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Elapsed_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Elapsed_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Elapsed_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_line_V_Seperator
scrRide2_line_V_Seperator = lv.line(scrRide2)
scrRide2_line_V_Seperator_line_points = [{"x":0, "y":0},{"x":0, "y":240},]
scrRide2_line_V_Seperator.set_points(scrRide2_line_V_Seperator_line_points, 2)
scrRide2_line_V_Seperator.set_pos(345, 119)
scrRide2_line_V_Seperator.set_size(5, 138)
scrRide2_line_V_Seperator.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_line_V_Seperator, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_line_V_Seperator.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_line_V_Seperator.set_style_line_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_line_V_Seperator.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_line_V_Seperator.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_img_Footer
scrRide2_img_Footer = lv.img(scrRide2)
scrRide2_img_Footer.set_src(load_image(r"C:\LocalData\MCX_EBike\MCX_EBike_480X320_GG160GA\generated\MicroPython\ebike_footer_bg_480_35.png"))
scrRide2_img_Footer.add_flag(lv.obj.FLAG.CLICKABLE)
scrRide2_img_Footer.set_pivot(50,50)
scrRide2_img_Footer.set_angle(0)
scrRide2_img_Footer.set_pos(0, 279)
scrRide2_img_Footer.set_size(480, 35)
scrRide2_img_Footer.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_img_Footer, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_img_Footer.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_line_H_Seperator
scrRide2_line_H_Seperator = lv.line(scrRide2)
scrRide2_line_H_Seperator_line_points = [{"x":0, "y":0},{"x":240, "y":0},]
scrRide2_line_H_Seperator.set_points(scrRide2_line_H_Seperator_line_points, 2)
scrRide2_line_H_Seperator.set_pos(225, 180)
scrRide2_line_H_Seperator.set_size(240, 1)
scrRide2_line_H_Seperator.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_line_H_Seperator, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_line_H_Seperator.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_line_H_Seperator.set_style_line_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_line_H_Seperator.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_line_H_Seperator.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Indicator_L
scrRide2_label_Indicator_L = lv.label(scrRide2)
scrRide2_label_Indicator_L.set_text("")
scrRide2_label_Indicator_L.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Indicator_L.set_pos(181, 301)
scrRide2_label_Indicator_L.set_size(28, 8)
scrRide2_label_Indicator_L.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Indicator_L, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Indicator_L.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_radius(4, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_bg_color(lv.color_hex(0xa8a6ad), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_L.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Indicator_M
scrRide2_label_Indicator_M = lv.label(scrRide2)
scrRide2_label_Indicator_M.set_text("")
scrRide2_label_Indicator_M.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Indicator_M.set_pos(229, 301)
scrRide2_label_Indicator_M.set_size(28, 8)
scrRide2_label_Indicator_M.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Indicator_M, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Indicator_M.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_radius(4, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_bg_color(lv.color_hex(0xa8a6ad), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_M.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Indicator_R
scrRide2_label_Indicator_R = lv.label(scrRide2)
scrRide2_label_Indicator_R.set_text("")
scrRide2_label_Indicator_R.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Indicator_R.set_pos(277, 301)
scrRide2_label_Indicator_R.set_size(28, 8)
scrRide2_label_Indicator_R.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Indicator_R, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Indicator_R.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_radius(4, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_bg_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Indicator_R.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Distance_Unit
scrRide2_label_Distance_Unit = lv.label(scrRide2)
scrRide2_label_Distance_Unit.set_text("KM")
scrRide2_label_Distance_Unit.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Distance_Unit.set_pos(368, 49)
scrRide2_label_Distance_Unit.set_size(48, 19)
scrRide2_label_Distance_Unit.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Distance_Unit, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Distance_Unit.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Distance_Unit.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_arc_Watts
scrRide2_arc_Watts = lv.arc(scrRide2)
scrRide2_arc_Watts.set_mode(lv.arc.MODE.NORMAL)
scrRide2_arc_Watts.set_range(0, 100)
scrRide2_arc_Watts.set_bg_angles(0, 360)
scrRide2_arc_Watts.set_angles(90, 180)
scrRide2_arc_Watts.set_rotation(0)
scrRide2_arc_Watts.set_style_arc_rounded(0,  lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_arc_rounded(0, lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_pos(10, 49)
scrRide2_arc_Watts.set_size(200, 200)
scrRide2_arc_Watts.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_arc_Watts, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_arc_Watts.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_arc_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_arc_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_radius(6, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_pad_top(20, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_pad_bottom(20, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_pad_left(20, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_pad_right(20, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for scrRide2_arc_Watts, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
scrRide2_arc_Watts.set_style_arc_width(2, lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_arc_color(lv.color_hex(0xffffff), lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for scrRide2_arc_Watts, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
scrRide2_arc_Watts.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DEFAULT)
scrRide2_arc_Watts.set_style_pad_all(5, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create scrRide2_label_Watts_Unit
scrRide2_label_Watts_Unit = lv.label(scrRide2)
scrRide2_label_Watts_Unit.set_text("Watts")
scrRide2_label_Watts_Unit.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Watts_Unit.set_pos(74, 147)
scrRide2_label_Watts_Unit.set_size(72, 26)
scrRide2_label_Watts_Unit.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Watts_Unit, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Watts_Unit.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_text_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Unit.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrRide2_label_Watts_Num
scrRide2_label_Watts_Num = lv.label(scrRide2)
scrRide2_label_Watts_Num.set_text("15.7")
scrRide2_label_Watts_Num.set_long_mode(lv.label.LONG.WRAP)
scrRide2_label_Watts_Num.set_pos(90, 119)
scrRide2_label_Watts_Num.set_size(53, 20)
scrRide2_label_Watts_Num.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrRide2_label_Watts_Num, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrRide2_label_Watts_Num.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_text_color(lv.color_hex(0x00ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_text_font(test_font("montserratMedium", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrRide2_label_Watts_Num.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

scrRide2.update_layout()

def scrOverview_event_handler(e):
    code = e.get_code()
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.RIGHT == gestureDir):
        if indev is not None: indev.wait_release()
        lv.scr_load_anim(scrRide1, lv.SCR_LOAD_ANIM.OVER_RIGHT, 10, 10, False)
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.LEFT == gestureDir):
        if indev is not None: indev.wait_release()
        lv.scr_load_anim(scrRide2, lv.SCR_LOAD_ANIM.NONE, 10, 10, False)

scrOverview.add_event_cb(lambda e: scrOverview_event_handler(e), lv.EVENT.ALL, None)

def scrRide1_event_handler(e):
    code = e.get_code()
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.LEFT == gestureDir):
        if indev is not None: indev.wait_release()
        lv.scr_load_anim(scrOverview, lv.SCR_LOAD_ANIM.OVER_LEFT, 10, 10, False)
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.RIGHT == gestureDir):
        if indev is not None: indev.wait_release()
        lv.scr_load_anim(scrRide2, lv.SCR_LOAD_ANIM.NONE, 10, 10, False)

scrRide1.add_event_cb(lambda e: scrRide1_event_handler(e), lv.EVENT.ALL, None)

def scrRide2_event_handler(e):
    code = e.get_code()
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.LEFT == gestureDir):
        if indev is not None: indev.wait_release()
        lv.scr_load_anim(scrRide1, lv.SCR_LOAD_ANIM.NONE, 10, 10, False)
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.RIGHT == gestureDir):
        if indev is not None: indev.wait_release()
        lv.scr_load_anim(scrOverview, lv.SCR_LOAD_ANIM.NONE, 10, 10, False)

scrRide2.add_event_cb(lambda e: scrRide2_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(scrRide2)

while SDL.check():
    time.sleep_ms(5)

