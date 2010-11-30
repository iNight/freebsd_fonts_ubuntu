--- src/cairo-type1-subset.c	2010-10-25 00:48:41.226430002 +0200
+++ src/cairo-type1-subset.c	2010-10-25 00:48:26.236429991 +0200
@@ -69,8 +69,8 @@
 	unsigned int font_id;
 	char *base_font;
 	unsigned int num_glyphs;
-	long x_min, y_min, x_max, y_max;
-	long ascent, descent;
+	double x_min, y_min, x_max, y_max;
+	double ascent, descent;
 
 	const char    *data;
 	unsigned long  header_size;
@@ -146,12 +146,12 @@
     memset (font, 0, sizeof (*font));
     font->base.unscaled_font = _cairo_unscaled_font_reference (unscaled_font);
     font->base.num_glyphs = face->num_glyphs;
-    font->base.x_min = face->bbox.xMin;
-    font->base.y_min = face->bbox.yMin;
-    font->base.x_max = face->bbox.xMax;
-    font->base.y_max = face->bbox.yMax;
-    font->base.ascent = face->ascender;
-    font->base.descent = face->descender;
+    font->base.x_min = face->bbox.xMin / (double)face->units_per_EM;
+    font->base.y_min = face->bbox.yMin / (double)face->units_per_EM;
+    font->base.x_max = face->bbox.xMax / (double)face->units_per_EM;
+    font->base.y_max = face->bbox.yMax / (double)face->units_per_EM;
+    font->base.ascent = face->ascender / (double)face->units_per_EM;
+    font->base.descent = face->descender / (double)face->units_per_EM;
 
     if (face->family_name) {
 	font->base.base_font = strdup (face->family_name);
@@ -566,7 +566,7 @@
 	    return CAIRO_INT_STATUS_UNSUPPORTED;
 	}
 
-	font->glyphs[i].width = font->face->glyph->linearHoriAdvance / 65536.0; /* 16.16 format */
+	font->glyphs[i].width = font->face->glyph->metrics.horiAdvance / (double)font->face->units_per_EM;
 
 	error = FT_Get_Glyph_Name(font->face, i, buffer, sizeof buffer);
 	if (error != FT_Err_Ok) {
