#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

//DATA is here

map<string, map<string, vector<string>>> KEYWORD_DATA = {
    {"valid", {
        {"medical",  {"hospitalized","surgery","emergency","diagnosed","illness",
                      "injury","accident","doctor","physician","clinic","hospital",
                      "prescription","medication","treatment","admitted","confinement",
                      "quarantine","infection","disease","medical emergency",
                      "broken bone","fracture","severe infection","intensive care",
                      "stroke","cardiac arrest","loss of limb","amputation",
                      "high fever","serious injury","medical certificate",
                      "panic attack","anxiety attack","seizure","asthma attack",
                      "allergic reaction","food poisoning","appendicitis",
                      "hospitalization","emergency room","ER visit","bedridden",
                      "lab test","medical procedure","check-up","blood test"}},
        {"family",   {"funeral","death","deceased","passed away","family emergency",
                      "calamity","flood","typhoon","fire","evacuation",
                      "death in family","bereavement","caregiving emergency",
                      "died","relative hospitalized","immediate family",
                      "house fire","missing family member","family accident",
                      "parent hospitalized","sibling hospitalized","spouse hospitalized",
                      "family calamity","natural disaster","displaced",
                      "newborn emergency","family crisis"}},
        {"official", {"government","court","legal","summons","hearing",
                      "appointment","clearance","certificate","document",
                      "court hearing","legal summons","police incident",
                      "government appointment","official meeting",
                      "immigration issue","document processing",
                      "enrollment requirement","administrative requirement",
                      "barangay clearance","NBI clearance","passport appointment",
                      "civil registry","SSS appointment","PhilHealth",
                      "school competition","academic competition","field trip",
                      "school event","official representation","varsity game",
                      "interschool event","department of health","LGU requirement"}}
    }},
    {"weak", {
        {"vague",    {"not feeling well","felt sick","exhausted","headache",
                      "stomachache","dizzy","unwell","body ache","body pain",
                      "fever","under the weather","not in good condition",
                      "feeling weak","not okay","feeling bad","slightly sick",
                      "mild fever","runny nose","cough and cold","sore throat",
                      "not at my best","low energy","feeling off"}},
        {"personal", {"personal reason","family matter","family reason",
                      "private matter","something came up","personal matter",
                      "private reason","unexpected issue","personal concern",
                      "urgent matter","unavoidable circumstances","unforeseen event",
                      "personal problem","family obligation","home situation",
                      "had to stay home","needed at home"}},
        {"transport",{"traffic","no transportation","vehicle broke down",
                      "car problem","commute","no fare","late bus","road block",
                      "train delay","missed bus","car trouble","traffic jam",
                      "heavy traffic","bus delay","jeepney delay","ride delay",
                      "grab delay","long queue","commute delay","flat tire",
                      "no transport available","transport issue","no ride",
                      "stranded","missed my ride","delayed commute",
                      "no jeepney","no tricycle","terminal problem"}}
    }},
    {"suspicious", {
        {"avoidance",   {"didnt want to","did not want","didnt feel like",
                         "felt lazy","overslept","slept in","forgot",
                         "wasnt interested","no mood","lost track of time",
                         "didnt feel like going","didnt want to go",
                         "wasnt in the mood","too tired to go","couldnt be bothered",
                         "felt bored","not motivated","didnt bother",
                         "decided not to go","chose not to attend",
                         "just wanted to rest","wanted to stay home",
                         "was playing","was gaming","stayed up late"}},
        {"vague_excuse",{"just because","no reason","various reasons",
                         "several reasons","many reasons","etc","and so on",
                         "for some reason","reasons","stuff happened",
                         "things came up","you know why","i had my reasons",
                         "personal stuff","some issues","blah blah",
                         "other things","i just didnt","i cant explain"}},
        {"inconsistent",{"but went out","but attended","but went to",
                         "still went","went anyway","but arrived elsewhere",
                         "but was seen","but i was at","instead went",
                         "ended up going","went somewhere else",
                         "was at the mall","was hanging out","went with friends",
                         "but posted online","but was online","was streaming"}}
    }}
};

map<string, map<string, int>> KEYWORD_SCORES = {
    {"valid",      {{"medical",90},  {"family",90},   {"official",90}}},
    {"weak",       {{"vague",  45},  {"personal",45}, {"transport",45}}},
    {"suspicious", {{"avoidance",5}, {"vague_excuse",5}, {"inconsistent",5}}}
};

map<string, int> BONUS = {
    {"valid",+3}, {"weak",+1}, {"suspicious",-5}
};

//lowercase a string is here

string toLower(string s) {
    for (auto& c : s) c = tolower(c);
    return s;
}

//Initial output(loop) is here

int evaluate(const string& input) {
    string low = toLower(input);
    map<string, int> bonusCount = {{"valid",0},{"weak",0},{"suspicious",0}};
    int baseScore = 0, bonusScore = 0;
    bool baseSet  = false, found = false;

    for (const auto& [cat, subcats] : KEYWORD_DATA) {
        for (const auto& [subcat, keywords] : subcats) {
            for (const auto& kw : keywords) {
                if (low.find(toLower(kw)) == string::npos) continue;
                found = true;

                if (!baseSet) {
                    baseScore = KEYWORD_SCORES[cat][subcat];
                    baseSet   = true;
                    cout << "\n--------------------"
                         << "\nMatched  : " << kw       << "\n"
                         << "Category : " << cat      << "\n"
                         << "Subcat   : " << subcat   << "\n"
                         << "Base     : " << baseScore << "\n"
                         << "--------------------\n";
                } else if (bonusCount[cat] < 3) {
                    bonusScore += BONUS[cat];
                    bonusCount[cat]++;
                    cout << "--------------------"
                         << "\nMatched  : " << kw << "\n"
                         << "Bonus    : " << (BONUS[cat] >= 0 ? "+" : "") << BONUS[cat] << "\n"
                         << "--------------------\n";
                }
            }
        }
    }

    if (!found) return -1;

    cout << "\n====================\n"
         << "Base    : " << baseScore  << "\n"
         << "Bonus   : " << (bonusScore >= 0 ? "+" : "") << bonusScore << "\n"
         << "Total   : " << baseScore + bonusScore << "\n"
         << "====================\n";

    return baseScore + bonusScore;
}

//MAIN is here

int main() {
    cout << "==============================\n"
         << "  ABSENCE EXCUSE VALIDATOR\n"
         << "==============================\n";

    char again = 'Y';

    while (toupper(again) == 'Y') {
        string input;
        cout << "\nEnter your excuse:\n> ";
        getline(cin, input);

        int score = evaluate(input);

        if (score == -1) {
            cout << "\n[X] No valid keyword found. Try again.\n";

        } else if (score >= 80) {
            cout << "\nWould you like your letter to be validated? (Y/N): ";
            char validate; cin >> validate; cin.ignore();

            if (toupper(validate) == 'Y') {
                cout << "\n[✓] Excuse validated. You are excused!\n";
            } else {
                cout << "\n[!] Validation skipped.\n";
            }

        } else if (score >= 50) {
            cout << "\n[!] Weak excuse. Ask your professor for approval.\n"
                 << "    Professor approved? (Y/N): ";
            char approval; cin >> approval; cin.ignore();
            cout << (toupper(approval) == 'Y'
                ? "\n[✓] Approved. You are excused!\n"
                : "\n[X] Not approved. Absence unexcused.\n");

        } else {
            cout << "\nWould you like your letter to be validated? (Y/N): ";
            char validate; cin >> validate; cin.ignore();

            if (toupper(validate) == 'Y') {
                cout << "\n[X] Letter not valid. Please write a better excuse.\n";
            } else {
                cout << "\n[!] Validation skipped.\n";
            }
        }

        cout << "\nSubmit another excuse? (Y/N): ";
        cin >> again;
        cin.ignore();
    }

    cout << "\nGoodbye!\n";
    return 0;
}