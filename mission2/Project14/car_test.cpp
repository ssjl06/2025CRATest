#include "gmock/gmock.h"
#include "Car.cpp"
#include <iostream>

using namespace testing;

//TEST(ValidityTest, TC0) {
//	Car car;
//	EXPECT_EQ(false, car.isWorkingCar());
//}
//TEST(ValidityTest, TC1) {
//	Sedan sedan;
//	EXPECT_EQ(false, sedan.isWorkingCar());
//}
//TEST(ValidityTest, TC2) {
//	SUV suv;
//	EXPECT_EQ(false, suv.isWorkingCar());
//}
//TEST(ValidityTest, TC3) {
//	Truck truck;
//	EXPECT_EQ(false, truck.isWorkingCar());
//}

TEST(ConstraintTest1, TC1) {
	Sedan sedan;
	sedan.setEngine(std::make_unique<ToyotaEngine>());
	sedan.setBrakeSystem(std::make_unique<BoschBrake>());
	sedan.setSteeringSystem(std::make_unique<MobisSteering>());
	EXPECT_EQ(false, sedan.isWorkingCar());
}

TEST(ConstraintTest1, TC1_1) {
	Sedan sedan;
	sedan.setEngine(std::make_unique<ToyotaEngine>());
	sedan.setBrakeSystem(std::make_unique<BoschBrake>());
	sedan.setSteeringSystem(std::make_unique<BoschSteering>());
	EXPECT_EQ(true, sedan.isWorkingCar());
}

TEST(ConstraintTest2, TC1) {
	Sedan sedan;
	sedan.setEngine(std::make_unique<ToyotaEngine>());
	sedan.setBrakeSystem(std::make_unique<ContinentalBrake>());
	sedan.setSteeringSystem(std::make_unique<BoschSteering>());
	EXPECT_EQ(false, sedan.isWorkingCar());
}

TEST(ConstraintTest2, TC1_1) {
	Sedan sedan;
	sedan.setEngine(std::make_unique<ToyotaEngine>());
	sedan.setBrakeSystem(std::make_unique<BoschBrake>());
	sedan.setSteeringSystem(std::make_unique<BoschSteering>());
	EXPECT_EQ(true, sedan.isWorkingCar());
}

TEST(ConstraintTest2, TC2) {
	SUV suv;
	suv.setEngine(std::make_unique<ToyotaEngine>());
	suv.setBrakeSystem(std::make_unique<ContinentalBrake>());
	suv.setSteeringSystem(std::make_unique<BoschSteering>());
	EXPECT_EQ(false, suv.isWorkingCar());
}

TEST(ConstraintTest2, TC2_1) {
	SUV suv;
	suv.setEngine(std::make_unique<WiaEngine>());
	suv.setBrakeSystem(std::make_unique<ContinentalBrake>());
	suv.setSteeringSystem(std::make_unique<BoschSteering>());
	EXPECT_EQ(true, suv.isWorkingCar());
}

TEST(ConstraintTest2, TC3) {
	Truck truck;
	truck.setEngine(std::make_unique<WiaEngine>());
	truck.setBrakeSystem(std::make_unique<ContinentalBrake>());
	truck.setSteeringSystem(std::make_unique<BoschSteering>());
	EXPECT_EQ(false, truck.isWorkingCar());
}

TEST(ConstraintTest2, TC3_1) {
	Truck truck;
	truck.setEngine(std::make_unique<ToyotaEngine>());
	truck.setBrakeSystem(std::make_unique<ContinentalBrake>());
	truck.setSteeringSystem(std::make_unique<BoschSteering>());
	EXPECT_EQ(true, truck.isWorkingCar());
}

TEST(ConstraintTest2, TC4) {
	Truck truck;
	truck.setEngine(std::make_unique<ToyotaEngine>());
	truck.setBrakeSystem(std::make_unique<MandoBrake>());
	truck.setSteeringSystem(std::make_unique<BoschSteering>());
	EXPECT_EQ(false, truck.isWorkingCar());
}

TEST(ConstraintTest2, TC4_1) {
	Truck truck;
	truck.setEngine(std::make_unique<ToyotaEngine>());
	truck.setBrakeSystem(std::make_unique<BoschBrake>());
	truck.setSteeringSystem(std::make_unique<BoschSteering>());
	EXPECT_EQ(true, truck.isWorkingCar());
}

TEST(CarTest, TC1) {
	std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
	std::ostringstream strCout;
	std::cout.rdbuf(strCout.rdbuf());

	Sedan sedan;
	sedan.setEngine(std::make_unique<ToyotaEngine>());
	sedan.setBrakeSystem(std::make_unique<BoschBrake>());
	sedan.setSteeringSystem(std::make_unique<MobisSteering>());
	sedan.testCar();

	std::cout.rdbuf(oldCoutStreamBuf);

	std::string expected = "자동차 부품 조합 테스트 결과 : FAIL\nBosch제동장치에는 Bosch조향장치 이외 사용 불가\n";
	EXPECT_THAT(strCout.str(), testing::Eq(expected));
}

TEST(CarTest, TC2) {
	std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
	std::ostringstream strCout;
	std::cout.rdbuf(strCout.rdbuf());

	Sedan sedan;
	sedan.setEngine(std::make_unique<ToyotaEngine>());
	sedan.setBrakeSystem(std::make_unique<BoschBrake>());
	sedan.setSteeringSystem(std::make_unique<BoschSteering>());
	sedan.testCar();

	std::cout.rdbuf(oldCoutStreamBuf);

	std::string expected = "자동차 부품 조합 테스트 결과 : PASS\n";
	EXPECT_THAT(strCout.str(), testing::Eq(expected));
}

TEST(CarTest, TC3) {
	std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
	std::ostringstream strCout;
	std::cout.rdbuf(strCout.rdbuf());

	Sedan sedan;
	sedan.setEngine(std::make_unique<ToyotaEngine>());
	sedan.setBrakeSystem(std::make_unique<ContinentalBrake>());
	sedan.setSteeringSystem(std::make_unique<BoschSteering>());
	sedan.testCar();

	std::cout.rdbuf(oldCoutStreamBuf);

	std::string expected = "자동차 부품 조합 테스트 결과 : FAIL\nSedan에는 Continental제동장치 사용 불가\n";
	EXPECT_THAT(strCout.str(), testing::Eq(expected));
}

TEST(CarTest, TC4) {
	std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
	std::ostringstream strCout;
	std::cout.rdbuf(strCout.rdbuf());

	SUV suv;
	suv.setEngine(std::make_unique<ToyotaEngine>());
	suv.setBrakeSystem(std::make_unique<ContinentalBrake>());
	suv.setSteeringSystem(std::make_unique<BoschSteering>());
	suv.testCar();

	std::cout.rdbuf(oldCoutStreamBuf);

	std::string expected = "자동차 부품 조합 테스트 결과 : FAIL\nSUV에는 TOYOTA엔진 사용 불가\n";
	EXPECT_THAT(strCout.str(), testing::Eq(expected));
}

TEST(CarTest, TC5) {
	std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
	std::ostringstream strCout;
	std::cout.rdbuf(strCout.rdbuf());

	Truck truck;
	truck.setEngine(std::make_unique<WiaEngine>());
	truck.setBrakeSystem(std::make_unique<ContinentalBrake>());
	truck.setSteeringSystem(std::make_unique<BoschSteering>());
	truck.testCar();

	std::string expected = "자동차 부품 조합 테스트 결과 : FAIL\nTruck에는 WIA엔진 사용 불가\n";
	EXPECT_THAT(strCout.str(), testing::Eq(expected));
}

TEST(CarTest, TC6) {
	std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
	std::ostringstream strCout;
	std::cout.rdbuf(strCout.rdbuf());

	Truck truck;
	truck.setEngine(std::make_unique<ToyotaEngine>());
	truck.setBrakeSystem(std::make_unique<MandoBrake>());
	truck.setSteeringSystem(std::make_unique<BoschSteering>());
	truck.testCar();

	std::string expected = "자동차 부품 조합 테스트 결과 : FAIL\nTruck에는 Mando제동장치 사용 불가\n";
	EXPECT_THAT(strCout.str(), testing::Eq(expected));
}