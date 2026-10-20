// =====================================================================
//  C++ WARM-UP  ·  African Olympiad Academy
//
//  The question descriptions are in README.md. Read them there.
//  This file holds the data, one worked example, and your answers.
//
//  BUILD AND RUN:   g++ -std=c++17 -Wall -o run warmup.cpp && ./run
//            or:    ./run.sh
//
//  Work on ONE question at a time. Write it, run it, check the output
//  against the README, commit it, move on.
// =====================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

/**
 * THE RECORD
 * One delivery: who brought it, how much, and what grade it was given.
 */
struct Delivery {
    string farmer;
    double kg;
    char   grade;
};


/**
 * THE DATA
 * Do not change these. Every expected answer in the README comes from exactly this data.
 */

// Q1 — one morning's weights, in the order they were weighed
vector<double> morningWeights = {
    45.5, 80.0, 12.0, -3.0, 66.5, 20.0, 31.0, 95.0, 50.0, 18.5, 0.0, 72.0
};

// Q2, Q3, Q4, Q7, Q8 — the day's logbook
vector<Delivery> logbook = {
    {"Keza",    45.5, 'A'},
    {"Bonu",    80.0, 'B'},
    {"Isanda",  20.0, 'A'},
    {"Keza",    12.0, 'C'},
    {"Onyinye", 66.5, 'B'},
    {"Karimi",  31.0, 'A'},
    {"Karimi",  31.0, 'A'},
    {"Keza",    18.5, 'B'},
    {"Bonu",    50.0, 'C'},
    {"Isanda",  20.0, 'A'},
    {"Onyinye", 72.0, 'A'}
};   // yes, one of these rows is in here twice. Q8 is about that.

// Q5 — records as the volunteers typed them, before any checking. Several of these are wrong. That is the point.
struct RawRecord {
    string id;
    string kg;        // text, because a volunteer can type anything
    char   grade;
};

vector<RawRecord> rawRecords = {
    {"F012", "45.5",  'A'},
    {"F7",   "20",    'A'},
    {"F033", "heavy", 'B'},
    {"F021", "0",     'C'},
    {"F044", "80",    'b'},
    {"F055", "",      'A'},
    {"F066", "31.5",  'D'},
    {"F077", "92",    'B'}
};

// Q6 — an Igisoro board. 16 pits, in sowing order.
//      Position 0 is unused so that board[1] really is pit 1.
vector<int> board = {0, 0, 0, 1, 0, 0, 4, 1, 0, 0, 2, 2, 0, 1, 5, 0, 0};


// ---------------------------------------------------------------------
//  A HELPER YOU MAY FIND USEFUL
// ---------------------------------------------------------------------
void printBoard(const vector<int> &b) {
    for (int i = 1; i <= 16; i++) cout << b[i] << " ";
    cout << "\n";
}
int findFarmer(const vector<Delivery> &log, string name);



int main() {

    // =================================================================
    //  WORKED EXAMPLE  ·  not a question
    //
    //  This is the house style: walk the data once, keep what you need
    //  as you go, print at the end. Read it before you start Q1.
    //
    //  It answers: how many deliveries were grade A, and what was the
    //  heaviest single delivery in the whole logbook?
    // =================================================================

    int gradeACount = 0;
    Delivery heaviest = logbook[0];        // start from a REAL entry,
                                           // never from a made-up 0
    for (Delivery d : logbook) {
        if (d.grade == 'A') {
            gradeACount++;
        }
        if (d.kg > heaviest.kg) {
            heaviest = d;                  // keep the WHOLE record,
        }                                  // not just the number
    }

    cout << "=== Worked example ===\n";
    cout << "Grade A deliveries: " << gradeACount << "\n";
    cout << "Heaviest: " << heaviest.farmer << " with "
         << heaviest.kg << " kg\n\n";


    // =================================================================
    //  Q1  ·  THE WEIGHING SESSION          (see README)
    //  Uses: morningWeights
    // =================================================================

    cout << "=== Q1 ===\n";
    int valids=0,pos=0,finalpos,consecvalids=0;
    vector<int> conses;
    double heavy=morningWeights[0],sum=0;
    for (double i:morningWeights){
        sum+=i;
        if (0.0<i and i<=80.0){
            valids+=1;
            consecvalids+=1;
        }else{
            conses.push_back(consecvalids);
            consecvalids=0;
        }
        if (i>heavy){
            heavy=i;
            finalpos=pos;
        }
        pos+=1;
    }
    double maximum=*max_element(conses.begin(),conses.end());
    cout<<"Total: "<<sum<<"kg"<<'\n';
    cout<<"Valid: "<<valids<<" of "<<"12"<<'\n';
    cout<<"Heaviest: "<<heavy<<" kg"<<" at position "<<finalpos<<'\n';
    cout<<"Longest Valid Run: "<<maximum<<'\n';



    cout << "\n";


    // =================================================================
    //  Q2  ·  GRADE SUMMARY                 (see README)
    //  Uses: logbook
    // =================================================================

    cout << "=== Q2 ===\n";
    map<char,vector<double>> grades;
    grades['A']=vector<double>(3);
    grades['B']=vector<double>(3);
    grades['C']=vector<double>(3);

    for (Delivery d: logbook){
         if (d.grade=='A'){
            grades['A'][0]+=1;
            grades['A'][1]+=d.kg;
         }else if (d.grade=='B'){
            grades['B'][0]+=1;
            grades['B'][1]+=d.kg;
         }else if (d.grade=='C'){
            grades['C'][0]+=1;
            grades['C'][1]+=d.kg;
         }
         
    }
    grades['A'][2]=grades['A'][1]/grades['A'][0];
         grades['B'][2]=grades['B'][1]/grades['B'][0];
         grades['C'][2]=grades['C'][1]/grades['C'][0];
         cout<<"Grade A: "<<grades['A'][0]<<" deliveries "<< grades['A'][1]<<" kg total "<< grades['A'][2]<<" average"<<'\n';
         cout<<"Grade B: "<<grades['B'][0]<<" deliveries "<< grades['B'][1]<<" kg total "<< grades['B'][2]<<" average"<<'\n';
         cout<<"Grade C: "<<grades['C'][0]<<" deliveries "<< grades['C'][1]<<" kg total "<< grades['C'][2]<<" average"<<'\n';





    cout << "\n";


    // =================================================================
    //  Q3  ·  WHO IS WHO                    (see README)
    //  Uses: logbook, and the findFarmer function you write below main
    // =================================================================

    cout << "=== Q3 ===\n";
    cout<<findFarmer(logbook,"Isanda")<<'\n';
    cout<<findFarmer(logbook,"Mukamana")<<'\n';
    map<string,pair<int,double>> mostest;
    for (Delivery d:logbook){
        mostest[d.farmer].first++;
        mostest[d.farmer].second+=d.kg;

    }
    int mostcount=0;
    double mostkg=0;
    string countname, kgname;
    for (auto d: mostest){
        if (d.second.second>mostkg){
            kgname=d.first;
            mostkg=d.second.second;
        }
        if (d.second.first>mostcount){
            countname=d.first;
            mostcount=d.second.first;
        }
    }
    cout<<"Most deliveries: "<<countname<<"("<<mostcount<<")"<<"\n";
    cout<<"Most kg: "<<kgname<<"("<<mostkg<<")"<<"\n";





    cout << "\n";


    // =================================================================
    //  Q4  ·  PAYMENT RUN WITH A DAILY CAP  (see README)
    //  Uses: logbook, and the payment function you write below main
    // =================================================================

    cout << "=== Q4 ===\n";
    string farmname;
    double weight,tots;
    for (Delivery d:logbook){
        weight=d.kg*450.0;
        if (d.grade=='A'){
            weight+=weight*0.1;
        }else if(d.grade=='C'){
            weight-=weight*0.2;
        }
        if (tots>=100000.0){
            weight-=weight*0.5;
        }
        tots+=weight;
        cout<<d.farmer<<' '<<d.kg<<" kg "<< " grade "<<d.grade<<" -> "<<weight<<'\n';
        
    }
    cout<<"Total paid: "<<tots;




    cout << "\n";


    // =================================================================
    //  Q5  ·  THE VALIDATION REPORT         (see README)
    //  Uses: rawRecords
    // =================================================================

    cout << "=== Q5 ===\n";
    int rejects=0, accepted=0;
    for (RawRecord r: rawRecords){
        if (r.id.size()!=4){
            cout <<r.id<< " REJECT - bad id\n";
            rejects++;
            continue;
        }
        int count=1;
        bool rejected=false;
        for (char k : r.id){
            if (count==1){
                count++;
                if (k!='F'){
                    cout<< r.id<<" REJECT - bad id\n";
                    rejected=true;
                    break;
                }
            }else{
                if (!isdigit(k)){
                    cout<<r.id<<" REJECT - bad id\n";
                    rejected=true;
                    break;
                }
            }
        }
        if (rejected){
            rejects++;
            continue;
        }
        string s=r.kg;
        if (s.empty()){
            cout<<r.id<<" REJECT - weight missing\n";
            rejects++;
            continue;
        }
        bool isNumber = true;
        int dots = 0;

        for (char c : s) {
            if (c == '.') {
                dots++;
                if (dots > 1) {
                    isNumber = false;
                    break;
                }
            }else if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }
        if (!isNumber){
            cout<<r.id<<" REJECT - weight not a number\n";
            rejects++;
            continue;
        }
        double w=stod(s);
        if (w<=0 || w>80){
            cout<<r.id << " REJECT - weight out of range\n";
            rejects++;
            continue;
        }
        char grade = toupper(r.grade);

        if (grade != 'A' && grade != 'B' && grade != 'C') {
            cout << r.id << " REJECT - unknown grade\n";
            rejects++;

            continue;
        }
                cout <<r.id<< " ACCEPT\n";
                accepted++;
            }    
            
                    cout << accepted << " accepted, " << rejects<< " rejected.";

    cout << "\n";

    // =================================================================
    //  Q6  ·  IGISORO: A FULL TURN          (see README)
    //  Uses: board
    // =================================================================

    cout << "=== Q6 ===\n";
    bool turn=true;
    int bnumb=6;
    int land,lap=0;
    while (turn){
        lap++;
        int pick=board[bnumb];
        board[bnumb]=0;
        for (int seeds=0;seeds<pick;seeds++){
            int drop=(bnumb+seeds)%16+1;
            board[drop]++;
            if (seeds==pick-1){
                if (board[drop]-1==0){
                    land=drop;
                    turn=false;
                }else{
                    bnumb=drop;
                }
            }
        }
    }
    cout<<"Final board: ";
    for (int i : board){
        cout<<i<<' ';
    }
    cout<<'\n';
    cout<<"Landed in pit "<<land<<" after "<<lap<<" laps";


    
    // =================================================================
    //  STRETCH  ·  optional
    // =================================================================

    // =================================================================
    //  Q7  ·  SORT THE LOGBOOK              (see README)
    //  Uses: logbook
    // =================================================================

    // cout << "=== Q7 ===\n";





    // =================================================================
    //  Q8  ·  SPOTTING DOUBLE-ENTRIES       (see README)
    //  Uses: logbook
    // =================================================================

    // cout << "=== Q8 ===\n";





    return 0;
}
int findFarmer(const vector<Delivery> &log, string name){
    int count=0;
    for (Delivery d:log){
        if (d.farmer==name){
            return count;
        }else{
            count+=1;
        }

    }
    return -1;
}



// =====================================================================
//  FUNCTIONS YOU WRITE
//
//  C++ reads a file top to bottom, so a function must be DECLARED above
//  the place that calls it. These two are declared here at the bottom,
//  which main() cannot see — so move them ABOVE main(), or leave a
//  one-line declaration up there. Working that out is part of Q3.
// =====================================================================

// Q3:  return the position of the first delivery by this farmer,
//      or -1 if the farmer is not in the log at all.
//
// int findFarmer(const vector<Delivery> &log, string name) {
//
// }


// Q4:  what one delivery earns, before any cap is applied.
//      Grade A pays 10% above the rate, B pays the rate,
//      anything else pays 20% below it. The rate is 450.
//
// double payment(double kg, char grade) {
//
// }
