#include <stdio.h>
#include <stdbool.h>
#include <string.h>
/* COP 3502C Assignment 2
This program is written by: Devon Villalona 2/14/2024 */
#define MAX_PEOPLE 10

int total_people, pairs;
char person_names[MAX_PEOPLE][20];
int popcorn_status[MAX_PEOPLE];
bool seating_restrictions[MAX_PEOPLE][MAX_PEOPLE] = {false};
bool seated[MAX_PEOPLE] = {false};
int arrangement[MAX_PEOPLE];
int arrangement_count = 0;

// Check if two people can sit together
bool allowed_together(int person1, int person2) {
    return !seating_restrictions[person1][person2];
}

// Check if a person has popcorn or is adjacent to someone with popcorn
bool has_access_to_popcorn(int position) {
    if (position == 0) {
        return popcorn_status[arrangement[position]] || popcorn_status[arrangement[position + 1]];
    } else if (position == total_people - 1) {
        return popcorn_status[arrangement[position]] || popcorn_status[arrangement[position - 1]];
    } else {
        return popcorn_status[arrangement[position]] || popcorn_status[arrangement[position + 1]] || popcorn_status[arrangement[position - 1]];
    }
}

// Validate the current seating arrangement
bool valid_arrangement() {
    for (int i = 0; i < total_people; i++) {
        if (!has_access_to_popcorn(i)) {
            return false;
        }
        if (i > 0 && !allowed_together(arrangement[i], arrangement[i - 1])) {
            return false;
        }
    }
    return true;
}

// Generate all possible seating arrangements
void generate_arrangements(int position) {
    if (position == total_people) {
        if (valid_arrangement()) {
            arrangement_count++;
        }
        return;
    }

    for (int i = 0; i < total_people; i++) {
        if (!seated[i]) {
            arrangement[position] = i;
            seated[i] = true;
            generate_arrangements(position + 1);
            seated[i] = false;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    fscanf(fp, "%d %d", &total_people, &pairs);
    for (int i = 0; i < total_people; i++) {
        fscanf(fp, "%s %d", person_names[i], &popcorn_status[i]);
    }
    for (int i = 0; i < pairs; i++) {
        char person1[20], person2[20];
        int index1 = -1, index2 = -1;
        fscanf(fp, "%s %s", person1, person2);
        for (int j = 0; j < total_people; j++) {
            if (strcmp(person1, person_names[j]) == 0) {
                index1 = j;
            }
            if (strcmp(person2, person_names[j]) == 0) {
                index2 = j;
            }
        }
        seating_restrictions[index1][index2] = true;
        seating_restrictions[index2][index1] = true;
    }

    fclose(fp);

    generate_arrangements(0);

    printf("%d\n", arrangement_count);

    return 0;
}