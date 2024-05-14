#include <iostream>
using namespace std;

struct Student{
    string id;
    int grade;
    string name;
};

const int SIZE = 100;
const int NUM_QUEUES = 3;

Student Queues[NUM_QUEUES][SIZE];
int fronts[NUM_QUEUES] = {-1 ,-1 ,-1 };
int backs[NUM_QUEUES] = {-1 ,-1 ,-1 };
int mainQueue = 0 , passedQueue = 1 ,failedQueue = 2;

int customSeed = 42; // Initial seed for custom random number generator

int generate_id(){
    const int a = 1664;
    const int c = 10139;
    customSeed = (a * customSeed + c) % 9000 + 1000; // ensure the result is a 4-digit number
    return customSeed < 0 ? customSeed * -1 : customSeed; // ensure that the random generated number isn't negative
}

bool isEmpty(int queueIndex) {
    return fronts[queueIndex] == -1 && backs[queueIndex] == -1;
}

bool isFull(int queueIndex) {
    return backs[queueIndex] == SIZE - 1;
}

void enqueue( int queueIndex, int grade , string name) {
    if (isFull(queueIndex)) {
        cout << "main queue is Full " << endl;
    } else {
        if(fronts[queueIndex] == -1 && backs[queueIndex] == -1){
            fronts[queueIndex]++;
            backs[queueIndex]++;
            Queues[queueIndex][backs[queueIndex]].grade = grade;
            Queues[queueIndex][backs[queueIndex]].name = name;
            Queues[queueIndex][backs[queueIndex]].id = "2023"+ to_string(queueIndex) + to_string(generate_id());
        }else{
            backs[queueIndex]++;
            Queues[queueIndex][backs[queueIndex]].grade = grade;
            Queues[queueIndex][backs[queueIndex]].name = name;
            Queues[queueIndex][backs[queueIndex]].id = "2023" + to_string(queueIndex) + to_string(generate_id());
        }
    }

}

void dequeue(int queueIndex){
    if(!isEmpty(queueIndex) && fronts[queueIndex] <= backs[queueIndex]){
        fronts[queueIndex]++;
    }else{
        cout<<"Empty Queue";
    }
}


void display(int queueIndex , string queuename) {
    if (isEmpty(queueIndex)) {
        cout << "\nEmpty " << queuename << " queue"<<endl;
        return;
    } else {
        cout << "\ndisplaying " << queuename << " queue" << endl;
        cout<<"\n";
        for (int i = fronts[queueIndex]; i <= backs[queueIndex] ; i++) {
            cout<<"id: " << Queues[queueIndex][i].id << " \n";
            cout<<"name: " << Queues[queueIndex][i].name << " \n";
            cout<<"grade: " << Queues[queueIndex][i].grade << " \n";
            cout << endl;
        }
    }
    
}

float grades_average(int queueIndex){
    if(isEmpty(queueIndex)){
        cout<<"no grades to calculate thier average.";
        return 0;
    }else{
        int ave = 0 , how_many_students = 0;
        for(int i = fronts[queueIndex]; i <= backs[queueIndex] ; i++){
            ave += Queues[queueIndex][i].grade;
            how_many_students++;
        }
        return (float)ave / how_many_students;
    }
}


void separate_students(){
    if(!isEmpty(mainQueue)){
         for (int i = fronts[mainQueue]; i <= backs[mainQueue]; i++){
            if(Queues[mainQueue][i].grade >= 50){
                dequeue(mainQueue);
                enqueue(passedQueue , Queues[mainQueue][i].grade , Queues[mainQueue][i].name);
            }else{
                dequeue(mainQueue);
                enqueue(failedQueue , Queues[mainQueue][i].grade , Queues[mainQueue][i].name);
            }
            
         }
         if(fronts[mainQueue] == backs[mainQueue]){  // if the front of the main queue > its back then the main queue is empty
            backs[mainQueue] = fronts[mainQueue] = -1;
         }
    }


}

int main()
{
    int choice;
    string queueName;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Enqueue student\n";
        cout << "2. Dequeue students\n";
        cout << "3. Display queues\n";
        cout << "4. Calculate grades average\n";
        cout << "5. Separate students\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice){
        case 1:{
            int how_many_students;
            cout<<"how many students to enqueue (maximum is 100): ";
            cin>>how_many_students;

            cout << "Enter student name then grade separated by space: \n";
            for (int i = 0; i < how_many_students; i++){
                int grade;
                string name;
                cin >> name>> grade;
                enqueue(mainQueue, grade, name);
            }
            break;
        }
        case 2:
            cout << "Select a queue to dequeue from (0: main, 1: passed, 2: failed): ";
            int dequeueChoice;
            cin >> dequeueChoice;
            dequeue(dequeueChoice);
            break;
        case 3:
            cout << "Select a queue to display (0: main, 1: passed, 2: failed): ";
            int displayChoice;
            cin >> displayChoice;

            switch (displayChoice)
            {
            case 0:
                queueName = "main";
                break;
            case 1:
                queueName = "passed";
                break;
            case 2:
                queueName = "failed";
                break;
            default:
                cout << "Invalid choice\n";
                continue;
            }

            display(displayChoice, queueName);
            break;
        case 4:
            cout << "Select a queue to calculate grades average (0: main, 1: passed, 2: failed): ";
            int averageChoice;
            cin >> averageChoice;
            cout << "Average grade: " << grades_average(averageChoice) << endl;
            break;
        case 5:
            separate_students();
            int see_changes;
            cout<<"do you want to see changes [press 1 for yes , 0 for no]\n";
            cin>>see_changes;
            if(see_changes){
                display(passedQueue , "passed");
                display(failedQueue , "failed");
            }else{
                cout<<"you can see the changes later by displaying the queues\n";
            }
            break;
        case 0:
            cout << "Exiting program\n";
            break;
        default:
            cout << "Invalid choice\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
