#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <thread>

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    BrakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    UNDEFINED_CAR = 0,
    SEDAN = 1,
    SUV,
    TRUCK
};
std::string car_names[4] = {"UNDEFINED_CAR", "Sedan", "SUV", "Truck"};

enum Engine
{
    UNDEFINED_ENGINE = 0,
    GM = 1,
    TOYOTA,
    WIA
};
std::string engine_names[4] = {"UNDEFINED_ENGINE", "GM", "TOYOTA", "WIA"};

enum brakeSystem
{
    UNDEFINED_BRAKE = 0,
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};
std::string brake_names[4] = {"UNDEFINED_BRAKE", "Mando", "Continental", "Bosch"};

enum SteeringSystem
{
    UNDEFINED_STEERING = 0,
    BOSCH_S = 1,
    MOBIS
};
std::string steering_names[4] = {"UNDEFINED_STEERING", "Bosch", "Mobis"};

void delay(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main()
{
    char buf[100];
    int step = CarType_Q;

    while (1)
    {
        if (step == CarType_Q)
        {
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
        }
        else if (step == Engine_Q)
        {
            std::cout<<CLEAR_SCREEN;
            std::cout<<"어떤 엔진을 탑재할까요?\n";
            std::cout<<"0. 뒤로가기\n";
            std::cout<<"1. GM\n";
            std::cout<<"2. TOYOTA\n";
            std::cout<<"3. WIA\n";
            std::cout<<"4. 고장난 엔진\n";
        }
        else if (step == BrakeSystem_Q)
        {
            std::cout<<CLEAR_SCREEN;
            std::cout<<"어떤 제동장치를 선택할까요?\n";
            std::cout<<"0. 뒤로가기\n";
            std::cout<<"1. MANDO\n";
            std::cout<<"2. CONTINENTAL\n";
            std::cout<<"3. BOSCH\n";
        }
        else if (step == SteeringSystem_Q)
        {
            std::cout<<CLEAR_SCREEN;
            std::cout<<"어떤 조향장치를 선택할까요?\n";
            std::cout<<"0. 뒤로가기\n";
            std::cout<<"1. BOSCH\n";
            std::cout<<"2. MOBIS\n";
        }
        else if (step == Run_Test)
        {
            std::cout<<CLEAR_SCREEN;
            std::cout<<"멋진 차량이 완성되었습니다.\n";
            std::cout<<"어떤 동작을 할까요?\n";
            std::cout<<"0. 처음 화면으로 돌아가기\n";
            std::cout<<"1. RUN\n";
            std::cout<<"2. Test\n";
        }
        std::cout<<"===============================\n";

        std::cout<<"INPUT > ";
        fgets(buf, sizeof(buf), stdin);

        // 엔터 개행문자 제거
        char *context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);

        if (!strcmp(buf, "exit"))
        {
            std::cout << "바이바이\n";
            break;
        }

        // 숫자로 된 대답인지 확인
        char *checkNumber;
        int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

        // 입력받은 문자가 숫자가 아니라면
        if (*checkNumber != '\0')
        {
            std::cout << "ERROR :: 숫자만 입력 가능\n";
            delay(800);
            continue;
        }

        if (step == CarType_Q && !(answer >= 1 && answer <= 3))
        {
            std::cout<<"ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n";
            delay(800);
            continue;
        }

        if (step == Engine_Q && !(answer >= 0 && answer <= 4))
        {
            std::cout<<"ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n";
            delay(800);
            continue;
        }

        if (step == BrakeSystem_Q && !(answer >= 0 && answer <= 3))
        {
            std::cout<<"ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n";
            delay(800);
            continue;
        }

        if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2))
        {
            std::cout<<"ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n";
            delay(800);
            continue;
        }

        if (step == Run_Test && !(answer >= 0 && answer <= 2))
        {
            std::cout<<"ERROR :: Run 또는 Test 중 하나를 선택 필요\n";
            delay(800);
            continue;
        }

        // 처음으로 돌아가기
        if (answer == 0 && step == Run_Test)
        {
            step = CarType_Q;
            continue;
        }

        // 이전으로 돌아가기
        if (answer == 0 && step >= 1)
        {
            step -= 1;
            continue;
        }

        if (step == CarType_Q)
        {
            selectCarType(answer);
            delay(800);
            step = Engine_Q;
        }
        else if (step == Engine_Q)
        {
            selectEngine(answer);
            delay(800);
            step = BrakeSystem_Q;
        }
        else if (step == BrakeSystem_Q)
        {
            selectbrakeSystem(answer);
            delay(800);
            step = SteeringSystem_Q;
        }
        else if (step == SteeringSystem_Q)
        {
            selectSteeringSystem(answer);
            delay(800);
            step = Run_Test;
        }
        else if (step == Run_Test && answer == 1)
        {
            runProducedCar();
            delay(2000);
        }
        else if (step == Run_Test && answer == 2)
        {
            std::cout<<"Test...\n";
            delay(1500);
            testProducedCar();
            delay(2000);
        }
    }
}

void selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    if (answer == 1)
        std::cout<<"차량 타입으로 Sedan을 선택하셨습니다.\n";
    if (answer == 2)
        std::cout<<"차량 타입으로 SUV을 선택하셨습니다.\n";
    if (answer == 3)
        std::cout<<"차량 타입으로 Truck을 선택하셨습니다.\n";
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    if (answer == 1)
        std::cout<<"GM 엔진을 선택하셨습니다.\n";
    if (answer == 2)
        std::cout<<"TOYOTA 엔진을 선택하셨습니다.\n";
    if (answer == 3)
        std::cout<<"WIA 엔진을 선택하셨습니다.\n";
}

void selectbrakeSystem(int answer)
{
    stack[BrakeSystem_Q] = answer;
    if (answer == 1)
        std::cout<<"MANDO 제동장치를 선택하셨습니다.\n";
    if (answer == 2)
        std::cout<<"CONTINENTAL 제동장치를 선택하셨습니다.\n";
    if (answer == 3)
        std::cout<<"BOSCH 제동장치를 선택하셨습니다.\n";
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    if (answer == 1)
        std::cout<<"BOSCH 조향장치를 선택하셨습니다.\n";
    if (answer == 2)
        std::cout<<"MOBIS 조향장치를 선택하셨습니다.\n";
}

bool sedanAndContinental() {
    if (stack[CarType_Q] == SEDAN && stack[BrakeSystem_Q] == CONTINENTAL) {
        return true;
    }
}
bool SUVAndToyota() {
    if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA) {
        return true;
    }
    return false;
}
bool truckAndWIA() {
    if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA) {
        return true;
    }
    return false;
}
bool truckAndMando() {
    if (stack[CarType_Q] == TRUCK && stack[BrakeSystem_Q] == MANDO) {
        return true;
    }
    return false;
}
bool boschBrakeAndNotBoschSteer() {
    if (stack[BrakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S) {
        return true;
    }
    return false;
}

int isValidCar()
{
    if (sedanAndContinental()) {
        return false;
    }
    if (SUVAndToyota()) {
        return false;
    }
    if (truckAndWIA()) {
        return false;
    }
    if (truckAndMando()) {
        return false;
    }
    if (boschBrakeAndNotBoschSteer()) {
        return false;
    }
    return true;
}

void runProducedCar()
{
    if (not isValidCar())
    {
        std::cout<<"자동차가 동작되지 않습니다\n";
        return;
    }
    if (stack[Engine_Q] == 4)
    {
        std::cout<<"엔진이 고장나있습니다.\n";
        std::cout<<"자동차가 움직이지 않습니다.\n";
        return;
    }
    std::cout << "Car Type : ";
    std::cout<<car_names[stack[CarType_Q]]<<"\n";

    std::cout<<"Engine : ";
    std::cout<<engine_names[stack[Engine_Q]]<<"\n";

    std::cout<<"Brake : ";
    std::cout<<brake_names[stack[BrakeSystem_Q]]<<"\n";

    std::cout<<"Steering : ";
    std::cout<<steering_names[stack[SteeringSystem_Q]]<<"\n";

    std::cout<<"자동차가 동작됩니다.\n";
}

void testProducedCar()
{
    if (sedanAndContinental())
    {
        std::cout<<"자동차 부품 조합 테스트 결과 : FAIL\n";
        std::cout<<"Sedan에는 Continental제동장치 사용 불가\n";
        return;
    }
    if (SUVAndToyota())
    {
        std::cout<<"자동차 부품 조합 테스트 결과 : FAIL\n";
        std::cout<<"SUV에는 TOYOTA엔진 사용 불가\n";
        return;
    }
    if (truckAndWIA())
    {
        std::cout<<"자동차 부품 조합 테스트 결과 : FAIL\n";
        std::cout<<"Truck에는 WIA엔진 사용 불가\n";
        return;
    }
    if (truckAndMando())
    {
        std::cout<<"자동차 부품 조합 테스트 결과 : FAIL\n";
        std::cout<<"Truck에는 Mando제동장치 사용 불가\n";
        return;
    }
    if (stack[BrakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
        return;
    }
    std::cout<<"자동차 부품 조합 테스트 결과 : PASS\n";
}