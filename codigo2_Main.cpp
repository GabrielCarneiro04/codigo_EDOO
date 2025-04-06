#include <iostream>

#include "list.hpp"

using namespace std;

int main()
{
	int nCases;
	cin >> nCases;
	string cmd;

	for (int caseNo = 0; caseNo < nCases; caseNo++) {
		SQ<int>* sqs[100]; 
		int count = 1; 
		sqs[0] = new SQ<int>(QUEUE);

		while (cin >> cmd) {
			if (cmd == "END") break;
			else if (cmd == "ADD") {
				int i, v;
				cin >> i >> v;
				sqs[i]->push(v);
			}
			else if (cmd == "DEL") {
				int i;
				cin >> i;
				if (sqs[i]->size() > 0)
					sqs[i]->pop();
			}
			else if (cmd == "SPL") {
				int i;
				cin >> i;
				for (int j = count; j > i + 1; j--) {
					sqs[j] = sqs[j - 1];
				}
				sqs[i + 1] = sqs[i]->split();
				count++;
			}
			else if (cmd == "MER") {
				int i, j;
				cin >> i >> j;
				if (i == j) continue;
				sqs[i]->merge(sqs[j]);
				delete sqs[j];
				for (int k = j; k < count - 1; k++) {
					sqs[k] = sqs[k + 1];
				}
				count--;
			}
			else if (cmd == "TRA") {
				int i;
				cin >> i;
				sqs[i]->transform();
			}
		}

		cout << "caso " << caseNo << ":";
		for (int i = 0; i < count; i++) {
			if (sqs[i]->size() == 0)
				cout << " ?";
			else
				cout << " " << sqs[i]->peek();
		}
		cout << endl;

		for (int i = 0; i < count; i++) {
			delete sqs[i];
		}

		string rest;
		getline(cin, rest); 
	}
}
