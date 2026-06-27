#include "ui.h"

Sigmadop sigma_from_index(guint index)
{
    switch (index)
    {
    case 0:
        return _C35;
    case 1:
        return _C45;
    case 2:
        return _40Cr;
    case 3:
        return _42CrMo4;
    default:
        return _C35;
    }
}

static void
on_request_calc(GtkEditable *editable, gpointer user_data)
{
    AppWidgets *w = user_data;

    const char *p_kw_text = gtk_editable_get_text(GTK_EDITABLE(w->entry_p_kw));
    const char *n_rpm_text = gtk_editable_get_text(GTK_EDITABLE(w->entry_n_rpm));

    const char *gear_x_text = gtk_editable_get_text(GTK_EDITABLE(w->entry_gear_x));
    const char *gear_d_text = gtk_editable_get_text(GTK_EDITABLE(w->entry_gear_d));

    const char *alpha_text = gtk_editable_get_text(GTK_EDITABLE(w->entry_alpha));
    const char *a_x_text = gtk_editable_get_text(GTK_EDITABLE(w->entry_a_x));
    const char *b_x_text = gtk_editable_get_text(GTK_EDITABLE(w->entry_b_x));

    char *end_p_kw, *end_n_rpm, *end_gear_x, *end_gear_d, *end_alpha, *end_a_x, *end_b_x;
    double p_kw = strtod(p_kw_text, &end_p_kw);
    double n_rpm = strtod(n_rpm_text, &end_n_rpm);

    double gear_x = strtod(gear_x_text, &end_gear_x);
    double gear_d = strtod(gear_d_text, &end_gear_d);

    double alpha = strtod(alpha_text, &end_alpha);
    double a_x = strtod(a_x_text, &end_a_x);
    double b_x = strtod(b_x_text, &end_b_x);

    if (*p_kw_text == '\0')
    {
        p_kw = 0;
    }

    if (*n_rpm_text == '\0')
    {
        n_rpm = 0;
    }

    if (*gear_x_text == '\0')
    {
        gear_x = 0;
    }

    if (*gear_d_text == '\0')
    {
        gear_d = 0;
    }

    if (*alpha_text == '\0')
    {
        alpha = 0;
    }

    if (*a_x_text == '\0')
    {
        a_x = 0;
    }

    if (*b_x_text == '\0')
    {
        b_x = 0;
    }

    guint selected_material = gtk_drop_down_get_selected(GTK_DROP_DOWN(w->dd_material));
    Sigmadop sigmadop = sigma_from_index(selected_material);
    ShaftResult result;
    calculate_shaft(p_kw, n_rpm, sigmadop, gear_x, gear_d, alpha, a_x, b_x, &result);

    SET_RESULT(mt, w, result.mt);
    SET_RESULT(ft, w, result.ft);
    SET_RESULT(fr, w, result.fr);
    SET_RESULT(mb, w, result.mb);
    SET_RESULT(meq, w, result.meq);
    SET_RESULT(d, w, result.min_d);
    SET_RESULT(optimal_d, w, result.optimal_d);
}

void on_activate(GtkApplication *app, gpointer user_data)
{
    AppWidgets *w = g_new0(AppWidgets, 1);

    w->provider = gtk_css_provider_new();

    gtk_css_provider_load_from_string(w->provider, EMBEDDED_CSS_STYLE);

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(w->provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), APP_NAME);
    gtk_window_set_default_size(GTK_WINDOW(window), W_WIDTH, W_HEIGHT);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_widget_set_margin_top(box, 12);
    gtk_widget_set_margin_bottom(box, 12);
    gtk_widget_set_margin_start(box, 12);
    gtk_widget_set_margin_end(box, 12);
    gtk_window_set_child(GTK_WINDOW(window), box);

    w->title_label = gtk_label_new(APP_NAME);
    gtk_box_append(GTK_BOX(box), w->title_label);

    GtkWidget *input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_widget_set_margin_top(input_box, 12);
    gtk_widget_set_margin_bottom(input_box, 12);

    GtkWidget *left_input_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    PREPARE_INPUT_FIELD(p_kw, "Предавана мощност P [kW]", w, left_input_box);
    PREPARE_INPUT_FIELD(n_rpm, "Обороти n [min⁻¹]", w, left_input_box);
    PREPARE_INPUT_FIELD(gear_x, "Зъбно колело позиция [mm]", w, left_input_box);
    PREPARE_INPUT_FIELD(gear_d, "Делителен диаметър d [mm]", w, left_input_box);

    GtkWidget *right_input_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    PREPARE_INPUT_FIELD(alpha, "Ъгъл на натиск α [°]", w, right_input_box);
    PREPARE_INPUT_FIELD(a_x, "Лагер A позиция [mm]", w, right_input_box);
    PREPARE_INPUT_FIELD(b_x, "Лагер B позиция [mm]", w, right_input_box);

    GtkWidget *material_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    static const char *material_names[] = {
        "C35", "C45", "40Cr", "42CrMo4", NULL};
    w->label_material = gtk_label_new("Материал");
    w->dd_material = gtk_drop_down_new_from_strings(material_names);

    gtk_box_append(GTK_BOX(material_box), w->label_material);
    gtk_box_append(GTK_BOX(material_box), w->dd_material);
    gtk_box_append(GTK_BOX(right_input_box), material_box);

    gtk_box_append(GTK_BOX(input_box), left_input_box);
    gtk_box_append(GTK_BOX(input_box), right_input_box);

    gtk_box_append(GTK_BOX(box), input_box);

    w->button = gtk_button_new_with_label("Calculate");
    gtk_box_append(GTK_BOX(box), w->button);

    GtkWidget *left_output_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_widget_set_halign(left_output_box, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(left_output_box, TRUE);
    gtk_widget_set_margin_start(left_output_box, 12);
    gtk_widget_set_margin_end(left_output_box, 12);

    GtkWidget *right_output_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_widget_set_halign(right_output_box, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(right_output_box, TRUE);
    gtk_widget_set_margin_start(right_output_box, 12);
    gtk_widget_set_margin_end(right_output_box, 12);

    w->result_label = gtk_label_new("==Results==");
    gtk_box_append(GTK_BOX(box), w->result_label);
    GtkWidget *output_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_widget_set_margin_top(output_box, 20);

    gtk_box_append(GTK_BOX(output_box), left_output_box);
    gtk_box_append(GTK_BOX(output_box), right_output_box);

    PREPARE_RESULT_FIELD(mt, "Въртящ момент[N.m]", w, left_output_box);
    PREPARE_RESULT_FIELD(ft, "Тангенциална сила[N]", w, left_output_box);
    PREPARE_RESULT_FIELD(fr, "Радиална сила[N]", w, left_output_box);
    PREPARE_RESULT_FIELD(mb, "Огъващ момент[N.mm]", w, left_output_box);
    PREPARE_RESULT_FIELD(meq, "Еквивалентен момент[N.mm]", w, right_output_box);

    PREPARE_RESULT_FIELD(d, "Минимален диаметър[mm]", w, right_output_box);
    PREPARE_RESULT_FIELD(optimal_d, "Препоръчителен стандартен диаметър[mm]", w, right_output_box);

    gtk_box_append(GTK_BOX(box), output_box);

    g_signal_connect(w->button, "clicked", G_CALLBACK(on_request_calc), w);

    g_signal_connect_swapped(window, "destroy", G_CALLBACK(g_free), w);

    gtk_window_present(GTK_WINDOW(window));
}