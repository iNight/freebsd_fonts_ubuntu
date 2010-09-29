--- src/xftint.h.orig
+++ src/xftint.h
@@ -145,6 +145,7 @@
     FcBool		antialias;	/* doing antialiasing */
     FcBool		embolden;	/* force emboldening */
     int			rgba;		/* subpixel order */
+    int			lcd_filter;	/* lcd filter */
     FT_Matrix		matrix;		/* glyph transformation matrix */
     FcBool		transform;	/* non-identify matrix? */
     FT_Int		load_flags;	/* glyph load flags */
