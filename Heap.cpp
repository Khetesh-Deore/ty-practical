#include <iostream>
#include <string>
using namespace std;

struct Job {
    string name;
    int experience;
    int priority;
};

class Heap {
    Job maxHeap[100];  // For highest priority (Max Heap)
    Job minHeap[100];  // For lowest priority (Min Heap)
    int maxSize, minSize;

public:
    Heap() {
        maxSize = 0;
        minSize = 0;
    }

    void insertJob(Job job);
    void insertMaxHeap(Job job);
    void insertMinHeap(Job job);
    void deleteMax();
    void displayMaxMin();
    void displayAll();
};

// ---------------- Insert into both Heaps ----------------
void Heap::insertJob(Job job) {
    insertMaxHeap(job);
    insertMinHeap(job);
    cout << "✅ Job added successfully!\n";
}

// ---------------- Insert into Max Heap ----------------
void Heap::insertMaxHeap(Job job) {
    maxSize++;
    int i = maxSize;

    while (i > 1 && job.priority > maxHeap[i / 2].priority) {
        maxHeap[i] = maxHeap[i / 2];
        i = i / 2;
    }
    maxHeap[i] = job;
}

// ---------------- Insert into Min Heap ----------------
void Heap::insertMinHeap(Job job) {
    minSize++;
    int i = minSize;

    while (i > 1 && job.priority < minHeap[i / 2].priority) {
        minHeap[i] = minHeap[i / 2];
        i = i / 2;
    }
    minHeap[i] = job;
}

// ---------------- Delete highest priority (Max Heap) ----------------
void Heap::deleteMax() {
    if (maxSize == 0) {
        cout << "❌ No jobs available!\n";
        return;
    }

    cout << "\n🗑️ Deleting highest priority job: " << maxHeap[1].name << "\n";

    Job temp = maxHeap[1];
    maxHeap[1] = maxHeap[maxSize];
    maxSize--;

    int i = 1, j = 2 * i;

    while (j <= maxSize) {
        if (j + 1 <= maxSize && maxHeap[j + 1].priority > maxHeap[j].priority)
            j++;

        if (maxHeap[i].priority < maxHeap[j].priority) {
            swap(maxHeap[i], maxHeap[j]);
            i = j;
            j = 2 * i;
        } else
            break;
    }
}

// ---------------- Display highest & lowest priority jobs ----------------
void Heap::displayMaxMin() {
    if (maxSize == 0 || minSize == 0) {
        cout << "❌ No jobs available!\n";
        return;
    }

    cout << "\n⭐ Highest Priority Job:\n";
    cout << "Name: " << maxHeap[1].name
         << " | Experience: " << maxHeap[1].experience
         << " | Priority: " << maxHeap[1].priority << endl;

    cout << "\n🕓 Lowest Priority Job:\n";
    cout << "Name: " << minHeap[1].name
         << " | Experience: " << minHeap[1].experience
         << " | Priority: " << minHeap[1].priority << endl;
}

// ---------------- Display all jobs by priority (Max Heap order) ----------------
void Heap::displayAll() {
    if (maxSize == 0) {
        cout << "❌ No jobs to display!\n";
        return;
    }

    cout << "\n📋 All Jobs in Priority Order (Max Heap):\n";
    for (int i = 1; i <= maxSize; i++) {
        cout << i << ". " << maxHeap[i].name
             << " | Exp: " << maxHeap[i].experience
             << " | Priority: " << maxHeap[i].priority << endl;
    }
}

// ---------------- Main Function ----------------
int main() {
    Heap h;
    int choice;

    do {
        cout << "\n------ Company Job Management (Using Min & Max Heap) ------\n";
        cout << "1. Insert a new job\n";
        cout << "2. Display highest and lowest priority jobs\n";
        cout << "3. Delete highest priority job\n";
        cout << "4. Display all jobs (priority order)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Job j;
            cout << "Enter job name: ";
            cin >> j.name;
            cout << "Enter experience (in years): ";
            cin >> j.experience;
            cout << "Enter priority (higher = more important): ";
            cin >> j.priority;
            h.insertJob(j);
            break;
        }
        case 2:
            h.displayMaxMin();
            break;
        case 3:
            h.deleteMax();
            break;
        case 4:
            h.displayAll();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "❌ Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
