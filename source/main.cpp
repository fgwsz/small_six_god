#include<string>//::std::getline ::std::stoull
#include<iostream>

unsigned long long read_ull(void){
    ::std::string unsigned_integer={""};
    unsigned long long result={0};
    bool flag={true};
    while(flag){
        flag=false;
        ::std::cout<<"Please input an unsigned integer: ";
        ::std::getline(::std::cin,unsigned_integer);
        try{
            result=::std::stoull(unsigned_integer);
        }catch(...){
            ::std::cout<<"Input error!";
            flag=true;
        }
    }
    return result;
}
unsigned long long char_count(unsigned long long number){
    unsigned long long result=::std::to_string(number).length();
    ::std::cout<<"char_count: "<<result<<'\n';
    return result;
}
unsigned long long char_sum(unsigned long long number){
    ::std::string string=::std::to_string(number);
    unsigned long long result={0};
    for(auto const& ch:string){
        result+=static_cast<unsigned long long>(ch-'0');
    }
    ::std::cout<<"char_sum: "<<result<<'\n';
    return result;
}
unsigned long long small_six_god(unsigned long long number){
    return (::char_sum(number)-(::char_count(number)-1))%6;
}
int main(int argc,char* argv[]){
    ::std::cout<<::small_six_god(::read_ull())<<'\n';
    return 0;
}
