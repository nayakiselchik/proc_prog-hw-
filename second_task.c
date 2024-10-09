#include <stdio.h>
#include <stdint.h>

void print_float_info(float number) {
    union {
        float f;
        uint32_t u;
    } float_union;

    float_union.f = number;

    uint32_t sign = (float_union.u >> 31) & 0x1;
    int32_t exponent = ((float_union.u >> 23) & 0xFF) - 127;
    uint32_t mantissa = float_union.u & 0x7FFFFF;

// ПЕРЕРОБИТИ!!!
    float mantissa_value = 1.0f; 
    for (int i = 0; i < 23; i++) {
        if (mantissa & (1 << (22 - i))) {
            mantissa_value += (1.0f / (1 << (i + 1)));
        }
    }

    printf("Sign: %s\n", sign ? "-" : "+");
    printf("Mantissa: %.5f\n", mantissa_value - 1.0f); 
    printf("Exponent: %d\n", exponent);

    float reconstructed_value = mantissa_value * (1 << exponent);
    printf("Reconstructed: (1.0 + %.5f) * 2**%d = %.6f\n", mantissa_value - 1.0f, exponent, reconstructed_value);
}

int main() {
    float number;

    printf("Enter a floating-point number: ");
    scanf("%f", &number);

    print_float_info(number);

    return 0;
}
