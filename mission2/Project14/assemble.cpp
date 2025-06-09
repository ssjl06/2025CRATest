#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <memory>
#include "Car.cpp"

#if _DEBUG

#include <gmock/gmock.h>

int main()
{
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}

#else

void runProducedCar(const std::shared_ptr<Car>& car);

class CarBuilder {
public:
    std::unique_ptr<Car> build() {
        selectCarType();
        buildEngine();
        buildBrake();
        buildSteering();
        return std::move(m_building_car);
    }
    void selectCarType() {
        std::cout<<CLEAR_SCREEN;

        std::cout<<"        ______________\n";
        std::cout<<"       /|            | \n";
        std::cout<<"  ____/_|_____________|____\n";
        std::cout<<" |                      O  |\n";
        std::cout<<" '-(@)----------------(@)--'\n";
        std::cout<<"===============================\n";
        std::cout<<"어떤 차량 타입을 선택할까요?\n";
        std::cout<<"1. Sedan\n";
        std::cout<<"2. SUV\n";
        std::cout<<"3. Truck\n";
        std::cout << "Debug: "<< std::endl;
        auto answer = getInput();
        std::cout << "Debug: answer: " << answer << std::endl;
        if (answer == 1) {
            std::cout << "차량 타입으로 Sedan을 선택하셨습니다.\n";
            m_building_car = std::make_unique<Sedan>();
            return;
        }
        if (answer == 2) {
            std::cout << "차량 타입으로 SUV을 선택하셨습니다.\n";
            m_building_car = std::make_unique<SUV>();
            return;
        }
        if (answer == 3) {
            std::cout << "차량 타입으로 Truck을 선택하셨습니다.\n";
            m_building_car = std::make_unique<Truck>();
            return;
        }
        std::cout<<"ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n";
        delay(800);
        selectCarType();
    }
    void buildEngine() {
        std::cout<<CLEAR_SCREEN;
        std::cout<<"어떤 엔진을 탑재할까요?\n";
        std::cout<<"0. 뒤로가기\n";
        std::cout<<"1. GM\n";
        std::cout<<"2. TOYOTA\n";
        std::cout<<"3. WIA\n";
        std::cout<<"4. 고장난 엔진\n";

        auto answer = getInput();
        if (answer == 0) {
            selectCarType();
            return;
        }
        if (answer == 1) {
            std::cout << "GM 엔진을 선택하셨습니다.\n";
            m_building_car->setEngine(std::make_unique<GMEngine>());
            return;
        }
        if (answer == 2) {
            std::cout << "TOYOTA 엔진을 선택하셨습니다.\n";
            m_building_car->setEngine(std::make_unique<ToyotaEngine>());
            return;
        }
        if (answer == 3) {
            std::cout << "WIA 엔진을 선택하셨습니다.\n";
            m_building_car->setEngine(std::make_unique<WiaEngine>());
            return;
        }
        if (answer == 4) {
            std::cout << "고장난 엔진을 선택하셨습니다.\n";
            m_building_car->setEngine(std::make_unique<BrokenEngine>());
            return;
        }
        std::cout << "Debug: answer: " << answer << std::endl;
        std::cout<<"ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n";
        delay(800);
        buildEngine();
    }
    void buildBrake() {
        std::cout<<CLEAR_SCREEN;
        std::cout<<"어떤 제동장치를 선택할까요?\n";
        std::cout<<"0. 뒤로가기\n";
        std::cout<<"1. MANDO\n";
        std::cout<<"2. CONTINENTAL\n";
        std::cout<<"3. BOSCH\n";
        auto answer = getInput();
        if (answer == 0) {
            buildEngine();
            return;
        }
        if (answer == 1) {
            std::cout << "MANDO 제동장치를 선택하셨습니다.\n";
            m_building_car->setBrakeSystem(std::make_unique<MandoBrake>());
            return;
        }
        if (answer == 2) {
            std::cout << "CONTINENTAL 제동장치를 선택하셨습니다.\n";
            m_building_car->setBrakeSystem(std::make_unique<ContinentalBrake>());
            return;
        }
        if (answer == 3) {
            std::cout << "BOSCH 제동장치를 선택하셨습니다.\n";
            m_building_car->setBrakeSystem(std::make_unique<BoschBrake>());
            return;
        }
        std::cout<<"ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n";
        delay(800);
        buildBrake();
    }
    void buildSteering() {
        std::cout<<CLEAR_SCREEN;
        std::cout<<"어떤 조향장치를 선택할까요?\n";
        std::cout<<"0. 뒤로가기\n";
        std::cout<<"1. BOSCH\n";
        std::cout<<"2. MOBIS\n";
        auto answer = getInput();
        if (answer == 0) {
            buildBrake();
            return;
        }
        if (answer == 1) {
            std::cout << "BOSCH 조향장치를 선택하셨습니다.\n";
            m_building_car->setSteeringSystem(std::make_unique<BoschSteering>());
            return;
        }
        if (answer == 2) {
            std::cout << "MOBIS 조향장치를 선택하셨습니다.\n";
            m_building_car->setSteeringSystem(std::make_unique<MobisSteering>());
            return;
        }
        std::cout<<"ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n";
        delay(800);
        buildSteering();
    }
private:
    std::unique_ptr<Car> m_building_car;
};

int main()
{
    CarBuilder builder;

    while (1)
    {
        std::shared_ptr<Car> car = builder.build();
        std::cout<<CLEAR_SCREEN;
        std::cout<<"멋진 차량이 완성되었습니다.\n";
        std::cout<<"어떤 동작을 할까요?\n";
        std::cout<<"0. 처음 화면으로 돌아가기\n";
        std::cout<<"1. RUN\n";
        std::cout<<"2. Test\n";
        std::cout<<"===============================\n";

        auto answer = getInput();
        // 처음으로 돌아가기
        if (answer == 0) {
            continue;
        }

        if (!(answer >= 0 && answer <= 2))
        {
            std::cout<<"ERROR :: Run 또는 Test 중 하나를 선택 필요\n";
            delay(800);
            answer = getInput();
            continue;
        }

        // 이전으로 돌아가기
        if (answer == 0) {
            continue;
        }
        if (answer == 1) {
            runProducedCar(car);
            delay(2000);
        }
        else if (answer == 2)
        {
            std::cout<<"Test...\n";
            delay(1500);
            car->testCar();
            delay(2000);
        }
    }
}

void runProducedCar(const std::shared_ptr<Car>& car)
{
    if (!car) {
        throw std::runtime_error("Invalid car");
    } 
    if (!car->isWorkingCar()) {
        std::cout<<"자동차가 동작되지 않습니다\n";
        return;
    }
    if (car->hasBrokenEngine()) {
        std::cout<<"엔진이 고장나있습니다.\n";
        std::cout<<"자동차가 움직이지 않습니다.\n";
        return;
    }
    car->run();
}

#endif