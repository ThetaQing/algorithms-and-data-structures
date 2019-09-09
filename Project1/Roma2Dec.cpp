// 时间20ms，内存8.4m
class Solution {
public:
    int romanToInt(string s) {
        int result = 0;
        int length = s.size();
        for(auto i=0; i<length;++i)
        {
            switch (s[i])
            {
                case'M':result += 1000; break;
                case'D':result += 500; break;
                case'C':
                    if(s[i+1] == 'D')
                    {result += 400;i += 1;break;}
                    else if(s[i+1] == 'M')
                    {result += 900;i += 1;break;}
                    else
                    {result += 100; break;}
                case 'L':result += 50;break;
                case 'X':
                    if(s[i+1] == 'L')
                    {result += 40;i += 1;break;}
                    else if(s[i+1] == 'C')
                    {result += 90;i += 1;break;}
                    else
                    {result += 10; break;}
                case 'V':result += 5;break;
                case 'I':
                    if(s[i+1] == 'V')
                    {result += 4;i += 1;break;}
                    else if(s[i+1] == 'X')
                    {result += 9;i += 1;break;}
                    else
                    {result += 1; break;}
            }          
                                  
        }
        return result;
        
    }
};
