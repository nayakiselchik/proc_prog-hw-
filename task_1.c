#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x, y;
} point_t;

typedef struct {
    char name[50];
    int num_points;
    point_t *points;
} polygon_t;

void free_polygons(polygon_t *polygons, int count) {
    for (int i = 0; i < count; i++) {
        free(polygons[i].points);
    }
    free(polygons);
}

int main() {
    FILE *file = fopen("C:/Users/Anastasiia/Desktop/uni/proc_prog(hw)/polygons.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    polygon_t *polygons = NULL;
    int count = 0;

    char name[50];
    int num_points;
    while (fscanf(file, "%s %d", name, &num_points) == 2) {
        polygons = realloc(polygons, (count + 1) * sizeof(polygon_t));
        if (!polygons) {
            perror("Memory allocation error");
            fclose(file);
            return 1;
        }

        polygon_t *polygon = &polygons[count++];
        strcpy(polygon->name, name);
        polygon->num_points = num_points;
        polygon->points = malloc(num_points * sizeof(point_t));
        for (int i = 0; i < num_points; i++) {
            fscanf(file, "%d %d", &polygon->points[i].x, &polygon->points[i].y);
        }
    }

    fclose(file);

    for (int i = 0; i < count; i++) {
        printf("Polygon: %s\nPoints: ", polygons[i].name);
        for (int j = 0; j < polygons[i].num_points; j++) {
            printf("(%d, %d)%s", polygons[i].points[j].x, polygons[i].points[j].y,
                   j < polygons[i].num_points - 1 ? ", " : "");
        }
        printf("\n");
    }

    free_polygons(polygons, count);
    return 0;
}
