/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}

//The method returns true, confirming the guess matches the secret
TEST(GuesserTest, correct_guess)
{
	Guesser object("correctpass1234");
	ASSERT_EQ(object.match("correctpass1234"), true);
}

//test if we reach the 32 character limit
TEST(GuesserTest, max_32_guess)
{
  Guesser object("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
  ASSERT_EQ(object.match("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMN"), false);
}

//test 32 max with special characters
TEST(GuesserTest, max_32_special_characters)
{
	Guesser object("1234567890!@#$%^&*()-_=+[{]}|;:'"); 
	ASSERT_EQ(object.match("1234567890!@#$%^&*()-_=+[{]}|;:'"), true);

}

//test with less than 32 character password
TEST(GuesserTest, less_than_32_correct_attempt)
{
  Guesser object("JulietRocks2025");
  ASSERT_EQ(object.match("JulietRocks2025"), true);
}

//test with more than 32 character password
TEST(GuesserTest, secret_over_32_characters_is_truncated)
{
  Guesser object("JulietLovesCyberSecurityAndCode2025!!Extra");
  ASSERT_EQ(object.match("JulietLovesCyberSecurityAndCode20"), false); 
}

//test after three wrong guesses locked out
TEST(GuesserTest, after_three_wrong_attempts)
{
  Guesser object("Juliet");
  object.match("Juliep"); 
  object.match("Juliep"); 
  object.match("Juliep"); 
  ASSERT_EQ(object.match("Juliet"), false); 
  ASSERT_EQ(object.remaining(), 0);
}

// This test checks that repeating the same incorrect guess (with small distance)
// properly decrements the number of remaining guesses until it reaches 0.
TEST(GuesserTest, multiple_attempts_with_same_wrong_guess_decrements)
{
  Guesser object("Cole1");
  ASSERT_EQ(object.match("Coke1"), false); 
  ASSERT_EQ(object.remaining(), 2);
  ASSERT_EQ(object.match("Coke1"), false); 
  ASSERT_EQ(object.remaining(), 1);
  ASSERT_EQ(object.match("Coke1"), false); 
  ASSERT_EQ(object.remaining(), 0);
}

// This test checks that once the Guesser is locked due to a brute-force guess,
// all future guesses, even correct ones, will fail.
TEST(GuesserTest, guess_after_lock_always_fails)
{
  Guesser object("Juliet123");
  object.match("WrongGuess"); 
  ASSERT_EQ(object.match("Juliet123"), false); 
}





