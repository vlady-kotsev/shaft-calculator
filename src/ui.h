#pragma once
#include <gtk/gtk.h>
#include "core.h"
#include "style.h"

#define W_WIDTH 960
#define W_HEIGHT 400

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

    GtkWidget *result_label_mt_label;
    GtkWidget *result_label_mt;

    GtkWidget *result_label_ft_label;
    GtkWidget *result_label_ft;

    GtkWidget *result_label_fr_label;
    GtkWidget *result_label_fr;

    GtkWidget *result_label_mb_label;
    GtkWidget *result_label_mb;

    GtkWidget *result_label_meq_label;
    GtkWidget *result_label_meq;

    GtkWidget *result_label_d_label;
    GtkWidget *result_label_d;

    GtkWidget *result_label_optimal_d_label;
    GtkWidget *result_label_optimal_d;

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

#define PREPARE_RESULT_FIELD(FIELD, LABEL, W, PARENT_BOX)                                   \
    do                                                                                      \
    {                                                                                       \
        GtkWidget *result_label_box_##FIELD = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);     \
        gtk_widget_set_hexpand(result_label_box_##FIELD, TRUE);                             \
        gtk_widget_add_css_class(result_label_box_##FIELD, "result-box");                   \
        W->result_label_##FIELD##_label = gtk_label_new(LABEL);                             \
        gtk_widget_set_halign(W->result_label_##FIELD##_label, GTK_ALIGN_CENTER);           \
        W->result_label_##FIELD = gtk_label_new("0");                                       \
        gtk_widget_set_halign(W->result_label_##FIELD, GTK_ALIGN_CENTER);                   \
        gtk_label_set_xalign(GTK_LABEL(W->result_label_##FIELD), 0.5);                      \
                                                                                            \
        gtk_box_append(GTK_BOX(result_label_box_##FIELD), W->result_label_##FIELD##_label); \
        gtk_box_append(GTK_BOX(result_label_box_##FIELD), W->result_label_##FIELD);         \
        gtk_box_append(GTK_BOX(PARENT_BOX), result_label_box_##FIELD);                      \
    } while (false)

#define SET_RESULT(FIELD, W, RES)                                    \
    do                                                               \
    {                                                                \
        char *msg = g_strdup_printf("%g", RES);                      \
        gtk_label_set_text(GTK_LABEL(W->result_label_##FIELD), msg); \
        g_free(msg);                                                 \
    } while (false)
