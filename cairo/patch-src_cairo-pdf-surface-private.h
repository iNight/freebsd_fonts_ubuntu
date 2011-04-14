--- src/cairo-pdf-surface-private.h
+++ src/cairo-pdf-surface-private.h
@@ -68,6 +68,7 @@
     cairo_hash_entry_t base;
     unsigned int id;
     cairo_bool_t interpolate;
+    cairo_bool_t mask;
     cairo_pdf_resource_t surface_res;
     int width;
     int height;
