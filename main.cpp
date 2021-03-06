#include "rccregisters.hpp"
#include "adc1registers.hpp"
#include "gpiocregisters.hpp"
#include "gpioaregisters.hpp"
#include <iostream>
#include <bitset>
#include "nvicregisters.hpp"
#include "adccommonregisters.hpp"
#include "usart2registers.hpp"
#include "tim2registers.hpp"

extern "C"
{
  int __low_level_init(void)
  {
    RCC::CR::HSEON::On::Set();
    while(!RCC::CR::HSERDY::Ready::IsSet())
    {
    }

    RCC::CFGR::SW::Hse::Set();
    while(!RCC::CFGR::SWS::Hse::IsSet())
    {
    }
    RCC::CR::HSION::Off::Set();
    
    RCC::AHB1ENR::GPIOAEN::Enable::Set();
    GPIOA::MODER::MODER0::Analog::Set();
    GPIOA::MODER::MODER3::Alternate::Set(); // TX
    GPIOA::MODER::MODER2::Alternate::Set(); //RX
    GPIOA::AFRL::AFRL2::Af7::Set(); // ??????? ??????????????? ?????
    GPIOA::AFRL::AFRL3::Af7::Set();
    GPIOA::OTYPER::OT2::OutputPushPull::Set();
    GPIOA::OTYPER::OT3::OutputPushPull::Set();
    GPIOA::PUPDR::PUPDR2::PullUp::Set();
    GPIOA::PUPDR::PUPDR3::PullUp::Set(); // ???? ? ???????
    
//    NVIC::ISER2::Write(1<<28); // ??????
//    TIM2::CR1::URS::OverflowEvent::Set();
//    RCC::APB1ENR::TIM2EN::Enable::Set();
//    TIM2::PSC::Set(7999U);
//    TIM2::ARR::Write(500);
//    TIM2::SR::UIF::NoInterruptPending::Set();
//    TIM2::CNT::Write(0U);
//    TIM2::DIER::UIE::Enable::Set();
//    TIM2::CR1::CEN::Enable::Set();
    
    RCC::APB2ENR::ADC1EN::Enable::Set();
    RCC::APB1ENR::USART2EN::Enable::Set(); // ?????????????
    
    USART2::CR1::M::Data8bits::Set(); // 8 ??? ?????
    USART2::CR1::PCE::ParityControlDisable::Set(); // ????????
    USART2::CR1::OVER8::OversamplingBy16::Set(); // ????????????? 1/16
    USART2::CR2::STOP::Value0::Set(); //1 ???? ???
    USART2::BRR::Write((8'000'000/(9600*8*2) << 4U)); //????????
    USART2::CR1::UE::Enable::Set(); //?????????
    USART2::CR1::TE::Enable::Set();
    
    
    ADC_Common::CCR::TSVREFE::Enable::Set();
    ADC1::CR1::RES::Bits12::Set();
    ADC1::CR1::SCAN::Enable::Set();
    ADC1::CR2::ADON::Enable::Set();
    
    ADC1::SQR3::SQ1::Channel18::Set();  
    ADC1::SQR3::SQ2::Channel17::Set();  
    ADC1::SQR3::SQ3::Channel0::Set(); 
    
    ADC1::CR2::CONT::SingleConversion::Set();
    ADC1::SQR1::L::Conversions3::Set();
    
    ADC1::CR2::EOCS::SingleConversion::Set();
    //ADC1::CR1::OVRIE::Enable::Set();
    
 
    return 1;
  }
}

int main()
{

  const auto Ts_Cal1 = static_cast<float> (*reinterpret_cast<uint16_t*>(0x1FFF7A2C));
  
  const auto Ts_Cal2 = static_cast<float> (*reinterpret_cast<uint16_t*>(0x1FFF7A2E)); 
  
  const auto Vref = static_cast<float> (*reinterpret_cast<uint16_t*>(0x1FFF7A2A));
  
  const char myString[] = "Hello, world! " ;
     
 
  for (;;)
  {
       
    //ADC1::SR::OVR::NoOverrun::Set();
    //ADC1::SR::STRT::Started::Set();
    
/*
    ADC1::CR2::SWSTART::On::Set(); 
    while(!ADC1::SR::EOC::ConversionComplete::IsSet())
    {
    }
    
    uint32_t Temp_Data = ADC1::DR::DATA::Get();
    while(!ADC1::SR::EOC::ConversionComplete::IsSet())
    {
    }
    
    uint32_t Vref_Data = ADC1::DR::DATA::Get();
    while(!ADC1::SR::EOC::ConversionComplete::IsSet())
    {
    }
    
    uint32_t Res_Data = ADC1::DR::DATA::Get();
    
    float Temp =((Temp_Data - Ts_Cal1)*(110.0f-30.0f) + 30.0f*(Ts_Cal2 - Ts_Cal1)) / (Ts_Cal2 - Ts_Cal1);
    float k = Vref / Vref_Data;
    float Voltage = (Res_Data * 3.3 / 4096.0) * k;
    

    std::cout << "???????????: " << Temp*k << " ?" << std::endl;
    std::cout << "??????? ??????????: " << Vref_Data << std::endl;
    std::cout << "?????????? " << Voltage << " V" << std::endl;
    std::cout << "_________________________________" << std::endl;
for(int i=0; i<strlen(myString); i++)
    {
      USART2::DR::Write(myString[i]);
      while(USART2::SR::TXE::DataRegisterNotEmpty::IsSet())
      {
      }
    }
    */
    USART2::DR::Write('A');
  }
  return 0;
}
