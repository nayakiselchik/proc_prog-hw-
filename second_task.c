#include <stdio.h>
#include <stdint.h>
#include <math.h>

void print_float_info(float number) {
    union {
        float f;
        uint32_t u;
    } float_union;
    
    float_union.f = number;

    uint32_t sign = (float_union.u >> 31) & 0x1;
    int32_t exponent = ((float_union.u >> 23) & 0xFF);
    uint32_t mantissa = float_union.u & 0x7FFFFF;

    float mantissa_value;
    int adjusted_exponent;

    // Якщо експонента дорівнює 0
    if (exponent == 0) {
        mantissa_value = mantissa / (float)(1 << 23);
        adjusted_exponent = -126;
        mantissa_value = 1.0f + mantissa / (float)(1 << 23);
        adjusted_exponent = exponent - 127;
    }

    printf("Sign bit: %s\n", sign ? "-" : "+");
    printf("Mantissa value: %.5f\n", mantissa_value - 1.0f);
    printf("Exponent value: %d\n", adjusted_exponent);

    // відновлене значення
    float reconstructed_value = (sign ? -1.0f : 1.0f) * mantissa_value * pow(2, adjusted_exponent);
    printf("Reconstructed value: (1.0 + %.5f) * 2**%d = %.6f\n", mantissa_value - 1.0f, adjusted_exponent, reconstructed_value);
}

int main() {
    float number;
    
    printf("Enter a floating-point number: ");
    scanf("%f", &number);
    
    print_float_info(number);

    return 0;
}
