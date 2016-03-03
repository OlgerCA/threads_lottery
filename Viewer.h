/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * viewer.h
 * Copyright (C) 2016 Wil C <wilz04@gmail.com>
 */

#ifndef _VIEWER_
#define _VIEWER_

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define VIEWER_TYPE_APPLICATION             (viewer_get_type())
#define VIEWER_APPLICATION(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), VIEWER_TYPE_APPLICATION, Viewer))
#define VIEWER_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass),  VIEWER_TYPE_APPLICATION, ViewerClass))
#define VIEWER_IS_APPLICATION(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), VIEWER_TYPE_APPLICATION))
#define VIEWER_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass),  VIEWER_TYPE_APPLICATION))
#define VIEWER_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj),  VIEWER_TYPE_APPLICATION, ViewerClass))

typedef struct _ViewerClass ViewerClass;
typedef struct _Viewer Viewer;
typedef struct _ViewerPrivate ViewerPrivate;

struct _ViewerClass {
	GtkApplicationClass parent_class;
};

struct _Viewer {
	GtkApplication parent_instance;

	ViewerPrivate* priv;
};

GType viewer_get_type (void) G_GNUC_CONST;
Viewer* viewer_new(void);

/* Callbacks */

G_END_DECLS

#endif /* _APPLICATION_H_ */
