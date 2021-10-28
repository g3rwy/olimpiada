#include <iostream>
#include <algorithm>
#include <vector>

typedef unsigned int uint;

using namespace std;

#define LOGARRAY(x,l) for(uint i = 0; i < l; ++i) cout << x[i] << " ";
#define LOGSOL(x,l) for(uint i = 0; i < l; ++i) cout << x[i].idx << " " << x[i].start_day << "|";
#define LOGVID(x,l) for(uint i = 0; i < l; ++i) cout << x[i].days << " " << x[i].dedline  << " " << i +1<<" <-i \n";
#define LOG(x,sep) cout << x << sep;

struct video {
	uint days,dedline; // intentional error
};

struct solution { uint idx, start_day;};

/*	void delete_vids(video vids[],const uint &vid_count,const uint& day){
		for (uint i = 0; i < vid_count; ++i)
		{
			if(vids[i].days == 0) continue;
			if(!(day + vids[i].days - 1 <= vids[i].dedline)){
				vids[i] = {0,0};
			}
		}
	}
*/

void delete_vids(video vids[],const uint &vid_count,const uint& day){
	for (uint i = 0; i < vid_count; ++i)
	{
		const bool t = (day + vids[i].days - 1 <= vids[i].dedline) ;
		vids[i].days    *= t;
		vids[i].dedline *= t;
	}
}

/*	solution choose_video(video vids[],const uint &vid_count, uint &day){
		uint max_vids_left = 0, max_vids_idx = 0;
		uint temp_day = day;
		uint possibl_count;

		for (uint i = 0; i < vid_count; ++i){
			if(vids[i].days == 0) continue;

			temp_day = day + vids[i].days - 1;
			possibl_count = 0;
			
			for (uint j = 0; j < vid_count; ++j)
				possibl_count += (temp_day <= vids[j].dedline) && (vids[j].days != 0);
			

			if(possibl_count > max_vids_left){
				max_vids_left = possibl_count;
				max_vids_idx = i;
			}

		}
		
		solution res = {max_vids_idx + 1,day};
		
		day += vids[max_vids_idx].days;
		vids[max_vids_idx] = {0,0};

		return res;
	}
*/

solution choose_video(video vids[],const uint &vid_count, uint &day){
	uint min_vids_diff = 4294967295, min_vids_idx = 0;
	uint temp_day = day;

	for (uint i = 0; i < vid_count; ++i){
		if(vids[i].days == 0) continue;

		temp_day = day + vids[i].days - 1;
		const uint t = vids[i].dedline - temp_day;

		if(t < min_vids_diff){
			min_vids_diff = t;
			min_vids_idx = i;
		}
		
	}
	
	solution res = {min_vids_idx + 1,day};
	
	day += vids[min_vids_idx].days;
	vids[min_vids_idx] = {0,0};

	return res;
}

bool pred(video i) { return i.days == 0;}

int main(){
	uint videos_count = 0;
	uint current_day = 1;

	cin >> videos_count;


	video* videos = new video[videos_count];

	vector<solution> res;
	res.reserve(videos_count);
	 
	for (uint i = 0; i < videos_count; ++i) cin >> videos[i].days >> videos[i].dedline;

	delete_vids(videos,videos_count,current_day);
	
	while(count_if(videos, videos + videos_count, pred) < videos_count){
		res.push_back(choose_video(videos,videos_count,current_day));
		delete_vids(videos,videos_count,current_day);
	}

	delete[] videos;

	//LOGVID(videos,videos_count)
	//LOG("===","\n")
	// Write answer
	LOG(res.size(),"\n")
	for(solution s : res) cout << s.idx << " " << s.start_day << "\n";

	return 0;
}