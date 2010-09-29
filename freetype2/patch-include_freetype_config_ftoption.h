--- include/freetype/config/ftoption.h.orig
+++ include/freetype/config/ftoption.h
@@ -93,7 +93,7 @@
   /* This is done to allow FreeType clients to run unmodified, forcing     */
   /* them to display normal gray-level anti-aliased glyphs.                */
   /*                                                                       */
-/* #define FT_CONFIG_OPTION_SUBPIXEL_RENDERING */
+#define FT_CONFIG_OPTION_SUBPIXEL_RENDERING
 
 
   /*************************************************************************/
--- include/freetype/config/ftoption.h.orig	2010-02-05 10:53:35.000000000 +0000
+++ include/freetype/config/ftoption.h	2010-02-05 10:54:29.000000000 +0000
@@ -574,7 +574,7 @@ FT_BEGIN_HEADER
   /*   http://partners.adobe.com/asn/developer/opentype/glyf.html          */
   /*   http://fonts.apple.com/TTRefMan/RM06/Chap6glyf.html                 */
   /*                                                                       */
-#undef TT_CONFIG_OPTION_COMPONENT_OFFSET_SCALED
+#define TT_CONFIG_OPTION_COMPONENT_OFFSET_SCALED
 
 
   /*************************************************************************/
