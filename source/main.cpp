#include<ctime>//::std::time_t,::std::strftime,::std::localtime
#include<string>//::std::string,::std::getline,::std::to_string
#include<chrono>//::std::chrono::system_clock
#include<random>//::std::random_device,::std::mt19937,
                //::std::uniform_int_distribution
#include<limits>//::std::numeric_limits
#include<iostream>//::std::cout
#include"result_info.hpp"//::result_info

::std::string time_string(void)noexcept{
    ::std::time_t time=::std::chrono::system_clock::to_time_t(
        ::std::chrono::system_clock::now()
    );
    char time_cstr[15];
    ::std::strftime(
        time_cstr,sizeof(time_cstr),"%Y%m%d%H%M%S",
        ::std::localtime(&time)
    );
    return ::std::string{time_cstr};
}
::std::string random_string(void)noexcept{
    ::std::random_device rd={};
    ::std::mt19937 gen(rd());
    unsigned long long ret=::std::uniform_int_distribution<unsigned long long>
        (0,::std::numeric_limits<unsigned long long>::max())(gen);
    return ::std::to_string(ret);
}
unsigned long long char_sum(::std::string const& number)noexcept{
    unsigned long long result=0;
    for(char ch:number){
        result+=static_cast<unsigned long long>(ch-'0');
    }
    return result;
}
void small_six_god(void)noexcept{
    ::std::string time_val=::time_string();
    unsigned long long time_len=time_val.length();
    unsigned long long time_sum=::char_sum(time_val);
    ::std::cout
        <<"time_val:"<<time_val<<'\n'
        <<"time_len:"<<time_len<<'\n'
        <<"time_sum:"<<time_sum<<'\n'
    ;
    ::std::string random_val=::random_string();
    unsigned long long random_len=random_val.length();
    unsigned long long random_sum=::char_sum(random_val);
    ::std::cout
        <<"random_val:"<<random_val<<'\n'
        <<"random_len:"<<random_len<<'\n'
        <<"random_sum:"<<random_sum<<'\n'
    ;
    unsigned long long number_sum=0;
    bool continue_flag=true;
    ::std::string number_val="";
    auto const input_error=[&continue_flag](void)->void{
        ::std::cout<<"Input error!\n";
        continue_flag=true;
    };
    while(continue_flag){
        ::std::cout<<"Input number(unsigned integer) with enter:";
        ::std::getline(::std::cin,number_val);
        if(number_val.length()==0){
            input_error();
            continue;
        }
        continue_flag=false;
        number_sum=0;
        for(char ch:number_val){
            if(ch>='0'&&ch<='9'){
                number_sum+=static_cast<unsigned long long>(ch-'0');
            }else{
                input_error();
                break;
            }
        }
    }
    unsigned long long number_len=number_val.length();
    ::std::cout
        <<"number_val:"<<number_val<<'\n'
        <<"number_len:"<<number_len<<'\n'
        <<"number_sum:"<<number_sum<<'\n'
    ;
    unsigned long long total_sum=time_sum+random_sum+number_sum;
    unsigned long long total_len=time_len+random_len+number_len;
    unsigned long long result=(total_sum-(total_len-1))%6;
    ::std::cout
        <<"total_len=(time_len+random_len+number_len)="<<total_len<<'\n'
        <<"total_sum=(time_summ+random_sum+number_sum)="<<total_sum<<'\n'
        <<"result=(total_sum-(total_len-1))%6="<<result<<'\n'
        <<::result_info[result]<<'\n'
    ;
}
int main(void)noexcept{
    ::small_six_god();
    return 0;
}
