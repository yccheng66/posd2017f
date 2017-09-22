#include "madRace.h"

TEST(madRace, car) {
  MadCar madCar(30);
  EXPECT_EQ(30, madCar.speed());
  madCar.boom(10);
  EXPECT_EQ(41, madCar.speed());
}

TEST(madRace, bike) {
  MadBike madBike(0, 3, 10);
  EXPECT_EQ(0, madBike.speed());
  madBike.boom();
  EXPECT_EQ(3, madBike.speed());
}
