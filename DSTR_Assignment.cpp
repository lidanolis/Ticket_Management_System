#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

//subway station 
class stationnode {
public:

    stationnode* prevLink;
    stationnode* nextLink;
    string information;

    string stationName;
    string stationID;

    float costPS;
    int distancePS;
    int timePS;

    float costNS;
    int distanceNS;
    int timeNS;

};

//ticket linked list 
class ticketnode {
public:
    ticketnode* link;

    string nameDeparture;
    string nameDestination;
    float total;
    int distance;
    string passengerName;
    string passengerID;
    string ic;
    string transactionID;
    string ticketID;
    string transactionDate;
    string departureTime;
    string status;
};

//profile linked list
class usernode {
public:
    usernode* link;

    string userID;
    string username;
    string password;
    string role;
    string contact;
    string ic;
};

//stack
class stacknode {
public:
    stacknode* link;
    string ticketID;
};

//stack related functions
class stackDataManagement {
public:
    stacknode* head;
    int size;
    stackDataManagement() {
        head = NULL;
        size = 0;
    }

    //push
    void insertAtBeginning(string ticketID) {
        //creating new node
        stacknode* newNode = new stacknode;
        newNode->ticketID = ticketID;

        if (size == 0) {
            //empty linked list
            newNode->link = NULL;
            head = newNode;
            size++;
        }
        else {
            //set the new node as the first in the linked list
            newNode->link = head;
            head = newNode;
            size++;
        }
    }

    //pop
    string pop() {
        string popID;
        stacknode* pop = head;
        head = pop->link;
        popID = pop->ticketID;
        size--;
        delete pop;
        return popID;
    }
};

//queue related functions
class QueueDataManagement {
public:
    stacknode* head;
    stacknode* tail;
    int size;
    QueueDataManagement() {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    //push
    void insertAtBeginning(string ticketID) {
        //creating new node
        stacknode* newNode = new stacknode;
        newNode->ticketID = ticketID;

        if (size == 0) {
            //empty linked list
            newNode->link = NULL;
            head = newNode;
            tail = newNode;
            size++;
        }
        else {
            //set the new node as the first in the linked list
            newNode->link = head;
            head = newNode;
            size++;
        }
    }

    //pop
    string pop() {
        string popID = tail->ticketID;
        stacknode* pop = head;

        if (size > 1) {
            while (pop->link->link != NULL) {
                pop = pop->link;
            }
            tail = pop;
            pop = pop->link;
            tail->link = NULL;
            delete pop;

            size--;
            return popID;
        }
        else {
            size--;
            pop = tail;
            tail->link = NULL;
            delete pop;
            return popID;
        }
    }
};

//station related functions
class stationDataManagement {
public:
    stationnode* head;
    stationnode* tail;
    int size;

    stationDataManagement() {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    void InsertAtEnd(string stationName, string stationID, string information, float costPS, int distancePS, int timePS, float costNS, int distanceNS, int timeNS) {
        stationnode* newNode = new stationnode;

        newNode->information = information;

        newNode->stationName = stationName;
        newNode->stationID = stationID;

        newNode->costPS = costPS;
        newNode->distancePS = distancePS;
        newNode->timePS = timePS;

        newNode->costNS = costNS;
        newNode->distanceNS = distanceNS;
        newNode->timeNS = timeNS;

        if (size == 0) {
            newNode->prevLink = NULL;
            newNode->nextLink = NULL;
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->prevLink = tail;
            newNode->prevLink->nextLink = newNode;
            newNode->nextLink = NULL;
            tail = newNode;
        }
        size++;
    }

    //read the total,distance and time of the trip
    void readprice() {
        stationnode* point = head;
        float price = 0;
        int distance = 0;
        int time = 0;
        while (point != NULL) {
            price = price + (point->costNS);
            distance = distance + (point->distanceNS);
            time = time + (point->timeNS);
            point = point->nextLink;
        }
        cout << "The total price: RM " << price << endl;
        cout << "The total distance:" << distance << " KM" << endl;
        cout << "The total time:" << time << " Mins" << endl;

        point = tail;
        price = 0;
        distance = 0;
        time = 0;
        while (point != NULL) {
            price = price + (point->costNS);
            distance = distance + (point->distanceNS);
            time = time + (point->timeNS);
            point = point->prevLink;
        }
        cout << "The total price: RM " << price << endl;
        cout << "The total distance:" << distance << " KM" << endl;
        cout << "The total time:" << time << " Mins" << endl;
    }

    //Display all station
    void readStation() {
        stationnode* curr = head;
        while (curr != nullptr) {
            cout << curr->stationID << "-" << curr->stationName << "-" << curr->information << "-" << curr->costPS << "-" << curr->distancePS << "-" << curr->timePS << "-" << curr->costNS << "-" << curr->distanceNS << "-" << curr->timeNS << endl;
            curr = curr->nextLink;

        }
    }

    //Used to select specific station
    string* searchStation(string id) {
        stationnode* curr = head;
        static string arr[8];
        while (curr != nullptr) {
            if (curr->stationID == id) {
                arr[0] = curr->stationID;
                arr[1] = curr->stationName;
                arr[2] = curr->information;
                arr[3] = to_string(curr->costPS);
                arr[4] = to_string(curr->distancePS);
                arr[5] = to_string(curr->timePS);
                arr[6] = to_string(curr->costNS);
                arr[7] = to_string(curr->distanceNS);
                arr[8] = to_string(curr->timeNS);
                break;
            }
            else {
                arr[0] = "N";
            }
            curr = curr->nextLink;
        }
        return arr;
    }

    //Update station information
    void editStation(string* arr) {
        stationnode* curr = head;
        while (curr != nullptr) {
            if (curr->stationID == arr[0]) {
                curr->information = arr[2];
                curr->stationName = arr[1];
                curr->stationID = arr[0];

                curr->costPS = stof(arr[3]);
                curr->distancePS = stoi(arr[4]);
                curr->timePS = stoi(arr[5]);

                curr->costNS = stof(arr[6]);
                curr->distanceNS = stoi(arr[7]);
                curr->timeNS = stoi(arr[8]);
                break;

            }
            curr = curr->nextLink;
        }
    }

    //for modify station information
    void modifystationinformation(string ID) {
        stationnode* edit;
        while (true) {
            int modification;
            edit = head;
            while (edit != NULL) {
                if (edit->stationID == ID) {
                    break;
                }
                edit = edit->nextLink;
            }

            cout << "Would you like to [0]exit \n [1]add \n [2]modify \n station information: ";
            cin >> modification;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "-INVALID INPUT-" << endl;
                Beep(520, 520);
                system("CLS");
                continue;
            }
            else if (modification == 0) {
                cout << "-EXITING-" << endl;
                Beep(520, 520);
                system("CLS");
                return;
            }
            else if (modification == 1 || modification == 2) {
                string detail;
                while (true) {
                    cout << "-Station Information: " << endl;
                    cout << edit->information << endl;
                    cout << "\nInput New/Modified Station Information:";
                    cin >> detail;

                    if (detail.empty()) {
                        cout << "-Cannot Be Empty-" << endl;
                        Beep(520, 520);
                        system("CLS");
                        continue;
                    }
                    else {
                        if (modification == 1) {
                            string oldinfo = edit->information;
                            oldinfo = oldinfo + "\n" + detail;
                            edit->information = oldinfo;
                            system("CLS");
                        }
                        else if (modification == 2) {
                            edit->information = detail;
                            system("CLS");
                        }
                        break;
                    }
                }
            }
        }

    }

    //to update the station
    void updateDLL(string ID) {
        stationnode* update = head;
        while (update != NULL) {
            if (update->stationID == ID) {
                break;
            }
            update = update->nextLink;
        }

        if (ID == "SID01") {
            update->nextLink->costPS = update->costNS;
            update->nextLink->distancePS = update->distanceNS;
            update->nextLink->timePS = update->timeNS;
        }
        else if (ID == "SID08") {
            update->prevLink->costNS = update->costPS;
            update->prevLink->distanceNS = update->distancePS;
            update->prevLink->timeNS = update->timePS;
        }
        else {
            update->nextLink->costPS = update->costNS;
            update->nextLink->distancePS = update->distanceNS;
            update->nextLink->timePS = update->timeNS;

            update->prevLink->costNS = update->costPS;
            update->prevLink->distanceNS = update->distancePS;
            update->prevLink->timeNS = update->timePS;
        }
        system("CLS");
    }
};

//ticket related functions
class ticketDataManagement {
public:
    ticketnode* head;
    int ticketSize;
    int transactionSize;
    ticketDataManagement() {
        head = NULL;
        ticketSize = 0;
        transactionSize = 0;
    }

    void insertTicketDataWithStatus(string nameDeparture, string nameDestination, float total, int distance, string passengerName, string passengerID, string ic, string transactionID, string ticketID, string transactionDate, string departureTime, string status) {
        ticketnode* newnode = new ticketnode;
        newnode->nameDeparture = nameDeparture;
        newnode->nameDestination = nameDestination;
        newnode->total = total;
        newnode->distance = distance;
        newnode->passengerName = passengerName;
        newnode->passengerID = passengerID;
        newnode->ic = ic;
        newnode->transactionID = transactionID;
        newnode->ticketID = ticketID;
        newnode->transactionDate = transactionDate;
        newnode->departureTime = departureTime;
        newnode->status = status;

        if (head == NULL) {
            newnode->link = NULL;
            head = newnode;
        }
        else {
            ticketnode* last = head;
            newnode->link = NULL;
            while (last->link != NULL) {
                last = last->link;
            }
            last->link = newnode;

        }
        ticketSize++;
    }

    void insertTicketData(string nameDeparture, string nameDestination, float total, int distance, string passengerName, string passengerID, string ic, string transactionID, string ticketID, string transactionDate, string departureTime) {
        ticketnode* newnode = new ticketnode;
        newnode->nameDeparture = nameDeparture;
        newnode->nameDestination = nameDestination;
        newnode->total = total;
        newnode->distance = distance;
        newnode->passengerName = passengerName;
        newnode->passengerID = passengerID;
        newnode->ic = ic;
        newnode->transactionID = transactionID;
        newnode->ticketID = ticketID;
        newnode->transactionDate = transactionDate;
        newnode->departureTime = departureTime;
        newnode->status = "PENDING";

        if (head == NULL) {
            newnode->link = NULL;
            head = newnode;
        }
        else {
            ticketnode* last = head;
            newnode->link = NULL;
            while (last->link != NULL) {
                last = last->link;
            }
            last->link = newnode;

        }
        ticketSize++;
    }

    //for sorting purpose
    void createTemporaryTicket(string nameDeparture, string nameDestination, float total, int distance, string passengerName, string passengerID, string ic, string transactionID, string ticketID, string transactionDate, string departureTime, string status) {
        ticketnode* newnode = new ticketnode;
        newnode->nameDeparture = nameDeparture;
        newnode->nameDestination = nameDestination;
        newnode->total = total;
        newnode->distance = distance;
        newnode->passengerName = passengerName;
        newnode->passengerID = passengerID;
        newnode->ic = ic;
        newnode->transactionID = transactionID;
        newnode->ticketID = ticketID;
        newnode->transactionDate = transactionDate;
        newnode->departureTime = departureTime;
        newnode->status = status;

        if (head == NULL) {
            newnode->link = NULL;
            head = newnode;
        }
        else {
            ticketnode* last = head;
            newnode->link = NULL;
            while (last->link != NULL) {
                last = last->link;
            }
            last->link = newnode;

        }
    }

    //stack function
    boolean temptdlt(string ID, stackDataManagement* SDM) {
        bool val = false;
        ticketnode* deletedNode;
        ticketnode* curr = head;
        while (curr->link != nullptr) {
            if (curr->ticketID == ID) {
                if (curr->status == "RNP" || curr->status == "RP") {
                    return false;
                }
                if (curr->status == "PENDING") {
                    curr->status = "RNP";
                }
                else if (curr->status == "PAID") {
                    curr->status = "RP";
                }
                SDM->insertAtBeginning(ID);
                val = true;
                break;

            }
            curr = curr->link;
        }
        return val;
    }

    //pay ticket function
    void retrievePendingData(string passengerID) {
        ticketDataManagement pendingTicket;
        //for stack
        stackDataManagement staking;
        QueueDataManagement queing;
        ticketnode* pending = head;

        while (pending != NULL) {
            if (pending->passengerID == passengerID && pending->status == "PENDING") {
                pendingTicket.insertTicketData(pending->nameDeparture, pending->nameDestination, pending->total, pending->distance, pending->passengerName, pending->passengerID, pending->ic, pending->transactionID, pending->ticketID, pending->transactionDate, pending->departureTime);
                pending = pending->link;
            }
            else {
                pending = pending->link;
            }
        }

        int value;
        int i;
        ticketnode* printOut;
        ticketnode* specificTicket;
        ticketnode* undo;

        while (true) {
            i = 0;
            //for printing
            printOut = pendingTicket.head;
            specificTicket = pendingTicket.head;
            undo = pendingTicket.head;
            system("CLS");

            while (printOut != NULL) {
                if (printOut->status == "PENDING") {
                    cout << i + 1 << ") " << printOut->ticketID << endl;
                    i++;
                }
                printOut = printOut->link;
            }
            cout << "\n0-Exit" << endl;
            if (staking.size > 0) {
                cout << "[-1]-Undo Payment" << endl;
            }
            cout << "Make Your Choice : ";
            cin >> value;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "-INVALID INPUT-" << endl;
                Beep(520, 520);
                system("CLS");
            }

            if (staking.size > 0 && value == -1) {
                string popValue = staking.pop();
                while (undo != NULL) {
                    if (popValue.compare(undo->ticketID) == 0) {
                        break;
                    }
                    undo = undo->link;
                }
                undo->status = "PENDING";
                Beep(520, 520);
                system("CLS");
            }
            else if (value == 0) {
                cout << "Exiting";
                Beep(520, 520);
                system("CLS");
                if (staking.size > 0) {
                    undo = pendingTicket.head;
                    while (undo != NULL) {
                        if (undo->status == "PAID") {
                            queing.insertAtBeginning(undo->ticketID);
                        }
                        undo = undo->link;
                    }

                    if (queing.size > 0) {

                        while (queing.size > 0) {
                            pending = head;
                            string popID = queing.pop();

                            while (pending != NULL) {
                                if (pending->ticketID == popID) {
                                    pending->status = "PAID";
                                    break;
                                }
                                pending = pending->link;
                            }
                        }

                    }
                }

                system("CLS");
                return;
            }
            else if (value < 1 || value > i) {
                cout << "-Invalid Input-";
                Beep(520, 520);
                system("CLS");
                continue;
            }
            else {
                system("CLS");
                for (int j = 0; j < value - 1; j++) {
                    if (specificTicket->status == "PAID") {
                        j--;
                    }
                    specificTicket = specificTicket->link;
                }
                while (specificTicket != NULL) {
                    if (specificTicket->status == "PENDING") {
                        break;
                    }
                    specificTicket = specificTicket->link;
                }


                while (true) {
                    int action;
                    cout << "Ticket Information-\n" << endl;
                    cout << "Departure: " << specificTicket->nameDeparture << endl;
                    cout << "Destination: " << specificTicket->nameDestination << endl;
                    cout << "Total: RM " << specificTicket->total << endl;
                    cout << "Distance: " << specificTicket->distance << " KM" << endl;
                    cout << "Passenger Name: " << specificTicket->passengerName << endl;
                    cout << "Passenger ID: " << specificTicket->passengerID << endl;
                    cout << "Ic/Passport Number: " << specificTicket->ic << endl;
                    cout << "Transaction ID: " << specificTicket->transactionID << endl;
                    cout << "Ticket ID: " << specificTicket->ticketID << endl;
                    cout << "Transaction Date: " << specificTicket->transactionDate;
                    cout << "Departure Time: " << specificTicket->departureTime << endl;
                    cout << "\n1-Pay Ticket\n2-Change Ticket" << endl;
                    cout << "\nPlease Make your Choice: ";
                    cin >> action;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "-INVALID INPUT-" << endl;
                        Beep(520, 520);
                        system("CLS");
                        continue;
                    }
                    else if (action > 0 && action <= 3) {
                        if (action == 1) {
                            cout << "Paid" << endl;
                            Beep(520, 520);
                            system("CLS");
                            specificTicket->status = "PAID";
                            staking.insertAtBeginning(specificTicket->ticketID);
                            break;
                        }
                        else if (action == 2) {
                            cout << "Changing Ticket" << endl;
                            Beep(520, 520);
                            system("CLS");
                            break;
                        }

                    }
                    else {
                        cout << "-Invalid Input-";
                        Beep(520, 520);
                        system("CLS");
                        continue;
                    }
                }
            }

        }
    }

    //arrange the order based on ID
    void sortIndex() {
        ticketDataManagement TTDM;
        ticketnode* curr = head;
        while (curr != NULL) {
            TTDM.createTemporaryTicket(curr->nameDeparture, curr->nameDestination, curr->total, curr->distance, curr->passengerName, curr->passengerID, curr->ic, curr->transactionID, curr->ticketID, curr->transactionDate, curr->departureTime, curr->status);
            curr = curr->link;
        }
        curr = TTDM.head;
        ticketnode* index = nullptr;
        if (head == nullptr) {


            return;
        }
        else {
            while (curr != nullptr) {
                index = curr->link;
                while (index != nullptr) {
                    int asize = curr->transactionID.size();
                    int bsize = index->transactionID.size();
                    string a = curr->transactionID.substr(4, asize);
                    string b = index->transactionID.substr(4, bsize);
                    if (stoi(a) > stoi(b)) {
                        swap(curr->nameDeparture, index->nameDeparture);
                        swap(curr->total, index->total);
                        swap(curr->distance, index->distance);
                        swap(curr->passengerName, index->passengerName);
                        swap(curr->passengerID, index->passengerID);
                        swap(curr->ic, index->ic);
                        swap(curr->transactionID, index->transactionID);
                        swap(curr->ticketID, index->ticketID);
                        swap(curr->transactionDate, index->transactionDate);
                        swap(curr->departureTime, index->departureTime);
                        swap(curr->status, index->status);

                    }
                    index = index->link;
                }
                curr = curr->link;
            }

            readAllFromTemp(TTDM);
        }
    }

    bool searchAllResult() {
        system("CLS");
        bool i = false;
        ticketnode* curr = head;
        while (curr != nullptr) {
            cout << "1-NameDeparture: " << curr->nameDeparture << endl;
            cout << "2-NameDestination: " << curr->nameDestination << endl;
            cout << "3-Total: RM " << curr->total << endl;
            cout << "4-Distance: " << curr->distance << endl;
            cout << "5-PassengerName: " << curr->passengerName << endl;
            cout << "6-PassengerID: " << curr->passengerID << endl;
            cout << "7-IC: " << curr->ic << endl;
            cout << "8-TransactionID: " << curr->transactionID << endl;
            cout << "9-TicketID: " << curr->ticketID << endl;
            cout << "10-TransactionDate: " << curr->transactionDate;
            cout << "11-DepartureTime: " << curr->departureTime << endl;
            cout << "12-Status: " << curr->status << endl;
            cout << " " << endl;
            i = true;
            curr = curr->link;
        }
        return i;

    }

    //find specific transaction
    bool searchResult(string name) {
        system("CLS");
        bool i = false;
        ticketnode* curr = head;
        while (curr != nullptr) {
            if (curr->passengerName == name) {
                cout << "1-NameDeparture: " << curr->nameDeparture << endl;
                cout << "2-NameDestination: " << curr->nameDestination << endl;
                cout << "3-Total: RM " << curr->total << endl;
                cout << "4-Distance: " << curr->distance << endl;
                cout << "5-PassengerName: " << curr->passengerName << endl;
                cout << "6-PassengerID: " << curr->passengerID << endl;
                cout << "7-IC: " << curr->ic << endl;
                cout << "8-TransactionID: " << curr->transactionID << endl;
                cout << "9-TicketID: " << curr->ticketID << endl;
                cout << "10-TransactionDate: " << curr->transactionDate;
                cout << "11-DepartureTime: " << curr->departureTime << endl;
                cout << "12-Status: " << curr->status << endl;
                cout << " " << endl;
                i = true;
            }
            curr = curr->link;
        }
        return i;

    }

    //update transaction details
    void modifytickect(string* arr) {
        ticketnode* curr = head;
        while (curr != nullptr) {
            if (curr->transactionID == arr[7]) {
                curr->nameDeparture = arr[0];
                curr->nameDestination = arr[1];
                curr->total = stof(arr[2]);
                curr->distance = stoi(arr[3]);
                curr->passengerName = arr[4];
                curr->passengerID = arr[5];
                curr->ic = arr[6];
                curr->transactionID = arr[7];
                curr->ticketID = arr[8];
                curr->transactionDate = arr[9];
                curr->departureTime = arr[10];
                curr->status = arr[11];
                break;
            }
            curr = curr->link;
        }

    }

    //delete transaction
    void deleteFun(string id) {
        ticketnode* see = head;
        ticketnode* beforedeleted = head;
        ticketnode* dlt;

        if (id == see->ticketID) {
            dlt = see;
            head = head->link;
            delete dlt;
        }
        else {
            while (beforedeleted->link->ticketID != id) {
                beforedeleted = beforedeleted->link;
            }
            dlt = beforedeleted->link;
            beforedeleted->link = dlt->link;
            delete dlt;
        }
    }

    //select the transaction record
    string* readSpecificTicket(string ID) {
        static string arr[12];
        ticketnode* curr = head;
        while (curr != nullptr) {
            if (curr->ticketID == ID) {
                arr[0] = curr->nameDeparture;
                arr[1] = curr->nameDestination;
                arr[2] = to_string(curr->total);
                arr[3] = to_string(curr->distance);
                arr[4] = curr->passengerName;
                arr[5] = curr->passengerID;
                arr[6] = curr->ic;
                arr[7] = curr->transactionID;
                arr[8] = curr->ticketID;
                arr[9] = curr->transactionDate;
                arr[10] = curr->departureTime;
                arr[11] = curr->status;
                break;
            }
            else {
                arr[0] = "N";
            }
            curr = curr->link;
        }
        return arr;

    }

    void readAll() {
        ticketnode* read = head;
        while (read != NULL) {
            cout << "Departure: " << read->nameDeparture << endl;
            cout << "Destination: " << read->nameDestination << endl;
            cout << "Total: " << read->total << endl;
            cout << "Distance: " << read->distance << endl;
            cout << "Passenger: " << read->passengerName << endl;
            cout << "Passenegr ID: " << read->passengerID << endl;
            cout << "Passenger IC: " << read->ic << endl;
            cout << "Transaction ID" << read->transactionID << endl;
            cout << "Ticket ID : " << read->ticketID << endl;
            cout << "Transaction Date: " << read->transactionDate;
            cout << "Departure Time: " << read->departureTime << endl;
            cout << "Status: " << read->status << endl;
            cout << " " << endl;
            read = read->link;
        }
    }

    void readAllFromTemp(ticketDataManagement& TDM) {
        ticketnode* read = TDM.head;
        while (read != NULL) {
            cout << "Departure: " << read->nameDeparture << endl;
            cout << "Destination: " << read->nameDestination << endl;
            cout << "Total: " << read->total << endl;
            cout << "Distance: " << read->distance << endl;
            cout << "Passenger: " << read->passengerName << endl;
            cout << "Passenegr ID: " << read->passengerID << endl;
            cout << "Passenger IC: " << read->ic << endl;
            cout << "Transaction ID" << read->transactionID << endl;
            cout << "Ticket ID : " << read->ticketID << endl;
            cout << "Transaction Date: " << read->transactionDate;
            cout << "Departure Time: " << read->departureTime << endl;
            cout << "Status: " << read->status << endl;
            cout << " " << endl;
            read = read->link;
        }
    }
};

//class for dealing with user linked list
class userDataManagement {
public:
    ticketDataManagement* ptr;
    int size;
    int passengerSize;
    int adminSize;
    usernode* head;

    //constructor set linkedlist
    userDataManagement() {
        passengerSize = 0;
        adminSize = 0;
        size = 0;
        head = NULL;
    }

    void insertAtBeginning(string username, string password, string role, string contact, string ic, string userID) {
        //creating new node
        usernode* newNode = new usernode;
        newNode->username = username;
        newNode->password = password;
        newNode->role = role;
        newNode->contact = contact;
        newNode->ic = ic;

        //for creating new passenger/admin ID only
        if (userID.empty()) {
            if (role == "PASSENGER") {
                passengerSize++;
                userID = "CID" + to_string(passengerSize);
                newNode->userID = userID;
            }
            else if (role == "ADMIN") {
                adminSize++;
                userID = "AID" + to_string(adminSize);
                newNode->userID = userID;
            }

        }
        else {
            newNode->userID = userID;
        }

        if (size == 0) {
            //empty linked list
            newNode->link = NULL;
            head = newNode;
            size++;
        }
        else {
            //set the new node as the first in the linked list
            newNode->link = head;
            head = newNode;
            size++;
        }
    }

    void insertAtSpecificIndex(string username, string password, string role, string contact, string ic, int placement, string userID) {
        //create new node
        usernode* newNode = new usernode;
        newNode->username = username;
        newNode->password = password;
        newNode->role = role;
        newNode->contact = contact;
        newNode->ic = ic;

        //for creating new passenger/admin ID only
        if (userID.empty()) {
            if (role == "PASSENGER") {
                passengerSize++;
                userID = "CID" + to_string(passengerSize);
                newNode->userID = userID;
            }
            else if (role == "ADMIN") {
                adminSize++;
                userID = "AID" + to_string(adminSize);
                newNode->userID = userID;
            }

        }
        else {
            newNode->userID = userID;
        }


        usernode* prev = head;
        for (int i = 0; i < placement - 1; i++) {
            prev = prev->link;
        }
        newNode->link = prev->link;
        prev->link = newNode;
        size++;

    }

    void insertUserData(string username, string password, string role, string contact, string ic, string userID) {
        //first node
        if (head == NULL) {
            insertAtBeginning(username, password, role, contact, ic, userID);
        }
        else {
            //to sort the newnode into the linked list
            usernode* place = head;
            int placement = 0;

            while (place != NULL) {
                //check if the newnode should preceed or suceed the node pointed by "place"
                if (username.compare(place->username) > 0) {
                    //node suceeds
                    place = place->link;
                    placement++;
                }
                else if (username.compare(place->username) < 0) {
                    //node proceeds
                    break;
                }
            }

            if (placement == 0) {
                //node proceeds all (placing it in the first of the linked list)
                insertAtBeginning(username, password, role, contact, ic, userID);
            }
            else {
                //set the node in the specific place
                insertAtSpecificIndex(username, password, role, contact, ic, placement, userID);
            }
        }
    }

    void modifySpecificData(string username, string password, string role, string contact, string ic, string userID) {

        usernode* next = head;
        while (next != NULL) {
            if (username == next->username) {
                next->username = username;
                next->password = password;
                next->role = role;
                next->contact = contact;
                next->ic = ic;
                next->userID = userID;
                break;
            }
            else {
                next = next->link;
            }
        }
    }

    void replaceSpecificNode(string name, string username, string password, string role, string contact, string ic, string userID) {
        usernode* next = head;
        int placement = 0;
        while (next != NULL) {
            //locate node
            if (name != next->username) {
                next = next->link;
                placement++;
            }
            else if (name == next->username) {
                break;
            }
        }

        usernode* prev = head;
        if (placement == 0) {
            head = prev->link;
            delete prev;
        }
        else {
            usernode* remove;
            for (int i = 0; i < placement - 1; i++) {
                prev = prev->link;
            }
            remove = prev->link;
            prev->link = remove->link;
            delete remove;
        }
        size--;
        insertUserData(username, password, role, contact, ic, userID);
    }

    string getid(string username) {
        usernode* find = head;
        while (find != NULL) {
            if (find->username == username) {
                break;
            }
            else {
                find = find->link;
            }

        }
        return (find->userID);
    }

    //read all content
    void readAll() {
        usernode* read = head;
        while (read != NULL) {
            cout << read->username << " " << read->password << " " << read->role << " " << read->contact << " " << read->ic << " " << read->userID << endl;
            read = read->link;
        }
    }

    //get size of linked list
    int getSize() {
        return size;
    }
};

//all passenger/admin function in here
class dataManagement {
public:
    ticketDataManagement* TDMptr;
    userDataManagement* UDMptr;
    stationDataManagement* SDMptr;

    dataManagement(ticketDataManagement& TDM, userDataManagement& UDM, stationDataManagement& SDM) {
        TDMptr = &TDM;
        UDMptr = &UDM;
        SDMptr = &SDM;
    }

    //login signup management
    template <typename T>
    string printArraySelection(T menu[], int sizeOfArray, string methodChoice, string passValue) {
        //print out all of the array data elements
        while (true) {
            int selection;
            for (int i = 0; i < sizeOfArray; i++) {
                cout << (i + 1) << " - " << menu[i] << endl;
            }

            //get user choice
            cout << "Please Make Your Choice: ";
            cin >> selection;

            //error in datatype
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "INVALID INPUT" << endl;
                Beep(520, 520);
                system("CLS");
            }
            //integer within scope
            else if (selection > 0 && selection <= sizeOfArray) {
                //actions for the selection
                if (selection > 0 && selection < sizeOfArray) {
                    if (methodChoice == "loginSignUpSelection") {
                        Beep(520, 520);
                        //selection making
                        loginSignUpSelection(selection);
                        system("CLS");
                    }
                    else if (methodChoice == "roleSelection") {
                        Beep(520, 520);
                        //role selection making
                        string results = roleSelection(selection);
                        return results;
                    }
                    else if (methodChoice == "passengerSelection") {
                        Beep(520, 520);
                        passValue = passengerSelection(selection, passValue);
                    }
                    else if (methodChoice == "adminSelection") {
                        Beep(520, 520);
                        passValue = adminSelection(selection, passValue);
                    }
                    //exit function
                }
                else if (selection == sizeOfArray) {
                    return "none";
                }
            }
            //integer out of scope
            else {
                cout << "INVALID INPUT" << endl;
                Beep(520, 520);
                system("CLS");
            }
        }
    }

    //determine role of user
    string roleSelection(int selection) {
        if (selection == 1) {
            return "ADMIN";
        }
        else {
            return "PASSENGER";
        }

    }

    //getid
    string locateID(string username) {
        usernode* locate = UDMptr->head;
        string results;

        //check it the username correlates to the role
        while (locate != NULL) {
            if (username == locate->username) {
                results = locate->userID;
                return results;
            }
            else {
                locate = locate->link;
            }
        }

        return results;
    }

    //getic
    string locateIC(string ID) {
        usernode* locate = UDMptr->head;
        string results;

        //check it the username correlates to the role
        while (locate != NULL) {
            if (ID == locate->userID) {
                results = locate->ic;
                return results;
            }
            else {
                locate = locate->link;
            }
        }

        return results;
    }

    //delete ticket
    void deleteTicket(string id) {
        ticketnode* beforedeleted = TDMptr->head;
        ticketnode* dlt;

        if (id == beforedeleted->ticketID) {
            dlt = beforedeleted;
            TDMptr->head = TDMptr->head->link;
            delete dlt;
        }
        else {
            while (beforedeleted->link->ticketID != id) {
                beforedeleted = beforedeleted->link;
            }
            dlt = beforedeleted->link;
            beforedeleted->link = dlt->link;
            delete dlt;
        }

    }

    //determine if user wants to login or signup
    void loginSignUpSelection(int selection) {
        if (selection == 1) {
            loginFunction();
        }
        else if (selection == 2) {
            signUpFunction("PASSENGER");
        }
    }

    //signup (only for passenger)
    void signUpFunction(string registrationRole) {
        usernode* validation = UDMptr->head;
        string name;
        string password;
        string role = registrationRole;
        string contact;
        string ic;
        int legitimateInfo = 0;

        while (legitimateInfo == 0) {
            system("CLS");
            cout << "-Please Enter Valid Credentials To Register As A New '" << role << "'-" << endl;
            cout << "\n1- (Input To Exit Feature)" << endl;
            cout << "Please Enter Your Username You Wish To Use: ";
            cin >> name;

            if (name == "1") {
                Beep(520, 520);
                system("CLS");
                return;
            }
            //ensure the name is not unique
            if (ValidateUnique(name, "username") != 0) {
                cout << "-Username Exist, Please Input Another One-" << endl;
                Beep(520, 520);
                system("CLS");
                continue;
            }

            while (true) {
                system("CLS");
                cout << "-Please Enter Valid Credentials To Register As A New '" << role << "'-" << endl;
                cout << "Please Enter Your Username You Wish To Use: " << name << endl;
                cout << "\n1- (Input To Exit Feature)" << endl;
                cout << "Please Enter Your Password You Wish To Use: ";
                cin >> password;

                if (password == "1") {
                    return;
                }

                if (password.empty()) {
                    cout << "-Password Cannot Be Empty!-";
                    continue;
                }
                else {
                    break;
                }
            }
            while (true) {
                system("CLS");
                cout << "-Please Enter Valid Credentials To Register As A New '" << role << "'-" << endl;
                cout << "Please Enter Your Username You Wish To Use: " << name << endl;
                cout << "Please Enter Your Password You Wish To Use: " << password << endl;
                cout << "\n1- (Input To Exit Feature)" << endl;
                cout << "Please Enter Your Malaysian Contact Number: +601";
                cin >> contact;
                Beep(520, 520);
                if (contact == "1") {
                    return;
                }

                if (contact.empty()) {
                    cout << "-Contact Cannot Be Empty!-";
                    continue;
                }
                else {
                    if (contactCheck(contact)) {
                        break;
                    }
                    else {
                        continue;
                    }
                }
            }
            while (true) {
                system("CLS");
                cout << "-Please Enter Valid Credentials To Register As A New '" << role << "'-" << endl;
                cout << "Please Enter Your Username You Wish To Use: " << name << endl;
                cout << "Please Enter Your Password You Wish To Use: " << password << endl;
                cout << "Please Enter Your Malaysian Contact Number: +601" << contact << endl;
                cout << "\n1- (Input To Exit Feature)" << endl;
                cout << "Please Enter Your Malaysian IC/Passport Number: ";
                cin >> ic;
                Beep(520, 520);
                if (ic == "1") {
                    return;
                }

                if (ic.empty()) {
                    cout << "-IC/Passport Number Cannot Be Empty!-";
                    continue;
                }
                else {
                    if (icCheck(ic)) {

                        legitimateInfo = 1;
                        break;
                    }
                    else {
                        continue;
                    }
                }
            }
        }

        //returning (id is left empty to be created)
        UDMptr->insertUserData(name, password, role, contact, ic, "");
        system("CLS");
        cout << "-Successfully Registered! Returning To The Previous Page-" << endl;
        Beep(520, 520);
        system("CLS");
        return;
    }

    //login
    void loginFunction() {

        string name;
        string password;
        string role;
        string validation = "";

        string roleMenu[3] = { "ADMIN","PASSENGER","(Input To Exit Feature)" };
        system("CLS");
        cout << "What Role Would You Like To Log Into:" << endl;
        role = printArraySelection<string>(roleMenu, 3, "roleSelection", "none");

        if (role == "none") {
            return;
        }
        while (true) {
            system("CLS");
            cout << "Role:" << role << endl;
            cout << "\n1- (Input To Exit Feature)" << endl;
            cout << "Please Enter Your Username: ";
            cin >> name;

            if (name == "1") {
                return;
            }
            validation = locateProfile(name, role);
            if (validation.empty()) {
                cout << "\n-Username Doesn't Exist, Please Input Another One-" << endl;
                Beep(520, 520);
                system("CLS");
                continue;
            }
            else {
                while (true) {
                    system("CLS");
                    cout << "Role:" << role << endl;
                    cout << "Username: " << name << endl;
                    cout << "\n1- (Input The Number To Exit Feature)" << endl;
                    cout << "Please Enter Your Password: ";
                    cin >> password;

                    if (password == "1") {
                        return;
                    }
                    if (password == validation) {
                        system("CLS");
                        cout << "-Successfully Logged In! Welcome Back " << name << "-" << endl;
                        string adminMenu[5] = { "View Profile", "Register New Admin", "Modify Subway Station Information", "Manage Passenger Ticket Purchase Information" ,"Exit" };
                        string passengerMenu[5] = { "View Profile","View Booking","Book Ticket","Pay Ticket","Exit" };

                        if (role == "ADMIN") {
                            printArraySelection<string>(adminMenu, 5, "adminSelection", name);
                            return;
                        }
                        else {
                            printArraySelection<string>(passengerMenu, 5, "passengerSelection", name);
                            return;
                        }
                    }
                    else {
                        cout << "\n-Incorrect Password-" << endl;
                        Beep(520, 520);
                        system("CLS");
                        continue;
                    }
                }
            }

        }
    }

    //passenger menu selection
    string passengerSelection(int selection, string name) {
        string username = name;
        //"View Profile", "View Booking", "Book Ticket", "Pay Ticket"
        if (selection == 1) {
            Beep(520, 520);
            username = modifyProfile(username);
            return username;
        }
        else if (selection == 2) {
            string passengerID = locateID(username);

            ticketDataManagement pendingTicket;
            //for stack
            stackDataManagement staking;
            QueueDataManagement queing;
            ticketnode* pending = TDMptr->head;

            //add into second linked list
            while (pending != NULL) {
                if (pending->passengerID == passengerID) {
                    pendingTicket.insertTicketDataWithStatus(pending->nameDeparture, pending->nameDestination, pending->total, pending->distance, pending->passengerName, pending->passengerID, pending->ic, pending->transactionID, pending->ticketID, pending->transactionDate, pending->departureTime, pending->status);
                    pending = pending->link;
                }
                else {
                    pending = pending->link;
                }
            }

            int value;
            int i;
            ticketnode* printOut;
            ticketnode* specificTicket;
            ticketnode* undo;

            while (true) {
                i = 0;
                //for printing
                printOut = pendingTicket.head;
                specificTicket = pendingTicket.head;
                undo = pendingTicket.head;
                system("CLS");

                while (printOut != NULL) {
                    if (printOut->status != "REMOVED") {
                        cout << i + 1 << ") " << printOut->ticketID << endl;
                        i++;
                    }
                    printOut = printOut->link;
                }

                cout << "\n0-Exit" << endl;
                if (staking.size > 0) {
                    cout << "[-1]-Undo Deletion" << endl;
                }
                cout << "Make Your Choice : ";
                cin >> value;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "-INVALID INPUT-" << endl;
                    Beep(520, 520);
                    system("CLS");
                    continue;
                }

                if (staking.size > 0 && value == -1) {
                    string popValue = staking.pop();
                    while (undo != NULL) {
                        if (popValue.compare(undo->ticketID) == 0) {
                            break;
                        }
                        undo = undo->link;
                    }
                    undo->status = "PAID";
                    Beep(520, 520);
                    system("CLS");
                }
                else if (value == 0) {
                    cout << "Exiting";
                    Beep(520, 520);
                    system("CLS");
                    if (staking.size > 0) {
                        undo = pendingTicket.head;
                        while (undo != NULL) {
                            if (undo->status == "REMOVED") {
                                queing.insertAtBeginning(undo->ticketID);
                            }
                            undo = undo->link;
                        }
                        stacknode* agn = queing.head;
                        while (agn != NULL) {
                            agn = agn->link;
                        }
                        agn = queing.head;

                        if (queing.size > 0) {

                            while (queing.size > 0) {
                                string popID = queing.pop();
                                //delete node
                                deleteTicket(popID);
                            }

                        }
                    }
                    system("CLS");

                    return username;
                }
                else if (value < 1 || value > i) {
                    cout << "-Invalid Input-";
                    Beep(520, 520);
                    system("CLS");
                    continue;
                }
                else {
                    system("CLS");
                    for (int j = 0; j < value - 1; j++) {
                        if (specificTicket->status == "REMOVED") {
                            j--;
                        }
                        specificTicket = specificTicket->link;
                    }
                    while (specificTicket != NULL) {
                        if (specificTicket->status != "REMOVED") {
                            break;
                        }
                        specificTicket = specificTicket->link;
                    }


                    while (true) {
                        int action;
                        cout << "Ticket Information-\n" << endl;
                        cout << "Departure: " << specificTicket->nameDeparture << endl;
                        cout << "Destination: " << specificTicket->nameDestination << endl;
                        cout << "Total: " << specificTicket->total << endl;
                        cout << "Distance: " << specificTicket->distance << endl;
                        cout << "Passenger Name: " << specificTicket->passengerName << endl;
                        cout << "Passenger ID: " << specificTicket->passengerID << endl;
                        cout << "Ic/Passport Number: " << specificTicket->ic << endl;
                        cout << "Transaction ID: " << specificTicket->transactionID << endl;
                        cout << "Ticket ID: " << specificTicket->ticketID << endl;
                        cout << "Transaction Date: " << specificTicket->transactionDate << endl;
                        cout << "Departure Time: " << specificTicket->departureTime << endl;
                        cout << "Ticket Status: " << specificTicket->status << endl;
                        cout << "\n1-Delete Ticket\n2-Change Ticket" << endl;
                        cout << "\nPlease Make your Choice: ";
                        cin >> action;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "-INVALID INPUT-" << endl;
                            Beep(520, 520);
                            system("CLS");
                            continue;
                        }
                        else if (action > 0 && action <= 3) {
                            if (action == 1) {
                                if (specificTicket->status == "PAID") {
                                    cout << "DELETED" << endl;
                                    Beep(520, 520);
                                    system("CLS");
                                    specificTicket->status = "REMOVED";
                                    staking.insertAtBeginning(specificTicket->ticketID);
                                    break;
                                }
                                else if (specificTicket->status == "PENDING") {
                                    cout << "CANNOT DELETE TICKETS THAT HAVEN'T BEEN PAID" << endl;
                                    Beep(520, 520);
                                    Sleep(1000);
                                    system("CLS");
                                    continue;
                                }
                            }
                            else if (action == 2) {
                                cout << "Changing Ticket" << endl;
                                Beep(520, 520);
                                system("CLS");
                                break;
                            }

                        }
                        else {
                            cout << "-Invalid Input-";
                            Beep(520, 520);
                            system("CLS");
                            continue;
                        }
                    }
                }

            }
            return username;
        }
        else if (selection == 3) {
            string bookorview[] = { "1-View Station Details","2-Book Ticket","3-Exit" };
            while (true) {
                system("CLS");
                int responce;
                cout << "-BOOK TICKET-" << endl;
                for (int i = 0; i < 3; i++) {
                    cout << bookorview[i] << endl;
                }
                cout << "Please Make Your Choice: ";
                cin >> responce;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "-INVALID INPUT-" << endl;
                    Beep(520, 520);
                    system("CLS");
                    continue;
                }
                else if (responce > 0 && responce < 4) {
                    if (responce == 1) {
                        int stationview;
                        string station[] = { "Titiwangsa","PWTC","Sultan Ismail","Majlis Jamek","Plaza Rakyat","Hang Tuah","Pudu","Chan Sow Lin" };
                        while (true) {
                            system("CLS");
                            for (int i = 0; i < 8; i++) {
                                cout << i + 1 << "-" << station[i] << endl;
                            }
                            cout << "0-Exit" << endl;
                            cout << "Which Station Do You Like To View: ";
                            cin >> stationview;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                cout << "-INVALID INPUT-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                continue;
                            }
                            else if (stationview == 0) {
                                cout << "-Exiting-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                break;
                            }
                            else if (stationview > 0 && stationview < 9) {
                                while (true) {
                                    int changeticket;
                                    stationnode* stationinfo = SDMptr->head;
                                    string stationname = station[stationview - 1];

                                    while (stationname.compare(stationinfo->stationName) != 0) {
                                        stationinfo = stationinfo->nextLink;
                                    }

                                    system("CLS");
                                    cout << "Station Name: " << stationinfo->stationName << endl;
                                    cout << "Station ID: " << stationinfo->stationID << endl;
                                    cout << "Station Information: " << stationinfo->information << endl;
                                    cout << "\n";
                                    if (stationview > 1 && stationview < 9) {
                                        cout << "Previous Station: " << stationinfo->prevLink->stationName << endl;
                                        cout << "Station Cost: " << stationinfo->costPS << endl;
                                        cout << "Station Distance: " << stationinfo->distancePS << endl;
                                        cout << "Station Time: " << stationinfo->timePS << endl;
                                    }
                                    cout << "\n";
                                    if (stationview > 0 && stationview < 8) {
                                        cout << "Next Station: " << stationinfo->nextLink->stationName << endl;
                                        cout << "Station Cost: " << stationinfo->costNS << endl;
                                        cout << "Station Distance: " << stationinfo->distanceNS << endl;
                                        cout << "Station Time: " << stationinfo->timeNS << endl;
                                    }

                                    cout << "\n";
                                    cout << "Press 0 to Change Station: ";
                                    cin >> changeticket;
                                    if (cin.fail()) {
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        cout << "-INVALID INPUT-" << endl;
                                        Beep(520, 520);
                                        system("CLS");
                                        continue;
                                    }
                                    if (changeticket == 0) {
                                        break;
                                    }

                                }
                            }
                            else {
                                cout << "-INVALID INPUT-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                continue;
                            }
                        }
                    }
                    else if (responce == 2) {
                        stationnode* stationchoice;
                        string station[] = { "SID01","SID02","SID03","SID04","SID05","SID06","SID07","SID08" };

                        while (true) {
                            stationchoice = SDMptr->head;
                            int dep, des;
                            system("CLS");
                            cout << "-STATION-" << endl;
                            for (int i = 0; i < 8; i++) {
                                cout << i + 1 << "-" << stationchoice->stationName << endl;
                                stationchoice = stationchoice->nextLink;
                            }
                            cout << "\n0-Exit\nPlease Select Your Departure Station: ";
                            cin >> dep;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                cout << "-INVALID INPUT-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                continue;
                            }
                            if (dep == 0) {

                                cout << "-Exiting-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                break;
                            }
                            if (dep < 1 || dep>8) {
                                cout << "-INVALID INPUT-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                continue;
                            }

                            cout << "Please Select Your Destination Station: ";
                            cin >> des;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                cout << "-INVALID INPUT-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                continue;
                            }
                            if (des == 0) {
                                cout << "-Exiting-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                break;
                            }
                            if (des < 1 || des>8) {
                                cout << "-INVALID INPUT-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                continue;
                            }
                            if (dep == des) {
                                cout << "-Departure Cannot Be The Same As The Destination-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                continue;
                            }
                            string departurevalue = station[dep - 1];
                            string destinationvalue = station[des - 1];

                            while (true) {
                                int decision;
                                float total = 0.0;
                                int km = 0;
                                int time = 0;
                                system("CLS");
                                if (dep < des) {
                                    ticketInformation("SID01", departurevalue, destinationvalue, total, km, time);
                                }
                                else if (dep > des) {
                                    ticketInformation("SID08", departurevalue, destinationvalue, total, km, time);
                                }
                                cout << "\n";
                                cout << "1-Confirm Booking" << endl;
                                cout << "2-Change Booking" << endl;
                                cout << "Your Choice: ";
                                cin >> decision;

                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(10000, '\n');
                                    cout << "-INVALID INPUT-" << endl;
                                    Beep(520, 520);
                                    system("CLS");
                                    continue;
                                }
                                if (decision == 1 || decision == 2) {
                                    if (decision == 1) {
                                        int selectTime;
                                        int departtime = 0;
                                        system("CLS");
                                        float arr[] = {
                                            6.0,6.3,7.0,7.3,8.0,8.3,9.0,9.3,10.0,10.3,11.0,11.3,
                                            12.0,12.3,13.0,13.3,14.0,14.3,15.0,15.3,16.0,16.3,17.0,17.3,
                                            18.0,18.3,19.0,19.3,20.0,20.3,21.0,21.3,22.0,22.3,23.0,23.3,24.0,24.3
                                        };
                                        if (dep < des) {
                                            departtime = departureTime("SID01", departurevalue);
                                        }
                                        else if (dep > des) {
                                            departtime = departureTime("SID08", departurevalue);
                                        }
                                        float dt = float(departtime) + 0.34;
                                        //get mins
                                        if (dt > 0) {
                                            dt = (dt - 0.34) / 100;
                                        }
                                        else {
                                            dt = 0.0;
                                        }


                                        for (int i = 0; i < 38; i++) {
                                            //0.39+6.3=     6.69
                                            float truetime = dt + arr[i];
                                            //6.30 = 6
                                            int checktime = (int)arr[i];
                                            //6.3-6.0=    0.3
                                            float newtime = arr[i] - (float)checktime;
                                            //0.3+0.39 >=0.69
                                            if (newtime + dt >= 0.6) {
                                                if (checktime == 24) {
                                                    cout << i + 1 << "-Possible Departure Time-" << (truetime + 1.0) - 0.6 - 24 << endl;
                                                }
                                                else {
                                                    //6.69+1-0.6
                                                    cout << i + 1 << "-Possible Departure Time-" << (truetime + 1.0) - 0.6 << endl;
                                                }

                                            }
                                            else {
                                                cout << i + 1 << "-Possible Departure Time-" << truetime << endl;
                                            }

                                        }
                                        cout << "Select The Time: ";
                                        cin >> selectTime;

                                        if (cin.fail()) {
                                            cin.clear();
                                            cin.ignore(10000, '\n');
                                            cout << "-INVALID INPUT-" << endl;
                                            Beep(520, 520);
                                            system("CLS");
                                            continue;
                                        }

                                        float truetime2 = dt + arr[selectTime - 1];
                                        int checktime2 = (int)arr[selectTime - 1];
                                        float newtime2 = arr[selectTime - 1] - (float)checktime2;

                                        if (newtime2 + dt >= 0.6) {
                                            if (checktime2 == 24) {
                                                truetime2 = (truetime2 + 1.0) - 0.6 - 24;
                                            }
                                            else {
                                                truetime2 = (truetime2 + 1.0) - 0.6;
                                            }
                                        }


                                        cout << "-Creating Ticket-" << endl;
                                        Beep(520, 520);
                                        system("CLS");
                                        createNewTicket(departurevalue, destinationvalue, total, km, username, to_string(truetime2));
                                        break;

                                    }
                                    else if (decision == 2) {
                                        cout << "-Cancelling Booking-" << endl;
                                        Beep(520, 520);
                                        system("CLS");
                                        break;
                                    }

                                }
                                else {
                                    cout << "-INVALID INPUT-" << endl;
                                    Beep(520, 520);
                                    system("CLS");
                                    continue;
                                }

                            }


                            ////////////////////////////////////////////////////////////////////////////
                        }
                    }
                    else if (responce == 3) {
                        cout << "-Exiting-" << endl;
                        Beep(520, 520);
                        system("CLS");
                        return username;
                    }
                }
                else {
                    cout << "-INVALID INPUT-" << endl;
                    Beep(520, 520);
                    system("CLS");
                    continue;
                }
            }


            //
        }
        else if (selection == 4) {
            string passengerID = UDMptr->getid(username);
            TDMptr->retrievePendingData(passengerID);
            return username;

        }
    }

    void ticketInformation(string start, string dep, string des, float& RM, int& KM, int& MN) {
        float total = 0.0;
        int km = 0;
        int time = 0;
        float* x = &RM;
        int* y = &KM;
        int* z = &MN;

        stationnode* departure;
        if (start == "SID01") {
            departure = SDMptr->head;
            while (departure->stationID != dep) {
                departure = departure->nextLink;
            }
            while (departure->stationID != des) {
                total += departure->costNS;
                km += departure->distanceNS;
                time += departure->timeNS;
                departure = departure->nextLink;
            }
        }
        else {
            departure = SDMptr->tail;
            while (departure->stationID != dep) {
                departure = departure->prevLink;
            }
            while (departure->stationID != des) {
                total += departure->costPS;
                km += departure->distancePS;
                time += departure->timePS;
                departure = departure->prevLink;
            }
        }

        cout << "TOTAL: RM" << total << endl;
        cout << "TOTAL DISTANCE TRAVELLED: " << km << " KM" << endl;
        cout << "DURATION: " << time << " MINUTES" << endl;
        *x = total;
        *y = km;
        *z = time;

    }

    int departureTime(string start, string end) {
        int time = 0;

        stationnode* departure;
        if (start == "SID01") {
            departure = SDMptr->head;
            while (departure->stationID != end) {
                time += departure->timeNS;
                departure = departure->nextLink;
            }
        }
        else {
            departure = SDMptr->tail;
            while (departure->stationID != end) {
                time += departure->timePS;
                departure = departure->prevLink;
            }
        }

        return time;
    }

    string adminSelection(int selection, string name) {
        string username = name;
        //"View Profile", "Register New Admin", "Modify Subway Station Information", "Manage Passenger Ticket"
        if (selection == 1) {
            Beep(520, 520);
            username = modifyProfile(username);
            return username;
        }
        else if (selection == 2) {
            signUpFunction("ADMIN");
            return username;
        }
        else if (selection == 3) {
            readallstation();
            system("CLS");
            return username;
            //
        }
        else if (selection == 4) {
            manageTicket();
            return username;
            //
        }
    }

    void manageTicket() {
        try {
            int selection;
            stackDataManagement TSD;
            while (true) {
                system("CLS");
                cout << "Manage Menu" << endl;
                cout << "1-view ticket\n2-Edit ticket\n3-Delete ticket\n4-Sort order\n5-Exit" << endl;
                cout << "Enter your selection: ";
                cin >> selection;
                if (selection == 1) {
                    system("CLS");
                    int ticketsselection;
                    cout << "0-Exit\n1-View All Ticket\n2-Search Ticket" << endl;
                    cout << "Your Choice: ";
                    cin >> ticketsselection;

                    system("CLS");
                    if (ticketsselection == 1)
                    {
                        while (true) {
                            system("CLS");
                            TDMptr->searchAllResult();
                            int proceed;
                            cout << "Press 0 to Change Feature:";
                            cin >> proceed;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                cout << "-INVALID INPUT-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                continue;
                            }
                            else if (proceed == 0) {
                                break;
                            }
                            else {
                                cout << "-INVALID INPUT-" << endl;
                                Beep(520, 520);
                                system("CLS");
                                continue;
                            }
                        }
                    }
                    if (ticketsselection == 2) {
                        while (true) {
                            string name;
                            cout << "0-Exit\nEnter customer name to search: ";
                            cin >> name;

                            if (name == "0") {
                                system("CLS");
                                break;
                            }
                            bool val = false;
                            val = TDMptr->searchResult(name);
                            if (val == true) {
                                cout << "Search successfully!!" << endl;
                            }
                            else {
                                cout << "No result is found!!" << endl;
                            }
                        }
                    }
                }
                else if (selection == 2) {
                    while (true) {
                        system("CLS");
                        float total;
                        int distance;
                        string nameDeparture, nameDestination, transactionID, ticketID, transactionDate, departureTime, status;
                        string* list;
                        cout << "0-Exit\nEnter the Ticket ID you want to edit: ";
                        cin >> ticketID;
                        list = TDMptr->readSpecificTicket(ticketID);
                        if (ticketID == "0") {
                            system("CLS");
                            break;
                        }
                        if (list[0] == "N") {
                            cout << "Invalid Input, Reenter your choice!" << endl;
                            Sleep(1000);
                            continue;
                        }
                        else {
                            cout << "\n";
                            while (true) {

                                cout << "1-NameDeparture : " << list[0] << endl;//
                                cout << "2-NameDestination : " << list[1] << endl;//
                                cout << "3-Total : " << list[2] << endl;//
                                cout << "4-Distance : " << list[3] << endl;//
                                cout << "5-PassengerName : " << list[4] << endl;
                                cout << "6-PassengerID : " << list[5] << endl;
                                cout << "7-IC : " << list[6] << endl;
                                cout << "8-TransactionID : " << list[7] << endl;
                                cout << "9-TicketID : " << list[8] << endl;
                                cout << "10-TransactionDate : " << list[9];
                                cout << "11-DepartureTime : " << list[10] << endl;//
                                cout << "12-Status :" << list[11] << endl;
                                cout << "\n0-Back\nEnter your selection to change: ";
                                int selection;
                                cin >> selection;
                                bool con = false;

                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(10000, '\n');
                                    cout << "-INVALID INPUT-" << endl;
                                    Beep(520, 520);
                                    system("CLS");
                                    continue;
                                }
                                if (selection == 0) {
                                    system("CLS");
                                    break;
                                }
                                else if (selection == 5 || selection == 6 || selection == 7 || selection == 8 || selection == 9 || selection == 10 || selection == 12) {
                                    cout << "This cannot be edit!!!\n" << endl;
                                    Sleep(1000);
                                    system("CLS");
                                    continue;
                                }
                                else if (selection == 1) {
                                    cout << "New Departure: ";
                                    cin >> nameDeparture;
                                    list[0] = nameDeparture;
                                    con = true;
                                    system("CLS");
                                }
                                else if (selection == 2) {
                                    cout << "New Destination: ";
                                    cin >> nameDestination;
                                    list[1] = nameDestination;
                                    con = true;
                                    system("CLS");
                                }
                                else if (selection == 3) {
                                    cout << "New Total : ";
                                    cin >> total;
                                    list[2] = to_string(total);
                                    con = true;
                                    system("CLS");
                                }
                                else if (selection == 4) {
                                    cout << "New Distance: ";
                                    cin >> distance;
                                    list[3] = to_string(distance);
                                    con = true;
                                    system("CLS");
                                }
                                else if (selection == 11) {
                                    cout << "New DepartureTime : ";
                                    cin >> departureTime;
                                    list[10] = departureTime;
                                    con = true;
                                    system("CLS");
                                }
                                else {
                                    cout << "Fail to update!! Enter correct selection!\n" << endl;
                                    Sleep(1000);
                                    continue;
                                }
                                if (cin.fail()) {
                                    con = false;
                                    throw 505;
                                }
                                if (con == true) {
                                    TDMptr->modifytickect(list);
                                    cout << "Update successful!!" << endl;
                                }

                            }
                        }
                    }
                }
                else if (selection == 3) {
                    while (true) {
                        system("CLS");
                        string ID;
                        bool val;
                        cout << "0-Exit" << endl;
                        if (TSD.size > 0) {
                            cout << "[-1]-Undo Deletion" << endl;
                        }
                        cout << "Enter your the ticket ID that you want to delete: ";
                        cin >> ID;
                        int idSize = ID.size();
                        if (ID == "0") {
                            system("CLS");
                            while (TSD.size > 0) {
                                string valuepop = TSD.pop();
                                deleteTicket(valuepop);
                            }
                            break;
                        }
                        if (TSD.size > 0 && ID.compare("-1") == 0) {
                            string popValue = TSD.pop();
                            ticketnode* undo = TDMptr->head;
                            while (undo != NULL) {
                                if (popValue.compare(undo->ticketID) == 0) {
                                    break;
                                }
                                undo = undo->link;
                            }
                            if (undo->status == "RNP") {
                                undo->status = "PENDING";
                            }
                            else if (undo->status == "RP") {
                                undo->status = "PAID";
                            }
                            Beep(520, 520);
                            system("CLS");
                        }
                        else if (idSize < 5) {
                            cout << "Invalid Input!!" << endl;
                            Sleep(1000);
                            system("CLS");
                        }
                        else {
                            val = TDMptr->temptdlt(ID, &TSD);

                            //val = TDMptr->deleteFun(ID, stack);
                            if (val != true) {
                                cout << "Fail to delete!!" << endl;
                                Sleep(1000);
                                system("CLS");
                            }
                            else {
                                cout << "Delete Successful" << endl;
                                Sleep(1000);
                                system("CLS");
                            }
                        }
                    }
                }
                else if (selection == 4) {
                    while (true) {
                        system("CLS");
                        int choice;
                        int sel;
                        cout << "Sort Menu" << endl;
                        cout << "1-Sort passenger name in ascending\n2-Sort in index\n3-Exit" << endl;
                        cout << "Enter your choice" << endl;
                        cin >> sel;
                        if (sel == 1) {
                            while (true) {
                                system("CLS");
                                TDMptr->readAll();
                                cout << "Press 0 to Change Sorting:";
                                cin >> choice;

                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(10000, '\n');
                                    cout << "-INVALID INPUT-" << endl;
                                    Beep(520, 520);
                                    system("CLS");
                                    continue;
                                }
                                else if (choice == 0) {
                                    cout << "-Returning-" << endl;
                                    Beep(520, 520);
                                    system("CLS");
                                    break;
                                }
                            }
                        }
                        else if (sel == 2) {
                            while (true) {
                                system("CLS");
                                TDMptr->sortIndex();
                                //TDMptr->readAll();
                                cout << "Press 0 to Continue:";
                                cin >> choice;

                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(10000, '\n');
                                    cout << "-INVALID INPUT-" << endl;
                                    Beep(520, 520);
                                    system("CLS");
                                    continue;
                                }
                                else if (choice == 0) {
                                    cout << "-Returning-" << endl;
                                    Beep(520, 520);
                                    system("CLS");
                                    break;
                                }
                            }
                        }
                        else if (sel == 3) {
                            cout << "Exit!!!" << endl;
                            break;
                        }
                        else {
                            cout << "Invalid input!" << endl;
                            continue;
                        }
                    }
                }
                else if (selection == 5) {
                    cout << "Exit successfully!" << endl;
                    Beep(520, 520);
                    Sleep(1000);
                    system("CLS");
                    break;
                }
                else {
                    cout << "Please enter correct number selection" << endl;
                    Beep(520, 520);
                    Sleep(1000);
                    break;
                }
            }
        }
        catch (...) {
            cout << "Invalid Input!!" << endl;
            Beep(520, 520);
            Sleep(1000);
        }


    }

    void readallstation() {
        int stationview;
        string station[] = { "SID01","SID02","SID03","SID04","SID05","SID06","SID07","SID08" };
        while (true) {
            system("CLS");
            for (int i = 0; i < 8; i++) {
                cout << i + 1 << "-" << station[i] << endl;
            }
            cout << "0-Exit" << endl;
            cout << "Which Station Do You Like To View: ";
            cin >> stationview;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "-INVALID INPUT-" << endl;
                Beep(520, 520);
                system("CLS");
                continue;
            }
            else if (stationview == 0) {
                cout << "-Exiting-" << endl;
                Beep(520, 520);
                system("CLS");
                return;
            }
            else if (stationview > 0 && stationview < 9) {
                while (true) {
                    string section[] = { "stationName" ,"information" ,"costPS" ,"distancePS" ,"timePS" ,"costNS" ,"distanceNS","timeNS" };
                    int changeticket;
                    stationnode* stationinfo = SDMptr->head;
                    string stationname = station[stationview - 1];

                    while (stationname.compare(stationinfo->stationID) != 0) {
                        stationinfo = stationinfo->nextLink;
                    }

                    system("CLS");
                    cout << "Station ID: " << stationinfo->stationID << endl;
                    cout << "1- Station Name: " << stationinfo->stationName << endl;
                    cout << "2- Station Information: " << stationinfo->information << endl;
                    cout << "\n";
                    if (stationview > 1 && stationview < 9) {
                        cout << "Previous Station: " << stationinfo->prevLink->stationName << endl;
                        cout << "3- Station Cost: RM" << stationinfo->costPS << endl;
                        cout << "4- Station Distance: " << stationinfo->distancePS << "KM" << endl;
                        cout << "5- Station Time: " << stationinfo->timePS << " Minutes" << endl;
                    }
                    cout << "\n";
                    if (stationview > 0 && stationview < 8) {
                        cout << "Next Station: " << stationinfo->nextLink->stationName << endl;
                        cout << "6- Station Cost: RM" << stationinfo->costNS << endl;
                        cout << "7- Station Distance: " << stationinfo->distanceNS << "KM" << endl;
                        cout << "8- Station Time: " << stationinfo->timeNS << " Minutes" << endl;
                    }

                    cout << "\n";
                    cout << "Press 0 to Change Station: " << endl;
                    cout << "What Section Would You Like To Modify: ";
                    cin >> changeticket;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "-INVALID INPUT-" << endl;
                        Beep(520, 520);
                        system("CLS");
                        continue;
                    }
                    if (changeticket == 0) {
                        system("CLS");
                        break;
                    }
                    else if (changeticket > 0 && changeticket < 9) {
                        if (stationview == 8 && changeticket > 5) {
                            cout << "-INVALID INPUT-" << endl;
                            Beep(520, 520);
                            system("CLS");
                            continue;
                        }
                        else if (stationview == 1 && (changeticket == 3 || changeticket == 4 || changeticket == 5)) {
                            cout << "-INVALID INPUT-" << endl;
                            Beep(520, 520);
                            system("CLS");
                            continue;
                        }
                        else {
                            string stringvalue;
                            int intvalue;
                            float floatvalue;

                            while (true) {
                                if (changeticket == 2) {
                                    system("CLS");
                                    SDMptr->modifystationinformation(stationinfo->stationID);
                                    break;
                                }
                                else {
                                    cout << "Input New values: ";
                                    if (changeticket == 1) {
                                        cin >> stringvalue;
                                    }
                                    if (changeticket == 3 || changeticket == 6) {
                                        cin >> floatvalue;
                                    }
                                    else if (changeticket == 5 || changeticket == 8 || changeticket == 4 || changeticket == 7) {
                                        cin >> intvalue;
                                    }

                                    if (cin.fail()) {
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        cout << "-INVALID INPUT-" << endl;
                                        Beep(520, 520);
                                        system("CLS");
                                        continue;
                                    }
                                    else {
                                        if (changeticket == 1) {
                                            stationinfo->stationName = stringvalue;
                                        }
                                        else if (changeticket == 3 || changeticket == 6) {
                                            if (changeticket == 3) {
                                                stationinfo->costPS = floatvalue;
                                            }
                                            else if (changeticket == 6) {
                                                stationinfo->costNS = floatvalue;
                                            }
                                            SDMptr->updateDLL(stationinfo->stationID);
                                        }
                                        else if (changeticket == 5 || changeticket == 8 || changeticket == 4 || changeticket == 7) {
                                            if (changeticket == 4) {
                                                stationinfo->distancePS = intvalue;
                                            }
                                            else if (changeticket == 5) {
                                                stationinfo->timePS = intvalue;
                                            }
                                            else if (changeticket == 7) {
                                                stationinfo->distanceNS = intvalue;
                                            }
                                            else if (changeticket == 8) {
                                                stationinfo->timeNS = intvalue;
                                            }
                                            SDMptr->updateDLL(stationinfo->stationID);
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                        return;
                    }

                }
            }
            else {
                cout << "-INVALID INPUT-" << endl;
                Beep(520, 520);
                system("CLS");
                continue;
            }
        }
    }

    //login username and password retrieval
    string locateProfile(string thingToLocate, string locateRole) {
        usernode* locate = UDMptr->head;
        string results = "";

        //check it the username correlates to the role
        while (locate != NULL) {
            if ((thingToLocate == locate->username) && (locateRole == locate->role)) {
                results = locate->password;
                return results;
            }
            else {
                locate = locate->link;
            }
        }

        return results;
    }

    //check to make sure username is unique
    int ValidateUnique(string thingToCheck, string elementInLL) {
        usernode* validation = UDMptr->head;
        int results = 0;

        if (elementInLL == "username") {
            while (validation != NULL) {
                if (thingToCheck == validation->username) {
                    results = 1;
                    return results;
                }
                else {
                    validation = validation->link;
                }
            }
        }
        return results;
    }

    //{ modify admin/passenger profile
    int profileModification(int modifiedInformation, string(&info)[4]) {
        string category[4] = { "Username:","Password:","Malaysia Contact Number: +601","Malaysian IC/Passport:" };
        string value;
        //integer within scope
        if (modifiedInformation > 0 && modifiedInformation <= 4) {
            while (true) {
                if (modifiedInformation == 1) {
                    while (true) {
                        cout << "Please Enter Your new " << category[modifiedInformation - 1];
                        cin >> value;
                        //ensure the name is not unique
                        if (ValidateUnique(value, "username") != 0) {
                            cout << "-Username Exist, Please Input Another One-" << endl;
                            Beep(520, 520);
                            system("CLS");
                            continue;
                        }
                        else {
                            info[modifiedInformation - 1] = value;
                            return 1;
                        }
                    }
                }
                else {
                    while (true) {
                        cout << "Please Enter Your new " << category[modifiedInformation - 1];
                        cin >> value;

                        if (value.empty()) {
                            cout << "-Changes Cannot Be Empty!-" << endl;
                            system("CLS");
                            Beep(520, 520);
                            continue;
                        }
                        else {
                            if (modifiedInformation == 3) {
                                if (contactCheck(value)) {
                                    info[modifiedInformation - 1] = value;
                                    return 1;
                                }
                                else {
                                    system("CLS");
                                    continue;
                                }
                            }
                            else if (modifiedInformation == 4) {
                                if (icCheck(value)) {
                                    info[modifiedInformation - 1] = value;
                                    system("CLS");
                                    return 1;
                                }
                                else {
                                    system("CLS");
                                    continue;
                                }
                            }
                            else {
                                Beep(520, 520);
                                system("CLS");
                                info[modifiedInformation - 1] = value;
                                return 1;
                            }
                        }
                    }
                }
            }

        }
        //integer out of scope
        else {
            cout << "INVALID INPUT" << endl;
            Beep(520, 520);
            system("CLS");
            return 0;
        }
    }

    string modifyProfile(string username) {
        usernode* locate = UDMptr->head;
        int modifiedInformation;
        string password;
        string role;
        string contact;
        string ic;
        string userID;

        //find the profile information
        while (locate != NULL) {
            if (username == locate->username) {
                password = locate->password;
                role = locate->role;
                contact = locate->contact;
                ic = locate->ic;
                userID = locate->userID;
                break;
            }
            else {
                locate = locate->link;
            }
        }
        string info[4] = { username,password,contact,ic };
        while (true) {
            system("CLS");
            cout << "-PROFILE INFORMATION-" << endl;
            cout << "Role: " << role << endl;
            cout << role << " " << "ID: " << userID << endl;
            cout << "1-Username: " << info[0] << endl;
            cout << "2-Password: " << info[1] << endl;
            cout << "3-contact: +601" << info[2] << endl;
            cout << "4-IC/Passport: " << info[3] << endl;
            cout << "5- (Input To Exit Function)" << endl;
            cout << "Select A Section To Modify: ";
            cin >> modifiedInformation;

            //error in datatype
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "INVALID INPUT" << endl;
                Beep(520, 520);
                system("CLS");
                continue;
            }
            else if (modifiedInformation == 5) {
                system("CLS");
                return username;
            }
            else if (profileModification(modifiedInformation, info) != 1) {
                cout << "-Invalid Input!-" << endl;
                Beep(520, 520);
                system("CLS");
                continue;
            }
            else {
                system("CLS");
                if (username == info[0]) {
                    UDMptr->modifySpecificData(info[0], info[1], role, info[2], info[3], userID);
                    cout << "-Profile Successfully Modified!-" << endl;
                    Beep(520, 520);
                }
                else {
                    UDMptr->replaceSpecificNode(username, info[0], info[1], role, info[2], info[3], userID);
                    cout << "-Profile Successfully Modified!-" << endl;
                    username = info[0];
                    Beep(520, 520);
                    if (role == "PASSENGER") {
                        Beep(520, 520);
                        ticketnode* updateName = TDMptr->head;
                        while (updateName != NULL) {
                            if (info[0].compare(updateName->passengerName) != 0) {
                                updateName->passengerName = username;
                            }
                            updateName = updateName->link;
                        }
                    }
                }
            }
        }
    }

    //check contect
    boolean contactCheck(string contact) {
        if (contact[0] == '1' || contact[0] == '5') {
            if (contact.size() != 9) {
                system("CLS");
                cout << "-Incorrect Format-" << endl;
                Beep(520, 520);
                return false;
            }
            else {
                for (int i = 1; i < contact.size(); i++) {
                    if (!(isdigit(contact[i]))) {
                        system("CLS");
                        cout << "-Incorrect Format-" << endl;
                        Beep(520, 520);
                        return false;
                    }
                }
                return true;
            }
        }
        else {
            if (contact.size() != 8) {
                system("CLS");
                cout << "-Incorrect Format-" << endl;
                Beep(520, 520);
                return false;
            }
            else {
                return true;
            }
        }
    }

    // check ic/passport-number
    boolean icCheck(string ic) {
        //ic
        if (ic.size() == 12) {
            for (int i = 0; i < ic.size(); i++) {
                if (!(isdigit(ic[i]))) {
                    system("CLS");
                    cout << "-Incorrect Format-" << endl;
                    Beep(520, 520);
                    return false;
                }
            }
            return true;
        }
        //passport
        else if (ic.size() == 9) {
            if (ic[0] == 'A' || ic[0] == 'H' || ic[0] == 'K') {
                if (ic.size() != 9) {
                    system("CLS");
                    cout << "-Incorrect Format-" << endl;
                    Beep(520, 520);
                    return false;
                }
                else {
                    for (int i = 1; i < ic.size(); i++) {
                        if (!(isdigit(ic[i]))) {
                            system("CLS");
                            cout << "-Incorrect Format-" << endl;
                            Beep(520, 520);
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        else {
            system("CLS");
            cout << "-Incorrect Format-" << endl;
            Beep(520, 520);
            return false;
        }
    }
    //}

    void createNewTicket(string nameDeparture, string nameDestination, float total, int distance, string passengerName, string ttime) {

        if (ttime[1] == '.') {
            ttime.resize(4);
            ttime[1] = ':';
        }
        else {
            ttime.resize(5);
            ttime[2] = ':';
        }

        if (TDMptr->head == NULL) {
            insertTkAtBeginning(nameDeparture, nameDestination, total, distance, passengerName, ttime);
        }
        else {
            //to sort the newnode into the linked list
            ticketnode* place = TDMptr->head;
            int placement = 0;

            while (place != NULL) {
                //check if the newnode should preceed or suceed the node pointed by "place"
                if (passengerName.compare(place->passengerName) > 0) {
                    //node suceeds
                    place = place->link;
                    placement++;
                }
                else if (passengerName.compare(place->passengerName) == 0) {
                    //node next to
                    place = place->link;
                    placement++;
                }
                else if (passengerName.compare(place->passengerName) < 0) {
                    //node proceeds
                    break;
                }
            }

            if (placement == 0) {
                //node proceeds all (placing it in the first of the linked list)
                insertTkAtBeginning(nameDeparture, nameDestination, total, distance, passengerName, ttime);
            }
            else {
                //set the node in the specific place
                insertTkAtSpecificIndex(nameDeparture, nameDestination, total, distance, passengerName, placement, ttime);
            }
        }
    }

    void insertTkAtBeginning(string nameDeparture, string nameDestination, float total, int distance, string passengerName, string ttime) {
        string passengerID = locateID(passengerName);
        string ic = locateIC(passengerID);

        time_t now = time(0);
        const char* dt = ctime(&now);
        string transactiontime = dt;

        TDMptr->ticketSize++;
        TDMptr->transactionSize++;
        string ticket = "TKID" + to_string(TDMptr->ticketSize);
        string transactID = "TSID" + to_string(TDMptr->transactionSize);
        ticketnode* newnode = new ticketnode;
        newnode->nameDeparture = nameDeparture;
        newnode->nameDestination = nameDestination;
        newnode->total = total;
        newnode->distance = distance;
        newnode->passengerName = passengerName;
        newnode->passengerID = passengerID;
        newnode->ic = ic;
        newnode->transactionID = transactID;
        newnode->ticketID = ticket;
        newnode->transactionDate = dt;
        newnode->departureTime = ttime;
        newnode->status = "PENDING";


        if (TDMptr->ticketSize == 0) {
            //empty linked list
            newnode->link = NULL;
            TDMptr->head = newnode;
        }
        else {
            //set the new node as the first in the linked list
            newnode->link = TDMptr->head;
            TDMptr->head = newnode;
        }
    }

    void insertTkAtSpecificIndex(string nameDeparture, string nameDestination, float total, int distance, string passengerName, int placement, string ttime) {
        string passengerID = locateID(passengerName);
        string ic = locateIC(passengerID);
        TDMptr->ticketSize++;
        TDMptr->transactionSize++;
        string ticket = "TKID" + to_string(TDMptr->ticketSize);
        string transactID = "TSID" + to_string(TDMptr->transactionSize);

        time_t now = time(0);
        const char* dt = ctime(&now);
        string transactiontime = dt;

        ticketnode* newnode = new ticketnode;
        newnode->nameDeparture = nameDeparture;
        newnode->nameDestination = nameDestination;
        newnode->total = total;
        newnode->distance = distance;
        newnode->passengerName = passengerName;
        newnode->passengerID = passengerID;
        newnode->ic = ic;
        newnode->transactionID = transactID;
        newnode->ticketID = ticket;
        newnode->transactionDate = dt;
        newnode->departureTime = ttime;
        newnode->status = "PENDING";

        ticketnode* prev = TDMptr->head;
        for (int i = 0; i < placement - 1; i++) {
            prev = prev->link;
        }
        newnode->link = prev->link;
        prev->link = newnode;
    }

};

//class for dealing with hardcoded data
class hardCodeData {
public:
    hardCodeData() {}
    //hardcode user data into the linked list
    void hardCodeUserData(userDataManagement& UDM) {
        UDM.insertUserData("eamon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("aamon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("zamon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("famon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("bamon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("damon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("camon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("hamon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("gamon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("iamon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("lamon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("jamon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("kamon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("manon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("namon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("nnon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("ooon", "chin", "PASSENGER", "68843213", "020711130551", "");
        UDM.insertUserData("admin", "chin", "ADMIN", "68843213", "020711130551", "");
        UDM.insertUserData("admin1", "chin", "ADMIN", "68843213", "020711130551", "");
    }
    void hardCodeStationData(stationDataManagement& SDM) {
        SDM.InsertAtEnd("Titiwangsa", "SID01", "none for now", 0, 0, 0, 0.4, 4, 3);
        SDM.InsertAtEnd("PWTC", "SID02", "none for now", 0.4, 4, 3, 0.8, 8, 7);
        SDM.InsertAtEnd("Sultan Ismail", "SID03", "none for now", 0.8, 8, 7, 0.8, 8, 7);
        SDM.InsertAtEnd("Majlis Jamek", "SID04", "none for now", 0.8, 8, 7, 0.6, 6, 5);
        SDM.InsertAtEnd("Plaza Rakyat", "SID05", "none for now", 0.6, 6, 5, 1.0, 10, 9);
        SDM.InsertAtEnd("Hang Tuah", "SID06", "none for now", 1.0, 10, 9, 0.5, 5, 4);
        SDM.InsertAtEnd("Pudu", "SID07", "none for now", 0.5, 5, 4, 0.5, 5, 4);
        SDM.InsertAtEnd("Chan Sow Lin", "SID08", "none for now", 0.5, 5, 4, 0, 0, 0);
    }
    void hardCodeTicketData(dataManagement& DM) {
        DM.createNewTicket("Titiwangsa", "Chan Sow Lin", 4.60, 46, "eamon", "6.09");
        DM.createNewTicket("Hang Tuah", "Sultan Ismail", 1.50, 50, "zamon", "6.09");
        DM.createNewTicket("Pudu", "PWTC", 3.70, 37, "famon", "6.09");
        DM.createNewTicket("Masjid Jamek", "Pudu", 2.10, 21, "zamon", "6.09");
        DM.createNewTicket("Plaza Rakyat", "Titiwangsa", 3.60, 26, "bamon", "6.09");
        DM.createNewTicket("Hang Tuah", "Chan Sow Lin", 1, 10, "camon", "6.09");
        DM.createNewTicket("Chan Sow Lin", "PWTC", 4.20, 42, "aamon", "6.09");
        DM.createNewTicket("PWTC", "Hang Tuah", 2.60, 32, "gamon", "6.09");
        DM.createNewTicket("PWTC", "Plaza Rakyat", 3.60, 22, "zamon", "6.09");
        DM.createNewTicket("Pudu", "Hang Tuah", 0.50, 5, "hamon", "6.09");
        DM.createNewTicket("Sultan Ismail", "Plaza Rakyat", 2.20, 14, "damon", "6.09");
        DM.createNewTicket("Hang Tuah", "Pudu", 1.50, 5, "namon", "6.09");
        DM.createNewTicket("Titiwangsa", "Plaza Rakyat", 2.60, 26, "mamon", "6.09");
        DM.createNewTicket("PWTC", "Titiwangsa", 0.40, 4, "zamon", "6.09");
        DM.createNewTicket("Sultan Ismail", "Chan Sow Lin", 3.40, 34, "kamon", "6.09");
        DM.createNewTicket("Majlis Jamek", "Hang Tuah", 1.60, 16, "jamon", "6.09");
        DM.createNewTicket("Sultan Ismail", "Pudu", 2.90, 29, "lamon", "6.09");
        DM.createNewTicket("Pudu", "Masjid Jamek", 2.10, 21, "iamon", "6.09");
    }
};

int main()
{
    //set instance
    ticketDataManagement TDM;
    userDataManagement UDM;
    stationDataManagement SDM;

    //allow access to other class instances
    dataManagement DM(TDM, UDM, SDM);

    //hardcode the data
    hardCodeData HD;
    //hardcode user data
    HD.hardCodeUserData(UDM);
    //hardcode station data
    HD.hardCodeStationData(SDM);
    HD.hardCodeTicketData(DM);

    //login/sign up selection
    string loginSignUpSelection[3] = { "Login","Signup","Exit" };
    DM.printArraySelection<string>(loginSignUpSelection, 3, "loginSignUpSelection", "none");

}