--- src/cairo-surface.c.orig	2008-09-25 22:28:56.000000000 +0200
+++ src/cairo-surface.c	2008-10-14 15:01:37.000000000 +0200
@@ -73,6 +73,7 @@
     FALSE,				/* has_font_options */	\
     { CAIRO_ANTIALIAS_DEFAULT,		/* antialias */		\
       CAIRO_SUBPIXEL_ORDER_DEFAULT,	/* subpixel_order */	\
+      CAIRO_LCD_FILTER_DEFAULT,		/* lcd_filter */	\
       CAIRO_HINT_STYLE_DEFAULT,		/* hint_style */	\
       CAIRO_HINT_METRICS_DEFAULT	/* hint_metrics */	\
     }					/* font_options */	\
