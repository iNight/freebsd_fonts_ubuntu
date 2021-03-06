--- src/cairo-pdf-surface.c
+++ src/cairo-pdf-surface.c
@@ -1129,6 +1129,7 @@ static cairo_status_t
 _cairo_pdf_surface_add_source_surface (cairo_pdf_surface_t	*surface,
 				       cairo_surface_t		*source,
 				       cairo_filter_t		 filter,
+				       cairo_bool_t              mask,
 				       cairo_pdf_resource_t	*surface_res,
 				       int                      *width,
 				       int                      *height)
@@ -1171,6 +1172,7 @@ _cairo_pdf_surface_add_source_surface (c
 
     surface_entry->id = surface_key.id;
     surface_entry->interpolate = interpolate;
+    surface_entry->mask = mask;
     _cairo_pdf_source_surface_init_key (surface_entry);
 
     src_surface.hash_entry = surface_entry;
@@ -1764,6 +1766,46 @@ _cairo_pdf_surface_supports_fine_grained
     return TRUE;
 }
 
+static cairo_status_t
+_cairo_pdf_surface_emit_imagemask (cairo_pdf_surface_t	 *surface,
+				   cairo_image_surface_t *image,
+				   cairo_pdf_resource_t	 *image_res)
+{
+    cairo_status_t status;
+    uint8_t *byte, output_byte;
+    int row, col, num_cols;
+
+
+    /* This is the only image format supported for stencil masking */
+    assert (image->format == CAIRO_FORMAT_A1);
+
+    status = _cairo_pdf_surface_open_stream (surface,
+					     image_res,
+					     TRUE,
+					     "   /Type /XObject\n"
+					     "   /Subtype /Image\n"
+					     "   /ImageMask true\n"
+					     "   /Width %d\n"
+					     "   /Height %d\n"
+					     "   /BitsPerComponent 1\n",
+					     image->width, image->height);
+    if (unlikely (status))
+	return status;
+
+    num_cols = (image->width + 7) / 8;
+    for (row = 0; row < image->height; row++) {
+	byte = image->data + row * image->stride;
+	for (col = 0; col < num_cols; col++) {
+	    output_byte = CAIRO_BITSWAP8_IF_LITTLE_ENDIAN (*byte);
+	    output_byte = ~output_byte;
+	    _cairo_output_stream_write (surface->output, &output_byte, 1);
+	    byte++;
+	}
+    }
+
+    return _cairo_pdf_surface_close_stream (surface);
+}
+
 /* Emit alpha channel from the image into the given data, providing
  * an id that can be used to reference the resulting SMask object.
  *
@@ -1872,7 +1914,8 @@ static cairo_status_t
 _cairo_pdf_surface_emit_image (cairo_pdf_surface_t     *surface,
                                cairo_image_surface_t   *image,
                                cairo_pdf_resource_t    *image_res,
-			       cairo_filter_t           filter)
+			       cairo_filter_t           filter,
+			       cairo_bool_t             mask)
 {
     cairo_status_t status = CAIRO_STATUS_SUCCESS;
     char *rgb;
@@ -1893,6 +1936,9 @@ _cairo_pdf_surface_emit_image (cairo_pdf
 	    image->format == CAIRO_FORMAT_A8 ||
 	    image->format == CAIRO_FORMAT_A1);
 
+    if (mask)
+	return _cairo_pdf_surface_emit_imagemask (surface, image, image_res);
+
     rgb_size = image->height * image->width * 3;
     rgb = _cairo_malloc_abc (image->width, image->height, 3);
     if (unlikely (rgb == NULL)) {
@@ -2089,7 +2135,8 @@ static cairo_status_t
 _cairo_pdf_surface_emit_image_surface (cairo_pdf_surface_t     *surface,
 				       cairo_surface_t         *source,
 				       cairo_pdf_resource_t     resource,
-				       cairo_bool_t 		interpolate)
+				       cairo_bool_t 		interpolate,
+				       cairo_bool_t             mask)
 {
     cairo_image_surface_t *image;
     void *image_extra;
@@ -2108,7 +2155,7 @@ _cairo_pdf_surface_emit_image_surface (c
 	return status;
 
     status = _cairo_pdf_surface_emit_image (surface, image,
-					    &resource, interpolate);
+					    &resource, interpolate, mask);
     if (unlikely (status))
 	goto BAIL;
 
@@ -2199,7 +2246,7 @@ _cairo_pdf_surface_emit_padded_image_sur
     }
 
     status = _cairo_pdf_surface_emit_image (surface, (cairo_image_surface_t *)pad_image,
-                                            resource, interpolate);
+                                            resource, interpolate, FALSE);
     if (unlikely (status))
         goto BAIL;
 
@@ -2358,7 +2405,8 @@ _cairo_pdf_surface_emit_surface (cairo_p
 	return _cairo_pdf_surface_emit_image_surface (surface,
 						      src_surface->surface,
 						      src_surface->hash_entry->surface_res,
-						      src_surface->hash_entry->interpolate);
+						      src_surface->hash_entry->interpolate,
+						      src_surface->hash_entry->mask);
     }
 }
 
@@ -2395,6 +2443,7 @@ _cairo_pdf_surface_emit_surface_pattern
 	status = _cairo_pdf_surface_add_source_surface (surface,
 							pattern->surface,
 							pdf_pattern->pattern->filter,
+							FALSE,
 							&pattern_resource,
 							&pattern_width,
 							&pattern_height);
@@ -3356,7 +3405,8 @@ _cairo_pdf_surface_emit_pattern (cairo_p
 
 static cairo_status_t
 _cairo_pdf_surface_paint_surface_pattern (cairo_pdf_surface_t     *surface,
-					  cairo_surface_pattern_t *source)
+					  cairo_surface_pattern_t *source,
+					  cairo_bool_t             mask)
 {
     cairo_pdf_resource_t surface_res;
     int width, height;
@@ -3367,6 +3417,7 @@ _cairo_pdf_surface_paint_surface_pattern
     status = _cairo_pdf_surface_add_source_surface (surface,
 						    source->surface,
 						    source->base.filter,
+						    mask,
 						    &surface_res,
 						    &width,
 						    &height);
@@ -3401,10 +3452,16 @@ _cairo_pdf_surface_paint_surface_pattern
     if (unlikely (status))
 	return status;
 
-    _cairo_output_stream_printf (surface->output,
-				 "/a%d gs /x%d Do\n",
-				 alpha,
-				 surface_res.id);
+    if (mask) {
+	_cairo_output_stream_printf (surface->output,
+				     "/x%d Do\n",
+				     surface_res.id);
+    } else {
+	_cairo_output_stream_printf (surface->output,
+				     "/a%d gs /x%d Do\n",
+				     alpha,
+				     surface_res.id);
+    }
 
     return _cairo_pdf_surface_add_xobject (surface, surface_res);
 }
@@ -5386,6 +5443,68 @@ _cairo_pdf_surface_start_fallback (cairo
     return _cairo_pdf_surface_open_content_stream (surface, NULL, TRUE);
 }
 
+/* A PDF stencil mask is an A1 mask used with the current color */
+static cairo_int_status_t
+_cairo_pdf_surface_emit_stencil_mask (cairo_pdf_surface_t   *surface,
+				      const cairo_pattern_t *source,
+				      const cairo_pattern_t *mask)
+{
+    cairo_status_t status;
+    cairo_surface_pattern_t *surface_pattern;
+    cairo_image_surface_t  *image;
+    void		   *image_extra;
+    cairo_pdf_resource_t pattern_res = {0};
+
+    if (! (source->type == CAIRO_PATTERN_TYPE_SOLID &&
+	   mask->type == CAIRO_PATTERN_TYPE_SURFACE))
+	return CAIRO_INT_STATUS_UNSUPPORTED;
+
+    surface_pattern = (cairo_surface_pattern_t *) mask;
+    if (surface_pattern->surface->type == CAIRO_SURFACE_TYPE_RECORDING)
+	return CAIRO_INT_STATUS_UNSUPPORTED;
+
+    status = _cairo_surface_acquire_source_image (surface_pattern->surface,
+						  &image,
+						  &image_extra);
+    if (unlikely (status))
+	return status;
+
+    if (image->base.status)
+	return image->base.status;
+
+    if (image->format != CAIRO_FORMAT_A1) {
+	status = CAIRO_INT_STATUS_UNSUPPORTED;
+	goto cleanup;
+    }
+
+    status = _cairo_pdf_surface_select_pattern (surface, source,
+						pattern_res, FALSE);
+    if (unlikely (status))
+	return status;
+
+    status = _cairo_pdf_operators_flush (&surface->pdf_operators);
+    if (unlikely (status))
+	return status;
+
+    _cairo_output_stream_printf (surface->output, "q\n");
+    status = _cairo_pdf_surface_paint_surface_pattern (surface,
+						       (cairo_surface_pattern_t *) surface_pattern,
+						       TRUE);
+    if (unlikely (status))
+	return status;
+
+    _cairo_output_stream_printf (surface->output, "Q\n");
+
+    _cairo_surface_release_source_image (surface_pattern->surface, image, image_extra);
+    status = _cairo_output_stream_get_status (surface->output);
+
+cleanup:
+    _cairo_surface_release_source_image (surface_pattern->surface, image, image_extra);
+
+    return status;
+}
+
+
 static cairo_int_status_t
 _cairo_pdf_surface_paint (void			*abstract_surface,
 			  cairo_operator_t	 op,
@@ -5435,7 +5554,8 @@ _cairo_pdf_surface_paint (void			*abstra
     {
 	_cairo_output_stream_printf (surface->output, "q\n");
 	status = _cairo_pdf_surface_paint_surface_pattern (surface,
-							   (cairo_surface_pattern_t *) source);
+							   (cairo_surface_pattern_t *) source,
+							   FALSE);
 	if (unlikely (status))
 	    return status;
 
@@ -5502,7 +5622,7 @@ _cairo_pdf_surface_paint (void			*abstra
 }
 
 static cairo_int_status_t
-_cairo_pdf_surface_mask	(void			*abstract_surface,
+_cairo_pdf_surface_mask (void			*abstract_surface,
 			 cairo_operator_t	 op,
 			 const cairo_pattern_t	*source,
 			 const cairo_pattern_t	*mask,
@@ -5553,6 +5673,15 @@ _cairo_pdf_surface_mask	(void			*abstrac
     if (unlikely (status))
 	return status;
 
+    status = _cairo_pdf_surface_select_operator (surface, op);
+    if (unlikely (status))
+	return status;
+
+    /* Check if we can use a stencil mask */
+    status = _cairo_pdf_surface_emit_stencil_mask (surface, source, mask);
+    if (status != CAIRO_INT_STATUS_UNSUPPORTED)
+	return status;
+
     group = _cairo_pdf_surface_create_smask_group (surface);
     if (unlikely (group == NULL))
 	return _cairo_error (CAIRO_STATUS_NO_MEMORY);
@@ -5592,10 +5721,6 @@ _cairo_pdf_surface_mask	(void			*abstrac
     if (unlikely (status))
 	return status;
 
-    status = _cairo_pdf_surface_select_operator (surface, op);
-    if (unlikely (status))
-	return status;
-
     _cairo_output_stream_printf (surface->output,
 				 "q /s%d gs /x%d Do Q\n",
 				 group->group_res.id,
@@ -5807,7 +5932,8 @@ _cairo_pdf_surface_fill (void			*abstrac
 	    return status;
 
 	status = _cairo_pdf_surface_paint_surface_pattern (surface,
-							   (cairo_surface_pattern_t *) source);
+							   (cairo_surface_pattern_t *) source,
+							   FALSE);
 	if (unlikely (status))
 	    return status;
 
