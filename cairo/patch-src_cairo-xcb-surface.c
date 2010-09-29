--- src/cairo-xcb-surface.c.orig	2008-12-14 06:01:40.000000000 -0500
+++ src/cairo-xcb-surface.c	2009-02-12 02:37:51.000000000 -0500
@@ -844,8 +844,11 @@
     case CAIRO_EXTEND_REPEAT:
 	_cairo_xcb_surface_set_repeat (surface, 1);
 	break;
-    case CAIRO_EXTEND_REFLECT:
     case CAIRO_EXTEND_PAD:
+	_cairo_xcb_surface_set_repeat (surface, 2);
+	break;
+    case CAIRO_EXTEND_REFLECT:
+    default:
 	return CAIRO_INT_STATUS_UNSUPPORTED;
     }
 
