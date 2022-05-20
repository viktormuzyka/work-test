#include "pch.h"
#include "../functions.h"
TEST(GetProductsAmountTest, TrueNeedLessCoinsThanThereAre) {
	std::vector<int> prices{ 50,30,20,10 };
	int amountOfMoney = 50;
	EXPECT_EQ(GetProductsAmount(prices, amountOfMoney), 2);

	prices={ 50,30,40,80 };
	amountOfMoney = 100;
	EXPECT_EQ(GetProductsAmount(prices, amountOfMoney), 2);
}
TEST(GetProductsAmountTest, TrueNeedMoreCoinsThanThereAre) {
	std::vector<int> prices{ 50,70,20,10 };
	int amountOfMoney = 200;
	EXPECT_EQ(GetProductsAmount(prices, amountOfMoney), 4);

	prices={ 1,8,23,7,3};
	amountOfMoney = 200;
	EXPECT_EQ(GetProductsAmount(prices, amountOfMoney), 5);
}
TEST(IsLeapYearTest, TrueYearMultiplyBy400) {
	EXPECT_TRUE(IsLeapYear(-400));
	EXPECT_TRUE(IsLeapYear(400));
	EXPECT_TRUE(IsLeapYear(800));
	EXPECT_TRUE(IsLeapYear(1200));
}

TEST(IsLeapYearTest, TrueYearMultiplyBy100ButNo400) {
	EXPECT_FALSE(IsLeapYear(100));
	EXPECT_FALSE(IsLeapYear(500));
	EXPECT_FALSE(IsLeapYear(1000));
	EXPECT_FALSE(IsLeapYear(1300));
}

TEST(IsLeapYearTest, TrueYearMultiplyBy4ButNo100) {
	EXPECT_EQ(IsLeapYear(40), 1);
	EXPECT_EQ(IsLeapYear(440), 1);
	EXPECT_EQ(IsLeapYear(840), 1);
	EXPECT_EQ(IsLeapYear(1240), 1);
}

TEST(IsLeapYearTest, FalseYearIsLeap) {
	EXPECT_EQ(IsLeapYear(45), 1);
	EXPECT_EQ(IsLeapYear(4435), 1);
	EXPECT_EQ(IsLeapYear(8421), 1);
	EXPECT_EQ(IsLeapYear(12417), 1);
}