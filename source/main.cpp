// c std
#include<cstddef>//::std::size_t
#include<cstdint>//::std::uint32_t
#include<ctime>//::std::time_t,::std::strftime,::std::localtime
#include<cstdio>//::std::printf
// cpp std
#include<utility>//::std::forward
#include<string>//::std::string,::std::getline,::std::to_string
#include<chrono>//::std::chrono::system_clock
#include<random>//::std::random_device,::std::mt19937,
                //::std::uniform_int_distribution
#include<limits>//::std::numeric_limits
#include<iostream>//::std::cin
// mine
#include"result_info.hpp"//::result_info
#include"chinese_characters.hpp"//::chinese_characters

::std::string time_string(void){
    ::std::time_t time=::std::chrono::system_clock::to_time_t(
        ::std::chrono::system_clock::now()
    );
    char time_cstr[15]={};
    ::std::strftime(
        time_cstr,sizeof(time_cstr),"%Y%m%d%H%M%S",
        ::std::localtime(&time)
    );
    return time_cstr;
}
//[begin,end)
template<typename _Type>
_Type random_value(
    _Type&& begin
    ,_Type&& end=::std::numeric_limits<_Type>::max()
){
    ::std::random_device rd={};
    ::std::mt19937 gen(rd());
    ::std::uniform_int_distribution<_Type> dist(
        ::std::forward<_Type>(begin),
        ::std::forward<_Type>(end)
    );
    return dist(gen);
}
unsigned long long char_sum(::std::string const& number){
    unsigned long long result=0;
    for(char ch:number){
        result+=static_cast<unsigned long long>(ch-'0');
    }
    return result;
}
template<typename _Type,::std::size_t _n>
consteval ::std::size_t array_size(_Type(&array_ref)[_n]){
    return _n;
}
::std::uint32_t random_chinese_character(void){
    return ::chinese_characters[
        ::random_value<::std::size_t>(0,::array_size(chinese_characters))
    ];
}
void utf32_to_utf8(::std::uint32_t utf32,char*utf8){
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
int main(void){
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
    ::std::string random_val=::std::to_string(::random_value(0ull));
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
    ::std::uint32_t utf32=0;
    char utf8[5]={};
    ::std::printf("神谕:\n");
    for(::std::size_t line=0;line<4;++line){
        ::std::printf("    ");
        for(::std::size_t count=0;count<5;++count){
            utf32=random_chinese_character();
            ::utf32_to_utf8(utf32,utf8);
            ::std::printf("%s",utf8);
        }
        ::std::printf("%c\n",(line+1)%2!=0?',':'.');
    }
    return 0;
}
