#include<cstddef>//::size_t
#include<cstdint>//::uint32_t
#include<ctime>//::std::time_t,::std::strftime,::std::localtime
#include<cstdio>//::std::printf
#include<string>//::std::string,::std::getline,::std::to_string
#include<chrono>//::std::chrono::system_clock
#include<random>//::std::random_device,::std::mt19937,
                //::std::uniform_int_distribution
#include<limits>//::std::numeric_limits
#include<iostream>//::std::cin,::std::cout
#include<utility>//forward
#include"result_info.hpp"//::result_info
#include"chinese_characters.h"//::chinese_characters

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
    unsigned long long number_sum=0;
    bool continue_flag=true;
    ::std::string number_val="";
    auto const input_error=[&continue_flag](void)->void{
        ::std::printf("Input error!\n");
        continue_flag=true;
    };
    while(continue_flag){
        ::std::printf("Input number(unsigned integer) with enter:");
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
    ::std::string time_val=::time_string();
    unsigned long long time_len=time_val.length();
    unsigned long long time_sum=::char_sum(time_val);
    ::std::string random_val=::random_string();
    unsigned long long random_len=random_val.length();
    unsigned long long random_sum=::char_sum(random_val);
    unsigned long long total_sum=time_sum+random_sum+number_sum;
    unsigned long long total_len=time_len+random_len+number_len;
    unsigned long long result=(total_sum-(total_len-1))%6;
    ::std::printf(
        "time\t:val=%s,sum=%llu,len=%llu\n"
        "random\t:val=%s,sum=%llu,len=%llu\n"
        "number\t:val=%s,sum=%llu,len=%llu\n"
        "total_sum=time_sum+random_sum+number_sum=%llu\n"
        "total_len=time_len+random_len+number_len=%llu\n"
        "result=(total_sum-(total_len-1))%%6=%llu\n"
        "%s\n"
        ,time_val.c_str(),time_sum,time_len
        ,random_val.c_str(),random_sum,random_len
        ,number_val.c_str(),number_sum,number_len
        ,total_sum,total_len,result
        ,::std::string{::result_info[result]}.c_str()
    );
}
static void utf32_to_utf8(uint32_t utf32,char*utf8)noexcept{
    if(utf32<=0x7F){
        //U+0000 to U+007F
        *utf8=(char)utf32;
        *++utf8='\0';
    }else if(utf32<=0x7FF){
        //U+0080 to U+07FF
        *utf8=0xC0|(utf32>>6);
        *++utf8=0x80|(utf32&0x3F);
        *++utf8='\0';
    }else if(utf32<=0xFFFF){
        //U+0800 to U+FFFF
        *utf8=0xE0|(utf32>>12);
        *++utf8=0x80|((utf32>>6)&0x3F);
        *++utf8=0x80|(utf32&0x3F);
        *++utf8='\0';
    }else if(utf32<=0x10FFFF){
        //U+10000 to U+10FFFF
        *utf8=0xF0|(utf32>>18);
        *++utf8=0x80|((utf32>>12)&0x3F);
        *++utf8=0x80|((utf32>>6)&0x3F);
        *++utf8=0x80|(utf32&0x3F);
        *++utf8='\0';
    }
}
template<typename _Type,size_t _n>
static consteval size_t array_size(_Type(&array_ref)[_n])noexcept{
    return _n;
}
//[begin,end)
template<typename _Type>
static _Type random_value(_Type&& begin,_Type&& end)noexcept{
    ::std::random_device rd;//创建一个随机设备对象
    ::std::mt19937 gen(rd());//使用随机设备对象作为随机数生成器的种子
    ::std::uniform_int_distribution<_Type> dist(
        ::std::forward<_Type>(begin),
        ::std::forward<_Type>(end)
    );//设置随机数的范围
    return dist(gen);//生成随机数
}
static uint32_t random_chinese_character()noexcept{
    return ::chinese_characters[
        ::random_value<size_t>(0,::array_size(chinese_characters))
    ];
}
static void god_sentences()noexcept{
    uint32_t utf32=0;
    char utf8[5];
    ::std::cout<<"神谕:\n";
    for(size_t line=0;line<4;++line){
        ::std::cout<<"    ";
        for(size_t count=0;count<5;++count){
            utf32=random_chinese_character();
            ::utf32_to_utf8(utf32,utf8);
            ::std::cout<<utf8;
        }
        ::std::cout<<((line+1)%2!=0?',':'.')<<'\n';
    }
}
int main(void)noexcept{
    ::small_six_god();
    ::god_sentences();
    return 0;
}
