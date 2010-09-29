--- src/cairo-types-private.h.orig	2008-09-25 22:29:06.000000000 +0200
+++ src/cairo-types-private.h	2008-10-14 15:01:37.000000000 +0200
@@ -113,9 +113,35 @@
     cairo_bool_t is_snapshot;
 };
 
+
+/**
+ * cairo_lcd_filter_t:
+ * @CAIRO_LCD_FILTER_DEFAULT: Use the default LCD filter for
+ *   font backend and target device
+ * @CAIRO_LCD_FILTER_NONE: Do not perform LCD filtering
+ * @CAIRO_LCD_FILTER_INTRA_PIXEL: Intra-pixel filter
+ * @CAIRO_LCD_FILTER_FIR3: FIR filter with a 3x3 kernel
+ * @CAIRO_LCD_FILTER_FIR5: FIR filter with a 5x5 kernel
+ *
+ * The LCD filter specifies the low-pass filter applied to LCD-optimized
+ * bitmaps generated with an antialiasing mode of %CAIRO_ANTIALIAS_SUBPIXEL.
+ *
+ * Note: This API was temporarily made available in the public
+ * interface during the 1.7.x development series, but was made private
+ * before 1.8.
+ **/
+typedef enum _cairo_lcd_filter {
+    CAIRO_LCD_FILTER_DEFAULT,
+    CAIRO_LCD_FILTER_NONE,
+    CAIRO_LCD_FILTER_INTRA_PIXEL,
+    CAIRO_LCD_FILTER_FIR3,
+    CAIRO_LCD_FILTER_FIR5
+} cairo_lcd_filter_t;
+
 struct _cairo_font_options {
     cairo_antialias_t antialias;
     cairo_subpixel_order_t subpixel_order;
+    cairo_lcd_filter_t lcd_filter;
     cairo_hint_style_t hint_style;
     cairo_hint_metrics_t hint_metrics;
 };
