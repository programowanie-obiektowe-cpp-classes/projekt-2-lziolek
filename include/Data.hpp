#include<print>
#include<vector>
#include<algorithm>
#include<format>
#include<ranges>
#include<string>
#include<stdexcept>
#include<cmath>
#include<iostream>

class Data
{
    public:
    Data(int r,int m, int d):r_{r},m_{m},d_{d}
    {
        if(m<1 || m>12) throw std::out_of_range("Niepoprawny miesiac (1-12)");
        if(d<1 || d>dniMsc(m,r)) throw std::out_of_range("Niepoprawny dzien dla podanego miesiaca i roku");
    }
    ~Data() =default;

    std::string formatISO() const
    {
        return std::format("{}-{:02}-{:02}",r_,m_,d_);
    };
    std::string formatEU() const
    {
        return std::format("{:02}.{:02}.{}",d_,m_,r_);
    };
    std::string formatUS() const
    {
        return std::format("{:02}/{:02}/{}",m_,d_,r_);
    };

    void przesunDni(int n) 
    {
        d_ += n;
        while (d_ > dniMsc(m_,r_)) 
        {
            d_ -= dniMsc(m_,r_);
            if (++m_ > 12) 
            { 
                m_ = 1; 
                ++r_; 
            }
        }
        while (d_ <1) 
        {
            --m_;
            if(m_<1)
            {
                m_+=12;
                --r_;
            }
            d_+= dniMsc(m_,r_); 
        }
    }
    void przesunMsc(int n) 
    {
        m_ += n;
        while (m_ > 12) 
        { 
            m_ -= 12; 
            ++r_; 
        }
        while(m_<1)
        {
            m_+=12;
            --r_;
        }
        d_ = std::min(d_, dniMsc(m_, r_));
    }
    void przesunLata(int n) 
    {
        r_ += n;
        d_ = std::min(d_, dniMsc(m_, r_));
    }

    int roznicaDni(const Data& a) const
        {
            int dr=0;
            if(a.r_<r_)
            {
                for(int i=a.r_; i<r_; ++i)
                {
                    dr+= czyPrzestepny(i) ? 366:365;
                }
            }
            if(a.r_>r_)
            {
                for(int i=r_; i<a.r_; ++i)
                {
                    dr-= czyPrzestepny(i) ? 366:365;
                }
            }
            return std::abs(policzDni()-a.policzDni()+dr);
        }
    std::vector<int> roznicaDat(const Data& a) const
    {
        const Data& starsza=(*this < a) ? *this : a;
        const Data& nowsza =(*this < a) ? a : *this;
        int lm=0, lr=0;
        int ld=nowsza.d_-starsza.d_;
        if (ld < 0)
        {
            if(nowsza.m_==1)
            {
                ld += dniMsc(12, nowsza.r_-1);
            }
            else ld+=dniMsc(nowsza.m_-1, nowsza.r_);
            lm = -1;
        }
        lm+=nowsza.m_-starsza.m_;
        if (lm < 0)
        {
            lm += 12;
            lr = -1;
        }
        lr+=nowsza.r_-starsza.r_;

        return {lr,lm,ld};
    }

    std::string dzienTygodnia() const
    {
        Data d0{2000,01,03}; //poniedziałek
        int a=roznicaDni(d0)%7;
        if(*this<d0 && a!=0)
        {
            a=7-a;
        }
        static const std::vector<std::string> dt
        {"poniedziałek","wtorek","środa","czwartek","piątek","sobota","niedziela"};
        return dt.at(a);
    }
    
    bool dzienSwiateczny() const 
    {
        static const std::vector<std::pair<int,int>> sw
        {
            {1,1},{6,1},{1,5},{3,5},{15,8},{1,11},{24,12},{25,12},{26,12}
        };
        return std::ranges::contains(sw, std::pair{d_, m_});
    }
  
      bool operator<(const Data& a) const
    {
    if (r_ != a.r_) return r_ < a.r_;
    if (m_ != a.m_) return m_ < a.m_;
    return d_ < a.d_;
    }

    private:
    int r_,m_,d_;

    static bool czyPrzestepny(int r) 
    {
        return (r%4 == 0 && r%100 !=0) || (r%400 == 0);
    }
   
    static int dniMsc (int m, int r) 
    {
        static const std::vector<int> dm{31,28,31,30,31,30,31,31,30,31,30,31};
        if (m == 2 && czyPrzestepny(r))
        { return 29; }
        else return dm.at(m-1);
    }
    
    int policzDni() const
    {
        int sd=0;
        for (int i=1; i<m_; ++i)
        {
            sd+=dniMsc(i,r_);
        }
        return sd+d_;
    }

};

Data utworzDate ()
    {
        int r, m, d;
        std::cout <<"Podaj rok, miesiac, dzien (np. 2000 11 1):";
        std::cin >> r >> m >> d;
        return Data(r,m,d);
    }