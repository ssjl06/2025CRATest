#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <thread>
#include <chrono>
#define CLEAR_SCREEN "\033[H\033[2J"

inline void delay(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

inline int getInput() {
    char buf[100];
    std::cout << "INPUT > ";
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        std::cout << "바이바이\n";
        exit(0);
    }

    // 숫자로 된 대답인지 확인
    char* checkNumber;
    int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0')
    {
        std::cout << "ERROR :: 숫자만 입력 가능\n";
        delay(800);
        answer = getInput();
    }
    return answer;
}

enum class Brand {
    GM,
    TOYOTA,
    WIA,
    MANDO,
    CONTINENTAL,
    BOSCH,
    MOBIS,
    Unknown
};

enum class CarType {
    Sedan,
    SUV,
    Truck,
    Unknown
};

inline std::string getBrandName(const Brand& brand) {
    switch (brand)
    {
    case Brand::GM:
        return "GM";
    case Brand::TOYOTA:
        return "Toyota";
    case Brand::MANDO:
        return "Mando";
    case Brand::CONTINENTAL:
        return "Continental";
    case Brand::BOSCH:
        return "Bosch";
    default:
        return "Unknown";
    }
    return "Unknown";
}

inline std::string getCarTypeName(const CarType& type) {
    switch (type)
    {
    case CarType::Sedan:
        return "Sedan";
    case CarType::SUV:
        return "SUV";
    case CarType::Truck:
        return "Truck";
    default:
        return "Unknown";
    }
    return "Unknown";
}

class Module {
public:
    Module(const Brand& brand) : m_brand(brand) {}
    Brand getBrand() const { return m_brand; }
private:
    Brand m_brand = Brand::Unknown;
};

/* Engine */
class Engine : public Module {
public:
    Engine(const Brand& brand, bool broken = false): Module(brand), m_broken(broken) {}
    bool isBroken() {
        return m_broken;
    }
    bool m_broken;
};

class GMEngine : public Engine {
public:
    GMEngine() : Engine(Brand::GM) {}
};

class ToyotaEngine : public Engine {
public:
    ToyotaEngine() : Engine(Brand::TOYOTA) {}
};

class WiaEngine : public Engine {
public:
    WiaEngine() : Engine(Brand::WIA) {}
};

class BrokenEngine : public Engine {
public:
    BrokenEngine() : Engine(Brand::Unknown, true) {}
};

/* BrakeSystem */
class BrakeSystem : public Module {
public:
    BrakeSystem(const Brand& brand) : Module(brand) {}
};

class MandoBrake : public BrakeSystem {
public:
    MandoBrake() : BrakeSystem(Brand::MANDO) {}
};

class ContinentalBrake : public BrakeSystem {
public:
    ContinentalBrake() : BrakeSystem(Brand::CONTINENTAL) {}
};

class BoschBrake : public BrakeSystem {
public:
    BoschBrake() : BrakeSystem(Brand::BOSCH) {}
};

/* SteeringSystem */
class SteeringSystem : public Module {
public:
    SteeringSystem(const Brand& brand) : Module(brand) {}
};

class BoschSteering : public SteeringSystem {
public:
    BoschSteering() : SteeringSystem(Brand::BOSCH) {}
};

class MobisSteering : public SteeringSystem {
public:
    MobisSteering() : SteeringSystem(Brand::MOBIS) {}
};

/* Car */
class Car {
public:
    Car(const CarType& car_type = CarType::Unknown): m_car_type(car_type) {}
    Car& setEngine(std::unique_ptr<Engine>&& engine) {
        m_engine = std::move(engine);
        return *this;
    }
    Car& setBrakeSystem(std::unique_ptr<BrakeSystem>&& brake_system) {
        m_brake_system = std::move(brake_system);
        return *this;
    }
    Car& setSteeringSystem(std::unique_ptr<SteeringSystem>&& steering_system) {
        m_steering_system = std::move(steering_system);
        return *this;
    }
    virtual bool isWorkingCar() {
        if (!m_engine || !m_brake_system || !m_steering_system) {
            return false;
        }
        if (m_brake_system->getBrand() == Brand::BOSCH && m_steering_system->getBrand() != Brand::BOSCH) {
            return false;
        }
        return true;
    }
    bool hasBrokenEngine() {
        if (!m_engine) {
            throw std::runtime_error("there is no engine yet");
        }
        return m_engine->isBroken();
    }
    void run()
    {
        if (!m_engine || !m_brake_system || !m_steering_system) {
            throw std::runtime_error("The car has not completed yet");
        }
        std::cout << "Car Type : ";
        std::cout<<getCarTypeName(m_car_type)<<"\n";

        std::cout<<"Engine : ";
        std::cout<<getBrandName(m_engine->getBrand())<<"\n";

        std::cout<<"Brake : ";
        std::cout<<getBrandName(m_brake_system->getBrand())<<"\n";

        std::cout<<"Steering : ";
        std::cout<<getBrandName(m_steering_system->getBrand())<<"\n";

        std::cout<<"자동차가 동작됩니다.\n";
    }
    virtual void testCar() {
        if (m_brake_system->getBrand() == Brand::BOSCH && m_steering_system->getBrand() != Brand::BOSCH) {
            std::cout << "자동차 부품 조합 테스트 결과 : FAIL\nBosch제동장치에는 Bosch조향장치 이외 사용 불가\n";
            return;
        }
        std::cout << "자동차 부품 조합 테스트 결과 : PASS\n";
    }
protected:
    std::unique_ptr<Engine> m_engine;
    std::unique_ptr<BrakeSystem> m_brake_system;
    std::unique_ptr<SteeringSystem> m_steering_system;
    CarType m_car_type;
};

class Sedan : public Car {
public:
    Sedan() : Car(CarType::Sedan) {}
    virtual bool isWorkingCar() override {
        if (m_brake_system->getBrand() == Brand::CONTINENTAL) {
            return false;
        }
        return Car::isWorkingCar();
    }
    virtual void testCar() override{
        if (m_brake_system->getBrand() == Brand::CONTINENTAL) {
            std::cout << "자동차 부품 조합 테스트 결과 : FAIL\n";
            std::cout << "Sedan에는 Continental제동장치 사용 불가\n";
            return;
        }
        Car::testCar();
    }
};

class SUV : public Car {
public:
    SUV() : Car(CarType::SUV) {}
    virtual bool isWorkingCar() override {
        if (m_engine->getBrand() == Brand::TOYOTA) {
            return false;
        }
        return Car::isWorkingCar();
    }
    virtual void testCar() override{
        if (m_engine->getBrand() == Brand::TOYOTA) {
            std::cout<<"자동차 부품 조합 테스트 결과 : FAIL\n";
            std::cout<<"SUV에는 TOYOTA엔진 사용 불가\n";
            return;
        }
        Car::testCar();
    }
};

class Truck : public Car {
public:
    Truck() : Car(CarType::Truck) {}
    virtual bool isWorkingCar() override {
        if (m_engine->getBrand() == Brand::WIA) {
            return false;
        }
        if (m_brake_system->getBrand() == Brand::MANDO) {
            return false;
        }
        return Car::isWorkingCar();
    }
    virtual void testCar() override{
        if (m_engine->getBrand() == Brand::WIA) {
            std::cout<<"자동차 부품 조합 테스트 결과 : FAIL\n";
            std::cout<<"Truck에는 WIA엔진 사용 불가\n";
            return;
        }
        if (m_brake_system->getBrand() == Brand::MANDO) {
            std::cout<<"자동차 부품 조합 테스트 결과 : FAIL\n";
            std::cout<<"Truck에는 Mando제동장치 사용 불가\n";
            return;
        }
        Car::testCar();
    }
};

