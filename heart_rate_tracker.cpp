#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

// Fonksiyon prototipleri
int calculateMaxHeartRate(int age);
int calculateTargetZone(int maxRate, float percentage);
void printBinary(int number);
void logToFile(int age, int restHR, int maxHR, int zones[], float percentages[], int count);

int main() {
    int age, restHR;

    cout << "Enter your age: ";
    cin >> age;

    cout << "Enter your resting heart rate: ";
    cin >> restHR;

    int maxHR = calculateMaxHeartRate(age);
    cout << "\nYour maximum heart rate is: " << maxHR << endl;

    // Fat Burn bölgesi için yüzdeler
    float percentages[] = {0.50f, 0.60f, 0.70f}; 
    int zones[3];

    cout << "Fat Burn Zone (50% - 70%):" << endl;

    for (int i = 0; i < 3; i++) {
        zones[i] = calculateTargetZone(maxHR, percentages[i]);
        cout << static_cast<int>(percentages[i] * 100) << "% zone: " << zones[i] << " bpm (";
        printBinary(zones[i]);
        cout << ")" << endl;
    }

    // Dosyaya kaydet
    logToFile(age, restHR, maxHR, zones, percentages, 3);

    return 0;
}

int calculateMaxHeartRate(int age) {
    return 220 - age;
}

int calculateTargetZone(int maxRate, float percentage) {
    return static_cast<int>(maxRate * percentage);
}

void printBinary(int number) {
    cout << bitset<8>(number);
}

void logToFile(int age, int restHR, int maxHR, int zones[], float percentages[], int count) {
    ofstream file("heart_log.txt", ios::app);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    file << "Age: " << age << ", Resting HR: " << restHR << ", Max HR: " << maxHR << endl;
    file << "Fat Burn Zone:" << endl;

    for (int i = 0; i < count; i++) {
        file << static_cast<int>(percentages[i] * 100) << "%: " << zones[i] << " bpm ("
             << bitset<8>(zones[i]) << ")" << endl;
    }

    file << "---------------------------" << endl;
    file.close();
}
