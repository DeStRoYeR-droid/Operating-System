#include <iostream>
#include <vector>

using namespace std;

/*
Get processes from the user
Sort on basis of arrival time and put in a process queue

Running -
Initialise a ready queue and iterator (clock) = 0
Check if any process has arrived (arrival time <= iterator)
Sort all arrived processes on the basis of burst time
Execute the top of the process queue
iterator += burst time of process which is executed.

If top not exist
iterator += 1
*/

class Process{
    private:
        string name;
        unsigned int arrival_time;
        unsigned int burst_time;

    public:
        Process(string name = "", unsigned int arrival_time = 0, unsigned int burst_time = 0){
            this->name = name;
            this->arrival_time = arrival_time;
            this->burst_time = burst_time;
        }

        unsigned int get_arrival_time(){
            return this->arrival_time;
        }

        unsigned int get_burst_time(){
            return this->burst_time;
        }
        string get_name(){
            return this->name;
        }

        friend istream& operator >> (istream& in, Process& p){
            cout << "Please enter the name of the process         ";
            cin >> p.name;
            cout << "Please enter the arrival time of the process ";
            cin >> p.arrival_time;
            cout << "Please enter the burst time of the process   ";
            cin >> p.burst_time;
            return in;
        }

        friend ostream& operator << (ostream& out, Process& p){
            out << "Process name         = " << p.name << endl;
            out << "Process arrival time = " << p.arrival_time << endl;
            out << "Process burst time   = " << p.burst_time << endl;
            return out;
        }
};

void bubble_sort_arrival_time(vector<Process>& arr, int length){
    for (int i = 0; i < length; i++){
        bool swapped = false;
        for (int j = 0; j < length - i - 1; j++){
            if (arr[j].get_arrival_time() < arr[j+1].get_arrival_time()){
                swap(arr[j] , arr[j+1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

void bubble_sort_burst_time(vector<Process>& arr, int length){
    for (int i = 0; i < length; i++){
        bool swapped = false;
        for (int j = 0; j < length - i - 1; j++){
            if (arr[j].get_burst_time() < arr[j+1].get_burst_time()){
                swap(arr[j] , arr[j+1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

int main(){
    vector<Process> ProcessQueue;
    vector<Process> ReadyQueue;
    int no_of_processes;

    // Entering the number of processes which are to be executed
    cout << "Please enter the number of processes ";
    cin >> no_of_processes;

    // Initialising the processses
    Process temp;
    for (int i = 0; i < no_of_processes; i++){
        cin >> temp;
        ProcessQueue.push_back(temp);
        cout << endl;
    }

    // Sorting on the basis of arrival time
    bubble_sort_arrival_time(ProcessQueue , no_of_processes);

    // Main execution of the algorithm
    int clock = 0;          // Denotes current clock time
    int ready_queue_length = 0; // Denotes the length of ready queue
    Process cur_process;    // Denotes current process
    while (!ProcessQueue.empty()){
        // Get all the processes which are now ready to be executed
        while (!ProcessQueue.empty() && ProcessQueue.back().get_arrival_time() <= clock){
            ReadyQueue.push_back(ProcessQueue.back());
            ProcessQueue.pop_back();
            ready_queue_length++;
        }
        
        // Sort the ready processes on the basis of burst time
        bubble_sort_burst_time(ReadyQueue, ready_queue_length);

        // If process exist, run the process
        if (!ReadyQueue.empty()){
            cur_process = ReadyQueue.back();
            cout << cur_process.get_name() << " ran for "  << cur_process.get_burst_time() << "ms";
            cout << " from " << clock << " to " << clock + cur_process.get_burst_time() << endl;
            ReadyQueue.pop_back();
            ready_queue_length--;
            clock = clock + cur_process.get_burst_time();
        }
        // Else CPU remains idle until next process arrives
        else {
            cout << "CPU Idle for " << clock << " to ";
            if (!ProcessQueue.empty()){
                cout <<  ProcessQueue.back().get_arrival_time() << "ms" << endl;
                clock = ProcessQueue.back().get_arrival_time();
            }
        }
    }
    
    
    return 0;
}