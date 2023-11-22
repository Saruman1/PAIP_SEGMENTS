#include <iostream>
#include <ctime>
#include <vector>
#include<cmath>

using namespace std;

struct point
{
	char c;
	float x;
	float y;
};
struct segment
{
	point first;
	point second;
	int quarter = 0;
};
float calculateLength(segment &segment)
{
	return sqrt(pow(segment.second.x - segment.first.x, 2) + pow(segment.second.y - segment.first.y, 2));
}
float calculateMaxLength(vector<segment>& segments)
{
	float maxLength = 0;
	for (segment& s : segments)
	{
		float length = calculateLength(s);
		if (length >= maxLength)
			maxLength = length;
	}
	return maxLength;
}
float calculateMinLength(vector<segment>& segments)
{
	float minLength = 10000000;
	for (segment& s : segments)
	{
		float length = calculateLength(s);
		if (minLength >= length)
			minLength = length;
	}
	return minLength;
}
void sortSegmentsByQuarter(vector<segment> &segments)
{   
	int n = segments.size();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (segments[j].quarter > segments[j + 1].quarter) {
				segment temp = segments[j];
				segments[j] = segments[j + 1];
				segments[j + 1] = temp;
			}
		}
	}
}
void sortSegmentsByLength(vector<segment>& segments)
{
	for (int i = 0, n = segments.size(); i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (calculateLength(segments[j]) > calculateLength(segments[j + 1]))
			{
				segment temp = segments[j];
				segments[j] = segments[j + 1];
				segments[j + 1] = temp;
			}
		}
	}
}
void createSegments(int N)
{
	if (N > 26)
	{
		cout << "N must be less or equal 26\n";
	}
	else
	{
		int index = 0;
		srand(time(NULL));
		vector<point> points(26);
		vector<segment> segments;
		for (char i = 'A'; i <= 'Z'; i++)
		{
			points[index].c = i;
			points[index].x = 500 - rand() % 1000;
			points[index].y = 500 - rand() % 1000;
			index++;
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = i + 1; j < N; j++)
			{
				segment s;
				s.first = points[i];
				s.second = points[j];

				if (s.first.x > 0 && s.first.y > 0 && s.second.x > 0 && s.second.y > 0)
					s.quarter = 1;
				if (s.first.x < 0 && s.first.y > 0 && s.second.x < 0 && s.second.y > 0)
					s.quarter = 2;
				if (s.first.x < 0 && s.first.y < 0 && s.second.x < 0 && s.second.y < 0)
					s.quarter = 3;
				if (s.first.x > 0 && s.first.y < 0 && s.second.x > 0 && s.second.y < 0)
					s.quarter = 4;

				segments.push_back(s);
				cout << segments.back().first.c << segments.back().second.c << endl;
			}
		}
		sortSegmentsByQuarter(segments);

		cout << endl;

		// check quarters

		/*for (int i = 0; i < segments.size(); i++)
		{
			cout << segments[i].first.c << segments[i].second.c << " quarter: " << segments[i].quarter << endl;
		}*/

		cout << "\n-----------------------------------------\n\n";

		vector<segment> firstQuarter;
		vector<segment> secondQuarter;
		vector<segment> thirdQuarter;
		vector<segment> fourthQuarter;

		for (segment& s : segments)
		{
			switch (s.quarter)
			{
			case 1:
				firstQuarter.push_back(s);
				break;
			case 2:
				secondQuarter.push_back(s);
				break;
			case 3:
				thirdQuarter.push_back(s);
				break;
			case 4:
				fourthQuarter.push_back(s);
				break;
			default:
				break;
			}
		}

		bool state = false;
		if (firstQuarter.size() >= 2)
		{
			state = true;
			cout << "I: ";
			for (segment& s : firstQuarter)
			{
				cout << s.first.c << s.second.c << " ";
			}
			cout << endl;
		}
		if (secondQuarter.size() >= 2)
		{
			state = true;
			cout << "II: ";
			for (segment& s : secondQuarter)
			{
				cout << s.first.c << s.second.c << " ";
			}
			cout << endl;
		}
		if (thirdQuarter.size() >= 2)
		{
			state = true;
			cout << "III: ";
			for (segment& s : thirdQuarter)
			{
				cout << s.first.c << s.second.c << " ";
			}
			cout << endl;
		}
		if (fourthQuarter.size() >= 2)
		{
			state = true;
			cout << "IV: ";
			for (segment& s : fourthQuarter)
			{
				cout << s.first.c << s.second.c << " ";
			}
			cout << endl;
		}
		if (!state)
		{
			cout << "There are no cammon segments." << endl;
		}
		// outputting max and min length
		cout << "\n-----------------------------------------\n";
		sortSegmentsByLength(segments);

		for (segment& s : segments)
		{
			cout << s.first.c << s.second.c << " length: " << calculateLength(s) << endl;
		}
		cout << endl << endl;
		cout << "Max length: " << calculateMaxLength(segments) << endl;
		cout << "Min length: " << calculateMinLength(segments) << endl;

		cout << "\n-----------------------------------------\n";

		sortSegmentsByLength(firstQuarter);
		sortSegmentsByLength(secondQuarter);
		sortSegmentsByLength(thirdQuarter);
		sortSegmentsByLength(fourthQuarter);

		if (firstQuarter.size() >= 2)
		{
			cout << "I:\n";
			for (int i = firstQuarter.size() - 1; i >= 0; i--)
			{
				cout << firstQuarter[i].first.c << firstQuarter[i].second.c << " length: " << calculateLength(firstQuarter[i]) << endl;
			}
			cout << endl;
		}

		if (secondQuarter.size() >= 2)
		{
			cout << "II:\n";
			for (int i = secondQuarter.size() - 1; i >= 0; i--)
			{
				cout << secondQuarter[i].first.c << secondQuarter[i].second.c << " length: " << calculateLength(secondQuarter[i]) << endl;
			}
			cout << endl;
		}

		if (thirdQuarter.size() >= 2)
		{
			cout << "III:\n";
			for (int i = thirdQuarter.size() - 1; i >= 0; i--)
			{
				cout << thirdQuarter[i].first.c << thirdQuarter[i].second.c << " length: " << calculateLength(thirdQuarter[i]) << endl;
			}
			cout << endl;
		}

		if (fourthQuarter.size() >= 2)
		{
			cout << "IV:\n";
			for (int i = fourthQuarter.size() - 1; i >= 0; i--)
			{
				cout << fourthQuarter[i].first.c << fourthQuarter[i].second.c << " length: " << calculateLength(fourthQuarter[i]) << endl;
			}
			cout << endl;
		}
	}
	
}
int main()
{
	createSegments(26);
}


