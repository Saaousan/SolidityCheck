//
// Created by xiaofeng on 2019/11/29.
//

//This program is used to detect warnings caused by private modifiers

//source file

/*
author=_xiaofeng_
*/

//Detection: By detecting state variables modified by private modifiers

//using head files
#include "PriModifier.h"
#include <iostream>

//constructor
PriModifier::PriModifier(const string _report_name, const vector<string> _content) {
    report_name = _report_name;
    content = _content;
    PrName = "Unencrypted private data on-chain";
    OtherOperation = "It is a common misconception that private type variables cannot be read. \n"
                     "Even if your contract is not published, attackers can look at contract \n"
                     "transactions to determine values stored in the state of the contract. For\n"
                     " this reason, it's important that unencrypted private data is not stored in\n"
                     " the contract code or state.\nBug level: warning";
}

//destructor
PriModifier::~PriModifier() {
    report_name.clear();
    content.clear();
    PrName.clear();
    OtherOperation.clear();
    row_number.clear();
}

//PriModifier::Detection,Detecting vulnerabilities and
//adding lines of code into row_number(vector<int>) that may have vulnerability
void PriModifier::Detection() {
    for (int i = 0; i < content.size(); i++) {
        //a vulnerability exists when a line contains "private" but does not contain "function" or "modifier"
        if ((content[i].find(PRI) < content[i].size()) &&
            (content[i].find(PR_FUN) > content[i].size() || content[i].find(PR_MOD) > content[i].size()))
            row_number.push_back((i + 1));
        else
            continue;
    }
}

//PriModifier::MakeReport,stitching test results
string PriModifier::MakeReport(const vector<int>& _row_number) {
    if (_row_number.empty()) {
        return "No unencrypted private data on-Chain.\n\n";
    }
    string _report = "";
    _report += "[Bug 1]\n";
    _report += "bug name: ";
    _report += PrName;
    _report += '\n';
    _report += "number of bugs: ";
    _report += to_string(_row_number.size());
    _report += '\n';
    _report += "row number: ";
    for (auto i = _row_number.begin(); i != _row_number.end(); i++) {
        _report += to_string((*i));
        _report += " ";
    }
    _report += '\n';
    if (OtherOperation.size() != 0) {
        _report += "additional description: ";
        _report += OtherOperation;
        _report += '\n';
    }
    return _report;
}

//return number of vulnerabilities
int PriModifier::GetNumber() {
    return row_number.size();
}

//return row_number
vector<int> PriModifier::GetRowNumber() {
    return row_number;
}

void PriModifier::Re_Detection()
{
    regex reg{ PR_RE_PRIVATE };
    for (int i = 0; i < content.size(); i++) {
        //a vulnerability exists when a line contains "private" but does not contain "function" or "modifier"
        if ((content[i].find(PRI) < content[i].size()) && (content[i].find(PR_FUN) > content[i].size() || content[i].find(PR_MOD) > content[i].size()))
            row_number.push_back((i + 1));
        else
            continue;
    }
}
