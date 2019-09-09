// 时间8.1ms，内存8.2m
class Solution {
public:
    bool isPalindrome(int x) {   
          
        if(x<0)
            return false;
        else if(x==0)
            return true;
        else
        {
            int input_x = x;
            long int y=0;
             for(;x;y = y*10+x%10, x/=10);
              
             if(y == input_x)
                 return true;
             else
                 return false;

              
        
        }
        return false;
    }  
    
};

// 时间16ms，内存8.1m
// 主要思想是存储在另一个变量中，返回这两个数是否相等即可
class Solution {
public:
    bool isPalindrome(int x) {       
        
       int temp=0;
        long int y=0;  // 注意这里的长度，如果只是int会导致溢出
        int input_x = x;
        if(x<0)
            return false;
        else if(x==0)
            return true;
        
        while(x)
        {
            temp = x%10;            
            x = x/10;
            y = y*10 + temp;
        }
        return y==input_x;
        
    }
};

//  花费时间44ms
// 主要思想是一位一位地比较
class Solution {
public:
    bool isPalindrome(int x) {
        vector<int> vet;
        int temp;
        if(x<0)
            return false;
        else if(x==0)
            return true;
        
        while(x)
        {
            temp = x%10;
            vet.push_back(temp);
            x = x/10;
        }
        temp = vet.size();
        for(auto i=0; i<= temp/2; ++i)
        {
            if(vet[i] != vet[temp-1-i])
                return false;
        }
        return true;
        
    }
};

