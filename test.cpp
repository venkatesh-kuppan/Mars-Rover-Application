#include<iostream>
#include "pch.h"
#include "CPosition.h"
#include "gtest/gtest.h"

using namespace std; 

struct rover_test:testing::Test {
	CPosition *prover;
	rover_test::rover_test() {
		prover = new CPosition;
	}
	rover_test::~rover_test() {
		delete prover;
	}
};

TEST_F(rover_test, test1) {
	prover->set_xyo(1, 2,'N');
	string command("LMLMLMLMM");
	prover->setRoverCommand(command);
	EXPECT_EQ(1, prover->get_x());
	EXPECT_EQ(3, prover->get_y());
	EXPECT_EQ('N', prover->get_orientation());
}

/*
create a test suite with inital values, command and final values
*/
struct rover_state
{
	/*
	x_max and y_max = max. right most coordinates
	*/
	int x_max; 
	int y_max;
	/*
	initial position & orientation of rover 
	*/
	int x_initial;
	int y_initial;
	char Or_initial;
	std::string command;
	/*
	final position & orientation of rover
	*/
	int x_final;
	int y_final;
	char Or_final;
};

/*
parameterize struct to load initial values and command for the test
*/
struct rover_state_test : rover_test, testing::WithParamInterface<rover_state>
{
	rover_state_test() {
		prover->set_xyo(GetParam().x_initial, GetParam().y_initial, GetParam().Or_initial);
		prover->setRoverCommand(GetParam().command);
	}
};

/*
the test case checks for the inputs provided
yields PASS or FAIL
*/
TEST_P(rover_state_test, test2) {
	auto as = GetParam();
	EXPECT_EQ(as.x_final, prover->get_x());
	EXPECT_EQ(as.y_final, prover->get_y());
	EXPECT_EQ(as.Or_final, prover->get_orientation());
	ASSERT_LE(as.x_final, as.x_max); // check if the final rover coordinates are within the range
	ASSERT_LE(as.y_final, as.y_max);
}

/*
provide values for the parameterized test suite.
*/
INSTANTIATE_TEST_CASE_P(Default,rover_state_test,
	testing::Values(
		rover_state {5,5,1,2,'N',"LMLMLMLMM",1,3,'N' },
		rover_state {5,5,3,3,'E',"MMRMMRMRRM",5,1,'E'},
		rover_state {5,5,2,2,'E',"LRMRMMLRLR",3,0,'S'},
		rover_state {5,5,1,3,'z',"LRMRMMRL",1,3,'X'} // invalid orientation
));


int main(int argc, char* argv[])
{
	/*
	init gtest framework and run the test
	*/
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}