#include <stdio.h>
#include <string.h>

#define MAX_DOCTORS 10
#define MAX_PATIENTS 20

// Doctor structure
struct Doctor {
    int id;
    char name[50];
    char specialty[50];
    int isBusy;
    int patientsAttended;
};

// Patient structure
struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    int isEmergency;
};

// Function prototypes
void loadSampleDoctors(struct Doctor doctors[], int* doctorCount);
void loadSamplePatients(struct Patient patients[], int* patientCount);
const char* getSpecialtyForDisease(const char* disease, int age);
int findDoctorInSpecialty(struct Doctor doctors[], int doctorCount, const char* specialty);
void assignDoctors(struct Doctor doctors[], int doctorCount, struct Patient patients[], int patientCount);

int main() {
    struct Doctor doctors[MAX_DOCTORS];
    struct Patient patients[MAX_PATIENTS];
    int doctorCount = 0, patientCount = 0;

    // Load sample data
    loadSampleDoctors(doctors, &doctorCount);
    loadSamplePatients(patients, &patientCount);

    // Error handling for maximum limits
    if (doctorCount >= MAX_DOCTORS) {
        printf("Error: Maximum doctor limit reached!\n");
        return 1;
    }

    if (patientCount >= MAX_PATIENTS) {
        printf("Error: Maximum patient limit reached!\n");
        return 1;
    }

    // Assign doctors to patients
    assignDoctors(doctors, doctorCount, patients, patientCount);

    return 0;
}

void loadSampleDoctors(struct Doctor doctors[], int* doctorCount) {
    // Sample doctors
    doctors[0] = (struct Doctor){1, "Dr. Smith", "Cardiology", 0, 0};
    doctors[1] = (struct Doctor){2, "Dr. Jones", "Orthopedics", 0, 0};
    doctors[2] = (struct Doctor){3, "Dr. Brown", "Neurology", 0, 0};
    doctors[3] = (struct Doctor){4, "Dr. Taylor", "Dermatology", 0, 0};
    doctors[4] = (struct Doctor){5, "Dr. Wilson", "Pulmonology", 0, 0};
    *doctorCount = 5;
}

void loadSamplePatients(struct Patient patients[], int* patientCount) {
    // Sample patients
    patients[0] = (struct Patient){1, "Alice", 45, "Heart Disease", 0};
    patients[1] = (struct Patient){2, "Bob", 30, "Back Problems", 0};
    patients[2] = (struct Patient){3, "Charlie", 10, "Fever", 0};
    patients[3] = (struct Patient){4, "Diana", 60, "Migraine", 1};
    patients[4] = (struct Patient){5, "Eve", 35, "Skin Allergy", 0};
    *patientCount = 5;
}

const char* getSpecialtyForDisease(const char* disease, int age) {
    if (strcmp(disease, "Heart Disease") == 0 || strcmp(disease, "Chest Pain") == 0 || 
        strcmp(disease, "High Blood Pressure") == 0 || strcmp(disease, "Cholesterol Management") == 0) {
        return "Cardiology";
    } else if (strcmp(disease, "Arthritis") == 0 || strcmp(disease, "Shoulder Pain") == 0 || 
               strcmp(disease, "Back Problems") == 0 || strcmp(disease, "Knee Replacement") == 0) {
        return "Orthopedics";
    } else if (age < 12) {
        return "Pediatrics";
    } else if (strcmp(disease, "Migraine") == 0 || strcmp(disease, "Memory Loss") == 0 || 
               strcmp(disease, "Nerve Pain") == 0) {
        return "Neurology";
    } else if (strcmp(disease, "Psoriasis") == 0 || strcmp(disease, "Skin Allergy") == 0) {
        return "Dermatology";
    } else if (strcmp(disease, "Lung Screening") == 0 || strcmp(disease, "Pneumonia") == 0) {
        return "Pulmonology";
    }
    return "General Medicine";
}

int findDoctorInSpecialty(struct Doctor doctors[], int doctorCount, const char* specialty) {
    for (int i = 0; i < doctorCount; i++) {
        if (strcmp(doctors[i].specialty, specialty) == 0 && !doctors[i].isBusy) {
            return doctors[i].id;
        }
    }
    return -1;
}

void assignDoctors(struct Doctor doctors[], int doctorCount, struct Patient patients[], int patientCount) {
    for (int i = 0; i < patientCount; i++) {
        const char* specialty = getSpecialtyForDisease(patients[i].disease, patients[i].age);
        int assignedDoctorId = findDoctorInSpecialty(doctors, doctorCount, specialty);

        if (assignedDoctorId != -1) {
            printf("Patient %s (ID: %d) assigned to Doctor %s (%s)\n", 
                   patients[i].name, patients[i].id, doctors[assignedDoctorId - 1].name, specialty);
            doctors[assignedDoctorId - 1].isBusy = 1; // Mark doctor as busy
            doctors[assignedDoctorId - 1].patientsAttended++;
        } else {
            printf("Patient %s (ID: %d) could not be assigned to any doctor in %s\n", 
                   patients[i].name, patients[i].id, specialty);
        }
    }

    // Print doctor assignment summary
    printf("\nDoctor Assignment Summary:\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("Doctor %s (%s): %d patients attended\n", 
               doctors[i].name, doctors[i].specialty, doctors[i].patientsAttended);
    }
}
