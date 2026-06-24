#pragma once
#include <gtk/gtk.h>
#include "core.h"

typedef struct
{
    GtkCssProvider *provider;
    GtkWidget *title_label;

    // Inputs
    GtkWidget *entry_p_kw;
    GtkWidget *label_p_kw;

    GtkWidget *entry_n_rpm;
    GtkWidget *label_n_rpm;

    GtkWidget *entry_gear_x;
    GtkWidget *label_gear_x;

    GtkWidget *entry_gear_d;
    GtkWidget *label_gear_d;

    GtkWidget *entry_alpha;
    GtkWidget *label_alpha;

    GtkWidget *entry_a_x;
    GtkWidget *label_a_x;

    GtkWidget *entry_b_x;
    GtkWidget *label_b_x;

    GtkWidget *label_material;
    GtkWidget *dd_material;

    // Outputs
    GtkWidget *result_label;
    GtkWidget *result_label_mv;
    GtkWidget *result_label_mh;
    GtkWidget *result_label_mb;
    GtkWidget *result_label_meq;
    GtkWidget *result_label_d;

    GtkWidget *button;
} AppWidgets;

void on_activate(GtkApplication *app, gpointer user_data);

#define PREPARE_INPUT_FIELD(FIELD, LABEL, W, PARENT_BOX)                    \
    do                                                                      \
    {                                                                       \
        GtkWidget *FIELD##_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);  \
        W->label_##FIELD = gtk_label_new(LABEL);                            \
        gtk_box_append(GTK_BOX(FIELD##_box), W->label_##FIELD);             \
        W->entry_##FIELD = gtk_entry_new();                                 \
        gtk_widget_set_hexpand(W->entry_##FIELD, TRUE);                     \
        gtk_entry_set_placeholder_text(GTK_ENTRY(W->entry_##FIELD), LABEL); \
        gtk_box_append(GTK_BOX(FIELD##_box), W->entry_##FIELD);             \
        gtk_box_append(GTK_BOX(PARENT_BOX), FIELD##_box);                   \
    } while (false)

#define PREPARE_RESULT_FIELD(FIELD, LABEL, W, PARENT_BOX)             \
    do                                                                \
    {                                                                 \
        W->result_label_##FIELD = gtk_label_new(LABEL ": 0");         \
        gtk_label_set_xalign(GTK_LABEL(W->result_label_##FIELD), 0);  \
        gtk_widget_set_hexpand(W->result_label_##FIELD, TRUE);        \
        gtk_box_append(GTK_BOX(PARENT_BOX), W->result_label_##FIELD); \
    } while (false)

#define SET_RESULT(FIELD, LABEL, W, RES)                             \
    do                                                               \
    {                                                                \
        char *msg = g_strdup_printf(LABEL ": %g", RES);              \
        gtk_label_set_text(GTK_LABEL(W->result_label_##FIELD), msg); \
        g_free(msg);                                                 \
    } while (false)
