--- src/cairo-mutex.c.orig	2008-09-25 13:36:35.000000000 +0200
+++ src/cairo-mutex.c	2008-10-14 14:22:45.000000000 +0200
@@ -35,7 +35,7 @@
 
 #include "cairo-mutex-private.h"
 
-#define CAIRO_MUTEX_DECLARE(mutex) cairo_mutex_t mutex = CAIRO_MUTEX_NIL_INITIALIZER;
+#define CAIRO_MUTEX_DECLARE(mutex) cairo_private cairo_mutex_t mutex = CAIRO_MUTEX_NIL_INITIALIZER;
 #include "cairo-mutex-list-private.h"
 #undef   CAIRO_MUTEX_DECLARE
