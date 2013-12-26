#include "CppUTest/TestHarness.h"

extern "C"{

#include "../../src/HomeAutomation/RandomMinute.h"
#include <stdio.h>
#include <string.h>
}
enum{ BOUND = 30};

TEST_GROUP(RandomMinute)
{
	int minute;

	void setup()
	{
		RandomMinute_Create(BOUND);
		srand(1);
	}
	void teardown(){

	}
	void AssertMinuteIsInRange()
	{
		if(minute < -BOUND || minute > BOUND){
			printf("bandminute value:%d\n",minute);
			FAIL("Minute out of range");
		}
	}

};


TEST(RandomMinute,GetIsInRange)
{
	for(int i=0; i <100;i++){
		minute = RandomMinute_Get();
		AssertMinuteIsInRange();
	}
}


TEST(RandomMinute,AllValuesPossible)
{
	int hit[2*BOUND + 1];
	memset(hit,0,sizeof(hit));

	for(int i=0;i<300;i++){
		minute = RandomMinute_Get();
		AssertMinuteIsInRange();
		hit[minute + BOUND]++;
	}

	for(int i=0; i < 2* BOUND+1;i++){
		CHECK(hit[i]>0);
	}
}
