--- src/cairo-xlib-screen.c.orig	2008-09-25 22:29:39.000000000 +0200
+++ src/cairo-xlib-screen.c	2008-10-14 15:01:37.000000000 +0200
@@ -150,13 +150,22 @@
     cairo_bool_t xft_antialias;
     int xft_hintstyle;
     int xft_rgba;
+    int xft_lcdfilter;
     cairo_antialias_t antialias;
     cairo_subpixel_order_t subpixel_order;
+    cairo_lcd_filter_t lcd_filter;
     cairo_hint_style_t hint_style;
 
     if (!get_boolean_default (dpy, "antialias", &xft_antialias))
 	xft_antialias = TRUE;
 
+    if (!get_integer_default (dpy, "lcdfilter", &xft_lcdfilter)) {
+	/* -1 is an non-existant Fontconfig constant used to differentiate
+	 * the case when no lcdfilter property is available.
+	 */
+	xft_lcdfilter = -1;
+    }
+
     if (!get_boolean_default (dpy, "hinting", &xft_hinting))
 	xft_hinting = TRUE;
 
@@ -239,6 +248,24 @@
 	subpixel_order = CAIRO_SUBPIXEL_ORDER_DEFAULT;
     }
 
+    switch (xft_lcdfilter) {
+    case FC_LCD_NONE:
+	lcd_filter = CAIRO_LCD_FILTER_NONE;
+	break;
+    case FC_LCD_DEFAULT:
+	lcd_filter = CAIRO_LCD_FILTER_FIR5;
+	break;
+    case FC_LCD_LIGHT:
+	lcd_filter = CAIRO_LCD_FILTER_FIR3;
+	break;
+    case FC_LCD_LEGACY:
+	lcd_filter = CAIRO_LCD_FILTER_INTRA_PIXEL;
+	break;
+    default:
+	lcd_filter = CAIRO_LCD_FILTER_DEFAULT;
+	break;
+    }
+
     if (xft_antialias) {
 	if (subpixel_order == CAIRO_SUBPIXEL_ORDER_DEFAULT)
 	    antialias = CAIRO_ANTIALIAS_GRAY;
@@ -251,6 +278,7 @@
     cairo_font_options_set_hint_style (&info->font_options, hint_style);
     cairo_font_options_set_antialias (&info->font_options, antialias);
     cairo_font_options_set_subpixel_order (&info->font_options, subpixel_order);
+    _cairo_font_options_set_lcd_filter (&info->font_options, lcd_filter);
     cairo_font_options_set_hint_metrics (&info->font_options, CAIRO_HINT_METRICS_ON);
 }
 
