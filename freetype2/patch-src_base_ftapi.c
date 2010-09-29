--- src/base/ftapi.c.orig
+++ src/base/ftapi.c
@@ -118,4 +118,18 @@
   }
 
 
+  FT_BASE_DEF( FT_Short )
+  FT_Get_Short( FT_Stream stream )
+  {
+    return FT_GET_SHORT();
+  }
+
+
+  FT_BASE_DEF( FT_Long )
+  FT_Get_Long( FT_Stream stream )
+  {
+    return FT_GET_LONG();
+  }
+
+
 /* END */
