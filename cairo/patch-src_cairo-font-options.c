--- src/cairo-font-options.c.orig	2008-09-25 22:30:14.000000000 +0200
+++ src/cairo-font-options.c	2008-10-14 15:01:37.000000000 +0200
@@ -39,6 +39,7 @@
 static const cairo_font_options_t _cairo_font_options_nil = {
     CAIRO_ANTIALIAS_DEFAULT,
     CAIRO_SUBPIXEL_ORDER_DEFAULT,
+    CAIRO_LCD_FILTER_DEFAULT,
     CAIRO_HINT_STYLE_DEFAULT,
     CAIRO_HINT_METRICS_DEFAULT
 };
@@ -54,6 +55,7 @@
 {
     options->antialias = CAIRO_ANTIALIAS_DEFAULT;
     options->subpixel_order = CAIRO_SUBPIXEL_ORDER_DEFAULT;
+    options->lcd_filter = CAIRO_LCD_FILTER_DEFAULT;
     options->hint_style = CAIRO_HINT_STYLE_DEFAULT;
     options->hint_metrics = CAIRO_HINT_METRICS_DEFAULT;
 }
@@ -64,6 +66,7 @@
 {
     options->antialias = other->antialias;
     options->subpixel_order = other->subpixel_order;
+    options->lcd_filter = other->lcd_filter;
     options->hint_style = other->hint_style;
     options->hint_metrics = other->hint_metrics;
 }
@@ -189,6 +192,8 @@
 	options->antialias = other->antialias;
     if (other->subpixel_order != CAIRO_SUBPIXEL_ORDER_DEFAULT)
 	options->subpixel_order = other->subpixel_order;
+    if (other->lcd_filter != CAIRO_LCD_FILTER_DEFAULT)
+	options->lcd_filter = other->lcd_filter;
     if (other->hint_style != CAIRO_HINT_STYLE_DEFAULT)
 	options->hint_style = other->hint_style;
     if (other->hint_metrics != CAIRO_HINT_METRICS_DEFAULT)
@@ -221,6 +226,7 @@
 
     return (options->antialias == other->antialias &&
 	    options->subpixel_order == other->subpixel_order &&
+	    options->lcd_filter == other->lcd_filter &&
 	    options->hint_style == other->hint_style &&
 	    options->hint_metrics == other->hint_metrics);
 }
@@ -246,7 +252,8 @@
 
     return ((options->antialias) |
 	    (options->subpixel_order << 4) |
-	    (options->hint_style << 8) |
+	    (options->lcd_filter << 8) |
+	    (options->hint_style << 12) |
 	    (options->hint_metrics << 16));
 }
 slim_hidden_def (cairo_font_options_hash);
@@ -328,6 +335,48 @@
 }
 
 /**
+ * _cairo_font_options_set_lcd_filter:
+ * @options: a #cairo_font_options_t
+ * @lcd_filter: the new LCD filter
+ *
+ * Sets the LCD filter for the font options object. The LCD filter
+ * specifies how pixels are filtered when rendered with an antialiasing
+ * mode of %CAIRO_ANTIALIAS_SUBPIXEL. See the documentation for
+ * #cairo_lcd_filter_t for full details.
+ *
+ * Since: 1.8
+ **/
+void
+_cairo_font_options_set_lcd_filter (cairo_font_options_t *options,
+				    cairo_lcd_filter_t    lcd_filter)
+{
+    if (cairo_font_options_status (options))
+	return;
+
+    options->lcd_filter = lcd_filter;
+}
+
+/**
+ * _cairo_font_options_get_lcd_filter:
+ * @options: a #cairo_font_options_t
+ *
+ * Gets the LCD filter for the font options object.
+ * See the documentation for #cairo_lcd_filter_t for full details.
+ *
+ * Return value: the LCD filter for the font options object
+ *
+ * Since: 1.8
+ **/
+cairo_lcd_filter_t
+_cairo_font_options_get_lcd_filter (const cairo_font_options_t *options)
+{
+    if (cairo_font_options_status ((cairo_font_options_t *) options))
+	return CAIRO_LCD_FILTER_DEFAULT;
+
+    return options->lcd_filter;
+}
+
+/**
  * cairo_font_options_set_hint_style:
  * @options: a #cairo_font_options_t
  * @hint_style: the new hint style
