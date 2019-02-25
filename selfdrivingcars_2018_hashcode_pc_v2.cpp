#include <iostream>
#include <fstream>
#include <stdio.h>
#include <queue>
#include <deque>
#include <cstdlib>
#include <iostream>
#include<bits/stdc++.h>

	int R;
    int C;
    int T;
    int B;
    int F;
    int N;


using namespace std;

int distance(int x1,int y1,int x2,int y2){
	int dist = abs(y1 - y2) + abs(x1 - x2);
	return dist;
}


class taxi {
public:

	int end_X;
	int end_Y;
	deque<int> rides;
	int available;

};

class ride {
public:

	int r1_ride;
	int r2_ride;
	int n_num;
	int x_pos;
	int y_pos;
	int start;
	int finish; 

	int ddistance(){
		int dist = distance(r1_ride, r2_ride, x_pos, y_pos);
		return dist;
	}
	
	ride(int thisr1, int thisr2,int thisxpos, int thisypos, int thisstart, int thisfinish, int thisnum){
		r1_ride = thisr1;
		r2_ride = thisr2;
		x_pos = thisxpos;
		y_pos = thisypos;
		start = thisstart;
		finish = thisfinish;
		n_num = thisnum;
	}


};





bool comp(ride r1,ride r2){
	bool boolean = r1.start < r2.start;
	return boolean;
}


class compare{
public:

	bool operator() (taxi tx1, taxi tx2){
		bool op = tx1.available > tx2.available;
		return op;
	}
};

priority_queue<taxi, vector<taxi>, compare> taxis;
deque <ride> que;

int main() {

	int TWOH = 200;
	int ONE = 1;
	int TWO = 2;
	int choice = 2;
	
	int e;
	int	r1;
	int r2;
	int finish;
	int start;
	int x_pos;
	int y_pos;
	int count_c;

	string outp;
	string inp;
	
	if(choice == 0){
		inp = "a_example.in";
		outp = "a_example.out"; 
	}else if(choice == 1){
		inp = "b_should_be_easy.in";
		outp = "b_example.out"; 
	}else if(choice == 2){
		inp = "c_no_hurry.in";
		outp = "c_no_hurry.out";
	}else if(choice == 3){
		inp = "d_metropolis.in";
		outp = "d_metropolis.out";
	}else if(choice == 4){
		inp = "e_high_bonus.in";
		outp = "e_high_bonus.out"; 
	}

	
	ifstream inf("b_example.in");
	
	if(!inf.is_open()){
		cout << "close";
		return -1;
	}
	else {
		cout << "open\n";
	}
	
		inf >> R >> C >> F >> N >> B >> T;

	for(e = 0; e < N; e++){

		inf >> r1 >> r2 >> x_pos >> y_pos >> start >> finish;
		ride tx(r1,r2,x_pos,y_pos,start,finish,e);
		que.push_back(tx);

	}
	inf.close();

	sort(que.begin(), que.end(), comp);

	int j = 0;
	
	while(j < F){
		taxi tx;
		tx.end_X = 0;
		tx.end_Y = 0;
		tx.available= 0;
		
		taxis.push(tx);
		j++;
	}


	long distance_total = 0;

	while(taxis.top().available < T && que.size() > 0){
	
		taxi tx = taxis.top();
		taxis.pop();
		

		int pos_best = -ONE;
		long long txnum_best = INT_MIN;
		
	    e = 0;
		
		while(e < que.size()){
			if( max(distance( tx.end_X, tx.end_Y, que[e].r1_ride, que[e].r2_ride) + tx.available ,que[e].start) + que[e].ddistance() >= que[e].finish){
				continue;
			}
			
			long long txpnum = que[e].ddistance();
			
			if (distance( tx.end_X, tx.end_Y, que[e].r1_ride, que[e].r2_ride) + tx.available < que[e].start){
				txpnum = txpnum + B;
			}
			
			txpnum = txpnum - (distance(tx.end_X, tx.end_Y, que[e].r1_ride, que[e].r2_ride) + max(que[e].start - (distance( tx.end_X, tx.end_Y, que[e].r1_ride, que[e].r2_ride) + tx.available), 0)) * TWOH;
			
			if(txpnum > txnum_best) {
				pos_best = e;
				txnum_best = txpnum;
			}
			
			e++;
		}
		if(pos_best < 0) {
			tx.available = T + TWO;
			taxis.push(tx);
			continue;
		}
		
		distance_total = distance_total + que[pos_best].ddistance();
		
		if (distance(tx.end_X, tx.end_Y, que[pos_best].r1_ride, que[pos_best].r2_ride) + tx.available <= que[pos_best].start){
			distance_total = distance_total + B;
		}
		
		tx.rides.push_back(que[pos_best].n_num);
		tx.available = max(distance(tx.end_X, tx.end_Y, que[pos_best].r1_ride, que[pos_best].r2_ride) + tx.available, que[pos_best].start) + que[pos_best].ddistance();

		tx.end_X = que[pos_best].x_pos;
		tx.end_Y = que[pos_best].y_pos;
		
		taxis.push(tx);
		que.erase(que.begin() + pos_best);
	}

	ofstream outf("b_example.out");

	while(!taxis.empty()){
		
		
		taxi tx = taxis.top();
		taxis.pop();
		
		outf << tx.rides.size();
		
		int o = 0;
		
		while(o < tx.rides.size()) {
			outf << tx.rides[e];
			++o;
		}
		outf << endl;
	}
	outf.close();
	
	cout << distance_total;

	return 0;
}
