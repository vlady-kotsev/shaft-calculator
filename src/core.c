#include "core.h"

void calculate_shaft(double p_kw, double n_rpm, Sigmadop material, double gear_x, double gear_d, double alpha, double a_x, double b_x, ShaftResult *result)
{
    double mt = 9550 * p_kw / n_rpm;
    double mt_nmm = mt * 1000;

    double ft = 2 * mt_nmm / gear_d;

    double fr = ft * tan(alpha * M_PI / 180.0);

    double span = b_x - a_x;
    double rbv = ft * (gear_x - a_x) / span;
    double rav = ft - rbv;

    double rbh = fr * (gear_x - a_x) / span;
    double rah = fr - rbh;

    double mv = rav * (gear_x - a_x);
    double mh = rah * (gear_x - a_x);

    double mb = sqrt(pow(mv, 2) + pow(mh, 2));

    double meq = sqrt(pow(mb, 2) + 0.75 * pow(mt_nmm, 2));

    double d = pow((32 * meq) / (M_PI * material), 1.0 / 3.0);

    double optimal_d = ceil(d / 5.0) * 5;

    *result = (ShaftResult){
        .mt = mt,
        .ft = ft,
        .fr = fr,
        .mb = mb,
        .meq = meq,
        .min_d = d,
        .optimal_d = optimal_d
    };
}
