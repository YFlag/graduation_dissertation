// copy from scipy.

#include <math.h>
#include <stdio.h> 

int
get_spline_interpolation_weights(double x, int order, double *weights);


int main() {
    // double weights = {1.2, 3.3}; // error!
    double weights[10]; 
    get_spline_interpolation_weights(0.31, 3, weights);
    for (int i = 0; i < 10; i ++)
        printf("%f ", weights[i]);
    printf("\n");
    return 0;
}

int
get_spline_interpolation_weights(double x, int order, double *weights)
{
    int i;
    double y, z, t;

    /* Convert x to the delta to the middle knot. */
    x -= floor(order & 1 ? x : x + 0.5);
    y = x;
    z = 1.0 - x;

    switch (order) {
        case 1:
            /* 0 <= x < 1*/
            weights[0] = 1.0 - x;
            break;
        case 2:
            /* -0.5 < x <= 0.5 */
            weights[1] = 0.75 - x * x;
            /* For weights[0] we'd normally do:
             *
             *   y = 1 + x  # 0.5 < y <= 1.5
             *   yy = 1.5 - y  # yy = 0.5 - x
             *   weights[0] = 0.5 * yy * yy
             *
             * So we set y = 0.5 - x directly instead.
             */
            y = 0.5 - x;
            weights[0] = 0.5 * y * y;
            break;
        case 3:
            /* y = x, 0 <= y < 1 */
            weights[1] = (y * y * (y - 2.0) * 3.0 + 4.0) / 6.0;
            /* z = 1 - x, 0 < z <= 1 */
            weights[2] = (z * z * (z - 2.0) * 3.0 + 4.0) / 6.0;
            /*
             * For weights[0] we would normally do:
             *
             *   y += 1.0  # y = 1.0 + x, 1 <= y < 2
             *   yy = 2.0 - y  # yy = 1 - x
             *   weights[0] = yy * yy * yy / 6.0
             *
             * But we already have yy in z.
             */
            weights[0] = z * z * z / 6.0;
            break;
        case 4:
            /* -0.5 < x <= 0.5 */
            t = x * x;
            weights[2] = t * (t * 0.25 - 0.625) + 115.0 / 192.0;
            /* y = 1 + x, 0.5 < y <= 1.5 */
            y = 1.0 + x;
            weights[1] = y * (y * (y * (5.0 - y) / 6.0 - 1.25) + 5.0 / 24.0) +
                         55.0 / 96.0;
            /* z = 1 - x, 0.5 <= z < 1.5 */
            weights[3] = z * (z * (z * (5.0 - z) / 6.0 - 1.25) + 5.0 / 24.0) +
                         55.0 / 96.0;
            /*
             * For weights[0] we would normally do:
             *
             *   y += 1.0  # y = 2.0 + x, 1.5 <= y < 2.5
             *   yy = 2.5 - y  # yy = 0.5 - x
             *  weights[0] = yy**4 / 24.0
             *
             * So we set y = 0.5 - x directly instead.
             */
            y = 0.5 - x;
            t = y * y;
            weights[0] = t * t / 24.0;
            break;
        case 5:
            /* y = x, 0 <= y < 1 */
            t = y * y;
            weights[2] = t * (t * (0.25 - y / 12.0) - 0.5) + 0.55;
            /* z = 1 - x, 0 < z <= 1 */
            t = z * z;
            weights[3] = t * (t * (0.25 - z / 12.0) - 0.5) + 0.55;
            /* y = 1 + x, 1 <= y < 2 */
            y += 1.0;
            weights[1] = y * (y * (y * (y * (y / 24.0 - 0.375) + 1.25) - 1.75)
                              + 0.625) + 0.425;
            /* z = 2 - x, 1 < z <= 2 */
            z += 1.0;
            weights[4] = z * (z * (z * (z * (z / 24.0 - 0.375) + 1.25) - 1.75)
                              + 0.625) + 0.425;
            /* For weights[0] we would normally do:
             *
             *   y += 1.0  # y = 2.0 + x, 2 <= y < 3
             *   yy = 3.0 - y  # yy = 1.0 - x
             *   weights[0] = yy**5 / 120.0
             *
             * So we set y = 2.0 - y = 1.0 - x directly instead.
             */
            y = 1.0 - x;
            t = y * y;
            weights[0] = y * t * t / 120.0;
            break;
        default:
            return 1; /* Unsupported spline order. */
    }

    /* All interpolation weights add to 1.0, so use it for the last one. */
    weights[order] = 1.0;
    for (i = 0; i < order; ++i) {
        weights[order] -= weights[i];
    }

    return 0;
}


